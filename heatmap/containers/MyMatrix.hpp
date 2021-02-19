template <typename T>
MyMatrix<T>::MyMatrix(const initializer_list<initializer_list<T>> &l)
{
    size_t init_list_size = l.begin()->size();
    for(auto &inner_list : l)
    {
        if(inner_list.size() != init_list_size)
            throw std::invalid_argument("init_list diff. sizes in matrix con");
    }

    m_data = new MyVector<T>[l.size()];
    for(size_t i = 0; i < l.size(); i++)
        m_data[i] = MyVector<T>(l.begin()->size());

    size_t curr_vect = 0;
    for(auto i = l.begin(); i != l.end(); i++)
    {
        size_t curr_i = 0;
        for(auto x = i->begin(); x != i->end(); x++)
        {
            m_data[curr_vect][curr_i] = *x;
            curr_i++;
        }
        curr_vect++;
    }
    r = l.size();
    c = l.begin()->size();
}

template <typename T>
MyMatrix<T>::~MyMatrix()
{
    delete[] m_data;
    m_data = nullptr;
}

template <typename T>
MyMatrix<T>::MyMatrix(const size_t rows, const size_t cols)
{
    if(rows <= 0 || cols <= 0)
        throw std::invalid_argument("matrix constr. given neg. size");

    m_data = new MyVector<T>[rows];
    for(size_t i = 0; i < rows; i++)
        m_data[i] = MyVector<T>(cols);
    r = rows;
    c = cols;

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < cols; j++)
            operator[](i).operator[](j) = 0;
    }
}

template <typename T>
MyMatrix<T>::MyMatrix(const MyMatrix<T> &a)
{
    m_data = new MyVector<T>[a.rows()];
    for(size_t i = 0; i < a.rows(); i++)
        m_data[i] = MyVector<T>(a.cols());

    r = a.rows();
    c = a.cols();

    for(size_t i = 0; i < r; i++)
    {
        for(size_t j = 0; j < c; j++)
            m_data[i][j] = a[i][j];
    }
}

template <typename T>
void swap(MyMatrix<T> &a, MyMatrix<T> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("swap function a size DNE b size");
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            std::swap(a.m_data[i][j], b.m_data[i][j]);
    }
}

template <typename T>
MyMatrix<T>& MyMatrix<T>::operator=(MyMatrix<T> a)
{
    swap(*this, a);
    return *this;
}

template <typename T>
void MyMatrix<T>::resize(const size_t new_r, const size_t new_c)
{
    if(new_r < 0 || new_c < 0)
        throw std::invalid_argument("matrix resize given neg. size");

    delete[] m_data;

    m_data = new MyVector<T>[new_r];
    for(size_t i = 0; i < new_r; i++)
        m_data[i] = MyVector<T>(new_c);
    r = new_r;
    c = new_c;

    for(size_t i = 0; i < new_r; i++)
    {
        for(size_t j = 0; j < new_c; j++)
            operator[](i).operator[](j) = 0;
    }
}

template <typename T>
MyVector<T> MyMatrix<T>::operator[](const size_t i) const
{
    if(i < 0)
        throw std::invalid_argument("[i] for matrix is negative");
    return m_data[i];
}

template <typename T>
MyVector<T>& MyMatrix<T>::operator[](const size_t i)
{
    if(i < 0)
        throw std::invalid_argument("[i] for matrix is negative");
    return *&m_data[i];
}

template <typename T>
T MyMatrix<T>::operator()(const size_t i, const size_t j) const
{
    if(i < 0 || j < 0)
        throw std::invalid_argument("negative index for matrix(i, j) call");
    return m_data[i][j];
}

template <typename T>
T& MyMatrix<T>::operator()(const size_t i, const size_t j)
{
    if(i < 0 || j < 0)
        throw std::invalid_argument("negative index for matrix(i, j) call");
    return *&m_data[i][j];
}

template <typename T>
MyMatrix<T>& MyMatrix<T>::operator-()
{
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
            operator[](i).operator[](j) *= -1;
    }
    return *this;
}

template <typename T>
ostream& operator<<(ostream &out, const MyMatrix<T> &src)
{
    for(size_t i = 0; i < src.rows(); i++)
    {
        for(size_t j = 0; j < src.cols(); j++)
        {
            if(j != src.cols() - 1)
                out << src[i][j] << " ";
            else
                out << src[i][j];
        }
        if(i != src.rows() - 1)
            out << std::endl;
    }
    return out;
}

template <typename T>
istream& operator>>(istream &in, MyMatrix<T> &src)
{
    for(size_t i = 0; i < src.rows(); i++)
    {
        for(size_t j = 0; j < src.cols(); j++)
            in >> src[i][j];
    }
    return in;
}

template <typename T>
MyMatrix<T> operator+(const MyMatrix<T> &a, const MyMatrix<T> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant add matrices, different sizes");

    MyMatrix<T> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] + b[i][j];
    }
    return added_matrix;
}

MyMatrix<float> operator+(const MyMatrix<int> &a, const MyMatrix<float> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant add matrices, different sizes");

    MyMatrix<float> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] + b[i][j];
    }
    return added_matrix;
}

template <typename T>
MyMatrix<T> operator-(const MyMatrix<T> &a, const MyMatrix<T> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant minus matrices, different sizes");

    MyMatrix<T> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] - b[i][j];
    }
    return added_matrix;
}

