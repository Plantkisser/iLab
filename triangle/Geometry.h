#pragma once
#include <vector>

namespace geom
{
	template <typename T> struct Point
	{
		T x, y;
	};


	template <typename T> Point<T> operator -(const Point<T>& pt1, const Point<T>& pt2);

	template <typename T> Point<T> operator +(const Point<T>& pt1, const Point<T>& pt2);

	template <typename T> bool operator ==(const Point<T>& pt1, const Point<T>& pt2);

	template <typename T> T VecMul(Point <T> v1, Point <T> v2);

	template <typename T> T ScalMul(Point <T> v1, Point <T> v2);

	template <typename T> std:: vector<Point<T>> GetParalIntersection(Point <T> p1, Point <T> p2, Point <T> p3, Point <T> p4);

	template <typename T> bool CheckIntersection(Point <T> p1, Point <T> p2, Point <T> p3, Point <T> p4);

	template <typename T> std:: vector<Point<T>> GetIntersection(Point <T> p1, Point <T> p2, Point <T> p3, Point <T> p4);

}

#include "Geometry.hpp"
