#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include "quaternion.h"

// DO THIS STUFF FOR GOD SAKE

// THIS WEEK
// EDIT NUMBER OF COLS AFTER MULTIPLICATION EG 2X3 AND 3X2 SHOULD RESULT IN 2X2 MATRIX (CALL CONSTRUCTOR POSSIBLY)
// ADD MULTIPLE MATRIX SIZES FOR CROSS PRODUCT
// ADD MATRIX INVERSE                               done! (2x2,3x3,4x4)
// ADD QUATERNION FUNCTIONS -this weekend
// ADD == OPERATOR -this weekend
// ADD MATRIX ROTATE FUNCTION -this weekend
// ADD MATRIX DETERMINANT -this weekend
// MATRIX TRANSPOSE -this weekend
// TEST IF ORTHOGONAL (INVERSE EQUILS TRANSPOSED MATRIX)
// MINOR
// COFACTOR


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

        Matrix<int,2,3> mat{1,3,5,2,4,6};

        Matrix<int,3,2> mat2{1,2,3,4,5,6};

        //Matrix<int,2,2> mult;

        //mult=(mat*mat2);

        //mult.print();

        //mat2 = mat.transpose();

        //mat2.print();

        //mat2.resize(3,1);

        //mat2.transpose();

        mat*mat2;


        mat.print();








    }
