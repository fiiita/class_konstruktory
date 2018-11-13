#include <iostream>
#include "CVector.h"


int main(int argv, char *argc[])
{ // n�sleduj�c� k�d vlo�te na za��tek funkce main

	{
		CVector v1; // implicitn� konstruktor � vynuluje v�echny prom�nn�
		{
			CVector x;
		}

		CVector v2(size_t(10)); // konverzn� konstruktor z int � naalokuje m�sto (iCapacity) podle dan�ho parametru. iSize bude stejn�. Pole nulovan�.

		std::cout << "v1.ID()" << v1.ID() << '\n';
		std::cout << "v1.Total()" << v1.Total() << '\n';
		std::cout << "v1.Living()" << v1.Living() << '\n';

		std::cout << "v2.ID()" << v2.ID() << '\n';
		std::cout << "v2.Total()" << v2.Total() << '\n';
		std::cout << "v2.Living()" << v2.Living() << '\n';

		CVector v22(v2);

		CVector v3(5.1); // konverzn� konstruktor z double � naalokuje m�sto pro jeden prvek a do n�j um�st� danou hodnotu.

		CVector v4(10, 8.2); // pou�ijte stejn� konstruktor jako u konverzn�ho pro int (v2) s pou�it�m implicitn�ho parametru. Prvn� parametr zna�� po�et alokovan�ch prvk� - v�echny se napln� danou hodnotou

		CVector v5("{1, 2, 3.4, 5.6, 45.67, 0}"); // konverzn� konstruktor z retezce � form�t jako u Print.

		double InitPole[6] = { 1, 2, 3.4, 5.6, 45.67, 0 };

		CVector v6(6, InitPole, 20); // konstruktor ze tri prvku: iSize, pole hodnot, iCapacity
		// CVector v6(6,InitPole); 
		v6.Print();
		CVector v7[5]; // pro pole se volaj� implicitn� konstruktory

		CVector *pv1 = new CVector; // konstruktor by se m�l volat i p�i alokaci

		CVector *pv2 = new CVector(v4); // p�i alokaci je mo�n� urcit typ pou�it�ho konstruktoru


		// zajist�te korektn� manipulaci s pam�t�

		delete pv1;
		delete pv2;
	}
	std::cout << "\nTotal()" << CVector::Total() << '\n';	// CVector::Total() - volame metodu tridy CVector
	std::cout << "Living()" << CVector::Living() << '\n';
return 0; // po odlad�n� t�to ��sti k�du zakomentujte

}