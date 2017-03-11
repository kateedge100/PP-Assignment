#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "quaternion.h"


/// \author Kate Edge
/// \version 1.0
/// \date 15/3/17 \n


template <typename T, size_t ROWS=0, size_t COLS=0>

/// \class Matrix
/// \brief Creates matrices and vectors using a template type, number of rows and numbers of columns and applies a variety of operations and functions to them
///
class Matrix
{
private:

    // number of rows
    int m_rows=ROWS;

    // number of columns
    int m_cols=COLS;

    // 2 dimensional array constaining the values of a matrix ( or vector if ROW or COL equils 1)
    T m_data[ROWS][COLS];

    // stores true after testing if matrix has one col or one row hence is a vector
    bool m_vector = false;

    // function to check for a valid row and column range.
    void rangeCheck(std::size_t rowID, std::size_t _colID);

    // function to check if matrix is a vector
    void vectorCheck();

public:

    // default contructor will set data to zero
    Matrix();

    // constructor that initialises data using an initializer list
    Matrix(std::initializer_list<T> data);

    // copy constructor
    Matrix(const Matrix<T,ROWS,COLS>& _rhs);


    // read only returns number of rows
    const int* rows() const { return m_rows; }
    // accessible number of rows
    int getRows(){return m_rows;}
    // read only returns number of cols
    const int* cols() const { return m_cols; }
    // accessably number of cols
    int getCols(){return m_cols;}

    // read only data
    const T* data(int _row, int _col) const { return m_data[_row][_col]; }
    // accessible data
    T data(int _row, int _col) { return m_data[_row][_col]; }


    // subscript operators
    //code referenced from http://www.learncpp.com/cpp-tutorial/99-overloading-the-parenthesis-operator/
    T& operator()(std::size_t _rowID, std::size_t _colID);
    const T& operator()(std::size_t _rowID, std::size_t _colID) const ; // for const objects


    /// Matrix and Vector Operation

    // assignment operator ( handles different sized matrices for matrix multiplication )
    template <size_t N,size_t M>
    Matrix<T, ROWS, COLS>
    operator= ( Matrix<T,N,M>& _rhs);


    // assignment operator (same size)
    Matrix& operator= (const Matrix<T,ROWS,COLS>& _rhs);
    // addition operator
    Matrix& operator+ (const Matrix<T,ROWS,COLS>& _rhs);
    // subtraction operator
    Matrix& operator- (const Matrix<T,ROWS,COLS>& _rhs);
    // equility operator
    bool operator== (const Matrix<T,ROWS,COLS>& _rhs);
    // negative operator
    Matrix& operator- ();


    // addition operator scalar
    Matrix& operator+ (T _scalar);
    // subtraction operator scalar
    Matrix& operator- (T _scalar);
    // multiply operator scalar
    Matrix& operator* (T _scalar);
    // division operator scalar
    Matrix& operator/ (T _scalar);

    /// Matrix only operations

    // multiply operator
    template <size_t N>
    Matrix<T, ROWS, COLS>&
    operator* ( Matrix<T,COLS,N>& _rhs);
    // inverses a matrix
    Matrix& inverse();
    // determinant of a matrix
    T determinant();
    // minor of a matrix
    Matrix&  minorMatrix(int _row, int _col);
    // transposes matrix
    Matrix& transpose();
    // tests if matrix is orthogonal
    bool orthogonal();


    /// Vector only methods

    // finds the magnitude of a vector
    float magnitude();
    // divide one vector by another
    Matrix& operator/ (Matrix<T,ROWS,COLS>& _rhs);
    // dot product
    float dot(Matrix<T,ROWS,COLS>& _rhs);
    // angle between vectors
    float angle(Matrix<T,ROWS,COLS>& _rhs);
    // cross product
    Matrix& cross(Matrix<T,ROWS,COLS>& _rhs);
    // rotates vector by angle _angle around axis _axis (if 3d)
    Matrix& rotateVector(T _angle, const char* _axis);
    // normalizes vector
    Matrix& normalizeVector();

    //resize matrix or vector
    void resize(int _rows, int _cols);

    // prints out matrix or vector
    void print();

};

//----------------------------------------------------------------------------------------------

/// Default constructor, sets all values to type T and equil to zero
template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix() // DEFAULT CONSTRUCTOR
{
  for (int r=0; r < ROWS; ++r)
  {
    for (int c=0; c < COLS; ++c)
    {

      m_data[r][c]=0;
    }
  }

  if(ROWS==1 || COLS==1)
  {
    m_vector=true;
  }
}
//----------------------------------------------------------------------------------------------

