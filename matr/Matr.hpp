

template <typename T>
ProxyMatrix<T>:: ProxyMatrix(std:: vector<T> &v, int width, int num):
width_(width),
str_(v),
num_(num)	
{}


template <typename T>
ConstProxyMatrix<T>:: ConstProxyMatrix(const std:: vector<T> &v, int width, int num):
width_(width),
str_const_(v),
num_(num)	
{}



template <typename T>
T& ProxyMatrix<T>:: operator [](int i)
{
	if (i >= width_)
	{
		std:: cout << "Incorrect iterator\n";
		exit(0);
	}

	return str_[i + width_ * num_];
}


template <typename T>
T ConstProxyMatrix<T>:: operator [](int i) const 
{
	if (i >= width_)
	{
		std:: cout << "Incorrect iterator\n";
		exit(0);
	}

	return str_const_[i + width_ * num_];
}




















template <typename T>
Matr<T>:: Matr(std:: string filename)
{
	std:: ifstream matr_fl(filename);

	matr_fl >> height_ >> width_;

	for(int i = 0; i < height_; ++i)
		for (int j = 0; j < width_; ++j)
		{
			T val;
			matr_fl >> val;
			matr_.push_back(val);
		}
}


template <typename T>
Matr<T>:: Matr(int width, int height):
width_(width),
height_(height)
{}



template <typename T>
void Matr<T>:: transp()
{
	*this = transp_nchanges(); //I think that this doesn't need special operator
}



template <typename T>
Matr<T> Matr<T>:: transp_nchanges() const
{
	Matr<T> new_M(geth(), getw());

	std:: vector<T> t_matr;

	for (int j = 0; j < width_; ++j)
		for (int i = 0; i < height_; ++i)
		{
			new_M.matr_.push_back(matr_[i * width_ + j]);
		}


	return new_M;
}

template <typename T>
void Matr<T>:: print()
{
	for(int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
			std:: cout << matr_[i * width_ + j] << " ";
		std:: cout << std:: endl;
	}
}



template <typename T>

T Matr<T>:: getw() const
{
	return width_;
}

template <typename T>

T Matr<T>:: geth() const
{
	return height_;
}
	





template <typename T> 
Matr<T> operator*(const Matr<T>& left, const Matr<T>& right)
{ 
	if (left.getw() != right.geth())
	{
		std:: cout << "Wrong matrix for mul\n";
		return Matr<T>(0, 0);
	}
	int left_h = left.geth();
	int right_w = right.getw();

	Matr<T> new_right(right.transp_nchanges());

	Matr<T> res_matr(right_w, left_h);

	for (int i = 0; i < left_h; ++i)
	{
		for (int j = 0; j < right_w; ++j)
		{
			T val = 0;
			
			for(int k = 0, n = right.geth(); k < n; ++k) //n is width of left too so we can use it
				val+= left[i][k] * new_right[j][k];
			
			res_matr.matr_.push_back(val);
		}
	}

	return res_matr;

}


template <typename T> 
Matr<T> operator +(const Matr<T>& left, const Matr<T>& right)
{
	if (left.geth() != right.geth() || left.getw() != right.getw())
	{
		std:: cout << "Wrong matrix for sum\n";
		return Matr<T>(0, 0);
	}

	int left_h = left.geth();
	int left_w = left.getw();

	Matr<T> res_matr(left_w, left_h);

	for (int i = 0; i < left_h; ++i)
		for (int j = 0; j < left_w; ++j)
			res_matr.matr_.push_back(left[i][j] + right[i][j]);

	return res_matr;
}








template <typename T>
T Matr<T>:: determinant() const
{
	if (height_ != width_)
	{
		std:: cout << "Error with counting determinant, not a square matrix ";
		return 0;
	}


	Matr<T> new_M(*this);

	for (int i = 0; i < new_M.height_; ++i)
	{
		if (new_M[i][i] == 0)
		{
			bool fl_any_not_zero = false;

			for (int j = i; j < new_M.height_; ++j)
			{
				if (new_M[j][i] != 0)
				{
					fl_any_not_zero = true;
					for (int k = 0; k < new_M.width_; ++k)
						new_M[i][k] += new_M[j][k];
				}
			}

			if (!fl_any_not_zero)
				return 0;
		}

		T sav_val = new_M[i][i];

		for (int j = i; j < new_M.width_; ++j)
		{
			new_M[i][j] /= sav_val;	
		}

		
		for (int j = i + 1; j < new_M.height_; ++j)
		{
			T first_val = new_M[j][i];
			for (int k = i; k < new_M.width_; ++k)
			{
				new_M[j][k] -= new_M[i][k] * first_val;	
			}
		}

		for (int j = i; j < new_M.width_; ++j)
		{
			new_M[i][j] *= sav_val;	
		}

		
	}

	T det = 1.0;


	for (int i = 0; i < new_M.width_; ++i)
		det *= new_M[i][i];

	return det;
}

template <typename T>
ProxyMatrix<T> Matr<T>:: operator [](int i)
{
	if (i >= height_)
	{
		std:: cout << "Incorrect iterator\n";
		exit(0);
	}
	return ProxyMatrix<T>(matr_, width_, i);
} 

template <typename T>
const ConstProxyMatrix<T> Matr<T>:: operator [](int i) const
{
	if (i >= height_)
	{
		std:: cout << "Incorrect iterator C\n";
		exit(0);
	}
	return ConstProxyMatrix<T>(matr_, width_, i);
} 































