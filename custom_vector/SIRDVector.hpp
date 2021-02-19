template <typename T>
SIRDVector<T>::SIRDVector(std::initializer_list<T> l)
{
    m_data = new T[l.size()];
    m_size = l.size();
    std::copy(l.begin(), l.end(), m_data);
}

template <typename T>
SIRDVector<T>::SIRDVector(const size_t space)
{
    if(space < 0)
        throw std::invalid_argument("m_size must be positive");

    m_data = new T[space];
    m_size = space;
}

template <typename T>
SIRDVector<T>::SIRDVector(const T *arr, const size_t n)
{
    m_size = n;
    m_data = new T[m_size];
    for(size_t i = 0; i < m_size; i++)
        m_data[i] = arr[i];
}

template <typename T>
SIRDVector<T>::~SIRDVector()
{
    delete[] m_data;
}

template <typename T>
SIRDVector<T>::SIRDVector(const SIRDVector<T> &src)
{
    m_size = src.m_size;
    m_data = new T[m_size];
    for(size_t i = 0; i < m_size; i++)
        m_data[i] = src.m_data[i];
}

template <typename T>
SIRDVector<T>& SIRDVector<T>::operator=(SIRDVector<T> src)
{
    if(src.size() != size())
        resize(src.size());
    swap(*this, src);
    return *this;
}

template <typename T>
void SIRDVector<T>::resize(const size_t new_size)
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

    if(new_size > m_size)
    {
        for(size_t i = m_size; i < new_size; i++)
            m_data[i] = 0;
    }

    m_size = new_size;
    delete[] m_data_copy;
}

template <typename T>
size_t SIRDVector<T>::size() const
{
    return m_size;
}

template <typename T>
SIRDVector<T>& SIRDVector<T>::apply(T(*func)(T))
{
    for(size_t i = 0; i < m_size; i++)
        m_data[i] = func(m_data[i]);
    return *this;
}

template <typename T>
SIRDVector<T>& SIRDVector<T>::operator-()
{
    for(size_t i = 0; i < m_size; i++)
        m_data[i] *= -1;
    return *this;
}

template <typename T>
T SIRDVector<T>::operator[](const size_t i) const
{
    if(i < 0 || i >= m_size)
        throw std::out_of_range("i is not in range of vector");
    return m_data[i];
}

template <typename T>
ostream& operator<<(ostream &out, const SIRDVector<T> &src)
{
    for(size_t i = 0; i < src.size(); i++)
        out << src[i] << " ";
    return out;
}

template <typename T>
istream& operator>>(istream &in, SIRDVector<T> &src)
{
    std::istream_iterator<T> eos;
    std::istream_iterator<T> iit(in);
    
    delete[] src.m_data;
    src.m_data = new T[9999];

    int current_index = 0;
    while(iit != eos)
    {
        src.m_data[current_index] = *iit;
        current_index++;
        iit++;
    }
    src.m_size = current_index;
    return in;
}

template <typename T>
void swap(SIRDVector<T> &a, SIRDVector<T> &b)
{
    std::swap(a.m_size, b.m_size);
    std::swap(a.m_data, b.m_data);
}

template <typename T>
SIRDVector<T> operator+(const SIRDVector<T> &a, const SIRDVector<T> &b)
{
    if(a.size() != b.size())
        throw std::invalid_argument("lhs and rhs of + not same size");

    T *m_data_copy = new T[a.size()];
    for(size_t i = 0; i < a.size(); i++)
        m_data_copy[i] = a[i] + b[i];
    
    SIRDVector<T> new_vect(m_data_copy, a.size());
    delete[] m_data_copy;
    return new_vect;
}

template <typename T>
SIRDVector<T> operator-(const SIRDVector<T> &a, const SIRDVector<T> &b)
{
    if(a.size() != b.size())
        throw std::invalid_argument("lhs and rhs of - not same size");

    T *m_data_copy = new T[a.size()];
    for(size_t i = 0; i < a.size(); i++)
        m_data_copy[i] = a[i] - b[i];
    
    SIRDVector<T> new_vect(m_data_copy, a.size());
    delete[] m_data_copy;
    return new_vect;
}

template <typename T>
SIRDVector<T> operator*(const SIRDVector<T> &lhs, const T &rhs)
{
    T *m_data_copy = new T[lhs.size()];
    for(size_t i = 0; i < lhs.size(); i++)
        m_data_copy[i] = lhs[i] * rhs;
    
    SIRDVector<T> new_vect(m_data_copy, lhs.size());
    delete[] m_data_copy;
    return new_vect;
}

template <typename T>
SIRDVector<T> operator*(const T lhs, const SIRDVector<T> &rhs)
{
    return (rhs * lhs);
}

template <typename T>
T operator*(const SIRDVector<T> &lhs, const SIRDVector<T> &rhs)
{
    if(lhs.size() != rhs.size())
        throw std::invalid_argument("lhs and rhs for * not of same size");

    T sum = 0;
    for(size_t i = 0; i < lhs.size(); i++)
        sum += (lhs[i] * rhs[i]);
    return sum;
}