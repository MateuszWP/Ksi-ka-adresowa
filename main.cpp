#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <sstream>
#include <string>

using namespace std;

struct Uzytkownik
{
	int idUzytkownika;
	string nazwaUzytkownika, hasloUzytkownika;
};

struct KsiazkaAdresowa
{
	string imie;
	string nazwisko;
	string adres;
	string email;
	string nrTelefonu;
	int id;
};

void zapiszDanePoEdycjiAdresata(vector<KsiazkaAdresowa> daneAdresatow, int idUzytkownika)
{
	fstream plikOryginalny, plikTymczasowy;
	string linia, liniaTymczasowa;

	int nrLinii = 0, pozycjaAdresata = 0;
	int idZPliku;
	int id;

	plikOryginalny.open("ksiazka_adresowa.txt", ios::in);
	plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);

	if (plikOryginalny.good() == false)
	{
		cout << "Nie udalo sie otworzyc oryginalnego pliku i wczytac danych. Zla nazwa badz pierwsze uruchomienie programu." << endl;
		plikOryginalny.close();
	}
	else
	{
		while (getline(plikOryginalny, linia))
		{
			liniaTymczasowa = linia;
			stringstream ss(linia);
			string pojedynczaDana;

			getline(ss, pojedynczaDana, '|');
			idZPliku = atoi(pojedynczaDana.c_str());

			if (pozycjaAdresata < daneAdresatow.size())
			{
				id = daneAdresatow[pozycjaAdresata].id;
			}

			if (idZPliku == id )
			{
				plikTymczasowy << daneAdresatow[pozycjaAdresata].id;
				plikTymczasowy << "|" << idUzytkownika;
				plikTymczasowy << "|" << daneAdresatow[pozycjaAdresata].imie;
				plikTymczasowy << "|" << daneAdresatow[pozycjaAdresata].nazwisko;
				plikTymczasowy << "|" << daneAdresatow[pozycjaAdresata].email;
				plikTymczasowy << "|" << daneAdresatow[pozycjaAdresata].nrTelefonu;
				plikTymczasowy << "|" << daneAdresatow[pozycjaAdresata].adres;
				plikTymczasowy << "|" << endl;
				pozycjaAdresata++;
				cout << "zapisuje adresata z nowymi danymi " << endl;
			}
			else
			{
				plikTymczasowy << liniaTymczasowa << endl;
			}
		}
	}
	plikOryginalny.close();
	plikTymczasowy.close();

	remove("ksiazka_adresowa.txt");
	rename("Adresaci_tymczasowy.txt", "ksiazka_adresowa.txt");
}

void zapiszDanePoUsunieciuAdresata(vector<KsiazkaAdresowa> daneAdresatow, int idAdresata)
{
	fstream plikOryginalny, plikTymczasowy;
	string linia, liniaTymczasowa;

	int nrLinii = 0;
	int idZPliku;

	plikOryginalny.open("ksiazka_adresowa.txt", ios::in);
	plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);

	if (plikOryginalny.good() == false)
	{
		cout << "Nie udalo sie otworzyc oryginalnego pliku i wczytac danych. Zla nazwa badz pierwsze uruchomienie programu" << endl;
		plikOryginalny.close();
	}
	else
	{
		while (getline(plikOryginalny, linia))
		{
			liniaTymczasowa = linia;
			stringstream ss(linia);
			string pojedynczaDana;

			getline(ss, pojedynczaDana, '|');
			idZPliku = atoi(pojedynczaDana.c_str());

			if(idZPliku != idAdresata)
			{
				plikTymczasowy << liniaTymczasowa << endl;
			}
		}
	}
	plikOryginalny.close();
	plikTymczasowy.close();

	remove("ksiazka_adresowa.txt");
	rename("Adresaci_tymczasowy.txt", "ksiazka_adresowa.txt");
}

