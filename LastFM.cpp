#pragma once

#include "LastFM.h"
#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace System::Threading;

LastFM::LastFM()
{
	index = 0;
}

LastFM::LastFM(string adres, string adres_zrodla, string baza, string adres_slownika)
{
	adres_ = adres;
	adres_zrodla_ = adres_zrodla;
	path = "strona.txt";
	database = baza;
	path_slownik = adres_slownika;
}

LastFM::~LastFM()
{
}

void LastFM::odczytaj_zrodlo_strony()
{

	HINTERNET hInternet = InternetOpenA("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	HINTERNET hConnection = InternetConnectA(hInternet, adres_.c_str(), 80, " ", " ", INTERNET_SERVICE_HTTP, 0, 0);

	HINTERNET hData = HttpOpenRequestA(hConnection, "GET", adres_zrodla_.c_str(), NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0);

	char buf[2048];

	HttpSendRequestA(hData, NULL, 0, NULL, 0);

	DWORD bytesRead = 0;
	DWORD totalBytesRead = 0;

	while (InternetReadFile(hData, buf, 2000, &bytesRead) && bytesRead != 0)
	{
		buf[bytesRead] = 0; // insert the null terminator.
		zrodlo_strony_cale = zrodlo_strony_cale + buf;
	}




	//-----WYSWIETLANIE DATY I GODZINY AKTUALIZACJI

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	//std::cout << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");

	stringstream buffer;
	buffer << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
	ostatnia_aktualizacja = buffer.str();

	//-----KONIEC WYSWIETLANIA DATY I GODZINY AKTUALIZACJI


	InternetCloseHandle(hData);
	InternetCloseHandle(hConnection);
	InternetCloseHandle(hInternet);
}

void LastFM::zapisz_zrodlo_do_pliku()
{
	ofstream fout;
	fout.open(path, ios_base::out | ios_base::trunc);
	fout << zrodlo_strony_cale;
}

void LastFM::szukaj_piosenek()
{
	liczba_znalezionych_nowych_piosenek = 0;
	string szukanaFraza = "<td class=\"subjectCell \">";
	string szukanaFrazaObecnieSluchane = "<td class=\"subjectCell highlight\">";
	string fraza_przed_nazwa_zespolu = "\">";
	string fraza_przed_tytulem = "\" >";
	size_t pozycja_za_wykonawca;
	size_t znalezionaPozycja = 0;

	//---szukanie obecnie odtwarzanego
	znalezionaPozycja = zrodlo_strony_cale.find(szukanaFrazaObecnieSluchane);
	if (znalezionaPozycja != std::string::npos)
	{
		status_online = 1;
		znalezionaPozycja = zrodlo_strony_cale.find(fraza_przed_nazwa_zespolu, znalezionaPozycja + szukanaFrazaObecnieSluchane.size());

		//przekazywanie do funkcji pozycji od ktorej zaczyna sie nazwa zespolu
		pozycja_za_wykonawca = znajdz_wykonawce(znalezionaPozycja + fraza_przed_nazwa_zespolu.size());
		znalezionaPozycja = zrodlo_strony_cale.find(fraza_przed_tytulem, pozycja_za_wykonawca);
		znalezionaPozycja = znajdz_tytul(znalezionaPozycja + fraza_przed_tytulem.size());
		liczba_znalezionych_nowych_piosenek++;

		//if (czy_jest_w_bazie())
		//{
		//	zapisz_element();
		//	//zapisz_tytul();
		//}
		//nazwa_klucza.clear();


		//std::cout << "Fraza zostala odnaleziona na pozycji " << znalezionaPozycja << std::endl;
		znalezionaPozycja = zrodlo_strony_cale.find(szukanaFraza, znalezionaPozycja + szukanaFraza.size());
	}
	else
	{
		status_online = 0;
	}

	//--KONIEC szukania obecnie odtwarzanego


	//---szukanie ostatnio słuchanych
	znalezionaPozycja = zrodlo_strony_cale.find(szukanaFraza);
	if (znalezionaPozycja == std::string::npos)
	{
		std::cout << "Wystapil jakis problem. Sprawdz jeszcze raz czy poprawnie wpisales nazwe uzytkownika" << std::endl;
		return;
	}

	do
	{
		znalezionaPozycja = zrodlo_strony_cale.find(fraza_przed_nazwa_zespolu, znalezionaPozycja + szukanaFraza.size());

		//przekazywanie do funkcji pozycji od ktorej zaczyna sie nazwa zespolu
		pozycja_za_wykonawca = znajdz_wykonawce(znalezionaPozycja + fraza_przed_nazwa_zespolu.size());
		znalezionaPozycja = zrodlo_strony_cale.find(fraza_przed_tytulem, pozycja_za_wykonawca);
		znalezionaPozycja = znajdz_tytul(znalezionaPozycja + fraza_przed_tytulem.size());
		liczba_znalezionych_nowych_piosenek++;

		//if (czy_jest_w_bazie())
		//{
		//	zapisz_element();
		//	//zapisz_tytul();
		//}
		//nazwa_klucza.clear();


		//std::cout << "Fraza zostala odnaleziona na pozycji " << znalezionaPozycja << std::endl;
		znalezionaPozycja = zrodlo_strony_cale.find(szukanaFraza, znalezionaPozycja + szukanaFraza.size());
	} while (znalezionaPozycja != std::string::npos);
	//---KONIEC szukania ostatnio sluchanych
	liczba_znalezionych_nowych_piosenek--;
	for (liczba_znalezionych_nowych_piosenek; liczba_znalezionych_nowych_piosenek >= 0; liczba_znalezionych_nowych_piosenek--)
	{
		if (czy_jest_w_bazie(liczba_znalezionych_nowych_piosenek))
		{
			zapisz_element(liczba_znalezionych_nowych_piosenek);
		}
		nazwa_klucza[liczba_znalezionych_nowych_piosenek].clear();
	}

	zrodlo_strony_cale.clear();
}

size_t LastFM::znajdz_wykonawce(size_t pozycja)
{
	ifstream fin;
	fin.open(path, ios_base::in);

	string szukanaFraza = "</a>";
	size_t znalezionaPozycja = zrodlo_strony_cale.find(szukanaFraza, pozycja);

	dlugosc_nazwy_zespolu = znalezionaPozycja - pozycja;
	//cout << "Dl: " << dlugosc_nazwy_zespolu << endl;

	nazwa_zespolu = new char[dlugosc_nazwy_zespolu];

	int i = 0;
	while (zrodlo_strony_cale[pozycja] != '<')
	{
		nazwa_zespolu[i] = zrodlo_strony_cale[pozycja];
		nazwa_klucza[liczba_znalezionych_nowych_piosenek] = nazwa_klucza[liczba_znalezionych_nowych_piosenek] + nazwa_zespolu[i];
		i++;
		pozycja++;
	}
	return pozycja;
}

void LastFM::zapisz_element(int indeks)
{
	//int j = 0;
	/*
	while (j < dlugosc_nazwy_zespolu)
	{
	cout << nazwa_zespolu[j];
	j++;
	}
	cout << " - ";
	*/

	ofstream fout;
	fout.open(database, ios_base::out | ios_base::app);
	
	/*
	j = 0;
	while (j < dlugosc_nazwy_zespolu)
	{*/
	fout << nazwa_klucza[indeks];
	fout << endl;
	//j++;
	//}
	//fout << " - ";

}

size_t LastFM::znajdz_tytul(size_t pozycja)
{

	ifstream fin;
	fin.open(path, ios_base::in);

	string szukanaFraza = "</a>";
	size_t znalezionaPozycja = zrodlo_strony_cale.find(szukanaFraza, pozycja);

	dlugosc_tytulu = znalezionaPozycja - pozycja;
	//cout << "Dl: " << dlugosc_nazwy_zespolu << endl;

	tytul = new char[dlugosc_tytulu];
	string separator = " - ";
	nazwa_klucza[liczba_znalezionych_nowych_piosenek] = nazwa_klucza[liczba_znalezionych_nowych_piosenek] + separator;

	int i = 0;
	while (zrodlo_strony_cale[pozycja] != '<')
	{
		tytul[i] = zrodlo_strony_cale[pozycja];
		nazwa_klucza[liczba_znalezionych_nowych_piosenek] = nazwa_klucza[liczba_znalezionych_nowych_piosenek] + tytul[i];
		i++;
		pozycja++;
	}

	return pozycja;
}

//void LastFM::zapisz_tytul()
//{
//
//	//int j = 0;
//	/*
//	while (j < dlugosc_tytulu)
//	{
//	cout << tytul[j];
//	j++;
//	}
//	cout << endl;
//	*/
//	ofstream fout;
//	fout.open(database, ios_base::out | ios_base::app);
//
//	//while (j < dlugosc_tytulu)
//	//{
//	fout << baza[nazwa_klucza];
//		//j++;
//	//}
//	fout << endl;
//
//}

bool LastFM::czy_jest_w_bazie(int indeks_piosenki)
{
	if (baza.count(nazwa_klucza[indeks_piosenki]) == 0)
	{
		baza[nazwa_klucza[indeks_piosenki]] = 0;
		kolejnosc_wpisywania_do_bazy[index++] = nazwa_klucza[indeks_piosenki];
		//cout << nazwa_klucza << endl;
		return TRUE;
	}
	else
		return FALSE;
}

void LastFM::zapisz_slownik()
{
	ofstream fout;
	fout.open(path_slownik, ios_base::out | ios_base::trunc);
	int licznik = 0;
	for (auto i : kolejnosc_wpisywania_do_bazy)
	{
		fout << i.second << endl
			<< baza[i.second];
		licznik++;
		if (licznik < baza.size())
		{
			fout << endl;
		}
	}
	fout.close();
}

void LastFM::wczytaj_slownik()
{
	ifstream slownik;
	string linia1;
	string linia2;
	int status;
	index = 0;
	slownik.open(path_slownik, ios_base::in);
	if (slownik.good() == true)
	{
		while (!slownik.eof())
		{
			getline(slownik, linia1);
			getline(slownik, linia2);
			if (linia2 == "0")
				status = 0;
			else if (linia2 == "1")
				status = 1;
			else if (linia2 == "2")
				status = 2;
			baza[linia1] = status;
			kolejnosc_wpisywania_do_bazy[index++] = linia1;
			//cout << linia << endl; //wyświetlenie linii
		}
	}
	else
	{

	}
	slownik.close();
}

int LastFM::glowny()
{
	status_aktualizacji = 0;
	odczytaj_zrodlo_strony();
	//zapisz_zrodlo_do_pliku();
	szukaj_piosenek();
	zapisz_slownik();
	status_aktualizacji = 1;
	return status_aktualizacji;
	//Thread::Sleep(5000);
}