/// Copy constructor
template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix(const Matrix<T,ROWS,COLS>& _rhs)
{
  for(int i=0; i<m_rows; i++)
  {
    for(int j=0; j<m_cols; j++)
    {
      m_data[i][j]=_rhs.m_data[i][j];
    }

  }
}

//----------------------------------------------------------------------------------------------

/// Initializer list constructor
/// Allows user to construct a matrix or vector using an initializer list to assign its values
/// Borrowed from Jon Macey code from Array.h
template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix(std::initializer_list<T> data)
{
  // throws error if too many values in initializer list, if too few the remaining vaules remain equil to 0
  if(data.size()>ROWS*COLS)
  {
    throw std::out_of_range("Too many elements initialized");
  }
  // copies the initializer lists data to m_data
  std::copy(data.begin(),data.end(),&m_data[0][0]);
}

//----------------------------------------------------------------------------------------------

//Assignment operator, variable sized matrices (for matrix multiplication assignment)
template <typename T, size_t ROWS, size_t COLS>
template<size_t N,size_t M>
Matrix<T,ROWS,COLS> Matrix< T,ROWS,COLS>::operator= ( Matrix<T,N,M>& _rhs)
{

  for(int i=0; i<m_rows; i++)
  {
    for(int j=0; j<m_cols; j++)
    {
      m_data[i][j]=_rhs.data(i,j);
    }

  }

  return *this;
}

//----------------------------------------------------------------------------------------------

/// Assignment Operator
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator= (const Matrix<T,ROWS,COLS>& _rhs)
{

  rangeCheck(_rhs.m_rows,_rhs.m_cols);

  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      m_data[i][j]=_rhs.m_data[i][j];
    }
  }

  return *this;
}

//----------------------------------------------------------------------------------------------

/// Equility Operator
template <typename T, size_t ROWS, size_t COLS>
bool Matrix< T,ROWS,COLS>::operator== (const Matrix<T,ROWS,COLS>& _rhs)
{
  for(int i = 0; i < m_rows; i ++)
  {
    for(int j = 0; j < m_cols; j ++)
    {
      if(m_data[i][j]!=_rhs.m_data[i][j])
      {
          return false;
      }
    }
  }

  return true;
}

//----------------------------------------------------------------------------------------------

