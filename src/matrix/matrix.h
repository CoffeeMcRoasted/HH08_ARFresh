#ifndef MATRIX_H
#define MATRIX_H

/** \brief Matrix class destined to be a container for decoded images
 *
 * The container should allow to access elements individually in random access or
 * continuously, as well as moving the information
 */

#include <vector>

template<typename T>
class matrix
{
public:
    //constructors
    matrix():_rows{0}, _cols{0} {}
    matrix(int row, int col):_rows{row},_cols{col}{
        int size = sizeof(T)*_rows*_cols;
        _vctr.resize(size);
    }


    matrix(const matrix &mat);  //Copy constructor
    matrix& operator=(const matrix&);  //copy assingment
/*
    matrix(matrix&&);   //move constructor
    matrix& operator=(matrix&&);    //move assignment
*/
    ~matrix(){} //destructor

    //operators

    //for random access
    T& operator ()(int row, int col);
    T& operator()(int row, int col, T value);
    const T& operator()(int row, int col)const;

    //for continous access of precalculated position direct accesss
    T& operator [](int n);

    const int getCols(){return _cols;}
    const int getRows(){return _rows;}
    std::vector<T>& getVector() const {return &_vctr;}

    void setVector(const std::vector<T> v){_vctr = v;}

    void setRows(int r){_rows = r;}
    void setCols(int c){_cols = c;}
    void setSize(int r, int c){_rows = r; _cols = c;}

    void resize(){_vctr.resize(sizeof(T)*_rows*_cols);}

private:
    std::vector<T> _vctr;
    //typename is there to specify the compiler _ivctr is a type as vector<T> is not specified
    typename std::vector<T>::iterator _ivctr = _vctr.begin();
    int _rows;
    int _cols;
};

#endif // MATRIX_H
