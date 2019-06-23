#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <cstdlib>

using namespace std;

class Statki
{
public:
	int kolumny, wiersze;
	int liczbaStatkow, liczbaStatkow2, liczbaStatkow3, liczbaStatkow4, liczbaStatkow5;
	char numerStatku;
	int dlugoscStatku;
	int trybWstawianiaStatkow; // 1 - recznie 2 - losowo
	int aktualnyGracz; // przyjmuje 1 lub 2
	int trybGracza; // 1 - cz³owiek, 2 - komputer
	int pokaz;
	char **planszaPC1Statki, **planszaPC1Strzaly, **planszaPC2Statki, **planszaPC2Strzaly, **planszaGracz1Statki, **planszaGracz1Strzaly, **planszaGracz2Statki, **planszaGracz2Strzaly;

	Statki()
	{
		wczytajKonfig();
		pokaz = 0;

		planszaPC1Statki = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaPC1Statki[i] = new char[kolumny];

		planszaPC1Strzaly = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaPC1Strzaly[i] = new char[kolumny];

		planszaPC2Statki = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaPC2Statki[i] = new char[kolumny];

		planszaPC2Strzaly = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaPC2Strzaly[i] = new char[kolumny];

		planszaGracz1Statki = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaGracz1Statki[i] = new char[kolumny];

		planszaGracz1Strzaly = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaGracz1Strzaly[i] = new char[kolumny];

		planszaGracz2Statki = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaGracz2Statki[i] = new char[kolumny];

		planszaGracz2Strzaly = new char *[wiersze];
		for (int i = 0; i < wiersze; i++)
			planszaGracz2Strzaly[i] = new char[kolumny];
	}

