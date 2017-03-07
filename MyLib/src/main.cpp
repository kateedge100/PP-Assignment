#include <iostream>
#include <cstdlib>
#include <string>
#include "include/matrix.h"
#include "include/quaternion.h"

// DO THIS STUFF FOR GOD SAKE

// THIS WEEK
// ADD MATRIX ROTATE FUNCTION -this weekend (might be done)
// COFACTOR
// PROJECTION MATRIX - might not do
// FIX NORM BUG


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

        Matrix<int,2,3> A{1,0,-2,0,3,-1};
        Matrix<int,3,2> B{0,3,-2,-1,0,4};
        Matrix<int,2,2> C;


       C= A*B;
       C.print();







    }
