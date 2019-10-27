#include <algorithm>
#include <cmath>
#include <vector>
//#include "Poligon.h"



namespace geom
{
	template <typename T> bool PolComp(Point<T> a, Point<T> b)
	{
		if (a.y > 0 && b.y < 0)
			return true;
		if (a.y < 0 && b.y > 0)
			return false;
		return VecMul(b, a) > 0;
	}
}



/* Алгоритм подсчета площади с помощью метода трапеций взят с хабра задача 8  
       Ссылка: https://habr.com/en/post/147691/*/

template <typename T> T Poligon<T>::  Square()
{
	//std:: cout << n << std:: endl;
	T sq = 0;

	for (int i = 0; i < n; i ++)
	{
		sq += (arrpt[(i + 1)%n].x - arrpt[i].x) * (arrpt[(i + 1)%n].y + arrpt[i].y);
	}


	sq = std:: abs(sq);
	sq /= 2;
	return sq;
}




// centre - координаты точки (точно!) находящейся внутри выпуклого многоугольника который класс Poligon описывает

template <typename T> void Poligon<T>:: Setcentre()
{
	int count = 0;
	centre.x = 0;
	centre.y = 0;

	for (int i = 0; i < n; i++)
	{
		centre = centre + arrpt[i];

		count++;
	}

	centre.x /= count;
	centre.y /= count;
}





template <typename T> void Poligon<T>:: SortP()
{
	Setcentre();

	for (int i = 0; i < n; i++)
		arrpt[i] = arrpt[i] - centre; 

	std:: sort(arrpt.begin(), arrpt.end(), geom:: PolComp<T>);

	for (int i = 0; i < n; i++)
	{
		arrpt[i] = centre + arrpt[i];
	}
}




template <typename T> void Poligon<T>:: AddPt(geom:: Point<T> pt)
{
	if (find_pt(pt))
		return;
	arrpt.push_back(pt);
	n++;
	SortP();
}

template<typename T> Poligon<T>:: Poligon():
n(0)
{
	centre.x = 0;
	centre.y = 0;
}



template<typename T> Poligon<T>:: Poligon(Poligon P1, Poligon P2):
n(0)
{
	centre.x = 0;
	centre.y = 0;
	for(int i = 0; i < P1.n; i++)
	{
		//std:: cout << "start" << std:: endl; 
		if (P2.IsPointInsidePol(P1.arrpt[i]))
		{
			AddPt(P1.arrpt[i]);
			//std:: cout << P1.arrpt[i].x << ' ' << P1.arrpt[i].y << std:: endl;
		}
		for(int j = 0; j < P2.n; j++)
		{

			std:: vector<geom:: Point<T>> v;


			//std:: cout << "begin" <<std:: endl;
			if(!CheckIntersection(P1.arrpt[i], P1.arrpt[(i + 1) % P1.n], P2.arrpt[j], P2.arrpt[(j + 1) % P2.n]))
				continue;
			//std:: cout << "end\n" << std:: endl;
			v = GetIntersection(P1.arrpt[i], P1.arrpt[(i + 1) % P1.n], P2.arrpt[j], P2.arrpt[(j + 1) % P2.n]);

			for(auto it : v)
			{
				//std:: cout << P1.arrpt[i].x << ' ' << P1.arrpt[i].y << ' ' << P1.arrpt[(i + 1) % P1.n].x << ' ' << P1.arrpt[(i + 1) % P1.n].y << " x " << P2.arrpt[j].x << ' ' << P2.arrpt[j].y << ' ' << P2.arrpt[(j + 1) % P2.n].x << ' ' << P2.arrpt[(j + 1) % P2.n].y << std:: endl;
				//std:: cout << it.x << ' ' << it.y << std:: endl;
				AddPt(it);
			}
		}
	}
	for (int j = 0; j < P2.n; j++)
		if (P1.IsPointInsidePol(P2.arrpt[j]))
		{
			AddPt(P2.arrpt[j]);
		}
}


template<typename T> bool Poligon<T>:: IsPointInsidePol(geom:: Point<T> pt)
{
	if (n == 1)
		return false;


	T prev = geom:: VecMul(arrpt[1] - arrpt[0], pt - arrpt[0]);
	for (int i = 1; i < n; i++)
	{
		T cur = geom:: VecMul(arrpt[(i + 1) % n] - arrpt[i], pt - arrpt[i]);
		if (cur * prev <= 0)
			return false;
		prev = cur;
	}
	return true;
}

template<typename T> bool Poligon<T>:: find_pt(geom:: Point<T> pt)
{
	for (auto it: arrpt)
	{
		if (pt == it)
		{
			return true;
		}
	}
	return false;
}





















