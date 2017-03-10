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

TEST(MatrixConstructors,InitializerListConstructor)
{
    Matrix<int,2,2> mat{1,2,3,4};

    Matrix<int,2,2> result;
    result(1,1)=1;
    result(1,2)=2;
    result(2,1)=3;
    result(2,2)=4;


    EXPECT_TRUE(mat == result);

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

/// correct results sourced from https://www.mathsisfun.com/algebra/matrix-inverse-row-operations-gauss-jordan.html
TEST(MatrixFunctions,MatrixInverse3x3)
{

    Matrix<float,3,3> mat{3,0,2,2,0,-2,0,1,1};
    Matrix<float,3,3> mat2;
    Matrix<float,3,3> result{0.2,0.2,0,-0.2,0.3,1,0.2,-0.3,0};
    mat2=mat.inverse();
    EXPECT_TRUE(mat2 == result);

}

/// correct results sourced from www.mathsisfun.com's matrix calculator
TEST(MatrixFunctions,MatrixInverse4x4)
{

    Matrix<float,4,4> mat{4,0,0,0,0,0,2,0,0,1,2,0,1,0,0,1};
    Matrix<float,4,4> mat2;
    Matrix<float,4,4> result{0.25,0,0,0,0,-1,1,0,0,0.5,0,0,-0.25,0,0,1};
    mat2=mat.inverse();
    EXPECT_TRUE(mat2 == result);

}

TEST(MatrixFunctions,MatrixDeterminant2x2)
{
    Matrix<float,2,2> mat{4,7,2,6};

    EXPECT_TRUE(mat.determinant() == 10);

}


TEST(MatrixFunctions,MatrixDeterminant3x3)
{
    Matrix<float,3,3> mat{6,9,4,5,6,2,5,4,3};

    EXPECT_TRUE(mat.determinant() == -25);

}


TEST(MatrixFunctions,MatrixDeterminant4x4)
{
    Matrix<float,4,4> mat{4,0,0,0,0,0,2,0,0,1,2,0,1,0,0,1};

    EXPECT_TRUE(mat.determinant() == -8);

}

/// correct results sourced from http://www.purplemath.com
TEST(MatrixFunctions,MinorMatrix)
{
    Matrix<float,4,4> mat{1,2,3,4,2,2,2,4,4,5,6,4,7,8,9,4};
    Matrix<float,3,3> mat2;
    Matrix<float,3,3> results{1,2,4,4,5,4,7,8,4};

    mat2=mat.minorMatrix(2,3);

    EXPECT_TRUE(mat2 == results);


}

TEST(MatrixFunctions,MinorMatrixLowerBoundary)
{
    Matrix<float,4,4> mat{1,2,3,4,2,2,2,4,4,5,6,4,7,8,9,4};
    Matrix<float,3,3> mat2;
    Matrix<float,3,3> results{2,2,4,5,6,4,8,9,4};

    mat2=mat.minorMatrix(1,1);

    EXPECT_TRUE(mat2 == results);

}

TEST(MatrixFunctions,MinorMatrixUpperBoundary)
{
    Matrix<float,4,4> mat{1,2,3,4,2,2,2,4,4,5,6,4,7,8,9,4};
    Matrix<float,3,3> mat2;
    Matrix<float,3,3> results{1,2,3,2,2,2,4,5,6};

    mat2=mat.minorMatrix(4,4);

    EXPECT_TRUE(mat2 == results);

}

// fixxx
TEST(MatrixFunctions,MatrixTranspose)
{
    Matrix<float,3,2> mat{1,2,3,4,5,6};
    Matrix<float,2,3> mat2;
    Matrix<float,2,3> results{1,3,5,2,4,6};

    mat2=mat.transpose();
    mat2.print();

    EXPECT_TRUE(mat2 == results);

}

// TEST ORTHOGONAL WHEN TRANSPOSE WORKSSSS


















