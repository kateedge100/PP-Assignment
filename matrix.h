#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <algorithm>
#include <iostream>

#define PI 3.14159265359

template <typename T, size_t ROWS=0, size_t COLS=0>
class Matrix
{
private:

    // row size
    int m_rows=ROWS;

    // column size
    int m_cols=COLS;

    T m_data[ROWS][COLS];

    // stores if vector after testing if matrix has more then one Col hence is a vector
    bool m_vector = false;

    // function to check for a valid row and column range.
    void rangeCheck(std::size_t rowID, std::size_t colID);

public:

    // contructor will set data to zero
    Matrix();

   // copy constructor
    Matrix(std::initializer_list<T> data);

    // read only returns number of rows
    const int* rows() const { return m_rows; }
    // read only returns number of cols
    const int* cols() const { return m_cols; }

    // read only data
    const T* data() const { return m_data; }
    // accessible data
    T* data() { return *m_data; }

    // this is constant so can be static
    static size_t size()  {return ROWS,COLS;}

    // subscript operators
    //code referenced from http://www.learncpp.com/cpp-tutorial/99-overloading-the-parenthesis-operator/
    T& operator()(std::size_t rowID, std::size_t colID);
    const T& operator()(std::size_t rowID, std::size_t colID) const ; // for const objects

    void vectorCheck();


    /// Matrix and Vector Operation

    // assignment operator
    Matrix& operator= (const Matrix<T,ROWS,COLS>& rhs);
    // addition operator
    Matrix& operator+ (const Matrix<T,ROWS,COLS>& rhs);
    // addition operator scalar
    Matrix& operator+ (T scalar);
    // subtraction operator
    Matrix& operator- (const Matrix<T,ROWS,COLS>& rhs);
    // subtraction operator scalar
    Matrix& operator- (T scalar);
    // negative operator
    Matrix& operator- ();

    // multiply operator scalar
    Matrix& operator* (T scalar);
    // division operator scalar
    Matrix& operator/ (T scalar);

    /// Matrix only opertaion
    // multiply operator
    Matrix<T,ROWS,COLS>& operator* (const Matrix<T,ROWS,COLS>& rhs);

    /// Vector only methods
    float magnitude();
    // divide one vector by another
    Matrix& operator/ (const Matrix<T,ROWS,COLS>& rhs);
    // dot product
    float dot(Matrix<T,ROWS,COLS>& rhs);
    // angle betwwen vectors
    float angle(Matrix<T,ROWS,COLS>& rhs);
    // cross product
    Matrix& cross(Matrix<T,ROWS,COLS>& rhs);






