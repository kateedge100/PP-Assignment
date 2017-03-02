#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
//#include <algorithm>
#include <iostream>
#include "quaternion.h"

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

    // this is constant so can be static
    static size_t size()  {return ROWS,COLS;}

    // subscript operators
    //code referenced from http://www.learncpp.com/cpp-tutorial/99-overloading-the-parenthesis-operator/
    T& operator()(std::size_t rowID, std::size_t colID);
    const T& operator()(std::size_t rowID, std::size_t colID) const ; // for const objects

    void vectorCheck();


    /// Matrix and Vector Operation

    // assignment operator ( different sizes)

    template <size_t N>
    Matrix<T, ROWS, COLS>
    operator= ( Matrix<T,ROWS,N>& rhs);


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

    template <size_t N>
    Matrix<T, ROWS, COLS>
    operator* ( Matrix<T,COLS,N>& rhs);
    Matrix& inverse();
    Matrix& minorMatrix();


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

/// Default constructor, sets all values to type T and equil to zero
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

    if(ROWS==1 || COLS==1)
    {
        m_vector=true;
        //std::cout<<"is a vector \n";
    }

}

//----------------------------------------------------------------------------------------------

/// Copy constructor
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

    if(ROWS==1 || COLS==1)
    {
        m_vector=true;
        //std::cout<<"is a vector \n";
    }
}

//----------------------------------------------------------------------------------------------

/// Assignment operator, variable sized matrices (for matrix multiplication assignment)
template <typename T, size_t ROWS, size_t COLS>
template<size_t N>
Matrix<T,ROWS,COLS> Matrix< T,ROWS,COLS>::operator= ( Matrix<T,ROWS, N>& rhs)
{



    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=rhs.data(i,j);

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
Matrix<T,ROWS,COLS> Matrix< T,ROWS,COLS>::operator* ( Matrix<T,COLS, N>& rhs)
{
    // matrix-matrix multiplication
    if(m_vector == false)
    {



    if( COLS!=rhs.getRows())
        throw std::out_of_range("number of columns of matrix 1 mustbe equil to number of rows of matrix 2");

    int i, j, k;


    // initialize tmp matrix values to 0
    T tmp[rhs.getRows()][m_cols];

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
            for(j = 0; j < rhs.getCols(); ++j)
            {
                for(k=0; k<m_cols; ++k)
                {
                    //std::cout<<m[i][j]<<"\n";
                    tmp[i][j] += m_data[i][k] * rhs.data(k,j);

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

/// Checks rows and columns are in correct range
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::rangeCheck(std::size_t rowID,std::size_t colID)
{
    if( rowID!=ROWS)
        throw std::out_of_range("row out of range");

    if( colID!=COLS)
        throw std::out_of_range("column out of range");
}

//----------------------------------------------------------------------------------------------

/// Checks that function is being applied to a vector not a matrix
template <typename T, size_t ROWS, size_t COLS>
void Matrix<T,ROWS,COLS>::vectorCheck()
{
    if( m_vector == false)
        throw std::out_of_range("You must use vectors only for this function");

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
  return const_cast<T&>(m_data[rowID][colID]);
}

//----------------------------------------------------------------------------------------------

/// Division operator for matrix/vector and matrix/vector
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
    if( COLS !=3)
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
    for(int i=0; i<COLS; i++)
    {


          m_data[0][i]=tmp[0][i];

          //std::cout<<m_data[0][i]<<"\n";

    }

    return *this;



}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::minorMatrix()
{
    T tmp[ROWS][COLS];

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          tmp[i][j]=0;

        }
    }

    // row of minor matrix
    for(int i = 0; i<ROWS; i++)
    {
        // col of minor matrix
        for( int j = 0; j<COLS; j++)
        {
            // row for calculation
            for(int k = 0; k<ROWS; k++)
            {
                if(k==i)
                {
                    k++;

                }

                // col for calculation
                for( int l = 0; l<COLS; l++)
                {
                    if(l==j)
                    {
                        l++;
                    }

                    tmp[i][j]+=m_data[k][l];
                    std::cout<<tmp[i][j]<<"\n";




                }
            }
        }
    }

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
          m_data[i][j]=tmp[i][j];

        }

    }

    return *this;




}

