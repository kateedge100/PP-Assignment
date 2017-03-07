#include <iostream>
#include "matrix.h"
#include <gtest/gtest.h>
#include <fstream>

// constructors
// operators
// checks
// functions


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();



}

TEST(MatrixConstructors,DefaultConstructor)
{
    Matrix<int,2,2> mat;
    Matrix<int,2,2> result{0,0,0,0};
    EXPECT_TRUE(mat == result);

}

TEST(MatrixConstructors,CopyConstructor)
{
    Matrix<int,2,2> mat{1,2,3,4};
    Matrix<int,2,2> mat2;
    Matrix<int,2,2> result{1,2,3,4};
    mat2=mat;
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixOperators,SubScriptOperator)
{
    Matrix<int,2,3> mat;
    mat(1,3)=5;
    Matrix<int,2,3> result{0,0,5,0,0,0};
    EXPECT_TRUE(mat == result);

}

TEST(MatrixOperators,AssignmentOperator)
{
    Matrix<int,2,2> mat{1,2,3,4};
    Matrix<int,2,2> mat2;
    Matrix<int,2,2> result{1,2,3,4};
    mat2=mat;
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixOperators,AssignmentOperatorDifferentSizes)
{
    Matrix<int,2,3> mat{1,2,3,4,5,6};
    Matrix<int,2,2> mat2;
    Matrix<int,2,2> result{1,2,4,5};
    mat2=mat;
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixOperators,AdditionOperatorMatrix)
{
    Matrix<int,3,3> mat{1,2,3,4,5,6,7,8,9};
    Matrix<int,3,3> mat2{2,3,4,5,6,7,8,9,10};
    Matrix<int,3,3> add;
    Matrix<int,3,3> result{3,5,7,9,11,13,15,17,19};

    add=mat+mat2;

    EXPECT_TRUE(add == result);

}

TEST(MatrixOperators,AdditionOperatorScalar)
{
     Matrix<int,3,3> mat{1,2,3,4,5,6,7,8,9};
     Matrix<int,3,3> result{5,6,7,8,9,10,11,12,13};

     mat= mat+ 4;

     EXPECT_TRUE(mat == result);

}

TEST(MatrixOperators,AdditionOperatorNegScalar)
{
    Matrix<int,3,3> mat{1,2,3,4,5,6,7,8,9};
    Matrix<int,3,3> result{-3,-2,-1,0,1,2,3,4,5};

    mat= mat+ -4;

    EXPECT_TRUE(mat == result);

}

TEST(MatrixOperators,SubtractionOperatorMatrix)
{
    Matrix<int,3,3> mat{1,2,3,4,5,6,7,8,9};
    Matrix<int,3,3> mat2{2,3,4,5,6,7,8,9,10};
    Matrix<int,3,3> sub;
    Matrix<int,3,3> result{-1,-1,-1,-1,-1,-1,-1,-1,-1};

    sub=mat-mat2;

    EXPECT_TRUE(sub == result);

}

TEST(MatrixOperators,SubtractionOperatorScalar)
{
     Matrix<int,3,3> mat{1,2,3,4,5,6,7,8,9};
     Matrix<int,3,3> result{-3,-2,-1,0,1,2,3,4,5};

     mat= mat- 4;

     EXPECT_TRUE(mat == result);

}

TEST(MatrixOperators,SubtractionOperatorNegScalar)
{
    Matrix<int,3,3> mat{1,2,3,4,5,6,7,8,9};
    Matrix<int,3,3> result{5,6,7,8,9,10,11,12,13};

    mat= mat- -4;

    EXPECT_TRUE(mat == result);

}

TEST(MatrixOperators,NegativeOperator)
{
    Matrix<int,2,2> mat{1,2,3,4};
    Matrix<int,2,2> mat2;
    Matrix<int,2,2> result{-1,-2,-3,-4};
    mat2=-mat;
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixOperators,MultiplicationOperator)
{
    Matrix<int,2,3> mat{1,0,-2,0,3,-1};
    Matrix<int,3,2> mat2{0,3,-2,-1,0,4};
    Matrix<int,2,2> mult;
    Matrix<int,2,2> result{0,-5,-6,-7};
    mult=mat*mat2;
    EXPECT_TRUE(mult == result);

}

TEST(MatrixOperators,MultiplicationOperatorScalar)
{
    Matrix<int,2,2> mat{1,2,3,4};
    Matrix<int,2,2> mat2;
    Matrix<int,2,2> result{4,8,12,16};
    mat2=mat*4;
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixOperators,DivisionOperatorScalar)
{
    Matrix<float,2,2> mat{1,2,3,4};
    Matrix<float,2,2> mat2;
    Matrix<float,2,2> result{0.25,0.5,0.75,1};
    mat2=mat/4;
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixFunctions,MatrixInverse2x2)
{
    Matrix<float,2,2> mat{4,7,2,6};
    Matrix<float,2,2> mat2;
    Matrix<float,2,2> result{0.6,-0.7,-0.2,0.4};
    mat2=mat.inverse();
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixFunctions,MatrixInverse3x3)
{

    Matrix<float,3,3> mat{6,9,4,5,6,2,5,4,3};
    Matrix<float,3,3> mat2{7,2,1,0,3,-1,-3,4,-2};
    Matrix<float,3,3> result2{-2,8,-5,3,-11,7,9,-34,21};
    Matrix<float,3,3> result{-0.4,0.44,0.24,0.2,0.08,-0.32,0.4,-0.84,0.36};
    mat2=mat.inverse();
    mat2.print();
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixFunctions,MatrixDeterminant2x2)
{
    Matrix<float,2,2> mat{4,7,2,6};

    EXPECT_TRUE(mat.determinant() == 10);

}

// fix inverse
TEST(MatrixFunctions,MatrixDeterminant3x3)
{
    Matrix<float,3,3> mat{6,9,4,5,6,2,5,4,3};

    std::cout<<mat.determinant();
    EXPECT_TRUE(mat.determinant() == -25);

}