	~Statki()
	{
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaPC1Statki[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaPC1Strzaly[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaPC2Statki[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaPC2Strzaly[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaGracz1Statki[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaGracz1Strzaly[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaGracz2Statki[i];
		for (int i = 0; i < wiersze; ++i)
			delete[] planszaGracz2Strzaly[i];
	}

	void wczytajKonfig()
	{
		string linia, temp;
		fstream plik;
		int pozDk;

		plik.open("config.txt", ios::in);
		if (!plik.good())
		{
			cout << "Nie mozna otworzyc pliku konfiguracyjnego config.txt!" << endl;
			system("Pause");
			exit(1);
		}

		getline(plik, linia);
		pozDk = linia.find(':');
		temp = linia.substr(pozDk + 2, linia.length());
		kolumny = temp[0] - 64;

		if ((kolumny < 1) || (kolumny > 26))
		{
			cout << "Niepoprawna liczba kolumn planszy(minumum: A, maximum: Z)! Sprawdz config.txt" << endl;
			system("Pause");
			exit(1);
		}


		getline(plik, linia);
		pozDk = linia.find(':');
		temp = linia.substr(pozDk + 2, linia.length());
		wiersze = stoi(temp);

		if ((wiersze < 1) || (wiersze > 10000))
		{
			cout << "Niepoprawna liczba wierszy planszy (minumum: 1, maximum: 10000)! Sprawdz config.txt" << endl;
			system("Pause");
			exit(1);
		}

		getline(plik, linia);
		pozDk = linia.find(':');
		temp = linia.substr(pozDk + 2, linia.length());
		liczbaStatkow2 = stoi(temp);

		if ((liczbaStatkow2 < 0) || (liczbaStatkow2 > 0.06 * (wiersze*kolumny / 2)))
		{
			cout << "Niepoprawna liczba statkow 2 masztowych (minumum: 0, maximum dla danej planszy: " << floor(0.06 * (wiersze*kolumny / 2)) <<") ! Sprawdz config.txt" << endl;
			system("Pause");
			exit(1);
		}

		getline(plik, linia);
		pozDk = linia.find(':');
		temp = linia.substr(pozDk + 2, linia.length());
		liczbaStatkow3 = stoi(temp);

		if ((liczbaStatkow3 < 0) || (liczbaStatkow3 > 0.07 * (wiersze*kolumny / 3)))
		{
			cout << "Niepoprawna liczba statkow 3 masztowych (minumum: 0, maximum dla danej planszy: " << floor(0.07 * (wiersze*kolumny / 3)) << ") ! Sprawdz config.txt" << endl;
			system("Pause");
			exit(1);
		}

		getline(plik, linia);
		pozDk = linia.find(':');
		temp = linia.substr(pozDk + 2, linia.length());
		liczbaStatkow4 = stoi(temp);

		if ((liczbaStatkow4 < 0) || (liczbaStatkow4 > 0.08 * (wiersze*kolumny / 4)))
		{
			cout << "Niepoprawna liczba statkow 4 masztowych (minumum: 0, maximum dla danej planszy: " << floor(0.08 * (wiersze*kolumny / 4)) << ") ! Sprawdz config.txt" << endl;
			system("Pause");
			exit(1);
		}

		getline(plik, linia);
		pozDk = linia.find(':');
		temp = linia.substr(pozDk + 2, linia.length());
		liczbaStatkow5 = stoi(temp);

		if ((liczbaStatkow5 < 0) || (liczbaStatkow5 > 0.05 * (wiersze*kolumny / 5)))
		{
			cout << "Niepoprawna liczba statkow 5 masztowych (minumum: 0, maximum dla danej planszy: " << floor(0.05 * (wiersze*kolumny / 5)) << ") ! Sprawdz config.txt" << endl;
			system("Pause");
			exit(1);
		}

	}

	void pokazPlansze(char **plansza)
	{
		char x = 'A';

		cout << "       ";
		for (int i = 0; i < kolumny; i++)
		{
			cout << " " << x << "  ";
			x++;
		}
		cout << endl;

		cout << "      ";
		for (int i = 0; i < kolumny; i++)
		{
			cout << "+---";
		}
		cout << "+" << endl;


		for (int i = 0; i < wiersze; i++)
		{
			cout << setw(5) << i + 1 << " ";
			for (int j = 0; j < kolumny; j++)
			{
				cout << "| " << plansza[i][j] << " ";
			}
			cout << "|" << endl;

			cout << "      ";
			for (int i = 0; i < kolumny; i++)
			{
				cout << "+---";
			}
			cout << "+" << endl;
		}
	}

	void wyczyscPlansze(char **plansza, int wybor)
	{
		if (wybor == 0) //wype³nienie pustymi polami do wstawienia staktów
		{
			for (int i = 0; i < wiersze; i++)
			{
				for (int j = 0; j < kolumny; j++)
					plansza[i][j] = ' ';
			}

		}
		else if (wybor == 1) //wype³nienie gwiazdkami do strzelania
		{
			for (int i = 0; i < wiersze; i++)
			{
				for (int j = 0; j < kolumny; j++)
					plansza[i][j] = '*';
			}
		}
	}

	void stylStatku(int numer)
	{
		switch (numer)
		{
		case 2:
			numerStatku = '2';
			dlugoscStatku = 2;
			liczbaStatkow = liczbaStatkow2;
			break;
		case 3:
			numerStatku = '3';
			dlugoscStatku = 3;
			liczbaStatkow = liczbaStatkow3;
			break;
		case 4:
			numerStatku = '4';
			dlugoscStatku = 4;
			liczbaStatkow = liczbaStatkow4;
			break;
		case 5:
			numerStatku = '5';
			dlugoscStatku = 5;
			liczbaStatkow = liczbaStatkow5;
			break;
		}
	}

	bool sprawdzStatek(int wsz, int kol, int dlugosc, int kierunek, char **plansza)
	{
		int pustePole = 0;
		switch (kierunek)
		{
		case 1:
			for (int i = 0; i < dlugosc; i++) // 1 warunek - kolejne pola do wstawienia sa puste
			{
				if (wsz - i >= 1 && wsz - i <= wiersze && kol >= 1 && kol <= kolumny && plansza[wsz - 1 - i][kol - 1] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{
				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol pod statkiem
				{
					if (wsz == wiersze) //pola pod statkiem poza plansza
					{
						pustePole = 3;
						break;
					}
					if (kol - 1 + i < 1) //lewe pole pod statkiem poza plansza
						pustePole++;
					else if (kol - 1 + i > kolumny) //prawe pole pod statkiem poza plansza
						pustePole++;
					else if(plansza[wsz][kol - 2 + i] == ' ') //sprawdzenie czy puste 3 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach statku
				{
					if (kol - 1 < 1) //pola po lewej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - i][kol - 2] == ' ') //sprawdzenie czy pole po lewej stronie jest puste
						pustePole++;
					if (kol + 1 > kolumny) //pola po prawej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - i][kol] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol nad statkiem
				{
					if (wsz - dlugosc < 1) //pola nad statkiem poza plansza
					{
						pustePole = 3;
						break;
					}
					if (kol - 1 + i < 1)  //lewe pole nad statkiem poza plansza
						pustePole++;
					else if (kol - 1 + i > kolumny)//prawe pole nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - dlugosc][kol - 2 + i] == ' ') //sprawdzenie czy puste 3 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 2:
			for (int i = 0; i < dlugosc; i++) // 1 warunek - kolejne pola do wstawienia sa puste
			{
				if (wsz + i >= 1 && wsz + i <= wiersze && kol >= 1 && kol <= kolumny && plansza[wsz - 1 + i][kol - 1] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{
				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol nad statkiem
				{
					if (wsz == 1) //pola nad statkiem poza plansza
					{
						pustePole = 3;
						break;
					}
					if (kol - 1 + i < 1) //lewe pole pod statkiem poza plansza
						pustePole++;
					else if (kol - 1 + i > kolumny) //prawe pole pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 2][kol - 2 + i] == ' ') //sprawdzenie czy puste 3 pola nad statkiem
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach statku
				{
					if (kol - 1 < 1) //pola po lewej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + i][kol - 2] == ' ') //sprawdzenie czy pole po lewej stronie jest puste
						pustePole++;
					if (kol + 1 > kolumny) //pola po prawej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + i][kol] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol pod statkiem
				{
					if (wsz + dlugosc > wiersze) //pola pod statkiem poza plansza
					{
						pustePole = 3;
						break;
					}
					if (kol - 1 + i < 1)  //lewe pole pod statkiem poza plansza
						pustePole++;
					else if (kol - 1 + i > kolumny) //prawe pole pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + dlugosc][kol - 2 + i] == ' ') //sprawdzenie czy puste 3 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 3:
			for (int i = 0; i < dlugosc; i++)
			{
				if (wsz >= 1 && wsz <= wiersze && kol - i >= 1 && kol - i <= kolumny && plansza[wsz - 1][kol - 1 - i] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{
				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol z prawej strony statku
				{
					if (kol == kolumny) //pola z prawej strony statku poza plansza
					{
						pustePole = 3;
						break;
					}
					if (wsz - 1 + i < 1) //gorne pole z prawej strony statku poza plansza
						pustePole++;
					else if (wsz - 1 + i > wiersze) //dolne pole z prawej strony statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 + i][kol] == ' ') //sprawdzenie czy puste pola z prawej strony statku
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól z góry i z do³u statku
				{
					if (wsz - 1 < 1) //pola nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 2][kol - 1 - i] == ' ') //sprawdzenie czy pole nad statkiem jest puste
						pustePole++;
					if (wsz + 1 > wiersze) //pola pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz][kol - 1 - i] == ' ') //sprawdzenie czy pole pod statkiem jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol z lewej strony statku
				{
					if (kol - dlugosc < 1) //pola z lewej strony statku poza plansza
					{
						pustePole = 3;
						break;
					}
					if (wsz - 1 + i < 1) //gorne pole z lewej strony statku poza plansza
						pustePole++;
					else if (wsz - 1 + i > wiersze) //dolne pole z lewej strony statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 + i][kol - 1 - dlugosc] == ' ') //sprawdzenie czy puste pola z lewej strony statku
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 4:
			for (int i = 0; i < dlugosc; i++)
			{
				if (wsz >= 1 && wsz <= wiersze && kol + i >= 1 && kol + i <= kolumny && plansza[wsz - 1][kol - 1 + i] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{
				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol z lewej strony statku
				{
					if (kol == 1) //pola z lewej strony statku poza plansza
					{
						pustePole = 3;
						break;
					}
					if (wsz - 1 + i < 1) //gorne pole z lewej strony statku poza plansza
						pustePole++;
					else if (wsz - 1 + i > wiersze) //dolne pole z lewej strony statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 + i][kol - 2] == ' ') //sprawdzenie czy puste pola z lewej strony statku
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól z góry i z do³u statku
				{
					if (wsz - 1 < 1) //pola nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 2][kol - 1 + i] == ' ') //sprawdzenie czy pole nad statkiem jest puste
						pustePole++;
					if (wsz + 1 > wiersze) //pola pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz][kol - 1 + i] == ' ') //sprawdzenie czy pole pod statkiem jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 3; i++) //sprawdzanie pol z prawej strony statku
				{
					if (kol + dlugosc > kolumny) //pola z prawej strony statku poza plansza
					{
						pustePole = 3;
						break;
					}
					if (wsz - 1 + i < 1) //gorne pole z prawej strony statku poza plansza
						pustePole++;
					else if (wsz - 1 + i > wiersze) //dolne pole z prawej strony statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 + i][kol - 1 + dlugosc] == ' ') //sprawdzenie czy puste pola z prawej strony statku
						pustePole++;
				}
				if (pustePole != 3)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 5:
			for (int i = 0; i < dlugosc; i++)
			{
				if (wsz - i >= 1 && wsz - i <= wiersze && kol + i >= 1 && kol + i <= kolumny && plansza[wsz - 1 - i][kol - 1 + i] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol pod statkiem
				{
					if (wsz == wiersze) //pola pod statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol - 1 + i < 1) //lewe pole pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz][kol - 2 + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach statku
				{
					if (kol - 1 + i < 1) //pola po lewej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - i][kol - 2 + i] == ' ') //sprawdzenie czy pole po lewej stronie jest puste
						pustePole++;
					if (kol + 1 + i > kolumny) //pola po prawej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - i][kol + i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach(na skos) statku
				{
					if (kol - 1 + i < 1) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz - 1 - i < 1) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 - i][kol - 2 + i] == ' ') //sprawdzenie czy pole po lewej stroniena skos jest puste
						pustePole++;
					if (kol + 1 + i > kolumny) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz + 1 - i > wiersze) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz - i][kol + i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol nad statkiem
				{
					if (wsz - dlugosc < 1) //pola nad statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol - 1 + dlugosc + i > kolumny) //prawe pole nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - dlugosc][kol - 2 + dlugosc + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 6:
			for (int i = 0; i < dlugosc; i++)
			{
				if (wsz - i >= 1 && wsz - i <= wiersze && kol - i >= 1 && kol - i <= kolumny && plansza[wsz - 1 - i][kol - 1 - i] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol pod statkiem
				{
					if (wsz == wiersze) //pola pod statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol + i > kolumny) //prawe pole pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz][kol - 1 + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach statku
				{
					if (kol - 1 - i < 1) //pola po lewej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - i][kol - 2 - i] == ' ') //sprawdzenie czy pole po lewej stronie jest puste
						pustePole++;
					if (kol + 1 - i > kolumny) //pola po prawej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - i][kol - i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach(na skos) statku
				{
					if (kol - 1 - i < 1) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz + 1 - i > wiersze) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz - i][kol - 2 - i] == ' ') //sprawdzenie czy pole po lewej stroniena skos jest puste
						pustePole++;
					if (kol + 1 - i > kolumny) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz - 1 - i < 1) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 - i][kol - i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol nad statkiem
				{
					if (wsz - dlugosc < 1) //pola nad statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol - dlugosc + i < 1) //lewe pole nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 1 - dlugosc][kol - 1 - dlugosc + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 7:
			for (int i = 0; i < dlugosc; i++)
			{
				if (wsz + i >= 1 && wsz + i <= wiersze && kol + i >= 1 && kol + i <= kolumny && plansza[wsz - 1 + i][kol - 1 + i] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol nad statkiem
				{
					if (wsz == 1) //pola nad statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol - 1 + i < 1) //lewe pole nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 2][kol - 2 + i] == ' ') //sprawdzenie czy puste 2 pola nad statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach statku
				{
					if (kol - 1 + i < 1) //pola po lewej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + i][kol - 2 + i] == ' ') //sprawdzenie czy pole po lewej stronie jest puste
						pustePole++;
					if (kol + 1 + i > kolumny) //pola po prawej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + i][kol + i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach(na skos) statku
				{
					if (kol - 1 + i < 1) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz + 1 + i > wiersze) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz + i][kol - 2 + i] == ' ') //sprawdzenie czy pole po lewej stroniena skos jest puste
						pustePole++;
					if (kol + 1 + i > kolumny) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz - 1 + i < 1) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 + i][kol + i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol podd statkiem
				{
					if (wsz + dlugosc > wiersze) //pola pod statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol - 1 + dlugosc + i > kolumny) //prawe pole pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + dlugosc][kol - 2 + dlugosc + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				return true;
			}
			else
				return false;
			break;

		case 8:
			for (int i = 0; i < dlugosc; i++)
			{
				if (wsz + i >= 1 && wsz + i <= wiersze && kol - i >= 1 && kol - i <= kolumny && plansza[wsz - 1 + i][kol - 1 - i] == ' ')
					pustePole++;
			}

			if (pustePole == dlugosc) // spe³niony 1 warunek
			{

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol nad statkiem
				{
					if (wsz == 1) //pola nad statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol + i > kolumny) //prawe pole nad statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 2][kol - 1 + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach statku
				{
					if (kol - 1 - i < 1) //pola po lewej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + i][kol - 2 - i] == ' ') //sprawdzenie czy pole po lewej stronie jest puste
						pustePole++;
					if (kol + 1 - i > kolumny) //pola po prawej stronie statku poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + i][kol - i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < dlugosc; i++) //sprawdzanie pól po bokach(na skos) statku
				{
					if (kol - 1 - i < 1) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz - 1 + i < 1) //pola po lewej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz - 2 + i][kol - 2 - i] == ' ') //sprawdzenie czy pole po lewej stroniena skos jest puste
						pustePole++;
					if (kol + 1 - i > kolumny) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (wsz + 1 + i > wiersze) //pole po prawej stronie na skos statku poza plansza
						pustePole++;
					else if (plansza[wsz + i][kol - i] == ' ') //sprawdzenie czy pole po prawej stronie jest puste
						pustePole++;
				}
				if (pustePole != 2 * dlugosc)
					return false;

				pustePole = 0;
				for (int i = 0; i < 2; i++) //sprawdzanie pol pod statkiem
				{
					if (wsz + dlugosc > wiersze) //pola pod statkiem poza plansza
					{
						pustePole = 2;
						break;
					}
					if (kol - dlugosc + i < 1) //lewe pole pod statkiem poza plansza
						pustePole++;
					else if (plansza[wsz - 1 + dlugosc][kol - 1 - dlugosc + i] == ' ') //sprawdzenie czy puste 2 pola pod statkiem
						pustePole++;
				}
				if (pustePole != 2)
					return false;

				return true;
			}
			else
				return false;
			break;
		}
	}

	void ustawStatkiXMasztowe(char **plansza)
	{
		bool warKol, warWsz, warKier;
		int aktualna = 0, wyborKolumna, wyborWiersz, kierunek, proba = 0;
		string wybor;
		while (aktualna != liczbaStatkow) //wstawienie wszystkich statkow x masztowych
		{
			if (trybWstawianiaStatkow == 1) //rêczne wstawianie statków
			{
				warKol = false;
				warWsz = false;
				warKier = false;
				cout << "Wstawiasz teraz " << numerStatku << " masztowiec!\t" << "Pozostalo: " << liczbaStatkow - aktualna << endl;

				while ((warKol && warWsz) == false)
				{
					cout << "Wybierz pole, w ktoym chcesz zaczepic statek (np. B5): ";
					cin >> wybor;

					wyborKolumna = wybor[0] - 64;
					if ((wyborKolumna >= 1) && (wyborKolumna <= kolumny))
						warKol = true;
					else
					{
						cout << "Niepoprawna kolumna!" << endl;
						warKol = false;
					}

					if (wybor.length() >= 2)
					{
						wyborWiersz = stoi(wybor.substr(1, wybor.length()));
						if ((wyborWiersz >= 1) & (wyborWiersz <= wiersze))
							warWsz = true;
						else
						{
							cout << "Niepoprawny wiersz!" << endl;
							warWsz = false;
						}
					}
					else
					{
						cout << "Podane pole jest zbyt krotkie!" << endl;
						warWsz = false;
					}


				}

				while (warKier == false)
				{
					cout << "Wybierz kierunek ustawienia statku: " << endl;
					cout << "1) GORA" << endl << "2) DOL" << endl << "3) LEWO" << endl << "4) PRAWO" << endl << "5) GORA PRAWO" << endl << "6) GORA LEWO" << endl << "7) DOL PRAWO" << endl << "8) DOL LEWO" << endl;
					cin >> kierunek;

					if ((kierunek >= 1) && (kierunek <= 8))
						warKier = true;
					else
					{
						cout << "Niepoprawny kierunek" << endl;
						warKier = false;
					}
				}


				switch (kierunek)
				{
				case 1:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 1, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 - i][wyborKolumna - 1] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 2:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 2, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 + i][wyborKolumna - 1] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 3:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 3, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1][wyborKolumna - 1 - i] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 4:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 4, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1][wyborKolumna - 1 + i] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 5:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 5, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 - i][wyborKolumna - 1 + i] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 6:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 6, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 - i][wyborKolumna - 1 - i] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 7:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 7, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 + i][wyborKolumna - 1 + i] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				case 8:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 8, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 + i][wyborKolumna - 1 - i] = numerStatku;
						aktualna++;
					}
					else
					{
						cout << "Nie mozna dodac statku!" << endl;
						system("pause");
					}
					break;

				default:
					break;
				}
				system("CLS");
				pokazPlansze(plansza);
			}
			else //losowe wstawienia statkow
			{
				wyborKolumna = rand() % kolumny + 1;
				wyborWiersz = rand() % wiersze + 1;
				kierunek = rand() % 8 + 1;

				switch (kierunek)
				{
				case 1:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 1, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 - i][wyborKolumna - 1] = numerStatku;
						aktualna++;
						if (trybGracza == 1 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 2:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 2, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 + i][wyborKolumna - 1] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 3:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 3, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1][wyborKolumna - 1 - i] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 4:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 4, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1][wyborKolumna - 1 + i] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 5:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 5, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 - i][wyborKolumna - 1 + i] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 6:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 6, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 - i][wyborKolumna - 1 - i] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 7:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 7, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 + i][wyborKolumna - 1 + i] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;

				case 8:
					if (sprawdzStatek(wyborWiersz, wyborKolumna, dlugoscStatku, 8, plansza))
					{
						for (int i = 0; i < dlugoscStatku; i++)
							plansza[wyborWiersz - 1 + i][wyborKolumna - 1 - i] = numerStatku;
						aktualna++;
						if (trybGracza != 2 || pokaz == 1)
						{
							system("CLS");
							pokazPlansze(plansza);
						}
					}
					else
						proba++;
					break;
				default:
					break;
				}

				if (proba == 1000 * (2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5))
				{
					cout << "Przekroczono limit wstawiania statkow! Podejmowanie kolejnej proby..." << endl;
					wyczyscPlansze(plansza, 0);
					system("pause");
					system("cls");
					ustawWszystkieStatki(plansza);
				}

			}

		}
	}

	void ustawWszystkieStatki(char **plansza)
	{
		if (trybGracza == 1)
		{
			cout << "Jak chcesz wstawiac statki?" << endl << "1)Recznie" << endl << "2)Losowo" << endl;
			cin >> trybWstawianiaStatkow;

			while ((trybWstawianiaStatkow != 1) && (trybWstawianiaStatkow != 2))
			{
				cout << "Podano nieprawidlowy numer!" << endl;
				cout << "Jak chcesz wstawiac statki?" << endl << "1)Recznie" << endl << "2)Losowo" << endl;
				cin >> trybWstawianiaStatkow;
			}
			system("cls");
			pokazPlansze(plansza);
		}


		stylStatku(2);
		ustawStatkiXMasztowe(plansza);

		stylStatku(3);
		ustawStatkiXMasztowe(plansza);

		stylStatku(4);
		ustawStatkiXMasztowe(plansza);

		stylStatku(5);
		ustawStatkiXMasztowe(plansza);
	}

	void cheatPlansza(char **planszaStatki, char **planszaStrzaly)
	{
		system("cls");
		cout << "Statki Twojego przeciwnika" << endl << endl;

		char x = 'A';

		cout << "       ";
		for (int i = 0; i < kolumny; i++)
		{
			cout << " " << x << "  ";
			x++;
		}
		cout << endl;

		cout << "      ";
		for (int i = 0; i < kolumny; i++)
		{
			cout << "+---";
		}
		cout << "+" << endl;


		for (int i = 0; i < wiersze; i++)
		{
			cout << setw(5) << i + 1 << " ";
			for (int j = 0; j < kolumny; j++)
			{
				if (planszaStrzaly[i][j] == 'x' || planszaStrzaly[i][j] == 'o')
					cout << "| " << planszaStrzaly[i][j] << " ";
				else
					cout << "| " << planszaStatki[i][j] << " ";
			}
			cout << "|" << endl;

			cout << "      ";
			for (int i = 0; i < kolumny; i++)
			{
				cout << "+---";
			}
			cout << "+" << endl;
		}

		system("pause");
		system("cls");
	}

	int strzelaj(char **planszaStatki, char **planszaStrzaly)
	{
		bool warKol = false, warWsz = false, warGwiazdka = false, cheat = false;
		string wybor;
		int wyborKolumna, wyborWiersz;
		char kolumna;

		pokazPlansze(planszaStrzaly);

		if (trybGracza == 1) // gracz - podaje w jakie pola strzela
		{
			while ((warKol && warWsz && warGwiazdka) == false)
			{
				cout << "Wybierz pole, w ktore chcesz strzelic (np. B5) lub wcisnij *, aby pokazac plansze przeciwnika: ";
				cin >> wybor;

				if (wybor[0] == '*')
				{
					cheat = true;
					cheatPlansza(planszaStatki, planszaStrzaly);
					cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;
					pokazPlansze(planszaStrzaly);
				}
				else
					cheat = false;

				if (cheat == false)
				{
					wyborKolumna = wybor[0] - 64;
					if ((wyborKolumna >= 1) && (wyborKolumna <= kolumny))
						warKol = true;
					else
					{
						cout << "Niepoprawna kolumna!" << endl;
						warKol = false;
					}

					if (wybor.length() >= 2)
					{
						wyborWiersz = stoi(wybor.substr(1, wybor.length()));
						if ((wyborWiersz >= 1) & (wyborWiersz <= wiersze))
							warWsz = true;
						else
						{
							cout << "Niepoprawny wiersz!" << endl;
							warWsz = false;
						}
					}
					else
					{
						cout << "Podane pole jest zbyt krotkie!" << endl;
						warWsz = false;
					}


					if ((warWsz && warKol) == true)
					{
						if (planszaStrzaly[wyborWiersz - 1][wyborKolumna - 1] == '*')
							warGwiazdka = true;
						else
						{
							cout << "W to pole juz strzelales!" << endl;
							warGwiazdka = false;
						}
					}
				}

			}
			kolumna = wyborKolumna + 64;
		}
		else if (trybGracza == 2) // komputer - losuje pole do strzelenia
		{
			while (warGwiazdka == false)
			{
				wyborKolumna = rand() % kolumny + 1;
				wyborWiersz = rand() % wiersze + 1;

				if (planszaStrzaly[wyborWiersz - 1][wyborKolumna - 1] == '*')
					warGwiazdka = true;
				else
					warGwiazdka = false;
			}
			kolumna = wyborKolumna + 64;
			cout << "Komputer strzela w pole: " << kolumna << wyborWiersz << endl;
			system("pause");
		}

		system("cls");

		if (planszaStatki[wyborWiersz - 1][wyborKolumna - 1] == '2' || planszaStatki[wyborWiersz - 1][wyborKolumna - 1] == '3' || planszaStatki[wyborWiersz - 1][wyborKolumna - 1] == '4' || planszaStatki[wyborWiersz - 1][wyborKolumna - 1] == '5')
		{
			planszaStrzaly[wyborWiersz - 1][wyborKolumna - 1] = 'x';
			cout << endl << endl;
			pokazPlansze(planszaStrzaly);
			cout << kolumna << wyborWiersz << " Trafiony statek " << planszaStatki[wyborWiersz - 1][wyborKolumna - 1] << " masztowy! Dodatkowy strzal!" << endl;
			return 1;
		}
		else
		{
			planszaStrzaly[wyborWiersz - 1][wyborKolumna - 1] = 'o';
			cout << endl << endl;
			pokazPlansze(planszaStrzaly);
			cout << kolumna << wyborWiersz << " Pudlo!" << endl;
			return 0;
		}

	}

	void graczKontraGracz()
	{
		int trafioneGracz1 = 0, trafioneGracz2 = 0;

		wyczyscPlansze(planszaGracz1Statki, 0);
		wyczyscPlansze(planszaGracz1Strzaly, 1);
		wyczyscPlansze(planszaGracz2Statki, 0);
		wyczyscPlansze(planszaGracz2Strzaly, 1);

		trybGracza = 1;

		aktualnyGracz = 1;
		cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;
		ustawWszystkieStatki(planszaGracz1Statki);
		cout << "Oto Twoje statki!" << endl;
		system("pause");
		system("cls");

		aktualnyGracz = 2;
		cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;
		ustawWszystkieStatki(planszaGracz2Statki);
		cout << "Oto Twoje statki!" << endl;
		system("pause");
		system("cls");

		while (1)
		{
			aktualnyGracz = 1;
			cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;

			while (strzelaj(planszaGracz2Statki, planszaGracz1Strzaly) == 1)
			{
				trafioneGracz1++;
				system("pause");
				system("cls");

				cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;
				if (trafioneGracz1 == ((2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5)))
				{
					cout << "WYGRYWA GRACZ 1!" << endl;
					system("pause");
					return;
				}
			}

			system("pause");
			system("cls");

			aktualnyGracz = 2;
			cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;

			while (trafioneGracz2 = strzelaj(planszaGracz1Statki, planszaGracz2Strzaly) == 1)
			{
				trafioneGracz2++;
				system("pause");
				system("cls");

				cout << "----------- AKTUALNA TURA: Gracz " << aktualnyGracz << "-----------" << endl << endl;
				if (trafioneGracz2 == ((2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5)))
				{
					cout << "WYGRYWA GRACZ 2!" << endl;
					return;
				}
			}

			system("pause");
			system("cls");
		}
	}

	void graczKontraPC()
	{
		int trafioneGracz = 0, trafionePC = 0;

		wyczyscPlansze(planszaGracz1Statki, 0);
		wyczyscPlansze(planszaGracz1Strzaly, 1);
		wyczyscPlansze(planszaPC1Statki, 0);
		wyczyscPlansze(planszaPC1Strzaly, 1);

		trybGracza = 1;
		cout << "----------- AKTUALNA TURA: Gracz -----------" << endl << endl;
		ustawWszystkieStatki(planszaGracz1Statki);
		cout << "Oto Twoje statki!" << endl;
		system("pause");
		system("CLS");

		trybGracza = 2;
		trybWstawianiaStatkow = 2;
		ustawWszystkieStatki(planszaPC1Statki);
		cout << "----------- AKTUALNA TURA: Komputer -----------" << endl << endl;
		cout << "Komputer ustawil swoje statki!" << endl;
		system("pause");
		system("CLS");

		while (1)
		{
			trybGracza = 1;
			cout << "----------- AKTUALNA TURA: Gracz -----------" << endl << endl;

			while (strzelaj(planszaPC1Statki, planszaGracz1Strzaly) == 1)
			{
				trafioneGracz++;
				system("pause");
				system("cls");

				cout << "----------- AKTUALNA TURA: Gracz -----------" << endl << endl;
				if (trafioneGracz == ((2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5)))
				{
					cout << "WYGRYWA GRACZ!" << endl;
					system("pause");
					return;
				}
			}

			system("pause");
			system("cls");

			trybGracza = 2;
			cout << "----------- AKTUALNA TURA: Komputer -----------" << endl << endl;


			while (strzelaj(planszaGracz1Statki, planszaPC1Strzaly) == 1)
			{
				trafionePC++;
				system("pause");
				system("cls");

				cout << "----------- AKTUALNA TURA: Komputer -----------" << endl << endl;
				if (trafionePC == ((2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5)))
				{
					cout << "WYGRYWA KOMPUTER" << endl;
					return;
				}
			}

			system("pause");
			system("cls");
		}
	}

	void PCKontraPC()
	{
		int trafionePC1 = 0, trafionePC2 = 0;
		pokaz = 1;

		wyczyscPlansze(planszaPC1Statki, 0);
		wyczyscPlansze(planszaPC1Strzaly, 1);
		wyczyscPlansze(planszaPC2Statki, 0);
		wyczyscPlansze(planszaPC2Strzaly, 1);

		trybGracza = 2;
		trybWstawianiaStatkow = 2;

		aktualnyGracz = 1;
		ustawWszystkieStatki(planszaPC1Statki);
		cout << "Komputer " << aktualnyGracz << " ustawil swoje statki!" << endl;
		system("pause");
		system("CLS");

		aktualnyGracz = 2;
		ustawWszystkieStatki(planszaPC2Statki);
		cout << "Komputer " << aktualnyGracz << " ustawil swoje statki!" << endl;
		system("pause");
		system("CLS");

		while (1)
		{
			aktualnyGracz = 1;
			cout << "----------- AKTUALNA TURA: Komputer " << aktualnyGracz << "-----------" << endl << endl;

			while (strzelaj(planszaPC2Statki, planszaPC1Strzaly) == 1)
			{
				trafionePC1++;
				system("pause");
				system("cls");

				cout << "----------- AKTUALNA TURA: Komputer " << aktualnyGracz << "-----------" << endl << endl;
				if (trafionePC1 == ((2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5)))
				{
					cout << "WYGRYWA KOMPUTER !!" << endl;
					system("pause");
					return;
				}
			}

			system("pause");
			system("cls");


			aktualnyGracz = 2;
			cout << "----------- AKTUALNA TURA: Komputer " << aktualnyGracz << "-----------" << endl << endl;

			while (strzelaj(planszaPC1Statki, planszaPC2Strzaly) == 1)
			{
				trafionePC2++;
				system("pause");
				system("cls");

				cout << "----------- AKTUALNA TURA: Komputer " << aktualnyGracz << "-----------" << endl << endl;
				if (trafionePC2 == ((2 * liczbaStatkow2) + (3 * liczbaStatkow3) + (4 * liczbaStatkow4) + (5 * liczbaStatkow5)))
				{
					cout << "WYGRYWA KOMPUTER 2!" << endl;
					return;
				}
			}

			system("pause");
			system("cls");
		}
	}

};


int main()
{
	srand(time(NULL));
	char opcja;
	Statki gra;

	while (1)
	{
		system("cls");
		cout << "Wybierz tryb gry: " << endl << "1) Player vs Player" << endl << "2) Player vs PC" << endl << "3) PC vs PC" << endl << "Q) Quit" << endl;
		cin >> opcja;

		switch (opcja)
		{
		case '1':
			system("cls");
			gra.graczKontraGracz();
			break;
		case '2':
			system("cls");
			gra.graczKontraPC();
			break;
		case '3':
			system("cls");
			gra.PCKontraPC();
			break;
		case 'q':
		case 'Q':
			exit(1);
			break;
		}
	}

	return 0;
}
