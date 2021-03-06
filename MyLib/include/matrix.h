#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "quaternion.h"


/// \author Kate Edge
/// \version 1.0
/// \date 13/3/17 \n


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

    // function to check if matrix is a vector, used when you want to check if its a vector without throwing an error if it is
    void vectorCheck();

public:

    // default contructor will set data to zero
    Matrix();

    // constructor that initialises data using an initializer list
    Matrix(std::initializer_list<T> data);

    // copy constructor
    Matrix(const Matrix<T,ROWS,COLS>& _rhs);


    // read only returns number of rows
    const int getRows() const { return m_rows; }
    // read only returns number of cols
    const int getCols() const { return m_cols; }


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
    // transposes matrix
    Matrix& transpose();
    // tests if matrix is orthogonal
    bool orthogonal();
    // determinant of a matrix
    T determinant();
    // minor of a matrix
    Matrix&  minorMatrix(int _row, int _col);



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

///@brief Default constructor, sets all values of m_data equil to zero, also determnines if the cretaed matrix is a vector or not
template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix()
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
///@brief Copy constructor
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
/// @brief Initializer list constructor, allows user to construct a matrix or vector using an initializer list to assign its values
/// Borrowed from Jon Macey code from Array.h
/// Modified from :-
/// Jon Macey (January 5th, 2017). Array.h [online].
/// [Accessed Jan 2017]. Available from: "http://www.github.com/".
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
/// @brief Assignment operator for variable sized matrices, needed for matrix multiplication.
/// param[in] _rhs, the matrix or vector that the first matrix or vector will be assigned too
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
/// @brief Asignment Operator
/// param[in] _rhs, the matrix or vector that the first matrix or vector will be assigned too
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
/// @brief Equility Operator, tests if vectors or matrices are equil and returns true if they are
/// param[in] _rhs, the matrix or vector to test that the first vector or matrix equils
template <typename T, size_t ROWS, size_t COLS>
bool Matrix< T,ROWS,COLS>::operator== (const Matrix<T,ROWS,COLS>& _rhs)
{
  bool equil = true;

  for(int i = 0; i < m_rows; i ++)
  {
    for(int j = 0; j < m_cols; j ++)
    {
      if(m_data[i][j]!=_rhs.m_data[i][j])
      {
        equil= false;
      }

    }
  }

  return equil;
}

//----------------------------------------------------------------------------------------------
/// @brief Addition operator for matrix/vector and matrix/vector addition
/// param[in] _rhs, the vector or matrix that is added to the first vector or matrix
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
/// @brief Addition operator for matrix/vector addition by a scalar amount
/// param[in] _scalar, amount to add to each value of m_data for the given matrix/vector
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
/// @brief Subtraction operator for matrix/vector and matrix/vector subtraction
/// param[in] _rhs, the vector or matrix that is subtracted from the first vector or matrix
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

