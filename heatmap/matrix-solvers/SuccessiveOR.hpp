SuccessiveOR::SuccessiveOR(const MyMatrix<double> &m)
{
    A.resize(m.rows(), m.cols());
    A = m;
    n = A.rows();
}

SuccessiveOR::SuccessiveOR(const SuccessiveOR &bg)
{
    A = bg.A;
    n = bg.size();
}

SuccessiveOR& SuccessiveOR::operator=(SuccessiveOR &bg)
{
    swap(bg, *this);
    return *this;
}

MyVector<double> SuccessiveOR::operator()(const MyVector<double> &b, const double w, const double es)
{
    if(b.size() != A.rows())
        throw std::invalid_argument("b not valid size for SOR to solve Ax = b");
    if(w <= 1 || w >= 2)
        throw std::invalid_argument("omega invalid for successiveor()");
    if(es <= 0)
        throw std::invalid_argument("invalid error threshold for succesiveor()");

    MyVector<double> x(b.size());
    x = x * double(0);

    double ea = 0;
    do
    {
        ea = 0;
        for(int i = 0; i < n; i++)
        {
            double sum = 0;
            for(int j = 0; j < n; j++)
                sum += (i != j) ? A[i][j]*x[j] : 0;

            double x_old = x[i];
            x[i] = x[i] + w * (((b[i] - sum)/ A[i][i]) - x[i]);
            double curr_error = std::abs(x_old - x[i]);
            if(curr_error > ea) ea = curr_error;
        }
    } while(ea > es);
    return x;
}

MyVector<double> SuccessiveOR::operator[](const size_t i) const
{
    if(int(i) < 0 || i >= A.rows())
        throw std::out_of_range("i out of range for successive-or[]");
    return A[i];
}

MyVector<double>& SuccessiveOR::operator[](const size_t i)
{
    if(int(i) < 0 || i >= A.rows())
        throw std::out_of_range("i out of range for successive-or[]");
    return A[i];
}

void swap(SuccessiveOR &a, SuccessiveOR &b)
{
    swap(a.A, b.A);
    std::swap(a.n, b.n);
}