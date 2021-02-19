#ifndef MY_ITERATOR_H
#define MY_ITERATOR_H

/*! SIRD Iterator class, custom iterator MyVector
 * @brief My Iterator class, custom iterator for MyVector object
 *        to allow for range based for loop usage on MyVector
 */
template <typename T>
class MyIterator
{
    public:
        /*! Paramterized constructor, give the pointer to type T
         * @brief parameterized constructor, given the pointer to type T
         * @pre none
         * @param[in] ptr pointer to object of type T to be used for iterator
         * @post creates a MyIterator object with this.ptr pointing to ptr
         */
        explicit MyIterator(T *ptr): ptr(ptr) {}

        /*! Increment operator, increments the pointer member variable
         * @brief Increment operator, increments the ptr member variable
         * @pre none
         * @post increments the ptr member variable and returns new calling obj
         * @returns modified calling obj. after ptr is incremented
         */
        MyIterator<T> operator++() {++ptr; return *this;}

        /*! Not comparison operator, returns true if pointers are not equal
         * @brief Not comp. operator, returns true if pointers are not equal
         * @pre none
         * @param[in] r second MyIterator object to compare to calling obj
         * @post compares this.ptr to r.ptr and returns result
         * @returns true if ptr != r.ptr, false otherwise
         */
        bool operator!=(const MyIterator<T>&r) const {return ptr != r.ptr;}

        /*! Dereference operator, returns the dereferenced pointer
         * @brief Deference operator, returns the dereferenced ptr member var.
         * @pre none
         * @post returns the deferenced ptr member var.
         * @returns the deferenced ptr member variable
         */
        const T& operator*() const {return *ptr;}
    
    private:
        T *ptr; //! pointer object to do iteration with
};

#endif