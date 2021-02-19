template <typename T>
MyComplex<T>::MyComplex(const T r, const T i)
{
    a = r;
    b = i;
}

template <typename T>
MyComplex<T>::MyComplex(const MyComplex<T> &c)
{
    a = c.real();
    b = c.imag();
}

template <typename T>
void swap(MyComplex<T> &c1, MyComplex<T> &c2)
{
    std::swap(c1.a, c2.a);
    std::swap(c1.b, c2.b);
}

template <typename T>
MyComplex<T>& MyComplex<T>::operator=(MyComplex<T> c)
{
    swap(*this, c);
    return *this;
}

template <typename T>
MyComplex<T>& MyComplex<T>::operator-() const
{
    return MyComplex<T>(-real(), imag());
}

template <typename T>
MyComplex<T>& MyComplex<T>::operator!() const
{
    return MyComplex<T>(real(), -imag());
}

template <typename T>
T MyComplex<T>::operator~() const
{
    return std::sqrt((real() * real()) + (imag() * imag()));
}

template <typename T>
ostream& operator<<(ostream &out, const MyComplex<T> &src)
{
    if(src.real() == 0 && src.imag() != 0)
        std::cout << src.imag() << "i";
    else if(src.real() != 0 && src.imag() == 0)
        std::cout << src.real();
    else if(src.real() == 0 && src.imag() == 0)
        std::cout << src.real();
    else
    {
        if(src.imag() > 0)
            std::cout << src.real() << " + " << src.imag() << "i";
        else
            std::cout << src.real() << " - " << -src.imag() << "i";
    }
    return out;
}

template <typename T>
MyComplex<T> operator+(const MyComplex<T> &a, const MyComplex<T> &b)
{
    return MyComplex<T>(a.real() + b.real(), a.imag() + b.imag());
}

template <typename T>
MyComplex<T> operator-(const MyComplex<T> &a, const MyComplex<T> &b)
{
    return MyComplex<T>(a.real() - b.real(), a.imag() - b.imag());
}

template <typename T>
MyComplex<T> operator*(const MyComplex<T> &a, const MyComplex<T> &b)
{
    return MyComplex<T>(a.real() * b.real() - a.imag() * b.imag(), 
        a.real() * b.imag() + a.imag() * b.real());
}