void menu(int wyborMenu)
{
	if (wyborMenu == 1)
	{
		cout << "LOGOWANIE i REJESTRACJA" << endl;
		cout << endl;
		cout << "1. Rejestracja" << endl;
		cout << "2. Logowanie" << endl;
		cout << "3. Zamknij program" << endl;
		cout << endl;
	}
	else if (wyborMenu == 2)
	{
		cout << "KSIAZKA ADRESOWA" << endl;
		cout << endl;
		cout << "1. Dodaj adresata." << endl;
		cout << "2. Wyswietl liste osob." << endl;
		cout << "3. Wyszukaj adresata wg imienia." << endl;
		cout << "4. Wyszukaj adresata wg nazwiska." << endl;
		cout << "5. Edytuj dane adresata." << endl;
		cout << "6. Usun adresata." << endl;
		cout << "7. Zmien haslo." << endl;
		cout << "8. Wyloguj sie." << endl;
		cout << endl;
	}
}

void zapisOsobDoPliku(KsiazkaAdresowa daneAdresatow, int idUzytkownika)
{
	fstream plik;
	plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
	if (plik.good() == true)
	{
		plik << daneAdresatow.id << "|";
		plik << idUzytkownika << "|";
		plik << daneAdresatow.imie << "|";
		plik << daneAdresatow.nazwisko << "|";
		plik << daneAdresatow.email << "|";
		plik << daneAdresatow.nrTelefonu << "|";
		plik << daneAdresatow.adres << "|";
		plik << endl;
		cout << "Osoba zapisana." << endl;
	}
	else
	{
		cout << "Blad zapisu." << endl;
	}
	plik.close();
}

void zapisUzytkownikaDoPliku(Uzytkownik uzytkownicy)
{
	fstream plik;
	plik.open("uzytkownicy.txt", ios::out | ios::app);
	if (plik.good() == true)
	{
		plik << uzytkownicy.idUzytkownika << "|";
		plik << uzytkownicy.nazwaUzytkownika << "|";
		plik << uzytkownicy.hasloUzytkownika << "|";
		plik << endl;
		cout << "Uzytkownik zapisany." << endl;
	}
	else
	{
		cout << "Blad zapisu." << endl;
	}
	plik.close();
}

void rejestracjaUzytkownika(vector<Uzytkownik> &osoby)
{
	Uzytkownik uzytkownicy;

	if (osoby.empty() == true)
	{
		uzytkownicy.idUzytkownika = 1;
	}
	else
	{
		uzytkownicy.idUzytkownika = osoby.back().idUzytkownika + 1;
	}

	cout << "Podaj nazwe uzytkownika: ";
	cin >> uzytkownicy.nazwaUzytkownika;

	cout << "Podaj haslo: ";
	cin >> uzytkownicy.hasloUzytkownika;

	osoby.push_back(uzytkownicy);
	zapisUzytkownikaDoPliku(uzytkownicy);

	system("pause");
}

int logowanieUzytkownika(vector<Uzytkownik> osoby)
{
	string nazwa, haslo;
	char wybor;

	do
	{
		cout << "Podaj nazwe uzytkownika: ";
		cin >> nazwa;

		cout << "Podaj haslo: ";
		cin >> haslo;

		for (int i = 0; i < osoby.size(); i++)
		{
			if (nazwa == osoby[i].nazwaUzytkownika && haslo == osoby[i].hasloUzytkownika)
			{
				cout << "Logowanie zakonczylo sie sukcesem. " << osoby[i].nazwaUzytkownika << endl;
				return osoby[i].idUzytkownika;
			}
		}
		cout << "Blad logowania!" << endl;
		cout << "Czy chcesz kontynuowac logowanie [t]?" << endl;
		cin >> wybor;
	} while (wybor == 't');
	return 0;
}

