#include <iostream>
#include "matrix.h"
#include "quaternion.h"

using namespace std;

int main()
{
    Matrix<int,2,2> mat{1,2,3,4};

    mat.print();

}
