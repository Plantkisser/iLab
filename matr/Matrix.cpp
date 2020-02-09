#include "Matr.h"





int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		std:: cout << "Forgot about argument\n";
		exit(0);
	}

	Matr<double> M1(argv[1]);
	Matr<double> M2(argv[2]);

	std:: cout << "Sum:\n";
	(M1 + M2).print();
	std:: cout << std:: endl;
	
	std:: cout << "Mul:\n";
	(M1 * M2).print();
	std:: cout << std:: endl;



	std:: cout << "Det first: " << M1.determinant() << std:: endl;
	std:: cout << "Det second: " << M2.determinant() << std:: endl;


	
	return 0;
}





