void dodajAdresata(vector<KsiazkaAdresowa> &adresaci, int idUzytkownika, int &idOstatniegoAdresata)
{
	KsiazkaAdresowa daneAdresatow;

	daneAdresatow.id = idOstatniegoAdresata + 1;
	idOstatniegoAdresata++;

	cout << "Podaj imie: ";
	cin >> daneAdresatow.imie;

	cout << "Podaj nazwisko: ";
	cin >> daneAdresatow.nazwisko;

	cout << "Podaj email: ";
	cin >> daneAdresatow.email;

	cout << "Podaj numer telefonu: ";
	cin.ignore();
	getline(cin, daneAdresatow.nrTelefonu);

	cout << "Podaj adres: ";
	getline(cin, daneAdresatow.adres);

	adresaci.push_back(daneAdresatow);

	zapisOsobDoPliku(daneAdresatow, idUzytkownika);

	system("pause");
}

int podzialStringow(vector<KsiazkaAdresowa> &adresaci, string wczytanaLinia, char znak, int idUzytkownika)
{
	KsiazkaAdresowa daneAdresatow;
	int idUzytkoanikaZPliku = 0;
	int numerPojedynczejDanej = 1;
	stringstream ss(wczytanaLinia);
	string pojedynczaDana;

	while (getline(ss, pojedynczaDana, znak))
	{
		switch (numerPojedynczejDanej)
		{
		case 1:
			daneAdresatow.id = atoi(pojedynczaDana.c_str());
			break;
		case 2:
			idUzytkoanikaZPliku = atoi(pojedynczaDana.c_str());
			break;
		case 3:
			daneAdresatow.imie = pojedynczaDana;
			break;
		case 4:
			daneAdresatow.nazwisko = pojedynczaDana;
			break;
		case 5:
			daneAdresatow.email = pojedynczaDana;
			break;
		case 6:
			daneAdresatow.nrTelefonu = pojedynczaDana;
			break;
		case 7:
			daneAdresatow.adres = pojedynczaDana;
			break;
		}
		numerPojedynczejDanej++;
	}

	if(idUzytkoanikaZPliku == idUzytkownika)
		adresaci.push_back(daneAdresatow);

	return daneAdresatow.id;
}

int wczytajOsobyZPlikuDoTablicyStruktur(vector<KsiazkaAdresowa> &adresaci, int idUzytkownika)
{
	string pobranaLiniaStringow;
	int idOstatniegoAdresata = 0;
	fstream plik;
	plik.open("ksiazka_adresowa.txt", ios::in);

	if (!plik.good())
	{
		plik.close();
	}
	else
	{
		while (getline(plik, pobranaLiniaStringow))
		{
			idOstatniegoAdresata = podzialStringow(adresaci, pobranaLiniaStringow, '|', idUzytkownika);
		}
		plik.close();
	}
	return idOstatniegoAdresata;
}

void wyswietlWszystkieOsobyZKsiazkiAdresowej(vector<KsiazkaAdresowa> &adresaci)
{
	vector<KsiazkaAdresowa>::iterator itr;

	if (adresaci.empty() == true)
	{
		cout << "Brak wpisow w ksiazce adresowej" << endl;
	}
	else
	{
		cout << "Aktualna lista osob: " << endl << endl;

		for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
		{
			cout << "Id:              " << itr->id << endl;
			cout << "Imie:            " << itr->imie << endl;
			cout << "Nazwisko:        " << itr->nazwisko << endl;
			cout << "Email:           " << itr->email << endl;
			cout << "Numer telefonu:  " << itr->nrTelefonu << endl;
			cout << "Adres:           " << itr->adres << endl;
			cout << endl;
		}
	}
	system("pause");
}

