#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include <array>

int main()
{
    //Matrix<int,3,2> myMatrix;
    //myMatrix={1,2,3,4,5,6};

    Matrix<int,2,3> myMatrix;
    myMatrix={1,2,3,4,5,6};
    myMatrix.print();




}