/// Addition operator for matrix/vector and matrix/vector addition
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator+ (const Matrix<T,ROWS,COLS>& _rhs)
{
  rangeCheck(_rhs.m_rows,_rhs.m_cols);

  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      m_data[i][j]=m_data[i][j]+_rhs.m_data[i][j];
    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Addition operator for _scalar and matrix/vector addition
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator+ (T _scalar)
{

  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      m_data[i][j]=m_data[i][j]+ _scalar;
    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Subtraction operator for matrix/vector and matrix/vector subtraction
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator- (const Matrix<T,ROWS,COLS>& _rhs)
{
  rangeCheck(_rhs.m_rows,_rhs.m_cols);

  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      m_data[i][j]=m_data[i][j]-_rhs.m_data[i][j];
    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Subtraction operator for matrix/vector and _scalar subtration
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator- (T _scalar)
{
  //std::copy(_rhs.begin(),_rhs.end(), begin());
  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      m_data[i][j]=m_data[i][j]- _scalar;

    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Negative operator
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator- ()
{

  //std::copy(_rhs.begin(),_rhs.end(), begin());
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

/// Matrix multiplication operator
template <typename T, size_t ROWS, size_t COLS>
template<size_t N>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator* ( Matrix<T,COLS, N>& _rhs)
{
  // matrix-matrix multiplication
  if(m_vector == false)
  {
    if( COLS!=_rhs.getRows())
    {
      throw std::out_of_range("number of columns of matrix 1 must be equil to number of rows of matrix 2");
    }

    // initialize tmp matrix values to 0
    T tmp[m_rows][_rhs.getCols()];

    for(int i=0; i<ROWS; i++)
    {
      for(int j=0; j<COLS; j++)
      {
        tmp[i][j]=0;
      }
    }

    // For loop structure referenced from http://stackoverflow.com/questions/10162467/matrix-multiplication-in-c
    // Multiplying matrices and storing values in matrix tmp
    for(int i = 0; i < m_rows; ++i)
    {
      for(int j = 0; j < _rhs.getCols(); ++j)
      {
        for(int k=0; k<m_cols; ++k)
        {
            tmp[i][j] += m_data[i][k] * _rhs.data(k,j);
        }
      }
    }

    // resizes matrix to 1st matrix rows x second matrix cols
    //resize(m_rows,_rhs.getCols());

    // assignning the tmp matrix's values to m_data
    for(int i=0; i<m_rows; i++)
    {
      for(int j=0; j<m_cols; j++)
      {
        m_data[i][j]=tmp[i][j];
      }
    }
  }

  // vector vector multiplication
  else if (m_vector == true)
  {
    for(int i = 0; i < COLS; i++)
    {
        m_data[0][i]=m_data[0][i]*_rhs.data(0,i);
    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Multiplication opertor for matrix/vector and _scalar
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator* (T _scalar)
{
  for(int i=0; i<ROWS; i++)
  {
      for(int j=0; j<COLS; j++)
      {
        m_data[i][j]=m_data[i][j]*_scalar;
      }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Division operator for matrix/vector and _scalar
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator/ (T _scalar)
{
  if(_scalar==0)
  {
    throw std::out_of_range("Cannot divide by 0");
  }


  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      m_data[i][j]=m_data[i][j]/_scalar;
    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

/// Checks rows and columns are in correct range
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::rangeCheck(std::size_t _rowID,std::size_t _colID)
{
  if( _rowID>ROWS || _rowID<1)
      throw std::out_of_range("row out of range");

  if( _colID>COLS || _colID<1)
      throw std::out_of_range("column out of range");
}

//----------------------------------------------------------------------------------------------

/// Checks that function is being applied to a vector not a matrix
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T, ROWS, COLS>::vectorCheck()
{
  if(m_rows !=1 && m_cols !=1)
  {
      throw std::out_of_range("You must use vectors only for this function");
  }

}

//----------------------------------------------------------------------------------------------

/// Subscript operator used to view or edit values of matrix/vector based on row and column
template <typename T, size_t ROWS, size_t COLS>
T& Matrix< T,ROWS,COLS>::operator()(std::size_t _rowID,std::size_t _colID)
{
  rangeCheck(_rowID,_colID);
  return m_data[_rowID-1][_colID-1];
}


//----------------------------------------------------------------------------------------------

/// Subscript operator used to view values of matrix/vector based on row and column (read only)
template <typename T, size_t ROWS, size_t COLS>
const T& Matrix< T,ROWS,COLS>::operator()(std::size_t _rowID,std::size_t _colID) const
{
  rangeCheck(_rowID,_colID);
  return const_cast<T&>(m_data[_rowID-1][_colID-1]);
}

//----------------------------------------------------------------------------------------------

/// Division operator for vector and vector
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator/ ( Matrix<T,ROWS,COLS>& _rhs)
{
  vectorCheck();
  _rhs.vectorCheck();

  if(m_rows==1)
  {
   for(int i = 0; i< COLS; i++)
   {
     m_data[0][i]=m_data[0][i]/_rhs.m_data[0][i];
   }
  }

  else if(m_cols==1)
  {
   for(int i = 0; i< ROWS; i++)
   {
     m_data[i][0]=m_data[i][0]/_rhs.m_data[i][0];
   }
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

  if(m_rows == 1)
  {
    for( int i = 0; i< COLS; i++)
    {
      sum += (m_data[0][i] * m_data[0][i]);
    }
  }

  if(m_cols == 1)
  {
    for( int i = 0; i< ROWS; i++)
    {
      sum += (m_data[i][0] * m_data[i][0]);
    }
  }

  mag= sqrt(sum);

  return mag;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
float Matrix<T,ROWS,COLS>::dot( Matrix<T,ROWS,COLS>& _rhs)
{
  vectorCheck();
  _rhs.vectorCheck();

  float dotProd = 0;

  if(m_rows == 1)
  {
    for(int i = 0; i<COLS; i++)
    {
      dotProd+=m_data[0][i]*_rhs.m_data[0][i];
    }
  }

  else if(m_cols == 1)
  {
    for(int i = 0; i<COLS; i++)
    {
      dotProd+=m_data[i][0]*_rhs.m_data[i][0];
    }
  }

  return dotProd;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
float Matrix<T,ROWS,COLS>::angle( Matrix<T,ROWS,COLS>& _rhs)
{
  vectorCheck();
  _rhs.vectorCheck();

  float angle = 0;
  float cosAngle = 0;
  float dotProd = 0;
  float mag1;
  float mag2;

  // calculate angles of each vector
  mag1=magnitude();
  mag2=_rhs.magnitude();
  // calculate dot product of vectors
  dotProd= dot(_rhs);

  // calculate cos angle
  cosAngle=dotProd / (mag1 * mag2);


  // calculate angle then change from radians to degrees
  angle = (180/M_PI)*acos(cosAngle);

  return angle;


}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS>& Matrix<T, ROWS, COLS>::cross( Matrix<T,ROWS,COLS>& _rhs)
{
  if( ROWS*COLS != 3)
  {
    throw std::out_of_range("You must use a 3D vector for the cross product function");
  }

  vectorCheck();
  _rhs.vectorCheck();

  T tmp[ROWS][COLS];

  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      tmp[i][j]=0;

    }
  }

  // col vector
  if(m_rows==1)
  {

    tmp[0][0]= m_data[0][1]*_rhs.m_data[0][2] - m_data[0][2]*_rhs.m_data[0][1];
    tmp[0][1]= m_data[0][2]*_rhs.m_data[0][0] - m_data[0][0]*_rhs.m_data[0][2];
    tmp[0][2]= m_data[0][0]*_rhs.m_data[0][1] - m_data[0][1]*_rhs.m_data[0][0];

    // assignning the tmp matrix's values to m_data
    for(int i=0; i<COLS; i++)
    {
      m_data[0][i]=tmp[0][i];
    }

  }

  // row vector
  else if(m_cols==1)
  {
    tmp[0][0]= m_data[1][0]*_rhs.m_data[2][0] - m_data[2][0]*_rhs.m_data[1][0];
    tmp[1][0]= m_data[2][0]*_rhs.m_data[0][0] - m_data[0][0]*_rhs.m_data[2][0];
    tmp[2][0]= m_data[0][0]*_rhs.m_data[1][0] - m_data[1][0]*_rhs.m_data[0][0];

    // assignning the tmp matrix's values to m_data
    for(int i=0; i<ROWS; i++)
    {
      m_data[0][i]=tmp[0][i];
    }
  }

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::minorMatrix(int _row, int _col)
{

  // temporary matrix to store the minor matrices data
  T tmp[ROWS-1][COLS-1];

  // new matrix row index
  int k=0;
  // nex matrix column index
  int l=0;

  for(int i=0; i<ROWS-1; i++)
  {
    for(int j=0; j<COLS-1; j++)
    {
      tmp[i][j]=0;
    }
  }

  // row of minor matrix
  for(int i = 0; i<m_rows; i++)
  {
    if(i==_row-1)
    {
        i++;
    }

    // col of minor matrix
    for(int j = 0; j<m_cols; j++)
    {
      if(j==_col-1)
      {
        j++;
      }
      tmp[k][l]=m_data[i][j];
      l++;
    }
    // go back to first column
    l=0;
    k++;

  }

  // m_data row 1 disquilified so m-data row 2 equils tmp row 1

  for(int i=0; i<ROWS-1; i++)
  {
    for(int j=0; j<COLS-1; j++)
    {
      m_data[i][j]=tmp[i][j];
    }

  }

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
T Matrix< T,ROWS,COLS>::determinant()
{
  // test to see if matrix times inverse equils identity
  if( ROWS != COLS)
  {
    throw std::out_of_range("You must use a square matrix for the inverse function");
  }

  T determinant = 0;

  if(ROWS==2)
  {
    determinant = (m_data[0][0]*m_data[1][1])-(m_data[0][1]*m_data[1][0]);

  }

  else if(ROWS==3)
  {
    for(int i=0;i<3;i++)
    {
     determinant = determinant + (m_data[0][i]*(m_data[1][(i+1)%3]*m_data[2][(i+2)%3] - m_data[1][(i+2)%3]*m_data[2][(i+1)%3]));
    }
  }

  else if(ROWS==4)
  {
    T inv[4][4];
    inv[0][0] = m_data[1][1] * m_data[2][2] * m_data[3][3] -
                m_data[1][1] * m_data[2][3] * m_data[3][2] -
                m_data[2][1] * m_data[1][2] * m_data[3][3] +
                m_data[2][1] * m_data[1][3] * m_data[3][2] +
                m_data[3][1] * m_data[1][2] * m_data[2][3] -
                m_data[3][1] * m_data[1][3] * m_data[2][2];



    inv[1][0] = -m_data[1][0] * m_data[2][2] * m_data[3][3] +
                 m_data[1][0] * m_data[2][3] * m_data[3][2] +
                 m_data[2][0] * m_data[1][2] * m_data[3][3] -
                 m_data[2][0] * m_data[1][3] * m_data[3][2] -
                 m_data[3][0] * m_data[1][2] * m_data[2][3] +
                 m_data[3][0] * m_data[1][3] * m_data[2][2];


    inv[2][0] =  m_data[1][0] * m_data[2][1] * m_data[3][3] -
                 m_data[1][0] * m_data[2][3] * m_data[3][1] -
                 m_data[2][0] * m_data[1][1] * m_data[3][3] +
                 m_data[2][0] * m_data[1][3] * m_data[3][1] +
                 m_data[3][0] * m_data[1][1] * m_data[2][3] -
                 m_data[3][0] * m_data[1][3] * m_data[2][1];

    inv[3][0] = -m_data[1][0] * m_data[2][1] * m_data[3][2] +
                 m_data[1][0] * m_data[2][2] * m_data[3][1] +
                 m_data[2][0] * m_data[1][1] * m_data[3][2] -
                 m_data[2][0] * m_data[1][2] * m_data[3][1] -
                 m_data[3][0] * m_data[1][1] * m_data[2][2] +
                 m_data[3][0] * m_data[1][2] * m_data[2][1];


    determinant = m_data[0][0] * inv[0][0] + m_data[0][1] * inv[1][0] + m_data[0][2] * inv[2][0] + m_data[0][3] * inv[3][0];

  }

  return determinant;
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::inverse()
{
  // test to see if matrix times inverse equils identity
  if( ROWS != COLS)
  {
   throw std::out_of_range("You must use a square matrix for the inverse function");
  }

  T tmp[ROWS][COLS];

  for(int i=0; i<ROWS; i++)
  {
    for(int j=0; j<COLS; j++)
    {
      tmp[i][j]=0;
    }
  }

  // find inverse of 2x2 matrix
  if(ROWS==2)
  {
    tmp[0][0]= m_data[1][1];
    tmp[0][1]=-m_data[0][1];
    tmp[1][0]=-m_data[1][0];
    tmp[1][1]= m_data[0][0];



    if( determinant()==0)
    {
      throw std::out_of_range("An inverse doesnt exist, the determinant is 0");
    }

    for(int i = 0; i<ROWS; i++)
    {
      for( int j = 0; j<COLS; j++)
      {

        tmp[i][j]=tmp[i][j]/determinant();
      }
    }
  }

  /// referenced from http://forgetcode.com/C/1781-Inverse-Matrix-of-3x3
  if(ROWS==3)
  {

    if( determinant()==0)
    {
      throw std::out_of_range("An inverse doesnt exist, the determinant is 0");
    }

    //std::cout<<"\nInverse of matrix is: \n\n";
    for(int i=0;i<3;i++)
    {

      for(int j=0;j<3;j++)
      {
        tmp[j][i] = ((m_data[(i+1)%3][(j+1)%3] * m_data[(i+2)%3][(j+2)%3]) -
                    (m_data[(i+1)%3][(j+2)%3]*m_data[(i+2)%3][(j+1)%3]))/ determinant();
      }
    }
  }

  // referenced from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
  // 4x4 matrix
  if(ROWS==4)
  {
    T inv[4][4];

    T det = 0;

    // initilize inv matrix values to zero
    for(int i = 0; i<ROWS; i++)
    {
      for( int j = 0; j<COLS; j++)
      {
        inv[i][j]=0;
      }
    }

    inv[0][0] = m_data[1][1]  * m_data[2][2] * m_data[3][3] - //0
                m_data[1][1]  * m_data[2][3] * m_data[3][2] -
                m_data[2][1]  * m_data[1][2]  * m_data[3][3] +
                m_data[2][1]  * m_data[1][3]  * m_data[3][2] +
                m_data[3][1] * m_data[1][2]  * m_data[2][3] -
                m_data[3][1] * m_data[1][3]  * m_data[2][2];



    inv[1][0] = -m_data[1][0]  * m_data[2][2] * m_data[3][3] + //4
                 m_data[1][0]  * m_data[2][3] * m_data[3][2] +
                 m_data[2][0]  * m_data[1][2]  * m_data[3][3] -
                 m_data[2][0]  * m_data[1][3]  * m_data[3][2] -
                 m_data[3][0] * m_data[1][2]  * m_data[2][3] +
                 m_data[3][0] * m_data[1][3]  * m_data[2][2];


    inv[2][0] = m_data[1][0]  * m_data[2][1] * m_data[3][3] - //8
                m_data[1][0]  * m_data[2][3] * m_data[3][1] -
                m_data[2][0]  * m_data[1][1] * m_data[3][3] +
                m_data[2][0]  * m_data[1][3] * m_data[3][1] +
                m_data[3][0] * m_data[1][1] * m_data[2][3] -
                m_data[3][0] * m_data[1][3] * m_data[2][1];

    inv[3][0] = -m_data[1][0]  * m_data[2][1] * m_data[3][2] + //12
                 m_data[1][0]  * m_data[2][2] * m_data[3][1] +
                 m_data[2][0]  * m_data[1][1] * m_data[3][2] -
                 m_data[2][0]  * m_data[1][2] * m_data[3][1] -
                 m_data[3][0] * m_data[1][1] * m_data[2][2] +
                 m_data[3][0] * m_data[1][2] * m_data[2][1];

    inv[0][1] = -m_data[0][1]  * m_data[2][2] * m_data[3][3] + //1
                 m_data[0][1]  * m_data[2][3] * m_data[3][2] +
                 m_data[2][1]  * m_data[0][2] * m_data[3][3] -
                 m_data[2][1]  * m_data[0][3] * m_data[3][2] -
                 m_data[3][1] * m_data[0][2] * m_data[2][3] +
                 m_data[3][1] * m_data[0][3] * m_data[2][2];

    inv[1][1] = m_data[0][0]  * m_data[2][2] * m_data[3][3] - //5
                m_data[0][0]  * m_data[2][3] * m_data[3][2] -
                m_data[2][0]  * m_data[0][2] * m_data[3][3] +
                m_data[2][0]  * m_data[0][3] * m_data[3][2] +
                m_data[3][0] * m_data[0][2] * m_data[2][3] -
                m_data[3][0] * m_data[0][3] * m_data[2][2];

    inv[2][1] = -m_data[0][0]  * m_data[2][1] * m_data[3][3] + //9
                 m_data[0][0]  * m_data[2][3] * m_data[3][1] +
                 m_data[2][0]  * m_data[0][1] * m_data[3][3] -
                 m_data[2][0]  * m_data[0][3] * m_data[3][1] -
                 m_data[3][0] * m_data[0][1] * m_data[2][3] +
                 m_data[3][0] * m_data[0][3] * m_data[2][1];

    inv[3][1] = m_data[0][0]  * m_data[2][1] * m_data[3][2] - //13
                m_data[0][0]  * m_data[2][2] * m_data[3][1] -
                m_data[2][0]  * m_data[0][1] * m_data[3][2] +
                m_data[2][0]  * m_data[0][2] * m_data[3][1] +
                m_data[3][0] * m_data[0][1] * m_data[2][2] -
                m_data[3][0] * m_data[0][2] * m_data[2][1];

    inv[0][2] = m_data[0][1]  * m_data[1][2] * m_data[3][3] - //2
                m_data[0][1]  * m_data[1][3] * m_data[3][2] -
                m_data[1][1]  * m_data[0][2] * m_data[3][3] +
                m_data[1][1]  * m_data[0][3] * m_data[3][2] +
                m_data[3][1] * m_data[0][2] * m_data[1][3] -
                m_data[3][1] * m_data[0][3] * m_data[1][2];

    inv[1][2] = -m_data[0][0]  * m_data[1][2] * m_data[3][3] + //6
                 m_data[0][0]  * m_data[1][3] * m_data[3][2] +
                 m_data[1][0]  * m_data[0][2] * m_data[3][3] -
                 m_data[1][0]  * m_data[0][3] * m_data[3][2] -
                 m_data[3][0] * m_data[0][2] * m_data[1][3] +
                 m_data[3][0] * m_data[0][3] * m_data[1][2];

    inv[2][2] = m_data[0][0]  * m_data[1][1] * m_data[3][3] - //10
                m_data[0][0]  * m_data[1][3] * m_data[3][1] -
                m_data[1][0]  * m_data[0][1] * m_data[3][3] +
                m_data[1][0]  * m_data[0][3] * m_data[3][1] +
                m_data[3][0] * m_data[0][1] * m_data[1][3] -
                m_data[3][0] * m_data[0][3] * m_data[1][1];

    inv[3][2] = -m_data[0][0]  * m_data[1][1] * m_data[3][2] + //14
                 m_data[0][0]  * m_data[1][2] * m_data[3][1] +
                 m_data[1][0]  * m_data[0][1] * m_data[3][2] -
                 m_data[1][0]  * m_data[0][2] * m_data[3][1] -
                 m_data[3][0] * m_data[0][1] * m_data[1][2] +
                 m_data[3][0] * m_data[0][2] * m_data[1][1];

    inv[0][3] = -m_data[0][1] * m_data[1][2] * m_data[2][3] + //3
                 m_data[0][1] * m_data[1][3] * m_data[2][2] +
                 m_data[1][1] * m_data[0][2] * m_data[2][3] -
                 m_data[1][1] * m_data[0][3] * m_data[2][2] -
                 m_data[2][1] * m_data[0][2] * m_data[1][3] +
                 m_data[2][1] * m_data[0][3] * m_data[1][2];

    inv[0][7] = m_data[0][0] * m_data[1][2] * m_data[2][3] - //7
                m_data[0][0] * m_data[1][3] * m_data[2][2] -
                m_data[1][0] * m_data[0][2] * m_data[2][3] +
                m_data[1][0] * m_data[0][3] * m_data[2][2] +
                m_data[2][0] * m_data[0][2] * m_data[1][3] -
                m_data[2][0] * m_data[0][3] * m_data[1][2];

    inv[2][3] = -m_data[0][0] * m_data[1][1] * m_data[2][3] + //11
                 m_data[0][0] * m_data[1][3] * m_data[2][1] +
                 m_data[1][0] * m_data[0][1] * m_data[2][3] -
                 m_data[1][0] * m_data[0][3] * m_data[2][1] -
                 m_data[2][0] * m_data[0][1] * m_data[1][3] +
                 m_data[2][0] * m_data[0][3] * m_data[1][1];

    inv[3][3] = m_data[0][0] * m_data[1][1] * m_data[2][2] - //15
                m_data[0][0] * m_data[1][2] * m_data[2][1] -
                m_data[1][0] * m_data[0][1] * m_data[2][2] +
                m_data[1][0] * m_data[0][2] * m_data[2][1] +
                m_data[2][0] * m_data[0][1] * m_data[1][2] -
                m_data[2][0] * m_data[0][2] * m_data[1][1];



    if( determinant()==0)
    {
         throw std::out_of_range("An inverse doesnt exist, the determinant is 0");
    }


    det=1.0/determinant();

    for(int i = 0; i<ROWS; i++)
    {
      for( int j = 0; j<COLS; j++)
      {
        tmp[i][j] = inv[i][j] * det;
      }
    }
  }

  for(int i = 0; i<ROWS; i++)
  {
    for( int j = 0; j<COLS; j++)
    {
      m_data[i][j]=tmp[i][j];
    }
  }

  return *this;
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS, COLS>& Matrix< T,ROWS,COLS>::transpose()
{
  std::cout<<"transpose \n";

  T tmp[COLS][ROWS];

  for(int i = 0;i<COLS;i++)
  {
    for(int j = 0;j< ROWS;j++)
    {
      tmp[i][j]=0;
      std::cout<<tmp[i][j]<<" ";
    }
      std::cout<<" tmp \n";
  }

  for(int i = 0; i< COLS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      tmp[i][j]= m_data[j][i];
      std::cout<<tmp[i][j]<<" ";
    }
    std::cout<<" assigned \n";
  }

  resize(COLS,ROWS);

  std::cout<<m_rows<<" m_rows resized \n";
  std::cout<<m_cols<<" m_colss resized \n";

  print();

  for(int i = 0; i<m_rows; i++)
  {
    for( int j = 0; j<m_cols; j++)
    {
      m_data[i][j]=tmp[i][j];
      std::cout<<i<<j<<m_data[i][j]<<" m_data resized \n";
      std::cout<<m_data[0][2]<<" correct this \n";
    }
    std::cout<<m_data[0][2]<<" correct this \n";
  }

  return *this;
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
bool Matrix< T,ROWS,COLS>::orthogonal()
{
  if(inverse()==transpose())
  {
    return true;
  }
  else
  {
    return false;
  }

}

//----------------------------------------------------------------------------------------------
/// rotates by angle _angle counter clockwise around the selected origin
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix<T,ROWS,COLS>::rotateVector(T _angle,const char* _axis)
{

  vectorCheck();

  if(m_cols!=1)
  {
    throw std::out_of_range("Must use a column vector for rotation eg Matrix<float,3,1>");
  }

  if(m_rows!= 2 && m_rows !=3)
  {
    throw std::out_of_range("Only 2D and 3D vectors are supported for rotation");
  }


  for(int i = 0; i < m_rows; i++)
  {
    for(int j; j< m_cols; j++)
    {
        //rotMat[i][j]=0;
    }
  }

  T tmp [m_rows];

  for(int i = 0 ;i<m_rows;i++)
  {
    tmp[i]=0;
  }

  //convert to radians
  double angle= _angle * (M_PI /180);


  // if 2d column vector use 2d rotation matrix
  if(m_rows==2)
  {
    T rotMat [m_rows][m_rows];

    // counter clockwise around the origin
    rotMat[0][0]=cos(angle);
    rotMat[0][1]= -sin(angle);
    rotMat[1][0]= sin(angle);
    rotMat[1][1]= cos(angle);

    for(int i = 0; i < 2; i ++)
    {
      for(int j = 0; j < 2; j++)
      {
          tmp[i]+=rotMat[i][j]*m_data[j][0];

      }
    }
  }

  // if 3d vector use 3d rotation matrix
  if(m_rows==3)
  {
    if(_axis == "x")
    {
      T rotMat [3][3]={1,0,0,0,cos(angle),-sin(angle),0,sin(-angle),cos(angle)};

      for(int i = 0; i < 3; i ++)
      {
        for(int j = 0; j < 3; j++)
        {
          tmp[i]+=rotMat[i][j]*m_data[j][0];
        }
      }
    }

    if(_axis == "y"){T rotMat [3][3]={cos(angle),0,sin(angle),0,1,0,-sin(angle),0,cos(-angle)};

      for(int i = 0; i < 3; i ++)
      {
        for(int j = 0; j < 3; j++)
        {
          tmp[i]+=rotMat[i][j]*m_data[j][0];
        }
      }
    }

    if(_axis == "z")
    {
      T rotMat [3][3]={cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1};

      for(int i = 0; i < 3; i ++)
      {
        for(int j = 0; j < 3; j++)
        {
          tmp[i]+=rotMat[i][j]*m_data[j][0];
        }
      }
    }
  }

  for(int i = 0; i < m_rows; i ++)
  {
    m_data[i][0]=tmp[i];
  }

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix<T,ROWS,COLS>::normalizeVector()
{
  vectorCheck();

  T mag=magnitude();

  if(m_rows==1)
  {
    for(int i=0; i<m_cols; i++)
    {
      m_data[0][i]=m_data[0][i]/mag;
    }
  }

  if(m_cols==1)
  {
    for(int i=0; i<m_rows; i++)
    {
      m_data[i][0]=m_data[i][0]/mag;
    }
  }

    return *this;
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
void Matrix< T,ROWS,COLS>::resize(int _rows, int _cols)
{
  if(ROWS*COLS != _rows*_cols)
  {
    throw std::out_of_range("Must resize to matrix with same number of elements, eg 2x3 to 3x2");
  }

  m_data[m_rows][m_cols]=m_data[_rows][_cols];

  m_rows=_rows;
  m_cols=_cols;

  for(int i = 0;i<m_rows;i++)
  {
    for(int j = 0;j< m_cols;j++)
    {
      m_data[i][j]=0;
    }

  }

//    T tmp[m_cols][m_ros];

//    for(int i = 0;i<m_rows;i++)
//       {
//           for(int j = 0;j< m_cols;j++)
//           {

//               tmp[i][j]=0;

//           }

//       }

//    for(int i = 0;i<m_rows;i++)
//       {
//           for(int j = 0;j< m_cols;j++)
//           {

//               tmp[i][j]=m_data[i][j];
//               std::cout<<tmp[i][j]<<" resize tmp \n";

//           }

//       }


    //std::cout<<m_data[2][0]<<"\n";
    //std::cout<<m_cols;
    //m_data[0][3]=0;

//    for(int i = 0;i<m_rows;i++)
//       {
//           for(int j = 0;j< m_cols;j++)
//           {

//               m_data[i][j]=tmp[j][i];
//               std::cout<<m_data[i][j]<<" resize new element \n";
//           }

//       }


//    // initialize new column elements to zero
//    for(int i = 0;i<m_rows;i++)
//    {
//        for(int j = m_cols;j< _cols;j++)
//        {
//            std::cout<<m_data[1][0]<<"\n";
//            //std::cout<<i<<" "<<j<<"\n";
//            //m_data[i][j]=0;
//            std::cout<< i<<j<<" element "<<m_data[i][j]<<" new element \n";
//        }

//    }

//    // initialize new row elements to zero
//    for(int i = m_rows;i<_rows;i++)
//    {
//        for(int j = 0;j< _cols;j++)
//        {
//            //m_data[i][j]=0;
//            std::cout<< i<<j<<" element "<<m_data[i][j]<<" new element \n";
//        }

//    }


}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
void Matrix< T,ROWS,COLS>::print()
{
  for(int i = 0; i<m_rows; i++)
  {
    for(int j = 0; j<m_cols; j++)
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
