#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include "quaternion.h"

// DO THIS STUFF FOR GOD SAKE

// THIS WEEK
// ADD QUATERNION FUNCTIONS -this weekend
// ADD MATRIX ROTATE FUNCTION -this weekend (might be done)
// COFACTOR
// PROJECTION MATRIX - might not do
// A  LENGTH,NORM,CONJUGATE AND INVERSE OF QUATERNION


// NEXT WEEK
// GET WORKING WITH RENDERING SCENE (ASK JOHN/RICHARD)
// ADD TESTING FEATURES, FROM NGL TEST EXAMPLES
//

// FOLLOWING WEEK (LAST WEEK)
// DO DOCUMENTATION
// USER GUIDE
// COMMENT CODE
// DO VIDEO
// DOXYGEN



// TESTTTTTTT , USE NGL TEST FOLDER EXAMPLES



    int main()
    {

        Matrix<int,4,4> mat{1,2,3,4,2,2,2,4,4,5,6,4,7,8,9,4};
        Matrix<int,3,3> vec{6,1,1,4,-2,5,2,8,7};
        Matrix<int,3,3> vec2;

        Matrix<int,2,3> mat3{1,2,3,4,5,6};
        Matrix<int,1,2> mat4;

       Matrix<int,3,2> mat2{7,8,9,10,11,12};

//        Matrix<float,4,4> inv{1,1,3,4,5,6,7,8,9,10,11,12,13,14,15,1};


       //vec=mat.minorMatrix(2,4);
       //mat4=mat3.minorMatrix(2,3);

        //std::cout<<vec.determinant();
        //mat3.print();



       //mat.vectorCheck();

//        //inv.inverse();

////        //inv.print();

        Quaternion<float> q{0,0,3,4};
        Quaternion<float> q2{5,6,7,8};


        std::cout<<q.length();
//         //mat.print();

//         q2 = q2*q;

         //q.print();
         //q2.print();




    }