MyMatrix<float> operator-(const MyMatrix<int> &a, const MyMatrix<float> &b)
{
    if(a.rows() != b.rows() || a.cols() != b.cols())
        throw std::invalid_argument("cant minus matrices, different sizes");

    MyMatrix<float> added_matrix(a.rows(), a.cols());
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            added_matrix[i][j] = a[i][j] - b[i][j];
    }
    return added_matrix;
}

template <typename T>
MyMatrix<T> operator*(const MyMatrix<T> &a, const MyMatrix<T> &b)
{
    if(a.cols() != b.rows())
        throw std::invalid_argument("cant mult. matrices, incompat. sizes");
    
    MyMatrix<T> product(a.rows(), b.cols());
    for(size_t i = 0; i < product.rows(); i++)
    {
        for(size_t j = 0; j < product.cols(); j++)
        {
            T curr_sum = 0;
            for(size_t curr_i = 0; curr_i < a.cols(); curr_i++)
                curr_sum += (a[i][curr_i] * b[curr_i][j]);
            product[i][j] = curr_sum;
        }
    }
    return product;
}

template <typename T>
MyMatrix<T> operator*(const T a, const MyMatrix<T> &b)
{
    return (b * a);
}

template <typename T>
MyMatrix<T> operator*(const MyMatrix<T> &a, const T b)
{
    MyMatrix<T> scaled_matrix(a);
    for(size_t i = 0; i < a.rows(); i++)
    {
        for(size_t j = 0; j < a.cols(); j++)
            scaled_matrix[i][j] *= b;
    }
    return scaled_matrix;
}

template <typename T>
MyMatrix<T> operator*(const MyVector<T> &a, const MyMatrix<T> &b)
{
    if(a.size() != b.rows())
        throw std::invalid_argument("cant mult. matrix/vect, incompat. sizes");
    
    MyMatrix<T> product(1, b.cols());
    for(size_t i = 0; i < product.cols(); i++)
    {
        T curr_sum = 0;
        for(size_t curr_r = 0; curr_r < a.size(); curr_r++)
            curr_sum += (a[curr_r] * b[curr_r][i]);
        product[0][i] = curr_sum;
    }
    return product;
}

template <typename T>
MyVector<T> operator*(const MyMatrix<T> &a, const MyVector<T> &b)
{
    if(a.cols() != b.size())
        throw std::invalid_argument("cant mult. vect/matrix, incompat. sizes");
    
    MyVector<T> product(b.size());
    for(size_t i = 0; i < product.size(); i++)
    {
        T curr_sum = 0;
        for(size_t curr_r = 0; curr_r < a.cols(); curr_r++)
            curr_sum += (a[i][curr_r] * b[curr_r]);
        product[i] = curr_sum;
    }
    return product;
}

template <typename T>
MyMatrix<int> MyMatrix<T>::identity()
{
    MyMatrix<int> iden(rows(), cols());
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
        {
            if(i == j)
                iden[i][j] = 1;
            else
                iden[i][j] = 0;
        }
    }
    return iden;
}

template <typename T>
MyMatrix<T> MyMatrix<T>::transpose()
{
    MyMatrix<T> this_copy(*this);
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < rows(); j++)
            this_copy[j][i] = operator[](i).operator[](j);
    }
    return this_copy;
}

template <typename T>
MyMatrix<T> MyMatrix<T>::invert() const
{
    T row_sum, col_sum;

    T sum = 0;
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
            sum += m_data[i][j];
        if(i == 0 || sum > row_sum)
            row_sum = sum;
    }
    sum = 0;
    for(size_t j = 0; j < cols(); j++)
    {
        for(size_t i = 0; i < rows(); i++)
            sum += m_data[i][j];
        if(j == 0 || sum > col_sum)
            col_sum = sum;
    }

    T t = 1 / (row_sum * col_sum);
    MyMatrix<T> this_transpose(*this);
    this_transpose.transpose();

    MyMatrix<T> b = t * this_transpose;
    bool is_accurate = false;
    while(!is_accurate)
    {
        MyMatrix<T> e = this_transpose.identity() - (b * *this);
        b = (this_transpose.identity() + e) * b;

        is_accurate = true;
        for(size_t i = 0; i < b.rows(); i++)
        {
            for(size_t j = 0; j < b.cols(); j++)
            {
                if(b[i][j] > 0.001)
                    is_accurate = false;
            }
        }
    }
    return b;
}

template <>
MyMatrix<float> MyMatrix<float>::invert() const
{
    float row_sum, col_sum;

    float sum = 0;
    for(size_t i = 0; i < rows(); i++)
    {
        for(size_t j = 0; j < cols(); j++)
            sum += m_data[i][j];
        if(i == 0 || sum > row_sum)
            row_sum = sum;
    }
    sum = 0;
    for(size_t j = 0; j < cols(); j++)
    {
        for(size_t i = 0; i < rows(); i++)
            sum += m_data[i][j];
        if(j == 0 || sum > col_sum)
            col_sum = sum;
    }

    float t = 1.0 / (row_sum * col_sum);
    MyMatrix<float> this_transpose(*this);
    this_transpose.transpose();

    MyMatrix<float> b = t * this_transpose;
    bool is_accurate = false;
    while(!is_accurate)
    {
        MyMatrix<float> e = (this_transpose.identity() - (b * *this));
        b = (this_transpose.identity() + e) * b;

        is_accurate = true;
        for(size_t i = 0; i < b.rows(); i++)
        {
            for(size_t j = 0; j < b.cols(); j++)
            {
                if(b[i][j] > 0.001)
                    is_accurate = false;
            }
        }
    }
    return b;
}