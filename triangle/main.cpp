#include <iostream>
#include "Poligon.h"




int main()
{
	geom:: Point<float> a1, b1, c1, a2, b2, c2;

	std:: cin >> a1.x >> a1.y >> b1.x >> b1.y >> c1.x >> c1.y >> a2.x >> a2.y >> b2.x >> b2.y >> c2.x >> c2.y;

	Poligon<float> tr1, tr2;

	tr1.AddPt(a1);
	tr1.AddPt(b1);
	tr1.AddPt(c1);


	tr2.AddPt(a2);
	tr2.AddPt(b2);
	tr2.AddPt(c2);

	Poligon<float> inpol(tr1, tr2);

	std:: cout << inpol.Square() << std:: endl;


	return 0;
}