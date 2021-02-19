CholeskyDecomp::CholeskyDecomp(const MyMatrix<double> &m)
{
    A.resize(m.rows(), m.cols());
    decompose(m, A);
    n = A.rows();
}

CholeskyDecomp::CholeskyDecomp(const CholeskyDecomp &cd)
{
    A = cd.A;
    n = cd.size();
}

CholeskyDecomp& CholeskyDecomp::operator=(CholeskyDecomp &cd)
{
    swap(cd, *this);
    return *this;
}

MyVector<double> CholeskyDecomp::operator()(MyVector<double> b)
{
    if(n != int(b.size()))
        throw std::invalid_argument("A, b in cholesky() different sizes");
    
    // solve system [Ly = b] for y, where L = A, y new vector, b is param
    MyVector<double> y(b.size());
    for(int i = 0; i < n; i++)
    {
        double s = 0;
        for(int j = 0; j < i; j++)
            s += (A[i][j] * y[j]);
        y[i] = (b[i] - s) / A[i][i];
    }

    // solve system [L(t)x = y], where L(t) is transpose of L, for x
    MyMatrix<double> LT = A.transpose();
    MyVector<double> x(b.size());
    for(int i = n - 1; i >= 0; i--)
    {
        x[i] = y[i];
        for(int j = i + 1; j < n; j++)
            x[i] -= LT[i][j] * x[j];
        x[i] /= LT[i][i];
    }

    // readjust A matrix so calling object can be reused
    A.transpose();

    // return completed x values after second back sub
    return x;
}

void CholeskyDecomp::decompose(const MyMatrix<double> &a, MyMatrix<double> &l)
{
    for(int k = 0; k < int(l.rows()); k++)
    {
        for(int i = 0; i < k; i++)
        {
            double sum = 0;
            for(int j = 0; j < i; j++)
                sum += l[i][j] * l[k][j];
            l[k][i] = (a[k][i] - sum) / l[i][i];
        }

        double sum = 0;
        for(int j = 0; j < k; j++)
            sum += l[k][j] * l[k][j];
        l[k][k] = std::sqrt(a[k][k] - sum);
    }
}

MyVector<double> CholeskyDecomp::operator[](const size_t i) const
{
    if(int(i) < 0 || i >= A.rows())
        throw std::out_of_range("i out of range for cholesky[]");
    return A[i];
}

MyVector<double>& CholeskyDecomp::operator[](const size_t i)
{
    if(int(i) < 0 || i >= A.rows())
        throw std::out_of_range("i out of range for cholesky[]");
    return A[i];
}

void swap(CholeskyDecomp &a, CholeskyDecomp &b)
{
    swap(a.A, b.A);
    std::swap(a.n, b.n);
}

ostream& operator<<(ostream &out, const CholeskyDecomp &cd)
{
    out << cd.A;
    return out;
}