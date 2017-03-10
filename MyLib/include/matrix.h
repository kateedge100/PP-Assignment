#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "quaternion.h"


template <typename T, size_t ROWS=0, size_t COLS=0>

class Matrix
{
private:

    // row size
    int m_rows=ROWS;

    // column size
    int m_cols=COLS;

    T m_data[ROWS][COLS];

    // stores if vector after testing if matrix has one col or one row hence is a vector
    bool m_vector = false;

    // function to check for a valid row and column range.
    void rangeCheck(std::size_t rowID, std::size_t colID);

public:

    // default contructor will set data to zero
    Matrix();

    // initialiser list constructor
    Matrix(std::initializer_list<T> data);

    // copy constructor
    Matrix(const Matrix<T,ROWS,COLS>& rhs);

    int getRows(){return m_rows;}
    int getCols(){return m_cols;}

    // read only returns number of rows
    const int* rows() const { return m_rows; }
    // read only returns number of cols
    const int* cols() const { return m_cols; }

    // read only data
    const T* data(int row, int col) const { return m_data[row][col]; }
    // accessible data
    T data(int row, int col) { return m_data[row][col]; }

    // number of elements in matix or array
    //static size_t size()  {return ROWS*COLS;}

    // subscript operators
    //code referenced from http://www.learncpp.com/cpp-tutorial/99-overloading-the-parenthesis-operator/
    T& operator()(std::size_t rowID, std::size_t colID);
    const T& operator()(std::size_t rowID, std::size_t colID) const ; // for const objects

    void vectorCheck();


    /// Matrix and Vector Operation

    // assignment operator ( different sized matrices for matrix multiplication )
    template <size_t N,size_t M>
    Matrix<T, ROWS, COLS>
    operator= ( Matrix<T,N,M>& rhs);


    // assignment operator (same size)
    Matrix& operator= (const Matrix<T,ROWS,COLS>& rhs);
    // addition operator
    Matrix& operator+ (const Matrix<T,ROWS,COLS>& rhs);
    // subtraction operator
    Matrix& operator- (const Matrix<T,ROWS,COLS>& rhs);
    // equility operator
    bool operator== (const Matrix<T,ROWS,COLS>& rhs);
    // negative operator
    Matrix& operator- ();


    // addition operator scalar
    Matrix& operator+ (T scalar);
    // subtraction operator scalar
    Matrix& operator- (T scalar);
    // multiply operator scalar
    Matrix& operator* (T scalar);
    // division operator scalar
    Matrix& operator/ (T scalar);

    /// Matrix only opertaion

    // multiply operator
    template <size_t N>
    Matrix<T, ROWS, COLS>&
    operator* ( Matrix<T,COLS,N>& rhs);
    Matrix& inverse();
    T determinant();
    Matrix&  minorMatrix(int _row, int _col);
    Matrix& transpose();
    bool orthogonal();


    /// Vector only methods

    float magnitude();
    // divide one vector by another
    Matrix& operator/ (Matrix<T,ROWS,COLS>& rhs);
    // dot product
    float dot(Matrix<T,ROWS,COLS>& rhs);
    // angle betwwen vectors
    float angle(Matrix<T,ROWS,COLS>& rhs);
    // cross product
    Matrix& cross(Matrix<T,ROWS,COLS>& rhs);
    // rotates vector by angle _angle
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
        //std::cout<<"is a vector \n";
    }



}
//----------------------------------------------------------------------------------------------

/// Copy constructor
template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix(const Matrix<T,ROWS,COLS>& rhs)
{
    for(int i=0; i<m_rows; i++)
    {
        for(int j=0; j<m_cols; j++)
        {
          m_data[i][j]=rhs.m_data[i][j];

        }

    }

    //std::cout<<" copy constructor called \n";
}

//----------------------------------------------------------------------------------------------

