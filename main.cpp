#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <sstream>
#include <string>

using namespace std;

struct KsiazkaAdresowa
{
    string imie;
    string nazwisko;
    string adres;
    string email;
    string nrTelefonu;
    int id;
};

void zapisOsobDoPliku(KsiazkaAdresowa daneAdresatow)
{
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    if(plik.good() == true)
    {
        plik << daneAdresatow.id << "|";
        plik << daneAdresatow.imie << "|";
        plik << daneAdresatow.nazwisko << "|";
        plik << daneAdresatow.email << "|";
        plik << daneAdresatow.nrTelefonu << "|";
        plik << daneAdresatow.adres << "|";
        plik << endl;
        plik.close();
        cout << "Osoba zapisana." << endl;
    }
    else
    {
        cout << "Blad zapisu." << endl;
    }
}

void dodajAdresata(vector<KsiazkaAdresowa> &adresaci)
{
    KsiazkaAdresowa daneAdresatow;

    if(adresaci.empty() == true)
    {
        daneAdresatow.id = 1;
    }
    else
    {
        daneAdresatow.id = adresaci.back().id + 1;
    }

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

    zapisOsobDoPliku(daneAdresatow);

    system("pause");
}

vector<KsiazkaAdresowa> podzialStringow(vector<KsiazkaAdresowa> &adresaci, string wczytanaLinia, char znak)
{
    KsiazkaAdresowa daneAdresatow;

    int numerPojedynczejDanej = 1;
    stringstream ss(wczytanaLinia);
    string pojedynczaDana;

    while (getline(ss, pojedynczaDana, znak))
    {
        switch(numerPojedynczejDanej)
        {
        case 1:
            daneAdresatow.id = atoi(pojedynczaDana.c_str());
            break;
        case 2:
            daneAdresatow.imie = pojedynczaDana;
            break;
        case 3:
            daneAdresatow.nazwisko = pojedynczaDana;
            break;
        case 4:
            daneAdresatow.email = pojedynczaDana;
            break;
        case 5:
            daneAdresatow.nrTelefonu = pojedynczaDana;
            break;
        case 6:
            daneAdresatow.adres = pojedynczaDana;
            break;
        }
        numerPojedynczejDanej++;
    }
    adresaci.push_back(daneAdresatow);
    return adresaci;
}

void wczytajOsobyZPlikuDoTablicyStruktur(vector<KsiazkaAdresowa> &adresaci)
{
    string pobranaLiniaStringow;

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);

    if (!plik.good())
    {
        cout << "Nie mozna otworzyc pliku." << endl;
        plik.close();
    }
    else
    {
        while(getline(plik, pobranaLiniaStringow))
        {
            adresaci = podzialStringow(adresaci, pobranaLiniaStringow, '|');
        }
        plik.close();
    }
}

