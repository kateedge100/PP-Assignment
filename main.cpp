#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    // creates a 4x4 matrix
    typedef Matrix<int,4,2> myMatrix;

    //myMatrix(0,1) = 5;

   typedef Matrix<int,2,3> myMatrix2;
    myMatrix2(0,1) = 5;
    cout << myMatrix2.data() << endl;


    //cout << myMatrix(0,1) << endl;
    return 0;
}
