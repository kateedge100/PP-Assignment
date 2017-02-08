#include "matrix.h"



template <typename T, int COLS, int ROWS>
Matrix< T,COLS,ROWS>::Matrix() // DEFAULT CONSTRUCTOR
{
    // default matrix types
     Matrix<int,2,2> Matrix2f;
     Matrix<int,3,3> Matrix3f;
     Matrix<int,4,4> Matrix4f;

    for (int r=0; r < ROWS; ++r)
    {
       for (int c=0; c < COLS; ++c)
       {
           m_data[r][c]=T();
       }
    }

}

template <typename T, int COLS, int ROWS>
T* Matrix< T, COLS, ROWS>::data()
{
    return m_data;
}





template <typename T, int COLS, int ROWS>
T& Matrix< T,COLS,ROWS>::operator()(T rowValue, T colValue)
{
//    assert(col >= 0 && col < 4);
//    assert(row >= 0 && row < 4);

      // throw error if rows or cols out of range

    T data[ROWS][COLS];

    // assign inputed data to privae data attribute
    m_data[rowValue][colValue] = data[rowValue][colValue];

    return data[rowValue][colValue];
}

template <typename T, int COLS, int ROWS>
const T& Matrix< T,COLS,ROWS>::operator()(T rowValue, T colValue) const
{
//    assert(col >= 0 && col < 4);
//    assert(row >= 0 && row < 4);

    T data[ROWS][COLS];

    // assign inputed data to privae data attribute
    m_data[rowValue][colValue] = data[rowValue][colValue];

    return data[rowValue][colValue];
}