    // prints out matrix
    void print();

};

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix() // DEFAULT CONSTRUCTOR
{
    for (int r=0; r < ROWS; ++r)
    {
       for (int c=0; c < COLS; ++c)
       {
           m_data[r][c]=T();
           //m_data[r][c]=0;
       }
    }

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix(std::initializer_list<T> data)
{
    // possibly use std::initializer_list<std::initializer_list<T>> data
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

    if(ROWS==1)
    {
        m_vector=true;
        std::cout<<"is a vector \n";
    }
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator= (const Matrix<T,ROWS,COLS>& rhs)
{

    rangeCheck(rhs.m_rows,rhs.m_cols);

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=rhs.m_data[i][j];

        }

    }

    return *this;
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator+ (const Matrix<T,ROWS,COLS>& rhs)
{
    rangeCheck(rhs.m_rows,rhs.m_cols);

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=m_data[i][j]+rhs.m_data[i][j];

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator+ (T scalar)
{

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=m_data[i][j]+ scalar;

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator- (const Matrix<T,ROWS,COLS>& rhs)
{
    rangeCheck(rhs.m_rows,rhs.m_cols);

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=m_data[i][j]-rhs.m_data[i][j];

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator- (T scalar)
{


    //std::copy(rhs.begin(),rhs.end(), begin());
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=m_data[i][j]- scalar;

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator- ()
{

    //std::copy(rhs.begin(),rhs.end(), begin());
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=-m_data[i][j];

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator* (const Matrix<T,ROWS,COLS>& rhs)
{
    // matrix-matrix multiplication
    if(m_vector == false)
    {



    if( COLS!=rhs.m_rows)
        throw std::out_of_range("number of columns of matrix 1 mustbe equil to number of rows of matrix 2");

    int i, j, k;


    // initialize tmp matrix values to 0
    T tmp[rhs.m_rows][m_cols];

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          tmp[i][j]=0;

        }
    }

        // Multiplying matrices and storing values in matrix tmp
        for(i = 0; i < m_rows; ++i)
        {
            for(j = 0; j < rhs.m_cols; ++j)
            {
                for(k=0; k<m_cols; ++k)
                {
                    //std::cout<<m[i][j]<<"\n";
                    tmp[i][j] += m_data[i][k] * rhs.m_data[k][j];

                    //std::cout<<m_data[i][k] * rhs.m_data[k][j]<<"\n";
                }
            }
        }

        // assignning the tmp matrix's values to m_data
        for(int i=0; i<ROWS; i++)
        {
            for(int j=0; j<COLS; j++)
            {
              m_data[i][j]=tmp[i][j];

            }

        }

    return *this;

    }

    // vector vector multiplication
    else if (m_vector == true)
    {
        for(int i = 0; i < COLS; i++)
        {
            m_data[0][i]=m_data[0][i]*rhs.m_data[0][i];
        }

        return *this;
    }

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator* (T scalar)
{

    //std::copy(rhs.begin(),rhs.end(), begin());
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=m_data[i][j]*scalar;

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator/ (T scalar)
{

    //std::copy(rhs.begin(),rhs.end(), begin());
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=m_data[i][j]/scalar;

        }

    }

    return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::rangeCheck(std::size_t rowID,std::size_t colID)
{
    if( rowID!=ROWS)
        throw std::out_of_range("row out of range");

    if( colID!=COLS)
        throw std::out_of_range("column out of range");
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::vectorCheck()
{
    if( m_vector == false)
        throw std::out_of_range("You must use vectors only for this function");

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
T& Matrix< T,ROWS,COLS>::operator()(std::size_t rowID,std::size_t colID)
{
    rangeCheck(rowID,colID);
    return m_data[rowID-1][colID-1];
}


//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
const T& Matrix< T,ROWS,COLS>::operator()(std::size_t rowID,std::size_t colID) const
{
    rangeCheck(rowID,colID);
  return const_cast<T&>(m_data[rowID][colID]);
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator/ (const Matrix<T,ROWS,COLS>& rhs)
{
    vectorCheck();
    rhs.vectorCheck();

    for(int i = 0; i< COLS; i++)
    {
        m_data[0][i]=m_data[0][i]/rhs.m_data[0][i];
    }

    return *this;


}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
float Matrix<T, ROWS, COLS>::magnitude()
{
    vectorCheck();

    T sum = 0;
    float mag = 0;

    for( int i = 0; i< COLS; i++)
    {
        sum += (m_data[0][i] * m_data[0][i]);
    }

    mag= sqrt(sum);

    std::cout<<"magnitude is "<<mag<<"\n";

    return mag;




}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
float Matrix<T,ROWS,COLS>::dot( Matrix<T,ROWS,COLS>& rhs)
{
    vectorCheck();
    rhs.vectorCheck();

    float dotProd = 0;

    for(int i = 0; i<COLS; i++)
    {
        dotProd+=m_data[0][i]*rhs.m_data[0][i];

    }

    std::cout<<"The dot product is "<<dotProd<< "\n";



    return dotProd;


}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
float Matrix<T,ROWS,COLS>::angle( Matrix<T,ROWS,COLS>& rhs)
{
    vectorCheck();
    rhs.vectorCheck();

    float angle = 0;
    float cosAngle = 0;
    float dotProd = 0;
    float mag1;
    float mag2;

    // calculate angles of each vector
    mag1=magnitude();
    mag2=rhs.magnitude();
    // calculate dot product of vectors
    dotProd= dot(rhs);

    // calculate cos angle
    cosAngle=dotProd / (mag1 * mag2);


    // calculate angle then change from radians to degrees
    angle = (180/PI)*acos(cosAngle);

    std::cout<<"The angle between these vectors is "<<angle<< "\n";


    return angle;


}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS>& Matrix<T, ROWS, COLS>::cross( Matrix<T,ROWS,COLS>& rhs)
{
    vectorCheck();
    rhs.vectorCheck();

    T tmp[ROWS][COLS];

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          tmp[i][j]=0;

        }
    }

//    float mag1 = magnitude();
//    float mag2 = rhs.magnitude();


    // try recursion based on i value to account for any size vector

    tmp[0][0]= m_data[0][1]*rhs.m_data[0][2] - m_data[0][2]*rhs.m_data[0][1];
    tmp[0][1]= m_data[0][2]*rhs.m_data[0][0] - m_data[0][0]*rhs.m_data[0][2];
    tmp[0][2]= m_data[0][0]*rhs.m_data[0][1] - m_data[0][1]*rhs.m_data[0][0];


//        switch(COLS)
//        case(COLS==3) :
//            tmp[0][0]= m_data[0][1]*rhs.m_data[0][2] - m_data[0][2]*rhs.m_data[0][1];
//            tmp[0][1]= m_data[0][2]*rhs.m_data[0][0] - m_data[0][0]*rhs.m_data[0][2];
//            tmp[0][2]= m_data[0][0]*rhs.m_data[0][1] - m_data[0][1]*rhs.m_data[0][0];
//            break

    // assignning the tmp matrix's values to m_data
    for(int i=0; i<ROWS; i++)
    {

          m_data[0][i]=tmp[0][i];

          std::cout<<m_data[0][i]<<"\n";



    }

    return *this;






}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
void Matrix< T,ROWS,COLS>::print()
{
    for(int i = 0; i<ROWS; i++)
      {
          for(int j = 0; j<COLS; j++)
          {
              std::cout<<m_data[i][j]<<" ";

          }
          // print space before starting next row
          std::cout<<"\n";

      }
    std::cout<<"\n";
}

//----------------------------------------------------------------------------------------------
#endif // MATRIX_H
