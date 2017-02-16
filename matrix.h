#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <algorithm>
#include <iostream>

template <typename T, size_t ROWS=0, size_t COLS=0>
class Matrix
{
private:

    // row size
    int m_rows=ROWS;

    // column size
    int m_cols=COLS;

    T m_data[COLS][ROWS];

    // function to check for a valid array range.
    void rangeCheck(std::size_t rowidx, std::size_t colidx);

public:

    // contructor will set data to zero
    Matrix();

    Matrix(std::initializer_list<T> data);

    // read only returns number of rows
    const T* rows() const { return m_rows; }
    // read only returns number of cols
    const T* cols() const { return m_cols; }

    // read only data
    const T* data() const { return m_data; }
    // accessible data
    T* data() { return *m_data; }

    // this is constant so can be static
    static size_t size()  {return ROWS,COLS;}
    // access data elements
    T& at(std::size_t rowidx, std::size_t colidx);
    // subscript operators
    T& operator()(std::size_t ridx, std::size_t colidx);
    const T& operator()(std::size_t rowidx, std::size_t colidx) const ;

    // subscript operators
    //T& operator[](int index);
    //const T& operator[](int index) const ;

    // assignment operator
    Matrix<T,ROWS,COLS>& operator= (const Matrix<T,ROWS,COLS>& rhs);

    void print();


    //code referenced from http://www.learncpp.com/cpp-tutorial/99-overloading-the-parenthesis-operator/
    // overload operator
    //T& operator()(int rowValue, int colValue);
    //const T& operator()(int rowValue, int colValue) const; // for const objects





};

template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix() // DEFAULT CONSTRUCTOR
{
    // default matrix types
//     Matrix<int,2,2> Matrix2f;
//     Matrix<int,3,3> Matrix3f;
//     Matrix<int,4,4> Matrix4f;

    for (int r=0; r < ROWS; ++r)
    {
       for (int c=0; c < COLS; ++c)
       {
           m_data[r][c]=T();
           //m_data[r][c]=0;
       }
    }

}

template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix(std::initializer_list<T> data)
{
    // as initializer_list returns a non constexpr size we cant static assert
// 	static_assert(	data.size()!=SIZE ,"Initialiser must be same size");
    std::copy(data.begin(),data.end(),&m_data[0][0]);

//    for(int i = 0; i<ROWS; i++)
//    {
//        for(int j = 0; j<ROWS; j++)
//        {
//            &m_data[i][j]=data;

//        }

//    }
}

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator= (const Matrix<T,ROWS,COLS>& rhs)
{
    //std::copy(rhs.begin(),rhs.end(), begin());
    for(int i=0; i<COLS; i++)
    {
        for(int j=0; j<ROWS; j++)
        {
          m_data[i][j]=rhs.m_data[i][j];

        }

    }

    return *this;
}


template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::rangeCheck(std::size_t rowidx,std::size_t colidx)
{
    if( rowidx>ROWS)
        throw std::out_of_range("index out of range in Array<T>::at");

    if( colidx>COLS)
        throw std::out_of_range("index out of range in Array<T>::at");
}

template <typename T, size_t ROWS, size_t COLS>
T& Matrix< T,ROWS,COLS>::operator()(std::size_t rowidx,std::size_t colidx)
{
    rangeCheck(rowidx,colidx);
    return m_data[rowidx][colidx];
}

template <typename T, size_t ROWS, size_t COLS>
T& Matrix< T,ROWS,COLS>::at(std::size_t rowidx,std::size_t colidx)
{
    rangeCheck(rowidx,colidx);
  return m_data[rowidx][colidx];
}



template <typename T, size_t ROWS, size_t COLS>
const T& Matrix< T,ROWS,COLS>::operator()(std::size_t rowidx,std::size_t colidx) const
{
    rangeCheck(rowidx,colidx);
  return const_cast<T&>(m_data[rowidx][colidx]);
}

template <typename T, size_t ROWS, size_t COLS>
void Matrix< T,ROWS,COLS>::print()
{
    for(int i = 0; i<COLS; i++)
      {
          for(int j = 0; j<ROWS; j++)
          {
              std::cout<<m_data[i][j]<<" ";

          }
          std::cout<<"\n";

      }
}


#endif // MATRIX_H
