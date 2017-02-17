#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include <array>

int main()
{
    //Matrix<int,3,2> myMatrix;
    //myMatrix={1,2,3,4,5,6};

    Matrix<int,2,2> myMatrix;
    myMatrix={1,2,3,4};

    myMatrix.print();

    //myMatrix(1,1)=2;

    //myMatrix.print();

    Matrix<int,2,2> newMatrix;
    newMatrix={1,2,3,4};

    Matrix<int,2,2> addMatrix;

    addMatrix= myMatrix *newMatrix;

    addMatrix.print();








}
