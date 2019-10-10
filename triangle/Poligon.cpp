#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include "Geometry.cpp"



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





template <typename T> class Poligon
{
public:
	std:: vector<geom:: Point<T>> arrpt;
	geom:: Point<T> centre;
	int n;
	void Setcentre();
	void AddPt(geom:: Point<T> pt);
	T Square();
	void SortP();
	bool IsPointInsidePol(geom:: Point<T> pt);
	Poligon();
	Poligon(Poligon P1, Poligon P2);
	~Poligon();
	bool find_pt(geom:: Point<T> pt);
};





/* Алгоритм подсчета площади с помощью метода трапеций взят с хабра задача 8  
       Ссылка: https://habr.com/en/post/147691/*/

template <typename T> T Poligon<T>::  Square()
{
	T sq = 0;

	for (int i = 0; i < n; i ++)
	{
		//std:: cout << arrpt[i].x << " " << arrpt[i].y << '\n';
		sq += (arrpt[(i + 1)%n].x - arrpt[i].x) * (arrpt[(i + 1)%n].y + arrpt[i].y);
	}


	sq = abs(sq);
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
	//std:: cout << pt.x << ' ' << pt.y << std:: endl;
	if (find_pt(pt))
		return;
	//std:: cout <<"**";
	arrpt.push_back(pt);
	n++;
	SortP();
	//std:: cout << centre.x << ' ' << centre.y << '\n';
}

template<typename T> Poligon<T>:: Poligon():
n(0)
{
	centre.x = 0;
	centre.y = 0;
}

template<typename T> Poligon<T>:: ~Poligon()
{
	arrpt.clear();
}

template<typename T> Poligon<T>:: Poligon(Poligon P1, Poligon P2):
n(0)
{
	centre.x = 0;
	centre.y = 0;
	for(int i = 0; i < P1.n; i++)
	{
		if (P2.IsPointInsidePol(P1.arrpt[i]))
		{
			AddPt(P1.arrpt[i]);
			//std:: cout << P1.arrpt[i].x << ' ' << P1.arrpt[i].y << std:: endl;
		}
		for(int j = 0; j < P2.n; j++)
		{

			std:: vector<geom:: Point<T>> v;

			if(!CheckIntersection(P1.arrpt[i], P1.arrpt[(i + 1) % P1.n], P2.arrpt[j], P2.arrpt[(j + 1) % P2.n]))
				continue;

			v = GetIntersection(P1.arrpt[i], P1.arrpt[(i + 1) % P1.n], P2.arrpt[j], P2.arrpt[(j + 1) % P2.n]);

			for(auto it : v)
			{
				//std:: cout << it.x << ' ' << it.y << std:: endl;
				AddPt(it);
			}
		}
	}
	for (int j = 0; j < P2.n; j++)
		if (P1.IsPointInsidePol(P2.arrpt[j]))
		{
			//std:: cout << P2.arrpt[j].x << ' ' << P2.arrpt[j].y << std:: endl;
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
	//std:: cout << "IPIP " << pt.x << ' ' << pt.y << '\n';
	return true;
}

template<typename T> bool Poligon<T>:: find_pt(geom:: Point<T> pt)
{
	for (auto it: arrpt)
	{
		if (pt == it)
		{
			//std:: cout << "**\n";
			return true;
		}
	}
	//std:: cout << "*\n";
	return false;
}





















