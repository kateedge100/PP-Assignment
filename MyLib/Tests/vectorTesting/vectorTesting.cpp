#include <iostream>
#include "matrix.h"
#include <gtest/gtest.h>

/// Tests for vector constructors, operators anf functions
/// Didnt repeat tests on initializer list and copy constructor as tested in matrixTesting.cpp
/// The same applies for the addition and subtraction operators both for vectors and scalar numbers

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(VectorConstructors,DefaultConstructor)
{
    Matrix<int,1,3> vec;
    Matrix<int,1,3> result{0,0,0};
    EXPECT_TRUE(vec == result);

}


TEST(VectorOperators,DivisionOperatorRowVector)
{
    Matrix<float,1,3> vec{2.0f,3.0f,9.0f};
    Matrix<float,1,3> vec2{1.0f,2.0f,3.0f};
    Matrix<float,1,3> div;
    Matrix<float,1,3> result{2.0f,1.5f,3.0f};

    div=vec/vec2;

    EXPECT_TRUE(div == result);
}

TEST(VectorOperators,DivisionOperatorColVector)
{
    Matrix<float,3,1> vec{2.0f,3.0f,9.0f};
    Matrix<float,3,1> vec2{1.0f,2.0f,3.0f};
    Matrix<float,3,1> div;
    Matrix<float,3,1> result{2.0f,1.5f,3.0f};

    div=vec/vec2;

    EXPECT_TRUE(div == result);
}

TEST(VectorOperators,DivisionOperatorVectorScalability)
{
    Matrix<int,1,100> vec;
    for(int i = 1; i<101; i++)
    {
        vec(1,i)=i*4;

    }

    Matrix<int,1,100> vec2;
    for(int i = 1; i<101; i++)
    {
        vec2(1,i)=i*8;
    }

    Matrix<int,1,100> div;

    Matrix<int,1,100> result;
    for(int i = 1; i<101; i++)
    {
        result(1,i)=2;
    }

    div=vec2/vec;

    EXPECT_TRUE(div == result);
}

TEST(VectorFunctions,RowVectorMagnitude)
{
    Matrix<int,1,3> vec{0,3,4};


    EXPECT_TRUE(vec.magnitude() == 5);
}

TEST(VectorFunctions,ColVectorMagnitude)
{
    Matrix<int,3,1> vec{0,3,4};

    EXPECT_TRUE(vec.magnitude() == 5);
}

TEST(VectorFunctions,NormalizeVector)
{
    Matrix<float,3,1> vec{4.0f,3.0f,0.0f};
    Matrix<float,3,1> result{0.8f,0.6f,0.0f};

    EXPECT_TRUE(vec.normalizeVector()==result);

}

TEST(VectorFunctions,RowVectorCrossProduct)
{
    Matrix<int,1,3> vec{2,3,4};
    Matrix<int,1,3> vec2{5,6,7};
    Matrix<int,1,3> cross;
    Matrix<int,1,3> result{-3,6,-3};

    cross=vec.cross(vec2);



    EXPECT_TRUE(cross == result);
}

TEST(VectorFunctions,ColVectorCrossProduct)
{
    Matrix<int,3,1> vec{2,3,4};
    Matrix<int,3,1> vec2{5,6,7};
    Matrix<int,3,1> cross;
    Matrix<int,3,1> result{-3,6,-3};

    cross=vec.cross(vec2);



    EXPECT_TRUE(cross == result);
}

TEST(VectorFunctions,VectorCrossProductOutofRange)
{
    Matrix<int,1,2> vec{2,3};
    Matrix<int,1,2> vec2{5,6};

    EXPECT_THROW(vec.cross(vec2),std::out_of_range);

}

TEST(VectorFunctions,Col2DVectorDotProduct)
{
    Matrix<int,1,2> vec{-12,16};
    Matrix<int,1,2> vec2{12,9};


    EXPECT_TRUE(vec.dot(vec2) == 0 );

}

