#include "matrix.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>








//template <typename T, size_t ROWS, size_t COLS>
//Matrix<T,ROWS,COLS>& Matrix< T,ROWS,COLS>::operator= (const Matrix<T,ROWS,COLS>& rhs)
//{
//    //std::copy(rhs.begin(),rhs.end(), begin());
//    for(int i=0; i<COLS; i++)
//    {
//        for(int j=0; j<ROWS; j++)
//        {
//          m_data[i][j]=rhs.m_data[i][j];

//        }

//    }

//    return *this;
//}

//template <typename T, size_t ROWS, size_t COLS>
//T* Matrix< T, ROWS, COLS>::data()
//{

//            return m_data;


//}

//template <typename T, size_t ROWS, size_t COLS>
//void Matrix<T,ROWS,COLS> ::operator= (const Matrix<T,ROWS,COLS> &m)
//{
//    for(int i = 0; i< ROWS*COLS; i++)
//    {
//        m_data=m.data();
//    }

//    return *this;

//}





//template <typename T, int ROWS, int COLS>
//T& Matrix< T,ROWS,COLS>::operator()(int rowValue,int colValue)
//{
////    assert(col >= 0 && col < 4);
////    assert(row >= 0 && row < 4);

//      // throw error if rows or cols out of range

//    //T data[ROWS][COLS];

//    // assign inputed data to privae data attribute
//    //m_data[rowValue][colValue] = data[rowValue][colValue];

//    return data[rowValue][colValue];
//}

//template <typename T, int ROWS, int COLS>
//const T& Matrix< T,ROWS, COLS>::operator()(int rowValue, int colValue) const
//{
////    assert(col >= 0 && col < 4);
////    assert(row >= 0 && row < 4);

//    //T data[ROWS][COLS];

//    // assign inputed data to privae data attribute
//    //m_data[rowValue][colValue] = data[rowValue][colValue];

//    return data[rowValue][colValue];
//}


