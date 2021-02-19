/*!
 * Author: Jackson Willbrand, 2/12/2020
 * File: interpolator.h
 * Class: CS 5201 Section A
 * Instructor: Clayton Price
 * Description: class and related function implementation for interpolator
 */

#include <iostream>
#include <tuple>
using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::tuple;
using std::ostream;
using std::istream;

// extraction operator, print data set of interpolator to stdout
template <typename T>
ostream& operator<<(ostream &out, const interpolator<T> &i)
{
    if(!i.is_increasing())
        throw std::invalid_argument("ind. vars. not increasing order");

    T ind_var, dep_var1, dep_var2;
    for(int point = 0; point < i.num_points; point++)
    {
        std::tie(ind_var, dep_var1, dep_var2) = i.data_set[point];
        cout << ind_var << ": " << dep_var1 << ", ";
        cout << dep_var2 << endl;
    }
    return out;
}

// insertion operator, take in a tuple of form (i, d1, d2)
template <typename T>
istream& operator>>(istream &in, interpolator<T> &i)
{
    T prev_ind_var, ind_var, dep_var1, dep_var2;
    for(int point = 0; point < i.num_points; point++)
    {
        if(point > 0)
            prev_ind_var = ind_var;

        cin >> ind_var >> dep_var1 >> dep_var2;

        if(point > 0 && ind_var < prev_ind_var)
            throw std::invalid_argument("ind. vars not in increasing order");
        
        i.data_set.push_back(tuple<T, T, T>(ind_var, dep_var1, dep_var2));
    }
    return in;
}

// > logical comparison, based on span of given two interpolator objects
template <typename T>
bool operator>(const interpolator<T> &a, const interpolator<T> &b)
{
    if(!a.is_increasing() || !b.is_increasing())
        throw std::invalid_argument("ind. vars not in increasing order");
    return (~a > ~b ? true : false);
}

// < logical comparison, based on span of given two interpolator objects
template <typename T>
bool operator<(const interpolator<T> &a, const interpolator<T> &b)
{
    if(!a.is_increasing() || !b.is_increasing())
        throw std::invalid_argument("ind. vars not in increasing order");
    return (~a < ~b ? true : false);
}

// == logical comparison, based on span of given two interpolator objects
template <typename T>
bool operator==(const interpolator<T> &a, const interpolator<T> &b)
{
    if(!a.is_increasing() || !b.is_increasing())
        throw std::invalid_argument("ind. vars not in increasing order");
    return (~a == ~b ? true : false);
}

// != logical comparison, based on span of given two interpolator objects
template <typename T>
bool operator!=(const interpolator<T> &a, const interpolator<T> &b)
{
    if(!a.is_increasing() || !b.is_increasing())
        throw std::invalid_argument("ind. vars not in increasing order");
    return (~a != ~b ? true : false);
}

// paramterized constructor, given data vector, store it in interpolator
template <typename T>
interpolator<T>::interpolator(const interpolator_vect data_points)
{
    num_points = data_points.size();
    for(int i = 0; i < num_points; i++)
        data_set.push_back(data_points[i]);
}

// parameterized constructor, given number of points, setup for cin later
template <typename T>
interpolator<T>::interpolator(const int num)
{
    num_points = num;
}

// copy constructor, deep copy of contents of src to container
template <typename T>
interpolator<T>::interpolator(const interpolator<T> &src)
{
    num_points = src.num_points;
    for(int i = 0; i < num_points; i++)
        data_set.push_back(src.data_set);
}

// swap function, swaps member contents of two interpolators
template <typename T>
void swap(interpolator<T> &i1, interpolator<T> &i2)
{
    std::swap(i1.num_points, i2.num_points);
    i1.data_set.swap(i2.data_set);
}

// assignment operator, pass src interpolator by copy, swap its contents
// with container and then return the container
template <typename T>
interpolator<T>& interpolator<T>::operator=(interpolator<T> src)
{
    swap(*this, src);
    return *this;
}

// increasing check, checks if all ind. vars. are in increasing order
template <typename T>
bool interpolator<T>::is_increasing() const
{
    bool is_increasing = true;

    if(num_points > 1)
    {
        T prev_val = get<0>(data_set[0]);
        for(int i = 1; i < num_points; i++)
        {
            T curr_val = get<0>(data_set[i]);
            if(curr_val < prev_val)
            {
                is_increasing = false;
                break;
            }
            prev_val = curr_val;
        }
    }
    return is_increasing;
}

// subscript operator, return reference to tuple of closest smaller index val
template <typename T>
tuple<T, T, T>& interpolator<T>::operator[](const T index)
{
    if(index < get<0>(data_set[0]))
        throw std::invalid_argument("no smaller ind. var. to access");
    
    int currIndex = num_points - 1;
    while(index < get<0>(data_set[currIndex]))
        currIndex--;
    
    return data_set[currIndex];
}

// subscript operator, return value of tuple of closest smaller index val
template <typename T>
const tuple<T, T, T>& interpolator<T>::operator[](const T index) const
{
    if(index < get<0>(data_set[0]))
        throw std::invalid_argument("no smaller ind. var. to access");
    
    int currIndex = num_points - 1;
    while(index < get<0>(data_set[currIndex]))
        currIndex--;
    
    return data_set[currIndex];
}

// get_min_higher(), return tuple of closest bigger index value
template <typename T>
std::tuple<T, T, T>& interpolator<T>::min_high(const T index)
{
    if(index > get<0>(data_set[num_points - 1]))
        throw std::invalid_argument("no greater ind. var. to access");
    
    int currIndex = 0;
    while(index > get<0>(data_set[currIndex]))
        currIndex++;
    
    return data_set[currIndex];
}

// bitwise operator, return range of independent variable
template <typename T>
T interpolator<T>::operator~() const
{
    if(num_points < 2)
        throw std::invalid_argument("not enough data points for ~");
    if(!is_increasing())
        throw std::invalid_argument("ind. vars not in increasing order");
    return get<0>(data_set[num_points - 1]) - get<0>(data_set[0]);
}

// evaluation operator, returns linear interpolation at ind. var. 'i'
template <typename T>
tuple<T, T> interpolator<T>::operator()(const T i)
{
    if(num_points < 2)
        throw std::invalid_argument("not enough data for interpolation");

    if(i < get<0>(data_set[0]) || i > get<0>(data_set[num_points - 1]))
        throw std::invalid_argument("value to interpolate not in range");
    
    if(!is_increasing())
        throw std::invalid_argument("ind. vars not in increasing order");
    
    T smaller1 = get<1>(this->operator[](i));
    T smaller2 = get<2>(this->operator[](i));
    T larger1 = get<1>(min_high(i));
    T larger2 = get<2>(min_high(i));
    T smaller0 = get<0>(this->operator[](i));
    T larger0 = get<0>(min_high(i));
    
    T dep_var1 = smaller1 + (larger1 - smaller1) * (i - smaller0) / 
        (larger0 - smaller0);
    T dep_var2 = smaller2 + (larger2 - smaller2) * (i - smaller0) /
        (larger0 - smaller0);
    return std::make_tuple(dep_var1, dep_var2);
}