void wyswietlOsobeWgImienia(vector<KsiazkaAdresowa> &adresaci)
{
	string imieAdresata;
	int iloscOsob = 0;

	cout << "Podaj imie: ";
	cin >> imieAdresata;

	vector<KsiazkaAdresowa>::iterator itr;

	for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
	{
		if (itr->imie == imieAdresata)
		{
			cout << "Id:              " << itr->id << endl;
			cout << "Imie:            " << itr->imie << endl;
			cout << "Nazwisko:        " << itr->nazwisko << endl;
			cout << "Email:           " << itr->email << endl;
			cout << "Numer telefonu:  " << itr->nrTelefonu << endl;
			cout << "Adres:           " << itr->adres << endl;
			cout << endl;
			iloscOsob++;
		}
	}
	if (iloscOsob == 0)
	{
		cout << "Kontakt o imieniu " << imieAdresata << " nie istnieje." << endl;
	}
	cout << endl;
	system("pause");
}

void wyswietlOsobeWgNazwiska(vector<KsiazkaAdresowa> &adresaci)
{
	string nazwiskoAdresata;
	int iloscOsob = 0;

	cout << "Podaj nazwisko: ";
	cin >> nazwiskoAdresata;

	vector<KsiazkaAdresowa>::iterator itr;

	for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
	{
		if (itr->nazwisko == nazwiskoAdresata)
		{
			cout << "Id:              " << itr->id << endl;
			cout << "Imie:            " << itr->imie << endl;
			cout << "Nazwisko:        " << itr->nazwisko << endl;
			cout << "Email:           " << itr->email << endl;
			cout << "Numer telefonu:  " << itr->nrTelefonu << endl;
			cout << "Adres:           " << itr->adres << endl;
			cout << endl;
			iloscOsob++;
		}
	}
	if (iloscOsob == 0)
	{
		cout << "Adresat o nazwisku " << nazwiskoAdresata << " nie istnieje." << endl;
	}
	cout << endl;
	system("pause");
}

void zapiszPlik(vector<KsiazkaAdresowa> &adresaci)
{
	ofstream plik;
	plik.open("ksiazka_adresowa.txt", ios::out);

	for (int i = 0; i < adresaci.size(); i++)
	{
		plik << adresaci[i].id << "|";
		plik << adresaci[i].imie << "|";
		plik << adresaci[i].nazwisko << "|";
		plik << adresaci[i].email << "|";
		plik << adresaci[i].nrTelefonu << "|";
		plik << adresaci[i].adres << "|" << endl;
	}
	plik.close();
}

void usunOsobe(vector<KsiazkaAdresowa> &adresaci)
{
	KsiazkaAdresowa daneAdresatow;
	char wybor, znak;
	bool sprawdzCzyAdresatIstniejeNaLiscieAdresatow = false;
	int IDAdresataDoUsuniecia;

	vector<KsiazkaAdresowa>::iterator itr;

	if (!adresaci.empty())
	{
		cout << "Aktualna lista osob: " << endl;

		for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
		{
			cout << "Id:              " << itr->id << endl;
			cout << "Imie:            " << itr->imie << endl;
			cout << "Nazwisko:        " << itr->nazwisko << endl;
			cout << "Email:           " << itr->email << endl;
			cout << "Numer telefonu:  " << itr->nrTelefonu << endl;
			cout << "Adres:           " << itr->adres << endl;
			cout << endl;
		}

		cout << "Usun adresata wg ID: ";
		cin >> IDAdresataDoUsuniecia;

		if (cin.fail())
		{
			cout << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl;
			cin.clear();
			cin.ignore();
		}
		else
		{
			for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
			{
				if (itr->id == IDAdresataDoUsuniecia)
				{
					sprawdzCzyAdresatIstniejeNaLiscieAdresatow = true;

					itr = adresaci.erase(itr);
					cout << endl << "Adresat zostal usuniety." << endl;
					zapiszDanePoUsunieciuAdresata(adresaci, IDAdresataDoUsuniecia);
					break;
				}
			}
			if (sprawdzCzyAdresatIstniejeNaLiscieAdresatow == false)
			{
				cout << "Nie ma takiego adresata." << endl;
			}
		}
	}
	system("pause");
}

