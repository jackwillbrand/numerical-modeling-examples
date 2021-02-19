template <typename T>
MyVector<T>::MyVector(const std::initializer_list<T> &l)
{
    m_data = new T[l.size()];
    m_size = l.size();
    std::copy(l.begin(), l.end(), m_data);
}

template <typename T>
MyVector<T>::MyVector(const size_t space)
{
    if(space < 0)
        throw std::invalid_argument("m_size must be positive");

    m_data = new T[space];
    m_size = space;
}

template <typename T>
MyVector<T>::MyVector(const T *arr, const size_t n)
{
    m_size = n;
    m_data = new T[m_size];
    for(size_t i = 0; i < m_size; i++)
        m_data[i] = arr[i];
}

template <typename T>
MyVector<T>::~MyVector()
{
    delete[] m_data;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &src)
{
    m_size = src.m_size;
    m_data = new T[m_size];
    for(size_t i = 0; i < m_size; i++)
        m_data[i] = src.m_data[i];
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T> src)
{
    if(src.size() != size())
        resize(src.size());
    swap(*this, src);
    return *this;
}

template <typename T>
void MyVector<T>::resize(const size_t new_size)
{
    if(new_size < 0)
        throw std::invalid_argument("m_size must be positive");

    size_t smaller_size = std::min(new_size, m_size);

    T *m_data_copy = new T[smaller_size];
    for(size_t i = 0; i < smaller_size; i++)
        m_data_copy[i] = m_data[i];
        
    delete[] m_data;
    m_data = new T[new_size];
    for(size_t i = 0; i < smaller_size; i++)
        m_data[i] = m_data_copy[i];

    m_size = new_size;
    delete[] m_data_copy;
}

template <typename T>
size_t MyVector<T>::size() const
{
    return m_size;
}

template <typename T>
MyVector<T>& MyVector<T>::apply(T(*func)(T))
{
    for(size_t i = 0; i < m_size; i++)
        m_data[i] = func(m_data[i]);
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator-()
{
    for(size_t i = 0; i < m_size; i++)
        m_data[i] *= -1;
    return *this;
}

template <typename T>
T MyVector<T>::operator^(const int p) const
{
    T sum = 0;
    for(size_t i = 0; i < m_size; i++)
        sum += exp_by_squaring(m_data[i] < 0 ? -m_data[i] : m_data[i], p);
    return sqrt_newton(double(sum), p);
}

template <typename T>
T MyVector<T>::operator[](const size_t i) const
{
    if(i < 0 || i >= m_size)
        throw std::out_of_range("i is not in range of vector");
    return m_data[i];
}

template <typename T>
T& MyVector<T>::operator[](const size_t i)
{
    if(i < 0 || i >= m_size)
        throw std::out_of_range("i is not in range of vector");
    return m_data[i];
}

template <typename T>
ostream& operator<<(ostream &out, const MyVector<T> &src)
{
    for(size_t i = 0; i < src.size() - 1; i++)
        out << src[i] << " ";
    if(src.size() != 0)
        out << src[src.size() - 1];
    return out;
}

template <typename T>
istream& operator>>(istream &in, MyVector<T> &src)
{
    std::istream_iterator<T> eos;
    std::istream_iterator<T> iit(in);

    delete[] src.m_data;
    src.resize(0);
    int current_index = 0;

    while(iit != eos)
    {
        src.resize(src.size() + 1);
        src.m_data[current_index] = *iit;
        current_index++;
        iit++;
    }
    
    return in;
}

template <typename T>
void swap(MyVector<T> &a, MyVector<T> &b)
{
    std::swap(a.m_size, b.m_size);
    std::swap(a.m_data, b.m_data);
}

template <typename T>
MyVector<T> operator+(const MyVector<T> &a, const MyVector<T> &b)
{
    if(a.size() != b.size())
        throw std::invalid_argument("lhs and rhs of + not same size");

    T *m_data_copy = new T[a.size()];
    for(size_t i = 0; i < a.size(); i++)
        m_data_copy[i] = a[i] + b[i];
    
    MyVector<T> new_vect(m_data_copy, a.size());
    delete[] m_data_copy;
    return new_vect;
}

template <typename T>
MyVector<T> operator-(const MyVector<T> &a, const MyVector<T> &b)
{
    if(a.size() != b.size())
        throw std::invalid_argument("lhs and rhs of - not same size");

    T *m_data_copy = new T[a.size()];
    for(size_t i = 0; i < a.size(); i++)
        m_data_copy[i] = a[i] - b[i];
    
    MyVector<T> new_vect(m_data_copy, a.size());
    delete[] m_data_copy;
    return new_vect;
}

template <typename T>
MyVector<T> operator*(const MyVector<T> &lhs, const T &rhs)
{
    T *m_data_copy = new T[lhs.size()];
    for(size_t i = 0; i < lhs.size(); i++)
        m_data_copy[i] = lhs[i] * rhs;
    
    MyVector<T> new_vect(m_data_copy, lhs.size());
    delete[] m_data_copy;
    return new_vect;
}

template <typename T>
MyVector<T> operator*(const T lhs, const MyVector<T> &rhs)
{
    return (rhs * lhs);
}

template <typename T>
T operator*(const MyVector<T> &lhs, const MyVector<T> &rhs)
{
    if(lhs.size() != rhs.size())
        throw std::invalid_argument("lhs and rhs for * not of same size");

    T sum = 0;
    for(size_t i = 0; i < lhs.size(); i++)
        sum += (lhs[i] * rhs[i]);
    return sum;
}

template <typename T>
T exp_by_squaring(const T x, const int n)
{
    if(n < 0)
        return exp_by_squaring(1.0 / x, -n);
    else if(n == 0)
        return 1;
    else if(n == 1)
        return x;
    else if(n % 2 == 0)
        return exp_by_squaring(x * x, n / 2);
    return x * exp_by_squaring(x * x, (n - 1) / 2);
}

template <typename T>
T sqrt_newton(const T x, const int n)
{
    T xn = x;
    T xn_next;
    for(int i = 0; i < 10; i++)
    {
        xn_next = (1.0/n) * ((n-1)*xn + (x/exp_by_squaring(xn, n-1)));
        xn = xn_next;
    }
    return xn_next;
}