#pragma once

#include <iostream>
#include <fstream>
#include <vector>


template <typename T>
class ProxyMatrix
{
	std::vector<T>& str_;
	int width_, num_;
	public:
	ProxyMatrix(std:: vector<T> &v, int width, int num);

	T& operator [](int i);
};

template <typename T>
class ConstProxyMatrix
{
	const std::vector<T>& str_const_;
	int width_, num_;
	public:
	ConstProxyMatrix(const std:: vector<T> &v, int width, int num);

	T operator [](int i) const;
};



template <typename T>
class Matr
{
	int width_;
	int height_;
public:
	T getw() const;
	T geth() const;

	std::vector<T> matr_;

	Matr(std:: string filename);
	Matr(int width, int height);

	void transp();
	Matr<T> transp_nchanges() const; // this function doesn't change current matrix
	T determinant() const; // because of this function typename must be float or double!!!!!!!!!

	void print();


	ProxyMatrix<T> operator [](int i);
	const ConstProxyMatrix<T> operator [](int i) const;
};



template <typename T> 
Matr<T> operator*(const Matr<T>& left, const Matr<T>& right);

template <typename T> 
Matr<T> operator +(const Matr<T>& left, const Matr<T>& right);


#include "Matr.hpp"