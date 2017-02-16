#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include <array>

int main()
{
    //Matrix<int,3,2> myMatrix;
    //myMatrix={1,2,3,4,5,6};

    Matrix<char,2,5> myMatrix;
    myMatrix={1,2,3,4,5,
              6,7,8,9,10};

    myMatrix.print();

    Matrix<char,2,5> newMatrix;
    newMatrix=myMatrix;

    newMatrix.print();






}
