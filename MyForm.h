#pragma once
#include "LastFM.h"
#include <msclr\marshal_cppstd.h>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <process.h>
#include <cstdio>

LastFM strona;

delegate void ZmianaLabela();
public ref class Odswiezanie_Daty_Godziny
{
public: static ZmianaLabela^ odswiez_label;
};


delegate void odswiezanie_list();
public ref class Odswiezanie_List
{
public: static odswiezanie_list^ odswiez_listy;
};

DWORD WINAPI odswiezanie(__in LPVOID lpParameter)
{
	while (true)
	{
		strona.glowny();
		Odswiezanie_List::odswiez_listy->Invoke();
		Odswiezanie_Daty_Godziny::odswiez_label->Invoke();
		System::Threading::Thread::Sleep(180000);
	}
	return 0;
}

DWORD WINAPI odswiezanie_list_w_tab(__in LPVOID lpParameter)
{
	while (true)
	{
		Odswiezanie_List::odswiez_listy->Invoke();
		System::Threading::Thread::Sleep(180000);
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
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tab_nie_pobrane;
	private: System::Windows::Forms::TabPage^  tab_pobrane;
	private: System::Windows::Forms::TabPage^  tab_sprawdzone;
	private: System::Windows::Forms::ListBox^  listbox_nie_pobrane;
	private: System::Windows::Forms::ListBox^  listbox_pobrane;
	private: System::Windows::Forms::ListBox^  listbox_sprawdzone;
	private: System::Windows::Forms::RadioButton^  radio_button_nie_pobrane;
	private: System::Windows::Forms::RadioButton^  radio_button_pobrane;
	private: System::Windows::Forms::RadioButton^  radio_button_sprawdzone;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox_zaznaczone;




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
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tab_nie_pobrane = (gcnew System::Windows::Forms::TabPage());
			this->listbox_nie_pobrane = (gcnew System::Windows::Forms::ListBox());
			this->tab_pobrane = (gcnew System::Windows::Forms::TabPage());
			this->listbox_pobrane = (gcnew System::Windows::Forms::ListBox());
			this->tab_sprawdzone = (gcnew System::Windows::Forms::TabPage());
			this->listbox_sprawdzone = (gcnew System::Windows::Forms::ListBox());
			this->radio_button_nie_pobrane = (gcnew System::Windows::Forms::RadioButton());
			this->radio_button_pobrane = (gcnew System::Windows::Forms::RadioButton());
			this->radio_button_sprawdzone = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox_zaznaczone = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1->SuspendLayout();
			this->tab_nie_pobrane->SuspendLayout();
			this->tab_pobrane->SuspendLayout();
			this->tab_sprawdzone->SuspendLayout();
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
			this->label2->Location = System::Drawing::Point(292, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Ostatnia aktualizacja: ";
			// 
			// label_aktualizacja
			// 
			this->label_aktualizacja->AutoSize = true;
			this->label_aktualizacja->Location = System::Drawing::Point(403, 13);
			this->label_aktualizacja->Name = L"label_aktualizacja";
			this->label_aktualizacja->Size = System::Drawing::Size(0, 13);
			this->label_aktualizacja->TabIndex = 5;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tab_nie_pobrane);
			this->tabControl1->Controls->Add(this->tab_pobrane);
			this->tabControl1->Controls->Add(this->tab_sprawdzone);
			this->tabControl1->Location = System::Drawing::Point(12, 95);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(278, 155);
			this->tabControl1->TabIndex = 6;
			// 
			// tab_nie_pobrane
			// 
			this->tab_nie_pobrane->BackColor = System::Drawing::Color::White;
			this->tab_nie_pobrane->Controls->Add(this->listbox_nie_pobrane);
			this->tab_nie_pobrane->Location = System::Drawing::Point(4, 22);
			this->tab_nie_pobrane->Name = L"tab_nie_pobrane";
			this->tab_nie_pobrane->Padding = System::Windows::Forms::Padding(3);
			this->tab_nie_pobrane->Size = System::Drawing::Size(270, 129);
			this->tab_nie_pobrane->TabIndex = 0;
			this->tab_nie_pobrane->Text = L"Nie pobrane";
			// 
			// listbox_nie_pobrane
			// 
			this->listbox_nie_pobrane->FormattingEnabled = true;
			this->listbox_nie_pobrane->Location = System::Drawing::Point(-2, -3);
			this->listbox_nie_pobrane->Name = L"listbox_nie_pobrane";
			this->listbox_nie_pobrane->Size = System::Drawing::Size(274, 134);
			this->listbox_nie_pobrane->TabIndex = 1;
			this->listbox_nie_pobrane->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listbox_nie_pobrane_SelectedIndexChanged);
			// 
			// tab_pobrane
			// 
			this->tab_pobrane->Controls->Add(this->listbox_pobrane);
			this->tab_pobrane->Location = System::Drawing::Point(4, 22);
			this->tab_pobrane->Name = L"tab_pobrane";
			this->tab_pobrane->Padding = System::Windows::Forms::Padding(3);
			this->tab_pobrane->Size = System::Drawing::Size(270, 129);
			this->tab_pobrane->TabIndex = 1;
			this->tab_pobrane->Text = L"Pobrane";
			this->tab_pobrane->UseVisualStyleBackColor = true;
			// 
			// listbox_pobrane
			// 
			this->listbox_pobrane->FormattingEnabled = true;
			this->listbox_pobrane->Location = System::Drawing::Point(-2, -3);
			this->listbox_pobrane->Name = L"listbox_pobrane";
			this->listbox_pobrane->Size = System::Drawing::Size(274, 134);
			this->listbox_pobrane->TabIndex = 1;
			this->listbox_pobrane->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listbox_pobrane_SelectedIndexChanged);
			// 
			// tab_sprawdzone
			// 
			this->tab_sprawdzone->Controls->Add(this->listbox_sprawdzone);
			this->tab_sprawdzone->Location = System::Drawing::Point(4, 22);
			this->tab_sprawdzone->Name = L"tab_sprawdzone";
			this->tab_sprawdzone->Size = System::Drawing::Size(270, 129);
			this->tab_sprawdzone->TabIndex = 2;
			this->tab_sprawdzone->Text = L"Sprawdzone";
			this->tab_sprawdzone->UseVisualStyleBackColor = true;
			// 
			// listbox_sprawdzone
			// 
			this->listbox_sprawdzone->FormattingEnabled = true;
			this->listbox_sprawdzone->Location = System::Drawing::Point(-2, -3);
			this->listbox_sprawdzone->Name = L"listbox_sprawdzone";
			this->listbox_sprawdzone->Size = System::Drawing::Size(274, 134);
			this->listbox_sprawdzone->TabIndex = 1;
			this->listbox_sprawdzone->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listbox_sprawdzone_SelectedIndexChanged);
			// 
			// radio_button_nie_pobrane
			// 
			this->radio_button_nie_pobrane->AutoSize = true;
			this->radio_button_nie_pobrane->Location = System::Drawing::Point(296, 189);
			this->radio_button_nie_pobrane->Name = L"radio_button_nie_pobrane";
			this->radio_button_nie_pobrane->Size = System::Drawing::Size(83, 17);
			this->radio_button_nie_pobrane->TabIndex = 7;
			this->radio_button_nie_pobrane->TabStop = true;
			this->radio_button_nie_pobrane->Text = L"Nie pobrane";
			this->radio_button_nie_pobrane->UseVisualStyleBackColor = true;
			this->radio_button_nie_pobrane->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radio_button_nie_pobrane_CheckedChanged);
			// 
			// radio_button_pobrane
			// 
			this->radio_button_pobrane->AutoSize = true;
			this->radio_button_pobrane->Location = System::Drawing::Point(296, 212);
			this->radio_button_pobrane->Name = L"radio_button_pobrane";
			this->radio_button_pobrane->Size = System::Drawing::Size(65, 17);
			this->radio_button_pobrane->TabIndex = 8;
			this->radio_button_pobrane->TabStop = true;
			this->radio_button_pobrane->Text = L"Pobrane";
			this->radio_button_pobrane->UseVisualStyleBackColor = true;
			this->radio_button_pobrane->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radio_button_pobrane_CheckedChanged);
			// 
			// radio_button_sprawdzone
			// 
			this->radio_button_sprawdzone->AutoSize = true;
			this->radio_button_sprawdzone->Location = System::Drawing::Point(296, 234);
			this->radio_button_sprawdzone->Name = L"radio_button_sprawdzone";
			this->radio_button_sprawdzone->Size = System::Drawing::Size(84, 17);
			this->radio_button_sprawdzone->TabIndex = 9;
			this->radio_button_sprawdzone->TabStop = true;
			this->radio_button_sprawdzone->Text = L"Sprawdzone";
			this->radio_button_sprawdzone->UseVisualStyleBackColor = true;
			this->radio_button_sprawdzone->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radio_button_sprawdzone_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(297, 114);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(69, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Zaznaczone:";
			// 
			// textBox_zaznaczone
			// 
			this->textBox_zaznaczone->Location = System::Drawing::Point(300, 131);
			this->textBox_zaznaczone->Name = L"textBox_zaznaczone";
			this->textBox_zaznaczone->ReadOnly = true;
			this->textBox_zaznaczone->Size = System::Drawing::Size(272, 20);
			this->textBox_zaznaczone->TabIndex = 11;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 262);
			this->Controls->Add(this->textBox_zaznaczone);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->radio_button_sprawdzone);
			this->Controls->Add(this->radio_button_pobrane);
			this->Controls->Add(this->radio_button_nie_pobrane);
			this->Controls->Add(this->tabControl1);
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
			this->tabControl1->ResumeLayout(false);
			this->tab_nie_pobrane->ResumeLayout(false);
			this->tab_pobrane->ResumeLayout(false);
			this->tab_sprawdzone->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void odswiez_date_godzine()
		{
			String^ data_godzina_aktualizacji_po_konwersji = gcnew String(strona.ostatnia_aktualizacja.c_str());
			label_aktualizacja->Text = data_godzina_aktualizacji_po_konwersji;
		}

		void odswiez_listy()
		{
			listbox_nie_pobrane->Items->Clear();
			listbox_pobrane->Items->Clear();
			listbox_sprawdzone->Items->Clear();
			listbox_nie_pobrane->BeginUpdate();
			listbox_pobrane->BeginUpdate();
			listbox_sprawdzone->BeginUpdate();
			for (auto i : strona.baza)
			{
				String^ element = gcnew String(i.first.c_str());
				if (i.second == 0)
				{
					if (!listbox_nie_pobrane->Items->Contains(element))
						listbox_nie_pobrane->Items->Add(element);
				}
				else if (i.second == 1)
				{
					if (!listbox_pobrane->Items->Contains(element))
						listbox_pobrane->Items->Add(element);
				}
				else if (i.second == 2)
				{
					if (!listbox_sprawdzone->Items->Contains(element))
						listbox_sprawdzone->Items->Add(element);
				}
			}
			listbox_nie_pobrane->EndUpdate();
			listbox_pobrane->EndUpdate();
			listbox_sprawdzone->EndUpdate();
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
				 string adres_slownika = "base_dictionary.txt";

				 HANDLE odswiez, odswiez_listy_handle;



				 System::String^ nazwa_uzytkownik_konwersja_na_string = nazwa_uzytkownika_textbox->Text;
				 std::string nazwa_uzytkownika = msclr::interop::marshal_as<std::string>(nazwa_uzytkownik_konwersja_na_string);

				 adres_zrodla = adres_zrodla + nazwa_uzytkownika;
				 pelny_adres = adres + adres_zrodla;
				 String^ pelny_adres_po_konwersji = gcnew String(pelny_adres.c_str());

				 label_pelny_adres_lastfm->Text = pelny_adres_po_konwersji;




				 string przyrostek = ".txt";
				 string nazwa_bazy = nazwa_uzytkownika + przyrostek;
				 transform(nazwa_bazy.begin(), nazwa_bazy.end(), nazwa_bazy.begin(), ::tolower);

				 strona = { adres, adres_zrodla, nazwa_bazy, adres_slownika };

				 strona.wczytaj_slownik();

				 listbox_nie_pobrane->Items->Clear();
				 listbox_pobrane->Items->Clear();
				 listbox_sprawdzone->Items->Clear();
				 
				 Odswiezanie_Daty_Godziny::odswiez_label = gcnew ZmianaLabela(this,&MyForm::odswiez_date_godzine);
				 Odswiezanie_List::odswiez_listy = gcnew odswiezanie_list(this, &MyForm::odswiez_listy);
				 odswiez = CreateThread(0, 0, odswiezanie, 0, 0, 0);
				 //odswiez_listy_handle = CreateThread(0, 0, odswiezanie_list_w_tab, 0, 0, 0);

	}
			