/// Initializer list constructor
/// Allows user to construct a matrix or vector using an initializer list to assign its values
/// Borrowed from Jon Macey
template <typename T, size_t ROWS, size_t COLS>
Matrix< T,ROWS,COLS>::Matrix(std::initializer_list<T> data)
{
    // thorws error if too many values in initializer list, if too few remaining vaules remain 0
    if(data.size()>ROWS*COLS)
        throw std::out_of_range("Too many elements initialized");
    // copies the initializer lists data to m_data
    std::copy(data.begin(),data.end(),&m_data[0][0]);
}

//----------------------------------------------------------------------------------------------

//Assignment operator, variable sized matrices (for matrix multiplication assignment)
template <typename T, size_t ROWS, size_t COLS>
template<size_t N,size_t M>
Matrix<T,ROWS,COLS> Matrix< T,ROWS,COLS>::operator= ( Matrix<T,N,M>& rhs)
{


    for(int i=0; i<m_rows; i++)
    {
        for(int j=0; j<m_cols; j++)
        {
          m_data[i][j]=rhs.data(i,j);
          //std::cout<<m_data[i][j]<<" final data \n";

        }

    }

    return *this;
}


//----------------------------------------------------------------------------------------------

/// Assignment Operator
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

/// Equility Operator
template <typename T, size_t ROWS, size_t COLS>
bool Matrix< T,ROWS,COLS>::operator== (const Matrix<T,ROWS,COLS>& rhs)
{
    for(int i = 0; i < m_rows; i ++)
    {
        for(int j = 0; j < m_cols; j ++)
        {
            if(m_data[i][j]!=rhs.m_data[i][j])
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

/// Addition operator for scalar and matrix/vector addition
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

/// Subtraction operator for matrix/vector and matrix/vector subtraction
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

/// Subtraction operator for matrix/vector and scalar subtration
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

/// Negative operator
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

/// Matrix multiplication operator
template <typename T, size_t ROWS, size_t COLS>
template<size_t N>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator* ( Matrix<T,COLS, N>& rhs)
{
    // matrix-matrix multiplication
    if(m_vector == false)
    {

    if( COLS!=rhs.getRows())
    {
     throw std::out_of_range("number of columns of matrix 1 must be equil to number of rows of matrix 2");
    }




    // initialize tmp matrix values to 0
    T tmp[m_rows][rhs.getCols()];

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
            for(int j = 0; j < rhs.getCols(); ++j)
            {
                for(int k=0; k<m_cols; ++k)
                {
                    //std::cout<<m[i][j]<<"\n";
                    tmp[i][j] += m_data[i][k] * rhs.data(k,j);

                    //std::cout<<m_data[i][k] * rhs.m_data[k][j]<<"\n";
                }
            }
        }

        // resizes matrix to 1st matrix rows x second matrix cols
        //resize(m_rows,rhs.getCols());

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
            m_data[0][i]=m_data[0][i]*rhs.data(0,i);
        }


    }


    return *this;

}

//----------------------------------------------------------------------------------------------

/// Multiplication opertor for matrix/vector and scalar
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

/// Division operator for matrix/vector and scalar
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator/ (T scalar)
{
    if(scalar==0)
    {
        throw std::out_of_range("Cannot divide by 0");
    }


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

/// Checks rows and columns are in correct range
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::rangeCheck(std::size_t rowID,std::size_t colID)
{
    if( rowID>ROWS || rowID<1)
        throw std::out_of_range("row out of range");

    if( colID>COLS || colID<1)
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
T& Matrix< T,ROWS,COLS>::operator()(std::size_t rowID,std::size_t colID)
{
    rangeCheck(rowID,colID);
    return m_data[rowID-1][colID-1];
}


//----------------------------------------------------------------------------------------------

/// Subscript operator used to view values of matrix/vector based on row and column (read only)
template <typename T, size_t ROWS, size_t COLS>
const T& Matrix< T,ROWS,COLS>::operator()(std::size_t rowID,std::size_t colID) const
{
    rangeCheck(rowID,colID);
  return const_cast<T&>(m_data[rowID-1][colID-1]);
}

//----------------------------------------------------------------------------------------------

/// Division operator for vector and vector
template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator/ ( Matrix<T,ROWS,COLS>& rhs)
{
    vectorCheck();
    rhs.vectorCheck();

    if(m_rows==1)
    {
       for(int i = 0; i< COLS; i++)
       {
          m_data[0][i]=m_data[0][i]/rhs.m_data[0][i];
       }
    }

    else if(m_cols==1)
    {
       for(int i = 0; i< ROWS; i++)
       {
          m_data[i][0]=m_data[i][0]/rhs.m_data[i][0];
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
float Matrix<T,ROWS,COLS>::dot( Matrix<T,ROWS,COLS>& rhs)
{
    vectorCheck();
    rhs.vectorCheck();

    float dotProd = 0;

    if(m_rows == 1)
    {
    for(int i = 0; i<COLS; i++)
    {
        dotProd+=m_data[0][i]*rhs.m_data[0][i];

    }
    }

    else if(m_cols == 1)
    {
    for(int i = 0; i<COLS; i++)
    {
        dotProd+=m_data[i][0]*rhs.m_data[i][0];

    }
    }


    //std::cout<<"The dot product is "<<dotProd<< "\n";



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
    angle = (180/M_PI)*acos(cosAngle);



    return angle;


}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T, ROWS, COLS>& Matrix<T, ROWS, COLS>::cross( Matrix<T,ROWS,COLS>& rhs)
{
    if( ROWS*COLS != 3)
        throw std::out_of_range("You must use a 3D vector for the cross product function");

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

    // col vector
    if(m_rows==1)
    {

    tmp[0][0]= m_data[0][1]*rhs.m_data[0][2] - m_data[0][2]*rhs.m_data[0][1];
    tmp[0][1]= m_data[0][2]*rhs.m_data[0][0] - m_data[0][0]*rhs.m_data[0][2];
    tmp[0][2]= m_data[0][0]*rhs.m_data[0][1] - m_data[0][1]*rhs.m_data[0][0];

    // assignning the tmp matrix's values to m_data
    for(int i=0; i<COLS; i++)
    {
          m_data[0][i]=tmp[0][i];
    }

    }

    // row vector
    else if(m_cols==1)
    {

    tmp[0][0]= m_data[1][0]*rhs.m_data[2][0] - m_data[2][0]*rhs.m_data[1][0];
    tmp[1][0]= m_data[2][0]*rhs.m_data[0][0] - m_data[0][0]*rhs.m_data[2][0];
    tmp[2][0]= m_data[0][0]*rhs.m_data[1][0] - m_data[1][0]*rhs.m_data[0][0];

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
            //l=i;

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
         // std::cout<<m_data[i][j]<<"final matrix \n";

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
        throw std::out_of_range("You must use a square matrix for the inverse function");

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


        determinant = m_data[0][0] * inv[0][0] + m_data[0][1] * inv[1][0] + m_data[0][2] * inv[2][0] + m_data[0][3] * inv[3][0];

        //determinant = 1.0 / determinant;
    }

    return determinant;
}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::inverse()
{
    // test to see if matrix times inverse equils identity
    if( ROWS != COLS)
        throw std::out_of_range("You must use a square matrix for the inverse function");

    //std::cout<<"inverse called \n";

    T tmp[ROWS][COLS];

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          tmp[i][j]=0;

        }
    }

    // find inverse of 2x2 matrix
    if(ROWS==2) //works!
    {


        tmp[0][0]= m_data[1][1];
        tmp[0][1]=-m_data[0][1];
        tmp[1][0]=-m_data[1][0];
        tmp[1][1]= m_data[0][0];



        if( determinant()==0)
            throw std::out_of_range("An inverse doesnt exist, the determinant is 0");

        //std::cout<<determinant<<"\n";

        for(int i = 0; i<ROWS; i++)
        {
            for( int j = 0; j<COLS; j++)
            {

                tmp[i][j]=tmp[i][j]/determinant();
                //std::cout<<tmp[i][j]<<"\n";

            }
        }
    }
/// referenced from http://forgetcode.com/C/1781-Inverse-Matrix-of-3x3
    if(ROWS==3) // works!
    {

    if( determinant()==0)
        throw std::out_of_range("An inverse doesnt exist, the determinant is 0");


     //std::cout<<"\nInverse of matrix is: \n\n";
     for(int i=0;i<3;i++){

        for(int j=0;j<3;j++)
        {

             tmp[j][i] = ((m_data[(i+1)%3][(j+1)%3] * m_data[(i+2)%3][(j+2)%3]) - (m_data[(i+1)%3][(j+2)%3]*m_data[(i+2)%3][(j+1)%3]))/ determinant();

             //std::cout<<tmp[i][j]<<"\n";


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
                 throw std::out_of_range("An inverse doesnt exist, the determinant is 0");


             det=1.0/determinant();

              for(int i = 0; i<ROWS; i++)
              {
                  for( int j = 0; j<COLS; j++)
                  {

                     tmp[i][j] = inv[i][j] * det;
                     //std::cout<<"final inverse matrix"<<tmp[i][j]<<"\n";
                  }
             }                     

     }

     for(int i = 0; i<ROWS; i++)
     {
         for( int j = 0; j<COLS; j++)
         {

             m_data[i][j]=tmp[i][j];
             //std::cout<<m_data[i][j]<<"\n";

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

           }

       }

    for(int i = 0; i< ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            tmp[j][i]= m_data[i][j];
            std::cout<<tmp[j][i]<<" tmp \n";

        }
    }


    resize(COLS,ROWS);

    std::cout<<m_rows<<" m_rows resized \n";
    std::cout<<m_cols<<" m_rows resized \n";

    print();

    for(int i = 0; i<m_rows; i++)
    {
        for( int j = 0; j<m_cols; j++)
        {

            m_data[i][j]=tmp[i][j];
            std::cout<<i<<j<<m_data[i][j]<<" m_data resized \n";

            std::cout<<m_data[0][2]<< " \n";

        }
        std::cout<<m_data[0][2]<< " \n";
    }

    std::cout<<m_data[0][2]<< " \n";




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
    {T rotMat [m_rows][m_rows];

        // counter clockwise around the origin
        rotMat[0][0]=cos(angle);
        rotMat[0][1]= -sin(angle);
        rotMat[1][0]= sin(angle);
        rotMat[1][1]= cos(angle);



        //std::cout<<rotMat[0][1]<<" \n";
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
            if(_axis == "x"){T rotMat [3][3]={1,0,0,0,cos(angle),-sin(angle),0,sin(-angle),cos(angle)};

                for(int i = 0; i < 3; i ++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        tmp[i]+=rotMat[i][j]*m_data[j][0];

                    }
                }}
            if(_axis == "y"){T rotMat [3][3]={cos(angle),0,sin(angle),0,1,0,-sin(angle),0,cos(-angle)};

                for(int i = 0; i < 3; i ++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        tmp[i]+=rotMat[i][j]*m_data[j][0];

                    }
                }
            }
            if(_axis == "z"){T rotMat [3][3]={cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1};

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
            //std::cout<<m_data[i][0]<<"\n";
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

    std::cout<<" resized called \n";

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

    m_data[m_rows][m_cols]=m_data[_rows][_cols];


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

    m_rows=_rows;
    m_cols=_cols;

    for(int i = 0;i<m_rows;i++)
           {
               for(int j = 0;j< m_cols;j++)
               {

                   m_data[i][j]=0;
                   //std::cout<<m_data[i][j]<<" resize new element \n";
               }

           }




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
