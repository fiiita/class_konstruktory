
#ifndef _CVECTOR_H__
#define _CVECTOR_H__

#include<algorithm>
#include<iostream>
#include "check.h"

extern const char *ErrorStr[];

enum TError
{
	EOk = 0,
	EWrongSize,
	ENoMemory,
	ENotAllocated,
	EAlreadyAllocated,
	EInvalidParameter,
	EInternalError,
};

const size_t KCVectorMinSize = 10;

// typedef double Type;
using Type = double;	// umoznuje, aby paramter zustal v sablone... vytvoreni noveho datoveho typu v C++
// constexpr auto Type = double;


//  Trida slouzi pro zakladni praci s vektory
class CVector
{
	// metoda ( IntegrityCheck() ) patri objektum (Tvector), ma vzdy implicitni parametr *this... 
	// void IntegrityCheck(CVector *this, const CVector &aVect).... *this ukazuje na aVect
	// metoda muze k objektum automaticky
	// vsichni v metode vi, kdo je zavolal... neni treba psat aVect.iSize, ale staci jen iSize

	Type *iData = nullptr;	// pri kompilaci dosadi za Type datovy typ
	size_t iSize = 0;		
	size_t iCapacity = 0;

	// iLiving - pocet aktualne existujicich objektu
	// iTotal - pocet objektu, ktere byly za behu vytvoreny
	// static - promenna zde neni definovana, je zde pouze deklarovana (definovana nekde jinde v programu)
	static size_t iLiving, iTotal;	//tridni promenne
	const size_t iID;				// objektova promenna

	void IntegrityCheck() const
	{
		if (iCapacity < iSize)
			throw EInternalError;
		if (bool(iData) != bool(iCapacity))	// A xor B
			throw EInternalError;
	}

	void Allocate(size_t aSize = KCVectorMinSize, Type aValue = 0);
	void Deallocate();
public:
	// konstruktor
	/*CVector()	
	{
		iData = nullptr;	
		iSize = 0;
		iCapacity = 0;
	}*/

	// Implicitni konstruktor
	// dvojtecka za CVector() ... nez vleze do tela, udela to, co je za dvojteckou
	// tento zapis umoznuje inicializovat konstanty (za dvojteckou)
	CVector(): iData(nullptr),iSize(0),iCapacity(0), iID(iTotal++)	// implicitni konstruktor
	{
		++iLiving;
	}

	// Copy konstruktor
	CVector(const CVector& aVect);	// copy konstruktor

	// Konverzni konstruktor
	CVector(size_t aSize, Type aValue = 0.0): iID(iTotal++)	// konverzni konstruktor
	{
		++iLiving;
		Allocate(aSize,aValue);
	}

	// Konverzni konstruktor
	CVector(Type aValue): iID(iTotal++)
	{
		++iLiving;
		Allocate(1, aValue);
	}

	// Konstruktor z retezce
	CVector(const char *aStr);	// kontruktor z retezce - CONST char *aStr
	
	// Konstruktor z pole prvku
	CVector(size_t aSize, const Type aData[], size_t aCapacity);
	CVector(size_t aSize, const Type aData[]) : CVector(aSize, aData, aSize)
	{}

	// destruktor
	~CVector()
	{
		Deallocate();
		--iLiving;
	}
	
	size_t ID() const
	{
		return iID;
	}

	static size_t Living()
	{
		return iLiving;
	}

	static size_t Total()
	{
		return iTotal;
	}

	// Vraci velikost vektoru
	size_t Size() const
	{
		IntegrityCheck();
		return iSize;
	}

	// Tisk vektoru
	void Print() const;

	// Nastavi / vrati hodnotu prvku vektoru	
	Type& At(size_t aIndex) const;

	// Zmena velikosti vektoru
	void Resize(size_t aNewSize, Type aValue = 0.0);

	// Scitani vektoru
	void Add(const CVector &aVec1, const CVector &aVec2);

	// Zkraceni vektoru
	void Shrink();

	// Kontrola kompatibilni velikosti 2 vektoru	
	bool Compatible(const CVector &aVec) const;

	// Kontrola rovnosti 2 vektoru	
	bool Equal(const CVector &aVec) const;

};	/* class */

#endif // !#ifndef _CVECTOR_H__