/// @brief Subtraction operator for matrix/vector subtration by a scalar amount
/// param[in] _scalar, amount to subtract from each value of m_data for the given matrix/vector
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
/// @brief Negative operator, returns each value of the matrix or vector with the opposite sign
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
/// @brief Multiplication operator for multiplying two matrices or vectors, the first matrix must have the same number of columns and the second has rows
/// param[in] _rhs, the matrix/vector at the first matrix/vector is multiplied by
/// For loop for multiplying vectors referenced from stackoverflow.com, [accessed Jan 2017](avaiable at http://stackoverflow.com/questions/10162467/matrix-multiplication-in-c)
template <typename T, size_t ROWS, size_t COLS>
template<size_t N>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator* ( Matrix<T,COLS, N>& _rhs)
{
  if( COLS!=_rhs.getRows())
  {
    throw std::out_of_range("number of columns of matrix 1 must be equil to number of rows of matrix 2");
  }

  // matrix-matrix multiplication
  if(m_vector == false)
  {
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
/// @brief Multiplication opertor for matrix/vector and _scalar
/// param[in] _scalar, the value to multiple each value of m_data of the given matrix/vector by
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
/// @brief Division operator for matrix/vector and _scalar
/// param[in] _scalar, the value to divide each value of m_data of the given matrix/vector by
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
/// @brief Checks rows and columns are in correct range, eg if you want the first row you would write 1 opposed to 0.
/// param[in] _rowID, the row you would like to check is within 0 and the number of rows.
/// param[in] _colID, the column you would like to check is within 0 and the number of columns.
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::rangeCheck(std::size_t _rowID,std::size_t _colID)
{
  if( _rowID>ROWS || _rowID<1)
      throw std::out_of_range("row out of range");

  if( _colID>COLS || _colID<1)
      throw std::out_of_range("column out of range");
}

//----------------------------------------------------------------------------------------------
/// @brief Checks that function is being applied to a matrix not a vector, throws error if it is a vector.
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T, ROWS, COLS>::vectorCheck()
{
  if(m_rows !=1 && m_cols !=1)
  {
      throw std::out_of_range("You must use vectors only for this function");
  }

}

//----------------------------------------------------------------------------------------------
/// @brief Subscript operator used to view values of matrix/vector based on row and column, starts at 1 not zero, eg first value is (1,1)
/// param[in] _rowID, the row of the data you would like to access (1 for first row).
/// param[in] _colID, the column of the data you would like to access (1 for first column).
template <typename T, size_t ROWS, size_t COLS>
T& Matrix< T,ROWS,COLS>::operator()(std::size_t _rowID,std::size_t _colID)
{
  rangeCheck(_rowID,_colID);
  return m_data[_rowID-1][_colID-1];
}


//----------------------------------------------------------------------------------------------
/// @brief Subscript operator used to view values of matrix/vector based on row and column (read only)
/// param[in] _rowID, the row of the data you would like to view (1 for first row).
/// param[in] _colID, the column of the data you would like to view (1 for first column).
template <typename T, size_t ROWS, size_t COLS>
const T& Matrix< T,ROWS,COLS>::operator()(std::size_t _rowID,std::size_t _colID) const
{
  rangeCheck(_rowID,_colID);
  return const_cast<T&>(m_data[_rowID-1][_colID-1]);
}

//----------------------------------------------------------------------------------------------
/// @brief Division operator for vector and vector
/// param[in] _rhs, the vector that the will be used to divide the other vector by
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
/// @brief Returns the magnitude of the given vector
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
/// @brief The dot product of the given vector and another vector passed in as a parameter
/// param[in] _rhs, the second vector that will be used to find the dot product
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
/// @brief Returns the angle between two vectors
/// param[in] _rhs, the angle is found between the applied to vector and this vector
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
/// @brief Finds the cross product of two vectors
/// param[in] the second vector that is used to find the cross product
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
/// @brief finds the minor matrix of a matrix
/// param[in] _row, the row to be excluded from the original matrix in order to find the minor matrix
/// param[in] _col, the column to be excluded from the original matrix in order to find the minor matrix
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
/// @brief Returns the determinant of a squre matrix, must be a 2d,3d or 4d vector
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
/// @brief Returns the inverse of a square matrix, must be a 2d,3d or 4d matrix.
/// 3X3 matrix inverse code modified from ForgotCode. [Accessed 2017]. Available from: "http://forgetcode.com/C/1781-Inverse-Matrix-of-3x3"
/// 4x4 matrix inverse code modified from StackOverFlow. [Accessed 2017]. Available from: "http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix"
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::inverse()
{
  // test to see if matrix times inverse equils identity
  if( ROWS != COLS)
  {
   throw std::out_of_range("You must use a square matrix for the inverse function");
  }

  if( determinant()==0)
  {
    throw std::out_of_range("An inverse doesnt exist, the determinant is 0");
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

    inv[0][0] = m_data[1][1] * m_data[2][2] * m_data[3][3] -
                m_data[1][1] * m_data[2][3] * m_data[3][2] -
                m_data[2][1] * m_data[1][2] * m_data[3][3] +
                m_data[2][1] * m_data[1][3] * m_data[3][2] +
                m_data[3][1] * m_data[1][2] * m_data[2][3] -
                m_data[3][1] * m_data[1][3] * m_data[2][2];



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
/// @brief returns the transpose version of a matrix
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS, COLS>& Matrix< T,ROWS,COLS>::transpose()
{ 

  T tmp[COLS][ROWS];

  for(int i = 0;i<COLS;i++)
  {
    for(int j = 0;j< ROWS;j++)
    {
      tmp[i][j]=0;      
    }      
  }

  for(int i = 0; i< COLS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      tmp[i][j]= m_data[j][i];      
    }
  }

  // resize matrix/vector to have reversed number of cols and rows
  resize(COLS,ROWS);

  for(int i = 0; i<m_rows; i++)
  {
    for( int j = 0; j<m_cols; j++)
    {
      m_data[i][j]=tmp[i][j];
    }
  }

  return *this;
}

//----------------------------------------------------------------------------------------------
/// @brief Tests if the matrix is orthogonal (if the inversed matrix equils the transposed matrix)
template <typename T, size_t ROWS, size_t COLS>
bool Matrix< T,ROWS,COLS>::orthogonal()
{
  // must be a square matrix to be orthogonal
  if(m_rows != m_cols)
    {
      return false;
    }

  // temp matrices to store values of transpose and inverse
  Matrix<T,ROWS,COLS> tmp;
  Matrix<T,ROWS,COLS> tmp2;

  tmp = transpose();

  tmp2 =inverse();

  bool orth = false;

  if(tmp == tmp2)
  {
    orth= true;
  }


  return orth;


}

//----------------------------------------------------------------------------------------------
/// @brief Rotates a 2d or 3d column vector by an angle counter clockwise around the selected axis (if 3d).
/// param[in] _angle, the angle to rotate the vector by.
/// param[in] _axis, the axis to rotate the vector around.
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
/// @brief Returns the normalized vector
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
/// @brief Resizes a matrix, resulting matrix must have the same number of elements as original matrix.
/// param[in] _rows, the number of rows of the resulting matrix
/// param[in] _cols, the number of columns of the resulting matrix
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

}

//----------------------------------------------------------------------------------------------
/// @brief Prints out the elements of the vector or matrix in the correct format
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