void wyswietlWszystkieOsobyZKsiazkiAdresowej(vector<KsiazkaAdresowa> &adresaci)
{
    vector<KsiazkaAdresowa>::iterator itr;

    if(adresaci.empty() == true)
    {
        cout << "Brak wpisow w ksiazce adresowej" << endl;
    }
    else
    {
        cout << "Aktualna lista osob: " << endl << endl;

        for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            cout << "Id:              " << itr -> id << endl;
            cout << "Imie:            " << itr -> imie << endl;
            cout << "Nazwisko:        " << itr -> nazwisko << endl;
            cout << "Email:           " << itr -> email << endl;
            cout << "Numer telefonu:  " << itr -> nrTelefonu << endl;
            cout << "Adres:           " << itr -> adres << endl;
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
        if (itr -> imie == imieAdresata)
        {
            cout << "Id:              " << itr -> id << endl;
            cout << "Imie:            " << itr -> imie << endl;
            cout << "Nazwisko:        " << itr -> nazwisko << endl;
            cout << "Email:           " << itr -> email << endl;
            cout << "Numer telefonu:  " << itr -> nrTelefonu << endl;
            cout << "Adres:           " << itr -> adres << endl;
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
    cin >> nazwiskoAdresata ;

    vector<KsiazkaAdresowa>::iterator itr;

    for (itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> nazwisko == nazwiskoAdresata)
        {
            cout << "Id:              " << itr -> id << endl;
            cout << "Imie:            " << itr -> imie << endl;
            cout << "Nazwisko:        " << itr -> nazwisko << endl;
            cout << "Email:           " << itr -> email << endl;
            cout << "Numer telefonu:  " << itr -> nrTelefonu << endl;
            cout << "Adres:           " << itr -> adres << endl;
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
            cout << "Id:              " << itr -> id << endl;
            cout << "Imie:            " << itr -> imie << endl;
            cout << "Nazwisko:        " << itr -> nazwisko << endl;
            cout << "Email:           " << itr -> email << endl;
            cout << "Numer telefonu:  " << itr -> nrTelefonu << endl;
            cout << "Adres:           " << itr -> adres << endl;
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
                if (itr -> id == IDAdresataDoUsuniecia)
                {
                    sprawdzCzyAdresatIstniejeNaLiscieAdresatow = true;

                    itr = adresaci.erase(itr);
                    cout << endl << "Adresat zostal usuniety." << endl;
                    zapiszPlik(adresaci);
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

void edytujDaneOsob(vector<KsiazkaAdresowa> &adresaci)
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
            cout << "Id:              " << itr -> id << endl;
            cout << "Imie:            " << itr -> imie << endl;
            cout << "Nazwisko:        " << itr -> nazwisko << endl;
            cout << "Email:           " << itr -> email << endl;
            cout << "Numer telefonu:  " << itr -> nrTelefonu << endl;
            cout << "Adres:           " << itr -> adres << endl;
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
                if (itr -> id == IDAdresataDoEdycji)
                {
                    sprawdzCzyAdresatIstniejeNaLiscieAdresatow = true;
                    cout << "Pola adresowe do edycji: " << endl;
                    cout << endl;
                    cout << "Id:              " << itr -> id << endl;
                    cout << "Imie:            " << itr -> imie << endl;
                    cout << "Nazwisko:        " << itr -> nazwisko << endl;
                    cout << "Email:           " << itr -> email << endl;
                    cout << "Numer telefonu:  " << itr -> nrTelefonu << endl;
                    cout << "Adres:           " << itr -> adres << endl;
                    cout << endl;

                    cout << "Wybierz pole adresowe, ktore chcesz edytowac: " << endl;
                    cout << "1. Imie" << endl;
                    cout << "2. Nazwisko" << endl;
                    cout << "3. Email" << endl;
                    cout << "4. Numer telefonu" << endl;
                    cout << "5. Adres" << endl;
                    cout << "6. Zakoncz" << endl;

                    cin >> ktoreDaneOsoboweEdytowac;

                    switch(ktoreDaneOsoboweEdytowac)
                    {
                    case 1:
                        cout << "Podaj imie: ";
                        cin >> itr -> imie;
                        zapiszPlik(adresaci);
                        cout << "Imie adresata zostalo zmienione.";
                        break;
                    case 2:
                        cout << "Podaj nazwisko: ";
                        cin >> itr -> nazwisko;
                        zapiszPlik(adresaci);
                        cout << "Nazwisko adresata zostalo zmienione.";
                        break;
                    case 3:
                        cout << "Podaj adres email: ";
                        cin >> itr -> email;
                        zapiszPlik(adresaci);
                        cout << "Email adresata zostal zmieniony.";
                        break;
                    case 4:
                        cout << "Podaj numer telefonu: ";
                        cin.ignore();
                        getline(cin, itr -> nrTelefonu);
                        zapiszPlik(adresaci);
                        cout << "Numer telefonu adresata zostal zmieniony.";
                        break;
                    case 5:
                        cout << "Podaj adres: ";
                        cin.ignore();
                        getline(cin, itr -> adres);
                        zapiszPlik(adresaci);
                        cout << "Adres adresata zostal zmieniony.";
                        break;
                    case 6:
                        break;
                    }
                    cout << endl;
                    if(sprawdzCzyAdresatIstniejeNaLiscieAdresatow == false)
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
int main()
{
    KsiazkaAdresowa daneAdresatow;
    vector<KsiazkaAdresowa> adresaci;

    if(adresaci.empty() == true)
    {
        fstream plik;
        plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    }

    wczytajOsobyZPlikuDoTablicyStruktur(adresaci);

    char wybor;

    while (1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << endl;
        cout << "1. Dodaj adresata." << endl;
        cout << "2. Wyswietl liste osob." << endl;
        cout << "3. Wyszukaj adresata wg imienia." << endl;
        cout << "4. Wyszukaj adresata wg nazwiska." << endl;
        cout << "5. Edytuj dane adresata." << endl;
        cout << "6. Usun adresata." << endl;
        cout << "7. Zamknij ksiazke adresowa." << endl;
        cout << endl;

        cin >> wybor;
        cin.ignore();

        switch (wybor)
        {
        case '1':
            dodajAdresata(adresaci);
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
            edytujDaneOsob(adresaci);
            break;

        case '6':
            usunOsobe(adresaci);
            break;

        case '7':
            koniecProgramu();
            break;

        default:
            cout << "Nie ma takiej opcji. Wybierz ponownie." << endl;
            break;
        }
    }
    return 0;
}