//----------------------------------------------------------------------------------------------

template <typename T, size_t ROWS, size_t COLS>
Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::inverse()
{
    // test to see if matrix times inverse equils identity
    if( ROWS != COLS)
        throw std::out_of_range("You must use a square matrix for the inverse function");

    std::cout<<"inverse called \n";

    T tmp[ROWS][COLS];
    T determinant = 0;

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

        determinant = (m_data[0][0]*m_data[1][1])-(m_data[0][1]*m_data[1][0]);

        for(int i = 0; i<ROWS; i++)
        {
            for( int j = 0; j<COLS; j++)
            {

                m_data[i][j]=tmp[i][j]/determinant;
                //std::cout<<m_data[i][j]<<"\n";

            }
        }
    }
/// referenced from http://forgetcode.com/C/1781-Inverse-Matrix-of-3x3
    if(ROWS==3)
    {


    for(int i=0;i<3;i++)
        determinant = determinant + (m_data[0][i]*(m_data[1][(i+1)%3]*m_data[2][(i+2)%3] - m_data[1][(i+2)%3]*m_data[2][(i+1)%3]));

     std::cout<<"\nInverse of matrix is: \n\n";
     for(int i=0;i<3;i++){

        for(int j=0;j<3;j++)
        {

             tmp[i][j] = ((m_data[(i+1)%3][(j+1)%3] * m_data[(i+2)%3][(j+2)%3]) - (m_data[(i+1)%3][(j+2)%3]*m_data[(i+2)%3][(j+1)%3]))/ determinant;

             //std::cout<<tmp[i][j]<<"\n";


        }
     }
    }

     // 4x4 matrix
     if(ROWS==4)
     {
         std::cout<<"inverse of matrix with 4 rows is  \n";

        T inv[4][4], det;

        T invOut[4][4];


// initilize arrays values to zero
        for(int i = 0; i<ROWS; i++)
        {
            for( int j = 0; j<COLS; j++)
            {
                inv[i][j]=0;

                invOut[i][j]=0;

            }
        }


        // set m's values to m_datas values

//        for( int k = 0; k<16; k++)
//        {
//        for(int i = 0; i<ROWS; i++)
//        {
//            for( int j = 0; j<COLS; j++)
//            {


//                    m[k]=m_data[i][j];

//                    std::cout<<m[k]<<" m";



//            }

//            std::cout<<"\n";
//        }
//        }


        std::cout<< "inv 0 is "<<inv[0]<<"\n";


             int i;

             inv[0][0] = m_data[1][1]  * m_data[2][2] * m_data[3][3] - //0
                      m_data[1][1]  * m_data[2][3] * m_data[3][2] -
                      m_data[2][1]  * m_data[1][2]  * m_data[3][3] +
                      m_data[2][1]  * m_data[1][3]  * m_data[3][2] +
                      m_data[3][1] * m_data[1][2]  * m_data[2][3] -
                      m_data[3][1] * m_data[1][3]  * m_data[2][2];

             std::cout<< "inv[0] is "<< inv[0]<<"\n";

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

             inv[0][0] = -m_data[0][1]  * m_data[2][2] * m_data[3][3] + //1
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

             det = m_data[0][0] * inv[0][0] + m_data[0][1] * inv[1][0] + m_data[0][2] * inv[2][0] + m_data[0][3] * inv[3][0];


             std::cout<<"det"<<det<<"\n";
            // if (det == 0)
                 // assert error

             det = 1.0 / det;

              std::cout<<"det"<<det<<"\n";

              for(int i = 0; i<ROWS; i++)
              {
                  for( int j = 0; j<COLS; j++)
                  {
                     invOut[i][j] = inv[i][j] * det;
                     std::cout<<"final inverse matrix"<<invOut[i]<<"\n";
                  }
             }

             for(int i = 0; i<ROWS; i++)
             {
                 for( int j = 0; j<COLS; j++)
                 {

                     m_data[i][j]=invOut[i][j];
                     //std::cout<<m_data[i][j]<<"\n";

                 }
             }

     }

     for(int i = 0; i<ROWS; i++)
     {
         for( int j = 0; j<COLS; j++)
         {

             m_data[i][j]=tmp[j][i];
             //std::cout<<m_data[i][j]<<"\n";

         }
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
