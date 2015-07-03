#pragma once

#include <string>
#include <map>

using namespace std;

class LastFM
{
private:
	//zmienne
	string adres_;
	string adres_zrodla_;
	string zrodlo_strony_cale;
	string path;
	string database;
	string nazwa_klucza [10];
	string klucz_do_przetworzenia;

	int liczba_znalezionych_nowych_piosenek;

	size_t dlugosc_nazwy_zespolu;
	size_t dlugosc_tytulu;

	char* nazwa_zespolu;
	char* tytul;

	//metody
	size_t znajdz_wykonawce(size_t pozycja);
	size_t znajdz_tytul(size_t pozycja);
	void zapisz_element(int indeks);
	//void zapisz_tytul();
	bool czy_jest_w_bazie(int indeks_piosenki);
	int status_aktualizacji;

public:
	int index;
	int status_online;
	map<string, int> baza;
	map<int, string> kolejnosc_wpisywania_do_bazy;
	string path_slownik;
	string ostatnia_aktualizacja;
	LastFM();
	LastFM(string adres, string adres_zrodla, string baza, string adres_slownika);
	~LastFM();
	void odczytaj_zrodlo_strony();
	void zapisz_zrodlo_do_pliku();
	void szukaj_piosenek();
	void zapisz_slownik();
	void wczytaj_slownik();
	int glowny();
};

