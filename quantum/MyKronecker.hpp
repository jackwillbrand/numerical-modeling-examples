template <typename T>
MyMatrix<T> MyKronecker<T>::operator()(const MyMatrix<T> &m1, const MyMatrix<T> &m2) const
{
    MyMatrix<T> result(m1.rows() + m2.rows(), m1.cols() + m2.cols());
    for(size_t i = 1; i <= m1.rows(); i++)
    {
        for(size_t j = 1; j <= m1.cols(); j++)
        {
            for(size_t k = 1; k <= m2.rows(); k++)
            {
                for(size_t l = 1; l <= m2.cols(); l++)
                {
                    size_t a = (m1.cols() * (i - 1)) + k;
                    size_t b = (m2.cols() * (j - 1)) + l;
                    result[a-1][b-1] = m1[i-1][j-1] * m2[k-1][l-1];
                }
            }
        }
    }
    return result;
}