void edytujDaneOsob(vector<KsiazkaAdresowa> &adresaci, int idUzytkowanika)
{
	KsiazkaAdresowa danaAdresatow;
	bool sprawdzCzyAdresatIstniejeNaLiscieAdresatow = false;
	int ktoreDaneOsoboweEdytowac;
	int IDAdresataDoEdycji;

	vector<KsiazkaAdresowa>::iterator itr;

	if (!adresaci.empty())
	{
		cout << "Aktualna lista osob: " << endl << endl;

		for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
		{
			cout << "Id:              " << itr->id << endl;
			cout << "Imie:            " << itr->imie << endl;
			cout << "Nazwisko:        " << itr->nazwisko << endl;
			cout << "Email:           " << itr->email << endl;
			cout << "Numer telefonu:  " << itr->nrTelefonu << endl;
			cout << "Adres:           " << itr->adres << endl;
			cout << endl;
		}
		cout << "Edytuj adresata wg ID: ";
		cin >> IDAdresataDoEdycji;

		if (cin.fail())
		{
			cout << "Blad danych. Powrot do menu glownego." << endl;
			cin.clear();
			cin.ignore();
		}
		else
		{
			for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
			{
				if (itr->id == IDAdresataDoEdycji)
				{
					sprawdzCzyAdresatIstniejeNaLiscieAdresatow = true;
					cout << "Pola adresowe do edycji: " << endl;
					cout << endl;
					cout << "Id:              " << itr->id << endl;
					cout << "Imie:            " << itr->imie << endl;
					cout << "Nazwisko:        " << itr->nazwisko << endl;
					cout << "Email:           " << itr->email << endl;
					cout << "Numer telefonu:  " << itr->nrTelefonu << endl;
					cout << "Adres:           " << itr->adres << endl;
					cout << endl;

					cout << "Wybierz pole adresowe, ktore chcesz edytowac: " << endl;
					cout << "1. Imie" << endl;
					cout << "2. Nazwisko" << endl;
					cout << "3. Email" << endl;
					cout << "4. Numer telefonu" << endl;
					cout << "5. Adres" << endl;
					cout << "6. Zakoncz" << endl;

					cin >> ktoreDaneOsoboweEdytowac;

					switch (ktoreDaneOsoboweEdytowac)
					{
					case 1:
						cout << "Podaj imie: ";
						cin >> itr->imie;
						cout << "Imie adresata zostalo zmienione.";
						break;
					case 2:
						cout << "Podaj nazwisko: ";
						cin >> itr->nazwisko;
						cout << "Nazwisko adresata zostalo zmienione.";
						break;
					case 3:
						cout << "Podaj adres email: ";
						cin >> itr->email;
						cout << "Email adresata zostal zmieniony.";
						break;
					case 4:
						cout << "Podaj numer telefonu: ";
						cin.ignore();
						getline(cin, itr->nrTelefonu);
						cout << "Numer telefonu adresata zostal zmieniony.";
						break;
					case 5:
						cout << "Podaj adres: ";
						cin.ignore();
						getline(cin, itr->adres);
						cout << "Adres adresata zostal zmieniony.";
						break;
					case 6:
						break;
					}
					zapiszDanePoEdycjiAdresata(adresaci, idUzytkowanika);
					cout << endl;

					if (sprawdzCzyAdresatIstniejeNaLiscieAdresatow == false)
					{
						cout << "Adresat nie wystepuje w ksiazce adresowej." << endl;
					}
				}
			}
		}
	}
	else
	{
		cout << "Ksiazka adresowa jest pusta." << endl << endl;
	}
	system("pause");
}

void koniecProgramu()
{
	cout << "Koniec programu!" << endl;
	exit(0);
}

