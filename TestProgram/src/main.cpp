#include <iostream>
#include "matrix.h"
#include "quaternion.h"

/// \author Kate Edge
/// \version 1.0
/// \date 13/3/17 \n

/// For use for testing and marking

int main()
{
    // Matrix Constructor
    Matrix<int,2,2> mat{1,2,3,4};

    // Vector Constructor (3D Row Vector)
    Matrix<int,1,3> vec{1,2,3};

    //Quaternion Constructor
    Quaternion<float> q{1.5,2,3,4};

    mat.print();

    vec.print();

    q.print();

}
