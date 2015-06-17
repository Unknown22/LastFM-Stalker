#pragma once
#include "LastFM.h"
#include <msclr\marshal_cppstd.h>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <process.h>
#include <cstdio>

LastFM strona;


DWORD WINAPI odswiezanie(__in LPVOID lpParameter)
{
	while (true)
	{
		strona.glowny();
		System::Threading::Thread::Sleep(5000);
	}
	return 0;
}

namespace LastFMStalker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  nazwa_uzytkownika_textbox;
	private: System::Windows::Forms::Button^  button_zatwierdzanie_nazwy_uzytkownika;
	private: System::Windows::Forms::Label^  label_pelny_adres_lastfm;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label_aktualizacja;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->nazwa_uzytkownika_textbox = (gcnew System::Windows::Forms::TextBox());
			this->button_zatwierdzanie_nazwy_uzytkownika = (gcnew System::Windows::Forms::Button());
			this->label_pelny_adres_lastfm = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label_aktualizacja = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(174, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Podaj nazwê u¿ytkownika LastFM: ";
			// 
			// nazwa_uzytkownika_textbox
			// 
			this->nazwa_uzytkownika_textbox->Location = System::Drawing::Point(16, 29);
			this->nazwa_uzytkownika_textbox->Name = L"nazwa_uzytkownika_textbox";
			this->nazwa_uzytkownika_textbox->Size = System::Drawing::Size(100, 20);
			this->nazwa_uzytkownika_textbox->TabIndex = 1;
			// 
			// button_zatwierdzanie_nazwy_uzytkownika
			// 
			this->button_zatwierdzanie_nazwy_uzytkownika->Location = System::Drawing::Point(123, 29);
			this->button_zatwierdzanie_nazwy_uzytkownika->Name = L"button_zatwierdzanie_nazwy_uzytkownika";
			this->button_zatwierdzanie_nazwy_uzytkownika->Size = System::Drawing::Size(32, 23);
			this->button_zatwierdzanie_nazwy_uzytkownika->TabIndex = 2;
			this->button_zatwierdzanie_nazwy_uzytkownika->Text = L"OK";
			this->button_zatwierdzanie_nazwy_uzytkownika->UseVisualStyleBackColor = true;
			this->button_zatwierdzanie_nazwy_uzytkownika->Click += gcnew System::EventHandler(this, &MyForm::button_zatwierdzanie_nazwy_uzytkownika_Click);
			// 
			// label_pelny_adres_lastfm
			// 
			this->label_pelny_adres_lastfm->AutoSize = true;
			this->label_pelny_adres_lastfm->Location = System::Drawing::Point(16, 56);
			this->label_pelny_adres_lastfm->Name = L"label_pelny_adres_lastfm";
			this->label_pelny_adres_lastfm->Size = System::Drawing::Size(0, 13);
			this->label_pelny_adres_lastfm->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 79);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Ostatnia aktualizacja: ";
			// 
			// label_aktualizacja
			// 
			this->label_aktualizacja->AutoSize = true;
			this->label_aktualizacja->Location = System::Drawing::Point(120, 79);
			this->label_aktualizacja->Name = L"label_aktualizacja";
			this->label_aktualizacja->Size = System::Drawing::Size(0, 13);
			this->label_aktualizacja->TabIndex = 5;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->label_aktualizacja);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label_pelny_adres_lastfm);
			this->Controls->Add(this->button_zatwierdzanie_nazwy_uzytkownika);
			this->Controls->Add(this->nazwa_uzytkownika_textbox);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"LastFM Stalker";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button_zatwierdzanie_nazwy_uzytkownika_Click(System::Object^  sender, System::EventArgs^  e) {

				 label_pelny_adres_lastfm->Text = "";

				 string adres = "www.last.fm";
				 string adres_zrodla = "/user/";
				 string uzytkownik;
				 string pelny_adres;

				 HANDLE odswiez, odswiez_aktualizacje;



				 System::String^ nazwa_uzytkownik_konwersja_na_string = nazwa_uzytkownika_textbox->Text;
				 std::string nazwa_uzytkownika = msclr::interop::marshal_as<std::string>(nazwa_uzytkownik_konwersja_na_string);

				 adres_zrodla = adres_zrodla + nazwa_uzytkownika;
				 pelny_adres = adres + adres_zrodla;
				 String^ pelny_adres_po_konwersji = gcnew String(pelny_adres.c_str());

				 label_pelny_adres_lastfm->Text = pelny_adres_po_konwersji;


				 string przyrostek = ".txt";
				 string nazwa_bazy = nazwa_uzytkownika + przyrostek;
				 transform(nazwa_bazy.begin(), nazwa_bazy.end(), nazwa_bazy.begin(), ::tolower);

				 strona = { adres, adres_zrodla, nazwa_bazy };

				 strona.wczytaj_slownik();
				 
				 odswiez = CreateThread(0, 0, odswiezanie, 0, 0, 0);
	}
	};
}