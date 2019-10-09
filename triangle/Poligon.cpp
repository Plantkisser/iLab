#include <iostream>
#include <cmath>
#include <Geometry.hpp>



namespace geom
{
	template <typename T> bool PolComp(Point<T> a, Point<T> b)
	{
		return VecMul(b, a) > 0;
	}
}





template <typename T> class Poligon
{
public:
	std:: vector<geom:: Point<T>> *arrpt;
	geom:: Point<T> centre;
	int n;
	void Setcentre();
	void AddPt(geom:: Point<T> pt);
	T Square();
	void SortP();
	Poligon();
	Poligon(Poligon P1, Poligon P2);
	~Poligon();
};


/* Алгоритм подсчета площади с помощью метода трапеций взят с хабра задача 8  
       Ссылка: https://habr.com/en/post/147691/*/



template <typename T> Poligon:: T Square()
{
	T sq = 0;

	for (i = 0; i < n-1; i ++)
		sq += (arrpt[i + 1].x - arrpt[i].x) * (arrpt[i + 1].y + arrpt[i].y);


	sq = abs(sq);
	sq /= 2;
	return sq;
}




// centre - координаты точки (точно!) находящейся внутри выпуклого многоугольника который класс Poligon описывает

Poligon:: void Setcentre()
{
	int count = 0;

	for (int i = 0; i < n; i++)
	{
		centre.x += arrpt[i].x;
		centre.y += arrpt[i].y;

		count++;
	}

	centre.x /= count;
	centre.y /= count;
}





Poligon:: void SortP()
{
	Setcentre();

	for (int i = 0; i < n; i++)
	{
		arrpt.y[i] -= centre.y;
		arrpt.x[i] -= centre.x; 
	}

	std:: Sort(arrpt.begin(), arrpt.end(), geom:: PolComp);

	for (int i = 0; i < n; i++)
	{
		arrpt.y[i] += centre.y;
		arrpt.x[i] += centre.x; 
	}
}




template <typename T> Poligon:: void AddPt(geom:: Point<T> pt)
{
	arrpt.push_back(pt);
	n++;
}

Poligon:: Poligon()
n(0),
centre.x(0),
centre.y(0)
{}

Poligon:: ~Poligon()
{
	arrpt.clear();
}

template<typename T> Poligon:: Poligon(Poligon P1, Poligon P2)
n(0),
centre.x(0),
centre.y(0)
{
	for(int i = 0; i < P1.n; i++)
		for(int j = 0; j < P2.n; j++)
		{
			std:: std::vector<geom:: Point<T> v;

			v = GetIntersectiion<T>(P1.arrpt[i], P1.arrpt[(i + 1) % P1.n], P2.arrpt[j], P2.arrpt[(j + 1) % P2.n]);

			for(auto it : v)
				AddPt<T>(it);
		}
}























