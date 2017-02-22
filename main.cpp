#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
//#include <array>

// EDIT NUMBER OF COLS AFTER MULTIPLICATION EG 2X3 AND 3X2 SHOULD RESULT IN 2X2 MATRIX

int main()
{
    //Matrix<int,3,2> myMatrix;
    //myMatrix={1,2,3,4,5,6};

    Matrix<int,2,3> myMatrix;
    myMatrix={1,2,3,4,5,6};


    Matrix<int,3,2> newMatrix;
    newMatrix={5,6,7,8,9,10};

    myMatrix= myMatrix*newMatrix;

    myMatrix.print();

//    Matrix<int,2,3> errorMatrix;
//    errorMatrix={1,2,3,4,5,6};

    // errors due to different COLS values in the template
    //myMatrix= myMatrix*errorMatrix;

   // myMatrix.print();




















}
