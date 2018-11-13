#include <iostream>
#include "CVector.h"


int main(int argv, char *argc[])
{ // následující kód vložte na zaèátek funkce main

	{
		CVector v1; // implicitní konstruktor – vynuluje všechny promìnné
		{
			CVector x;
		}

		CVector v2(size_t(10)); // konverzní konstruktor z int – naalokuje místo (iCapacity) podle daného parametru. iSize bude stejné. Pole nulované.

		std::cout << "v1.ID()" << v1.ID() << '\n';
		std::cout << "v1.Total()" << v1.Total() << '\n';
		std::cout << "v1.Living()" << v1.Living() << '\n';

		std::cout << "v2.ID()" << v2.ID() << '\n';
		std::cout << "v2.Total()" << v2.Total() << '\n';
		std::cout << "v2.Living()" << v2.Living() << '\n';

		CVector v22(v2);

		CVector v3(5.1); // konverzní konstruktor z double – naalokuje místo pro jeden prvek a do nìj umístí danou hodnotu.

		CVector v4(10, 8.2); // použijte stejný konstruktor jako u konverzního pro int (v2) s použitím implicitního parametru. První parametr znaèí poèet alokovaných prvkù - všechny se naplní danou hodnotou

		CVector v5("{1, 2, 3.4, 5.6, 45.67, 0}"); // konverzní konstruktor z retezce – formát jako u Print.

		double InitPole[6] = { 1, 2, 3.4, 5.6, 45.67, 0 };

		CVector v6(6, InitPole, 20); // konstruktor ze tri prvku: iSize, pole hodnot, iCapacity
		// CVector v6(6,InitPole); 
		v6.Print();
		CVector v7[5]; // pro pole se volají implicitní konstruktory

		CVector *pv1 = new CVector; // konstruktor by se mìl volat i pøi alokaci

		CVector *pv2 = new CVector(v4); // pøi alokaci je možné urcit typ použitého konstruktoru


		// zajistìte korektní manipulaci s pamìtí

		delete pv1;
		delete pv2;
	}
	std::cout << "\nTotal()" << CVector::Total() << '\n';	// CVector::Total() - volame metodu tridy CVector
	std::cout << "Living()" << CVector::Living() << '\n';
return 0; // po odladìní této èásti kódu zakomentujte

}