void podzialStringow(vector<Uzytkownik> &osoby, string wczytanaLinia, char znak)
{
	Uzytkownik uzytkownicy;
	int numerPojedynczejDanej = 1;

	stringstream ss(wczytanaLinia);
	string pojedynczaDana;

	while (getline(ss, pojedynczaDana, znak))
	{
		switch (numerPojedynczejDanej)
		{
		case 1:
			uzytkownicy.idUzytkownika = atoi(pojedynczaDana.c_str());
			break;
		case 2:
			uzytkownicy.nazwaUzytkownika = pojedynczaDana;
			break;
		case 3:
			uzytkownicy.hasloUzytkownika = pojedynczaDana;
			break;
		}
		numerPojedynczejDanej++;
	}

		osoby.push_back(uzytkownicy);
}

void wczytajUzytkoanikowZPlikuDoTablicyStruktur(vector<Uzytkownik> &osoby)
{
	string pobranaLiniaStringow;

	fstream plik;
	plik.open("uzytkownicy.txt", ios::in);

	if (!plik.good())
	{
		cout << "Nie mozna otworzyc pliku." << endl;
		plik.close();
	}
	else
	{
		while (getline(plik, pobranaLiniaStringow))
		{
			podzialStringow(osoby, pobranaLiniaStringow, '|');
		}
		plik.close();
	}
}

void zapiszUzytkownikow(vector<Uzytkownik> osoby)
{
	fstream plik;
	plik.open("uzytkownicy.txt", ios::out);

	for (int i = 0; i < osoby.size(); i++)
	{
		plik << osoby[i].idUzytkownika << "|";
		plik << osoby[i].nazwaUzytkownika << "|";
		plik << osoby[i].hasloUzytkownika << "|";
		plik << endl;
	}
	plik.close();
}

void zmianaHasla(vector<Uzytkownik> &osoby, int idUzytkownika)
{
	string noweHaslo;
	cout << "Wprowadz nowe haslo:";
	cin >> noweHaslo;

	osoby[idUzytkownika - 1].hasloUzytkownika = noweHaslo;
	zapiszUzytkownikow(osoby);
}

int main()
{
	vector<KsiazkaAdresowa> adresaci(0);
	vector<Uzytkownik> osoby(0);

	wczytajUzytkoanikowZPlikuDoTablicyStruktur(osoby);

	char wybor;

	while (true)
	{
		system("cls");
		menu(1);

		cin >> wybor;

		switch (wybor)
		{
		case '1':
		{
			rejestracjaUzytkownika(osoby);
			break;
		}
		case '2':
		{
			int ostatnieIDzKsiazkiAdresowej;
			int idUzytkownika = 0;
			idUzytkownika = logowanieUzytkownika(osoby);
			cout << idUzytkownika << endl;

			if (idUzytkownika != 0)
			{
				ostatnieIDzKsiazkiAdresowej = wczytajOsobyZPlikuDoTablicyStruktur(adresaci, idUzytkownika);
			}
			while (idUzytkownika != 0)
			{
				menu(2);

				cin >> wybor;
				cin.ignore();

				switch (wybor)
				{
				case '1':
					dodajAdresata(adresaci, idUzytkownika, ostatnieIDzKsiazkiAdresowej);
					break;

				case '2':
					wyswietlWszystkieOsobyZKsiazkiAdresowej(adresaci);
					break;

				case '3':
					wyswietlOsobeWgImienia(adresaci);
					break;

				case '4':
					wyswietlOsobeWgNazwiska(adresaci);
					break;

				case '5':
					edytujDaneOsob(adresaci, idUzytkownika);
					break;

				case '6':
					usunOsobe(adresaci);
					break;

				case '7':
					zmianaHasla(osoby, idUzytkownika);
					break;

				case '8':
					idUzytkownika = 0;
					adresaci.clear();
					break;

				default:
					cout << "Nie ma takiej opcji. Wybierz ponownie." << endl;
					break;
				}
			}
			break;
		}
		case '3':
		{
			exit(0);
			break;
		}
		default:
			break;
		}
	}
}

