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
        _vctr.resize(sizeof(T)*_rows*_cols);
    }


    matrix(const matrix &mat);  //Copy constructor
    matrix& operator=(const matrix&);  //copy assingment
/*
    matrix(matrix&&);   //move constructor
    matrix& operator=(matrix&&);    //move assignment
*/
    virtual ~matrix(){} //destructor

    //operators

    //for random access
    T& operator ()(int row, int col);
    T& operator()(int row, int col, T value);
    const T& operator()(int row, int col)const;

    //for continous access of precalculated position direct accesss
    T& operator [](int n);

    const int getCols() const {return _cols;}
    const int getRows()const {return _rows;}
    const std::vector<T>& getVector() const {return _vctr;}
    typename std::vector<T>::iterator& getIterator() const{return _ivctr;};
    const T* getDataPtr() const {return _data.data();}
    T* getDataPtr() {return _data.data();}



    void setRows(int r){_rows = r;}
    void setCols(int c){_cols = c;}
    void setSize(int r, int c){_rows = r; _cols = c;}
    void setVector(const std::vector<T>& v){_vctr = v;}
    void setIterator(const typename std::vector<T>::iterator it){_ivctr = it;}
    void resize(){_vctr.resize(sizeof(T)*_rows*_cols);}
    //Dangerous as it overrides the rows cols restrictions
    void resize(int size){_vctr.resize(size);}
    void resize(unsigned int rows, unsigned int cols){
      _rows = rows;
      _cols = cols;
      _vctr.resize(sizeof(T)*_rows*_cols);
    };

private:
    std::vector<T> _vctr;
    //typename is there to specify the compiler _ivctr is a type as vector<T> is not specified
    typename std::vector<T>::iterator _ivctr = _vctr.begin();
    unsigned int _rows = 0;
    unsigned int _cols = 0;
};

#endif // MATRIX_H
