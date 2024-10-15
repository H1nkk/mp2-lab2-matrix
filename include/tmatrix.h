// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	int sz;
	T* pMem;
public:
	TDynamicVector(int size = 1) : sz(size)
	{
		if (sz <= 0) {
			throw out_of_range("Vector size should be greater than zero");
		}
		if (sz > MAX_VECTOR_SIZE) {
			throw out_of_range("Vector size should be less than 100000001");
		}
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, int s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector vector requires non-nullptr arg");
		if (sz > MAX_VECTOR_SIZE) {
			throw out_of_range("Vector size should be less than 100000001");
		}
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v) : TDynamicVector(v.pMem, v.sz) {}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		sz = v.sz;
		pMem = v.pMem;
		v.pMem = nullptr;
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (sz != v.sz) {
			T* tmp = new T[v.sz]();
			delete[] pMem;
			sz = v.sz;
			pMem = tmp;
		}
		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		sz = v.sz;
		swap(pMem, v.pMem);
		return *this;
	}

	int size() const noexcept { return sz; }

	// индексация
	T& operator[](int ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(int ind)
	{
		if (ind < 0) {
			throw out_of_range("Vector index should be non-negative");
		}
		if (ind >= sz) {
			throw out_of_range("Vector index out of range");
		}
		return pMem[ind];
	}
	const T& at(int ind) const
	{
		if (ind < 0) {
			throw out_of_range("Vector index should be non-negative");
		}
		if (ind >= sz) {
			throw out_of_range("Vector index out of range");
		}
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz) return false;
		for (int i = 0; i < sz; i++) {
			if (v.pMem[i] != pMem[i]) return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz) return true;
		for (int i = 0; i < sz; i++) {
			if (v.pMem[i] != pMem[i]) return true;
		}
		return false;
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector res(*this);
		for (int i = 0; i < sz; i++) {
			res.pMem[i] += val;
		}
		return res;
	}
	TDynamicVector operator-(T val)
	{
		TDynamicVector res(*this);
		for (int i = 0; i < sz; i++) {
			res.pMem[i] -= val;
		}
		return res;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector res(*this);
		for (int i = 0; i < sz; i++) {
			res.pMem[i] *= val;
		}
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (v.sz != sz) {
			throw invalid_argument("Cannot sum vectors of different sizes");
		}
		TDynamicVector res(*this);
		for (int i = 0; i < sz; i++) {
			res.pMem[i] += v.pMem[i];
		}
		return res;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (v.sz != sz) {
			throw invalid_argument("Cannot subtract vectors of different sizes");
		}
		TDynamicVector res(*this);
		for (int i = 0; i < sz; i++) {
			res.pMem[i] -= v.pMem[i];
		}
		return res;
	}
	T operator*(const TDynamicVector& v) // removed noexcept because multiplication of vectors with different sizes must throw an exception
	{
		if (v.sz != sz) {
			throw invalid_argument("Cannot multiply vectors of different sizes");
		}
		T res = T();
		for (int i = 0; i < sz; i++) {
			res += pMem[i] * v[i];
		}
		return res;

	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(int s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s > MAX_MATRIX_SIZE) {
			throw out_of_range("Matrix size should be less than 10001");
		}
		if (s <= 0) {
			throw out_of_range("Matrix size should be greater than zero");
		}
		for (int i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}
	TDynamicMatrix(const TDynamicMatrix<T>& m): TDynamicVector<TDynamicVector<T>>(m.sz) {
		for (int i = 0; i < sz; i++)
			pMem[i] = m[i];

	}
	using TDynamicVector<TDynamicVector<T>>::operator[];
	using TDynamicVector<TDynamicVector<T>>::at;
	int size() const noexcept { return sz; }

	// сравнение
	bool operator==(const TDynamicMatrix<T>& m) const noexcept
	{
		if (m.sz != sz) return false;
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				if (pMem[i][j] != m.pMem[i][j]) return false;

		return true;
	}
	bool operator!=(const TDynamicMatrix<T>& m) const noexcept
	{
		if (m.sz != sz) return true;
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				if (pMem[i][j] != m.pMem[i][j]) return true;

		return false;
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix<T> tmp = *this; // aaaaaaaaaaaaaaaaaaaaaaaaaaaaa проверить норм ли работает копирование указателей
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				tmp.pMem[i][j] *= val;
		return tmp;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		int vsz = v.size();
		if (vsz != sz) {
			throw invalid_argument("Cannot multiply vector and matrix of different sizes");
		}
		TDynamicVector<T> tmp(v.size());
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++) {
				tmp[i] += v[j] * pMem[j][i];
			}
		return tmp;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz) {
			throw invalid_argument("Cannot sum matrices of different sizes");
		}
		TDynamicMatrix<T> tmp(sz);
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				tmp[i][j] = pMem[i][j] + m.pMem[i][j];

		return tmp;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz) {
			throw invalid_argument("Cannot subtract matrices of different sizes");
		}
		TDynamicMatrix<T> tmp(sz);
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				tmp[i][j] = pMem[i][j] - m.pMem[i][j];

		return tmp;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz) {
			throw invalid_argument("Cannot multiply matrices of different sizes");
		}
		TDynamicMatrix<T> tmp(sz);
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				for (int k = 0; k < sz; k++)
					tmp[i][j] += pMem[i][k] * m.pMem[k][j];

		return tmp;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (int i = 0; i < v.sz; i++) {
			for (int j = 0; j < v.sz; j++) {
				istr >> v[i][j];
			}
		}
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (int i = 0; i < v.sz; i++) {
			for (int j = 0; j < v.sz; j++)
				ostr << v[i][j] << ' ';
			ostr << endl;
		}
		return ostr;
	}
};

#endif
