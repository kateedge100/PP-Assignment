#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include "quaternion.h"

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

        Matrix<float,2,1> vec{2,9};

        vec=vec.rotateVector(50);

        vec.print();






    }
