namespace geom
{
	template <typename T> struct Point
	{
		T x, y;
	};


	template <typename T> Point<T> operator -(const Point<T>& pt1, const Point<T>& pt2)
	{
		Point<T> ret;
		ret.x = pt1.x - pt2.x;
		ret.y = pt1.y - pt2.y;

		return ret;
	}

	template <typename T> Point<T> operator +(const Point<T>& pt1, const Point<T>& pt2)
	{
		Point<T> ret;
		ret.x = pt1.x + pt2.x;
		ret.y = pt1.y + pt2.y;

		return ret;
	}

	template <typename T> bool operator ==(const Point<T>& pt1, const Point<T>& pt2)
	{
		if (pt1.x == pt2.x && pt1.y == pt2.y)
			return true;
		return false;
	}


	template <typename T> T VecMul(Point <T> v1, Point <T> v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	template <typename T> T ScalMul(Point <T> v1, Point <T> v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <typename T> std:: vector<Point<T>> GetParalIntersection(Point <T> p1, Point <T> p2, Point <T> p3, Point <T> p4)
	{	
		static bool isFirst = false;

		std:: vector<Point<T>> ret;		
		Point <T> vec1, vec2, vec3, vec4;

		vec1 = p2 - p3;
		vec2 = p1 - p3;

		if (ScalMul(vec1, vec2) < 0) ret.push_back(p3);
		else ret.push_back(p4);

		if (isFirst == true)
		{
			isFirst = false;
			return ret;
		}

		isFirst = true;

		if (GetParalIntersection<T>(p3, p4, p1, p2).size() != 0)
		{
			isFirst = true;
			ret.push_back(GetParalIntersection<T>(p3, p4, p1, p2).front());
		}

		return ret;
	}


	template <typename T> bool CheckIntersection(Point <T> p1, Point <T> p2, Point <T> p3, Point <T> p4)
	{
		static bool isFirst = false;
		static bool isPrevZero = false;


		Point <T> vec1, vec2, vec3, vec4;

		vec1 = p2 - p1;

		vec2 = p3 - p1;

		vec3 = p4 - p1;

		T res1 = VecMul<T>(vec2, vec1);
		T res2 = VecMul<T>(vec1, vec3);

		if (res1 * res2 < 0)
		{
			isFirst = false;
			isPrevZero = false;

			\return false; // По одну сторону от отрезка
		}
		else if (isFirst == false)
		{
			isFirst = true;
			if (res1 * res2 == 0) isPrevZero = true;
			return CheckIntersection<T>(p3, p4, p1, p2); // для первого отрезка точки находятся по разные стороны
		}
		else if (res1 * res2 != 0)
		{
			isFirst = false;
			isPrevZero = false;


			return true; // для обоих отрезков точки по разные стороны => они пересекаются
		}
		else // случай когда все 4 точки лежат на одной прямой
		{
			if (!isPrevZero)
			{
				isFirst = false;
				return true;
			}
			if (GetParalIntersection<T>(p1, p2, p3, p4).size() == 2) // если вернет 2 значит отрезки накладываются друг на друга
			{
				isFirst = false;
				isPrevZero = false;
				return true;
			}
		}
		isFirst = false;
		isPrevZero = false;

		return false;
	}



	 
	template <typename T> std:: vector<Point<T>> GetIntersection(Point <T> p1, Point <T> p2, Point <T> p3, Point <T> p4) //Пересечение может дать 2 точки они будут хранится в векторе
	{
		std:: vector<Point<T>> ret;

		T A1, B1, C1; // параметры прямых для первых двух точек и вторых соответственно
		T A2, B2, C2;
		
		A1 = p1.y - p2.y;
		B1 = p2.x - p1.x;
		C1 = -(A1*p1.x + B1*p1.y);


		A2 = p3.y - p4.y;
		B2 = p4.x - p3.x;
		C2 = -(A2*p3.x + B2*p3.y);

		if (A2*B1 - A1*B2 == 0 && A1*C2 - A2*C1 == 0)
		{
			return GetParalIntersection<T>(p1, p2, p3, p4);
		}

		Point<T> retpt;
		if (A1 != 0)
		{
			retpt.y = (A1*C2 - A2*C1)/(A2*B1 - A1*B2);
			retpt.x = (-C1 - B1*retpt.y)/A1;
		}
		else
		{
			retpt.y = (A1*C2 - A2*C1)/(A2*B1 - A1*B2);
			retpt.x = (-C2 - B2*retpt.y)/A2;	
		}
		ret.push_back(retpt);

		return ret;
	}

}