private: System::Void listbox_nie_pobrane_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 radio_button_nie_pobrane->Checked = FALSE;
			 radio_button_pobrane->Checked = FALSE;
			 radio_button_sprawdzone->Checked = FALSE;

			 String^ curItem = listbox_nie_pobrane->SelectedItem->ToString();
			 string sprawdz_radio_button = msclr::interop::marshal_as<std::string>(curItem);
			 textBox_zaznaczone->Text = curItem;

			 if (strona.baza[sprawdz_radio_button] == 0)
			 {
				 radio_button_nie_pobrane->Checked = TRUE;
				 radio_button_pobrane->Checked = FALSE;
				 radio_button_sprawdzone->Checked = FALSE;
			 }
			 else if (strona.baza[sprawdz_radio_button] == 1)
			 {
				 radio_button_nie_pobrane->Checked = FALSE;
				 radio_button_pobrane->Checked = TRUE;
				 radio_button_sprawdzone->Checked = FALSE;
			 }
			 else if (strona.baza[sprawdz_radio_button] == 2)
			 {
				 radio_button_nie_pobrane->Checked = FALSE;
				 radio_button_pobrane->Checked = FALSE;
				 radio_button_sprawdzone->Checked = TRUE;
			 }

}
private: System::Void radio_button_nie_pobrane_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		
			 //
			 // DO NAPISANIA EVENT RADIO BUTTON NIE POBRANE
			 //
}
private: System::Void radio_button_pobrane_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 //
			 // DO NAPISANIA EVENT RADIO BUTTON POBRANE
			 //
}
private: System::Void radio_button_sprawdzone_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 //
			 // DO NAPISANIA EVENT RADIO BUTTON SPRAWDZONE
			 //
}
private: System::Void listbox_pobrane_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 radio_button_nie_pobrane->Checked = FALSE;
			 radio_button_pobrane->Checked = FALSE;
			 radio_button_sprawdzone->Checked = FALSE;


			 String^ curItem = listbox_pobrane->SelectedItem->ToString();
			 string sprawdz_radio_button = msclr::interop::marshal_as<std::string>(curItem);
			 textBox_zaznaczone->Text = curItem;

			 if (strona.baza[sprawdz_radio_button] == 0)
			 {
				 radio_button_nie_pobrane->Checked = TRUE;
				 radio_button_pobrane->Checked = FALSE;
				 radio_button_sprawdzone->Checked = FALSE;
			 }
			 else if (strona.baza[sprawdz_radio_button] == 1)
			 {
				 radio_button_nie_pobrane->Checked = FALSE;
				 radio_button_pobrane->Checked = TRUE;
				 radio_button_sprawdzone->Checked = FALSE;
			 }
			 else if (strona.baza[sprawdz_radio_button] == 2)
			 {
				 radio_button_nie_pobrane->Checked = FALSE;
				 radio_button_pobrane->Checked = FALSE;
				 radio_button_sprawdzone->Checked = TRUE;
			 }
}
private: System::Void listbox_sprawdzone_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 radio_button_nie_pobrane->Checked = FALSE;
			 radio_button_pobrane->Checked = FALSE;
			 radio_button_sprawdzone->Checked = FALSE;

			 String^ curItem = listbox_sprawdzone->SelectedItem->ToString();
			 string sprawdz_radio_button = msclr::interop::marshal_as<std::string>(curItem);
			 textBox_zaznaczone->Text = curItem;

			 if (strona.baza[sprawdz_radio_button] == 0)
			 {
				 radio_button_nie_pobrane->Checked = TRUE;
				 radio_button_pobrane->Checked = FALSE;
				 radio_button_sprawdzone->Checked = FALSE;
			 }
			 else if (strona.baza[sprawdz_radio_button] == 1)
			 {
				 radio_button_nie_pobrane->Checked = FALSE;
				 radio_button_pobrane->Checked = TRUE;
				 radio_button_sprawdzone->Checked = FALSE;
			 }
			 else if (strona.baza[sprawdz_radio_button] == 2)
			 {
				 radio_button_nie_pobrane->Checked = FALSE;
				 radio_button_pobrane->Checked = FALSE;
				 radio_button_sprawdzone->Checked = TRUE;
			 }
}
};
}

