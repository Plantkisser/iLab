#pragma once
#include <vector>
#include "Geometry.h"



namespace geom
{
	template <typename T> bool PolComp(Point<T> a, Point<T> b);
}




template <typename T> class Poligon
{
private:
	void Setcentre();
	std:: vector<geom:: Point<T>> arrpt;
	geom:: Point<T> centre;
	bool find_pt(geom:: Point<T> pt);
	int n;


public:
	void AddPt(geom:: Point<T> pt);

	T Square();

	void SortP();

	bool IsPointInsidePol(geom:: Point<T> pt);

	Poligon();

	Poligon(Poligon P1, Poligon P2);

	~Poligon();
};

#include "Poligon.hpp"















