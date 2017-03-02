#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include "quaternion.h"

// DO THIS STUFF FOR GOD SAKE


// EDIT NUMBER OF COLS AFTER MULTIPLICATION EG 2X3 AND 3X2 SHOULD RESULT IN 2X2 MATRIX
// ADD MULTIPLE MATRIX SIZES FOR CROSS PRODUCT
// ADD MATRIX INVERSE
// ADD QUATERNION FUNCTIONS
// ADD == OPERATOR
// ADD MATRIX ROTATE FUNCTION
// ADD MATRIX DETERMINANT

// TESTTTTTTT , USE NGL TEST FOLDER EXAMPLES



    int main() {

//        Quaternion<int> q(2,3,4,5);
//        Quaternion<int> q2;
//        q2=q;

//        q2.print();

        Matrix<float,3,3> mat3= {3,0,2,2,0,-2,0,1,1};

        //mat3.inverse();

        Matrix<float,4,4> mat4= {1,0,1,0,0,2,2,2,3,3,0,3,4,4,4,0};

        mat4.inverse();

        mat4.print();

        //mat.minorMatrix();

        //mat3.print();



//        Matrix<int,1,3> vector= {2,3,4};
//        Matrix<int,1,3> vector2= {5,7,5};

//        std::cout<<vector.angle(vector2)<<"\n";

//        vector=vector.cross(vector2);

//        vector.print();


    }
