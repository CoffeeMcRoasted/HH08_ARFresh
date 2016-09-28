#include <matrix.h>

//Constructors
//Copy
template <typename T>
matrix<T>::matrix(const matrix &mat){
    _cols = mat.getCols();
    _rows = mat.getRows();
    _vctr = mat.getVector();
}

//operators
//copy assingment
template <typename T>
matrix<T>& matrix<T>::operator =(const matrix & mat){
    _cols = mat.getCols();
    _rows = mat.getRows();
    _vctr = mat.getVector();
    return *this;
}
template matrix<unsigned char>& matrix<unsigned char>::operator=(const matrix<unsigned char> & mat);
//operator () for access and chage of values

template <typename T>
const T& matrix<T>::operator ()(int row, int col) const {
    return this->_vctr[((row-1)*this->getCols() + col - 1)];
}

template <typename T>
T& matrix<T>::operator ()(int row, int col) {
    return this->_vctr[((row-1)*this->getCols() + col - 1)];
}

template <typename T>
T& matrix<T>::operator ()(int row, int col, T value){
    int pos = ((row-1)*this->getCols() + col - 1);
    this->_vctr[pos] = value;
    return this->_vctr[pos];
}

template <typename T>
T& matrix<T>::operator [](int n){
    return this->_vctr[n];
}