TEST(VectorFunctions,Row2DVectorDotProduct)
{
    Matrix<int,1,2> vec{-12,16};
    Matrix<int,1,2> vec2{12,9};


    EXPECT_TRUE(vec.dot(vec2) == 0 );

}

TEST(VectorFunctions,Col3DVectorDotProduct)
{
    Matrix<int,1,3> vec{4,8,10};
    Matrix<int,1,3> vec2{9,2,7};


    EXPECT_TRUE(vec.dot(vec2) == 122 );

}

TEST(VectorFunctions,Row3DVectorDotProduct)
{
    Matrix<int,1,3> vec{4,8,10};
    Matrix<int,1,3> vec2{9,2,7};


    EXPECT_TRUE(vec.dot(vec2) == 122 );

}

TEST(VectorFunctions,VectorDotProductScalability)
{
    Matrix<int,1,100> vec;
    for(int i = 1; i<101; i++)
    {
        vec(1,i)=1;

    }

    Matrix<int,1,100> vec2;
    for(int i = 1; i<101; i++)
    {
        vec2(1,i)=4;
    }



    EXPECT_TRUE(vec.dot(vec2) == 400 );

}

TEST(VectorFunctions,Row2DAngle)
{
    Matrix<int,1,2> vec{3,0};
    Matrix<int,1,2> vec2{5,5};

    EXPECT_TRUE(vec.angle(vec2) == 45 );

}

TEST(VectorFunctions,Col2DAngle)
{
    Matrix<int,2,1> vec{3,0};
    Matrix<int,2,1> vec2{5,5};

    EXPECT_TRUE(vec.angle(vec2) == 45 );

}


TEST(VectorFunctions,Row3DAngle)
{
    Matrix<int,1,3> vec{4,0,7};
    Matrix<int,1,3> vec2{-2,1,3};

    EXPECT_NEAR(vec.angle(vec2) == 64.4725, vec.angle(vec2) == 64.4724,0.0001 );

}

TEST(VectorFunctions,Col3DAngle)
{
    Matrix<int,3,1> vec{4,0,7};
    Matrix<int,3,1> vec2{-2,1,3};

    EXPECT_NEAR(vec.angle(vec2) == 64.4725, vec.angle(vec2) == 64.4724,0.0001 );

}

TEST(VectorFunctions,2DVectorRotation)
{
    Matrix<int,2,1> vec{1,0};
    Matrix<int,2,1> result{0,1};

    // for a 2d rotation axix selected is irrelevent
    vec=vec.rotateVector(90,"x");

    EXPECT_TRUE(vec==result);

}

TEST(VectorFunctions,3DVectorRotationXAxis)
{
    Matrix<int,3,1> vec{1,0,0};
    Matrix<int,3,1> result{1,0,0};

    vec=vec.rotateVector(90,"x");

    EXPECT_TRUE(vec==result);

}

TEST(VectorFunctions,3DVectorRotationYAxis)
{
    Matrix<int,3,1> vec{1,0,0};
    Matrix<int,3,1> result{0,0,-1};

    vec=vec.rotateVector(90,"y");

    EXPECT_TRUE(vec==result);

}

TEST(VectorFunctions,3DVectorRotationZAxis)
{
    Matrix<int,3,1> vec{1,0,0};
    Matrix<int,3,1> result{0,1,0};

    vec=vec.rotateVector(90,"z");

    EXPECT_TRUE(vec==result);

}

TEST(VectorFunctions,RowVectorRotationError)
{
    Matrix<int,1,3> vec{1,0,0};
    EXPECT_THROW(vec.rotateVector(90,"x"),std::out_of_range);

}

TEST(VectorFunctions,4DVectorRotationError)
{
    Matrix<int,4,1> vec{1,0,0,1};


    EXPECT_THROW(vec.rotateVector(90,"x"),std::out_of_range);

}




