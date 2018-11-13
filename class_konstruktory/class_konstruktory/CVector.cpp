#include <sstream>
#include"CVector.h"

#define TOSTR(a) (#a)		// # - operator preprocesoru...stringifikace...prevod na string

/*
#define SPOJ(a,b)	(a##b)
// SPOJ(prom,1) = 2;
// vysledek:
// prom1 = 2;
*/
const char *ErrorStr[] = { TOSTR(EOk), TOSTR(EWrongSize),
						   TOSTR(ENoMemory), TOSTR(ENotAllocated),
						   TOSTR(EAlreadyAllocated), TOSTR(EInvalidParameter),
							TOSTR(EInternalError) };

size_t CVector::iLiving = 0, CVector::iTotal = 0;

CVector::CVector(const CVector& aVect): iID(iTotal++)
{
	++iLiving;
	iData = nullptr;
	iSize = iCapacity = 0;

	aVect.IntegrityCheck();
	if (aVect.Size())
	{
		try
		{
			Type* data = new Type[aVect.Size()];
			iData = data;
			iSize = iCapacity = aVect.Size();
			for (size_t i = 0; i < iSize; ++i)
				iData[i] = aVect.iData[i];
		}
		catch (const std::bad_alloc& /*e*/)
		{
			throw ENoMemory;
		}
	}
}

CVector::CVector(const char *aStr): iID(iTotal++)
{
	++iLiving;
	iSize = iCapacity = 0;
	iData = nullptr;

	if (!aStr)
		throw EInvalidParameter;

	std::stringstream iss(aStr);
	// std::cout << iss.str();

	char ch = 0;
	iss >> ch;
	if (ch != '{')
		throw EInvalidParameter;
	
	size_t index = 0;
	
	do
	{
		Type value = 0;
		iss >> value;	// nacteni hodnoty

		ch = 0;
		iss >> ch;
		if (ch != '}' && ch != ',')
			throw EInvalidParameter;
		if (index >= iSize)
			Resize(index + 10, 0);
		iData[index] = value;
		++index;
		iSize = index;
	} 
	while (ch != '}');
	Shrink();
}

CVector::CVector(size_t aSize, const Type aData[], size_t aCapacity): iID(iTotal++)
{
	++iLiving;
	iSize = iCapacity = 0;
	iData = nullptr;

	if (aCapacity < aSize)
		throw EWrongSize;

	if (!aData)
		throw EInvalidParameter;
	Allocate(aSize);

	for (size_t i = 0; i < iSize; ++i)
		iData[i] = aData[i];
}

void CVector::Allocate(size_t aSize, Type aValue)			// CVector::Allocate ... rika, ze Allocate je ze tridy CVector
															// v hlavicce nepiseme CVector::Allocate, protoze uz jsme v jmennem prostoru, 
{
	if (iData)	// pokud je pamet ve strukture jiz alokovana
		throw EAlreadyAllocated;
	if (aSize)
	{
		try
		{
			iData = new Type[aSize];
		}
		catch (const std::bad_alloc& /*e*/)
		{
			throw ENoMemory;
		}
	}
	iSize = iCapacity = aSize;

	for (size_t i = 0; i < iSize; ++i)
		iData[i] = aValue;
	// IntegrityCheck();
}

void CVector::Deallocate()
{
	IntegrityCheck();
	delete[] iData;
	iData = nullptr;
	iCapacity = iSize = 0;
}

void CVector::Print() const
{
	std::cout << '{';
	for (size_t i = 0; i < iSize; ++i)
	{
		// std::cout << iData[i] << ", ";
		std::cout << iData[i];
		if (i < iSize - 1)
			std::cout << ", ";
	}
	std::cout << '}';
}

Type& CVector::At(size_t aIndex) const
{
	IntegrityCheck();
	if (aIndex >= iSize)
		throw EWrongSize;
	return iData[aIndex];
}

void CVector::Resize(size_t aNewSize, Type aValue)
{
	IntegrityCheck();
	if (iCapacity < aNewSize)
	{
		Type *data = nullptr;
		try
		{
			data = new Type[aNewSize];
		}
		catch (const std::bad_alloc& /*e*/)
		{
			throw ENoMemory;
		}

		for (size_t i = 0; i < iSize; ++i)
			data[i] = iData[i];

		std::swap(iData, data);
		delete[] data;
		iCapacity = aNewSize;
	}

	for (size_t i = iSize; i < aNewSize; ++i)
		iData[i] = aValue;
	iSize = aNewSize;
}

void CVector::Shrink()
{
	IntegrityCheck();
	if (iSize > iCapacity)
		throw EInternalError;
	if (iSize == iCapacity)
		return;
	if (!iSize && iCapacity)
	{
		delete[] iData;
		iData = nullptr;
		iCapacity = 0;
		return;
	}

	Type *data = nullptr;
	try
	{
		data = new Type[iSize];
	}
	catch (const std::bad_alloc&)
	{
		throw ENoMemory;
	}

	for (size_t i = 0; i < iSize; ++i)
		data[i] = iData[i];

	std::swap(iData, data);
	delete[] data;
	iCapacity = iSize;
}

void CVector::Add(const CVector &aVec1, const CVector &aVec2)
{
	if (!aVec1.Compatible(aVec2))
		throw EWrongSize;

	if (!aVec1.iSize && !aVec2.iSize)
		throw EWrongSize;

	IntegrityCheck();
	Resize(aVec1.iSize);
	for (size_t i = 0; i < iSize; ++i)
		At(i) = aVec1.At(i) + aVec2.At(i);
		//iData[i] = aVec1.iData[i] + aVec2.iData[i];	// rychlejsi
}



bool CVector::Compatible(const CVector &aVec) const
{
	IntegrityCheck();
	aVec.IntegrityCheck();
	return (iSize == aVec.iSize);
}

bool CVector::Equal(const CVector & aVec) const
{
	if (!Compatible(aVec))
		return false;
	for (size_t i = 0; i < iSize; ++i)
		if (iData[i] != aVec.iData[i])
			return false;
	return true;
}