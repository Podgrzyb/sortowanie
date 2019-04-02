// Sortowanie.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

template < class typ >
void quicksort(typ *tab, int left, int right)
{
	typ pivot = tab[(left + right) / 2];
	int i, j;
	typ x;
	i = left;
	j = right;

	do
	{
		while (tab[i] < pivot) i++;
		while (tab[j] > pivot) j--;
		if (i <= j)
		{
			x = tab[i];
			tab[i] = tab[j];
			tab[j] = x;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > left) quicksort(tab, left, j);
	if (i < right) quicksort(tab, i, right);
}
template < class typ >
void merge(typ *arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	typ *L=new typ[n1], *R=new typ[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
template < class typ >
void mergeSort(typ *arr, int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

template <class Item>
void Exchange(Item *Array, long i, long j)
{
	Item temp;
	temp = Array[i];
	Array[i] = Array[j];
	Array[j] = temp;
}
template <class Item>
void MedianOfThree(Item *Array, long &L, long &R)
{
	if (Array[++L - 1] > Array[--R])
		Exchange(Array, L - 1, R);
	if (Array[L - 1] > Array[R / 2])
		Exchange(Array, L - 1, R / 2);
	if (Array[R / 2] > Array[R])
		Exchange(Array, R / 2, R);
	Exchange(Array, R / 2, R - 1);
}
template <class Item>
long Partition(Item *Array, long L, long R)
{
	long i, j;
	if (R >= 3)
		MedianOfThree(Array, L, R);
	for (i = L, j = R - 2; ; )
	{
		for (; Array[i] < Array[R - 1]; ++i);
		for (; j >= L && Array[j] > Array[R - 1]; --j);
		if (i < j)
			Exchange(Array, i++, j--);
		else break;
	}
	Exchange(Array, i, R - 1);
	return i;
}


template <class Item>
void Heapify(Item *Array, long i, long N)
{
	long j;
	while (i <= N / 2)
	{
		j = 2 * i;
		if (j + 1 <= N && Array[j + 1] > Array[j])
			j = j + 1;
		if (Array[i] < Array[j])
			Exchange(Array, i, j);
		else break;
		i = j;
	}
}
template <class Item>
void Heap_Sort(Item *Array, long N)
{
	long i;
	for (i = N / 2; i > 0; --i)
		Heapify(Array - 1, i, N);
	for (i = N - 1; i > 0; --i)
	{
		Exchange(Array, 0, i);
		Heapify(Array - 1, 1, i);
	}
}
template <class Item>
void Insertion_Sort(Item *Array, long N)
{
	long i, j;
	Item temp;
	for (i = 1; i < N; ++i)
	{
		temp = Array[i];
		for (j = i; j > 0 && temp < Array[j - 1]; --j)
			Array[j] = Array[j - 1];
		Array[j] = temp;
	}
}
template <class Item>
void IntroSort(Item *Array, long N, int M)
{
	long i;
	if (M <= 0)
	{
		Heap_Sort(Array, N);
		return;
	}
	i = Partition(Array, 0, N);
	if (i > 9)
		IntroSort(Array, i, M - 1);
	if (N - 1 - i > 9)
		IntroSort(Array + i + 1, N - 1 - i, M - 1);
}

template <class Item>
void Hybrid_Introspective_Sort(Item *Array, long N)
{
	IntroSort(Array, N, (int)floor(2 * log(N) / log(2)));
	Insertion_Sort(Array, N);
}

template<typename T>
bool checkIfCorrect(std::vector<T> table, const std::vector<T>& result)
{
	std::sort(table.begin(), table.end());
	return (table == result);
}

template<typename T, size_t N>
bool checkIfCorrect(const T(&table)[N], const  T(&result)[N])
{
	T sorted[N];
	std::copy(table, table + N, sorted);
	std::sort(std::begin(sorted), std::end(sorted));

	return std::equal(std::begin(sorted), std::end(sorted),
		std::begin(result), std::end(result));
}
template <class T>
void sprawdzenie(T *sortedTab,int n)
{
	
	for (int i = 0; i < n - 1; i++)
	{
		if (sortedTab[i] > sortedTab[i + 1])
			cout << "zle sortuje";
	}
}
int main()
{
	srand(time(NULL));

	std::vector<int> nVector{ 10000, 50000, 100000,500000, 1000000 };
	const int nbOfExperiments = 2;
	int liczba;
	int *pom;
	int *pom2;
	int *pom3;
	int *tablica;
	int *tablica2;
	int *tablica3;
	int *tablica4;
	int *tablica5;
	int *tablica6;
	int *tablica7;
	int *tablica8;
	ofstream plik1("dane1q.txt");
	ofstream plik2("dane1m.txt");
	ofstream plik3("dane1i.txt");

	

	/*Badanie dla każdego rozmiaru tablicy n*/
	for (const auto& n : nVector)
	{
		pom = new int[n];
		pom2 = new int[n];
		pom3 = new int[n];
		tablica = new int[n];
		tablica2 = new int[n];
		tablica3 = new int[n];
		tablica4 = new int[n];
		tablica5 = new int[n];
		tablica6 = new int[n];
		tablica7 = new int[n];
		tablica8 = new int[n];
		cout << "wielkosc:" << n<<endl;
		/*Wykonanie eksperymentu nbOfExperiments razy dla tablic o rozmiarze n*/
		for (int i = 0; i < nbOfExperiments; ++i)
		{
			for (int i = 0; i < n; i++)
			{
				liczba = rand() % n;
				tablica[i] = liczba;
			}
			
			for (int i = 0; i < n; i++)
			{
				if (i > n / 4)
				{
					liczba = rand() % n;
					tablica2[i] = liczba;
				}
				else
					tablica2[i] = i;
			}
			
			for (int i = 0; i < n; i++)
			{
				if (i > n / 2)
				{
					liczba = rand() % n;
					tablica3[i] = liczba;
				}
				else
					tablica3[i] = i;
			}
			
			for (int i = 0; i < n; i++)
			{
				if (i > 0.75*n)
				{
					liczba = rand() % n;
					tablica4[i] = liczba;
				}
				else
					tablica4[i] = i;
			}
			
			for (int i = 0; i < n; i++)
			{
				if (i > 0.95*n)
				{
					liczba = rand() % n;
					tablica5[i] = liczba;
				}
				else
					tablica5[i] = i;
			}
			
			for (int i = 0; i < n; i++)
			{
				if (i > 0.99*n)
				{
					liczba = rand() % n;
					tablica6[i] = liczba;
				}
				else
					tablica6[i] = i;
			}
			
			for (int i = 0; i < n; i++)
			{
				if (i > 0.997*n)
				{
					liczba = rand() % n;
					tablica7[i] = liczba;
				}
				else
					tablica7[i] = i;
			}
			
			for (int i = n; i>0; i--)
			{
				tablica8[i-1] = i;
			}
			


			

			/*
			Przygotowanie tablic o rozmiarze n:
			•wszystkie elementy tablicy losowe,
			• 25%, 50%, 75%, 95%, 99%, 99,7% początkowych elementów tablicy jest już posortowanych,
			• wszystkie elementy tablicy już posortowane ale w odwrotnej kolejności.
			*/
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica[i];
				pom2[i] = tablica[i];
				pom3[i] = tablica[i];
			}

			/* Mierzenie czasu trwania jednego eksperymentu
			Poniższy fragment wykonywany jest wielokrotnie
			osobno dla każdej kombinacji algorytmu i tablicy wejściowej
			//pojedyncze wykonanie jednego algorytmu sortowania dla jednej tablicy
			//sortowanie na kopii tablic wejściowych
			*/
			// **TABLICA 1**
			
			//quick
			auto start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = end - start; // w sekundach https://en.cppreference.com/w/cpp/chrono/duration
			double durationTime = diff.count(); // zmierzony czas zapisać do pliku lub zagregować, zapisać liczbę badanych elementów
			plik1 <<n<<" 1 " <<durationTime << endl;
			//sprawdzenie(pom, n); // sprawdzenie poprawnosci sortowania
			
			
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 1 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 1 " << durationTime << endl;
			
			// **TABLICA 2**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica2[i];
				pom2[i] = tablica2[i];
				pom3[i] = tablica2[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start; 
			durationTime = diff.count(); 
			plik1 << n << " 2 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 2 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 2 " << durationTime << endl;
			
			// **TABLICA 3**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica3[i];
				pom2[i] = tablica3[i];
				pom3[i] = tablica3[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik1 << n << " 3 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 3 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 3 " << durationTime << endl;
			 
			// **TABLICA 4**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica3[i];
				pom2[i] = tablica3[i];
				pom3[i] = tablica3[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik1 << n << " 4 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 4 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 4 " << durationTime << endl;
			
			// **TABLICA 5**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica5[i];
				pom2[i] = tablica5[i];
				pom3[i] = tablica5[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik1 << n << " 5 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 5 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 5 " << durationTime << endl;
			// **TABLICA 6**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica6[i];
				pom2[i] = tablica6[i];
				pom3[i] = tablica6[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik1 << n << " 6 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 6 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 6 " << durationTime << endl;
			
			// **TABLICA 7**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica7[i];
				pom2[i] = tablica7[i];
				pom3[i] = tablica7[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik1 << n << " 7 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 7 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 7 " << durationTime << endl;
			// **TABLICA 8**
			for (int i = 0; i < n; i++) //kopiowanie tablicy
			{
				pom[i] = tablica8[i];
				pom2[i] = tablica8[i];
				pom3[i] = tablica8[i];
			}
			//quick
			start = std::chrono::system_clock::now();
			quicksort<int>(pom, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik1 << n << " 8 " << durationTime << endl;
			//merge
			start = std::chrono::system_clock::now();
			mergeSort<int>(pom2, 0, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik2 << n << " 8 " << durationTime << endl;
			//intro
			start = std::chrono::system_clock::now();
			Hybrid_Introspective_Sort<int>(pom3, n);
			end = std::chrono::system_clock::now();
			diff = end - start;
			durationTime = diff.count();
			plik3 << n << " 8 " << durationTime << endl;
			//Sprawdzenie poprawności działania algorytmu
			
		}
		/*
		delete[] pom;
		delete[] pom2;
		delete[] pom3;
		delete[] tablica;
		delete[] tablica2;
		delete[] tablica3;
		delete[] tablica4;
		delete[] tablica5;
		delete[] tablica6;
		delete[] tablica7;
		delete[] tablica8;
	*/
		
	}
	/*
	delete[] pom;
	delete[] pom2;
	delete[] pom3;
	delete[] tablica;
	delete[] tablica2;
	delete[] tablica3;
	delete[] tablica4;
	delete[] tablica5;
	delete[] tablica6;
	delete[] tablica7;
	delete[] tablica8;
	pom = nullptr;
	pom2 = nullptr;
	pom3 = nullptr;
	tablica = nullptr;
	tablica2 = nullptr;
	tablica3 = nullptr;
	tablica4 = nullptr;
	tablica5 = nullptr;
	tablica6 = nullptr;
	tablica7 = nullptr;
	tablica8 = nullptr;
	*/
	return 0;
	
}



// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln


