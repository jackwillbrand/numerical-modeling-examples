#ifndef _INTERPOLATOR_H
#define _INTERPOLATOR_H


//! \class interpolator
// \brief An object containing a vector of tuples to interpolate over
// 
// This class is useful for interpolating over a range of inputted tuples
// representing points. Tuples are of the form (i, d1, d2), where i is the
// independent variables, and d1 and d2 are two dependent variables. Call
// interpolation on object i and point p with "i(p)"

template<typename T>
class interpolator {
  private:
    ///< vector storage of templated 3-tuples
    interpolator_vect data_set;

    ///< total number of tuples in data_set
    int num_points;


  public:
    //! Parameterized constructor given interpolator vector tuple data
    //
    //\pre data_points ind. vars. must be in increasing order
    //\throws std::invalid_argument if ind. vars. not increasing order
    //\post new interpolator obj created, with data_points as data_set
    //      and num_points as total number of tuples in data_set
    
    interpolator(const interpolator_vect data_points);

    //! Parameterized constructor given number of points in data set
    //
    //\pre num must be in (0, inf], all inputted tuples' ind. var.
    //     must be submitted in increasing order
    //\throws std::invalid argument thrown if num out of (0, inf) or
    //        if ind. vars. are not in increasing order
    //\post new interpolator obj created with empty data set, with 
    //      num_points set to given num value, defaulted to 20 points
    
    interpolator(const int num);

    //! Copy constructor
    //
    //\pre none
    //\post creates a new interpolator object with copies of information
    //      from src interpolator, and same num_points
    
    interpolator(const interpolator<T> & src);

    //! Assignment operator
    //
    //\pre none
    //\returns a copy of 'src' with all information copied
    
    interpolator<T> & operator =(interpolator<T> src);

    //! Check for increasing ind. var. values
    //
    //\pre none
    //\returns a bool representing if all indepedent variables in the
    //         container are increasing. used to throw exceptions in
    //         other functions when they need to use ind. vars.
    
    bool is_increasing() const;

    //! Subscript operator given index to look for to access/modify
    //
    //\pre index is greater than or equal to an independent variable
    //     already existing in data_set
    //\throws std::invalid_argument if not >= to existing ind. var.
    //\returns a reference to the tuple with the closest independent
    //         variable less than or equal to index
    
    tuple<T, T, T> & operator [](const T index);

    //! Subscript operator given index to look for to access
    //
    //\pre index is greater than or equal to an independent variable
    //     already existing in data_set
    //\throws std::invalid_argument if not >= to existing ind. var.
    //\returns the tuple with the closest independent variable less than
    //         or equal to index, to access (not modify)
    
    const tuple<T, T, T> & operator [](const T index) const;

    //! Function to return reference to closest larger ind. var. tuple
    //
    //\pre index is less than or equal to an independent variable
    //     already existing in data_set
    //\throws std::invalid_argument if not <= to existing ind. var.
    //\returns a reference to the tuple with the closest independent
    //         variable greater than or equal to index
    
    tuple<T, T, T> & min_high(const T index);

    //! Bitwise operator to return range of ind. var. of given interpolator
    //
    //\pre src must contain at least two data points to determine span, and
    //     subtraction must be valid operation of ind. vars type, and ind.
    //     vars must be in increasing order
    //\throws std::invalid_argument if any above pre not fulfilled
    //\returns returns largest ind. var minus smallest (aka span)
    //\relatesalso interpolator
    
    T operator ~() const;

    //! Function evaluation operator to interpolate on 'i' value
    //
    //\pre i must be valid independent variable (in span of data set) and
    //     data set must contain at least two points, ind. vars must be
    //     in increasing order
    //\returns a pair representing the two dependent values
    //         associated with 'i' after interpolating over 'i'
    
    tuple<T, T> operator ()(const T i);

    //! Insertion operator for printing points in dataset
    //
    //\pre 'T' type must support insertion operation
    //\post prints all tuples in src's data_set of form 'a: b, c\n', where
    //      a is independent vars, b and c are dependent vars, and each point
    //      is separated by a newline, ind. vars. increasing order
    //\returns the modified ostream object
    //\relatesalso interpolator
    
    friend ostream & operator << <T>(ostream & out, const interpolator<T> & i);

    //! Extraction operator for reading in given number of points
    // 
    //\pre input must be of form 'a b c', where a is independent variable and
    //     b and c are dependent variables, with a newline separating each point.
    //     there should also exist an equal number of points to the one specified.
    //     'T' type should also support extraction operation, ind. vars must be
    //     in increasing order
    //\throws std::invalid_argument if any above preconditions not fulfilled
    //\post reads in the given points to interpolator object, overwriting any
    //      existing data in the process
    //\returns the modified istream object
    //\relatesalso interpolator
    
    friend istream & operator >> <T>(istream & in, interpolator<T> & i);

    //! Swap function
    //
    //\pre none
    //\post swaps the member contents of the two objects with eachother
    //\relatesalso interpolator
    
    friend void swap<T>(interpolator<T> & i1, interpolator<T> & i2);

};
#endif
