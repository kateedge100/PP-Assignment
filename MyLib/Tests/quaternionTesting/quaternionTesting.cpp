#include <iostream>
#include "quaternion.h"
#include <gtest/gtest.h>

/// Tests for quaternion constructors, operators and functions.

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(QuaternionConstructors,DefaultConstructor)
{
    Quaternion<int> q;
    Quaternion<int>result(0,0,0,0);
    EXPECT_TRUE(q == result);

}

TEST(QuaternionConstructors,InitializeConstructor)
{
    Quaternion<int> q(1,2,3,4);
    Quaternion<int>result{1,2,3,4};
    EXPECT_TRUE(q == result);

}

TEST(QuaternionConstructors,CopyConstructor)
{
    Quaternion<int> q(1,2,3,4);
    Quaternion<int> q2;
    Quaternion<int> result(1,2,3,4);
    q2=q;

    EXPECT_TRUE(q2 == result);

}

TEST(QuaternionOperators,AssignmentOperatorQuaternion)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> q2;
    Quaternion<int> result(0,2,3,4);

    q2=q;

    EXPECT_TRUE(q2 == result);

}

TEST(QuaternionOperators,EquilityOperatorQuaternionTrue)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> result(0,2,3,4);

    EXPECT_TRUE(q == result);

}

TEST(QuaternionOperators,EquilityOperatorQuaternionFalse)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> result(0,2,3,5);

    EXPECT_FALSE(q == result);

}

TEST(QuaternionOperators,AdditionOperatorQuaternion)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> q2(0,5,8,2);
    Quaternion<int> add;
    Quaternion<int> result(0,7,11,6);

    add=q+q2;

    EXPECT_TRUE(add == result);

}

TEST(QuaternionOperators,AdditionOperatorScalar)
{
    Quaternion<int> q(0,2,3,4);

    Quaternion<int> result(4,6,7,8);



    EXPECT_TRUE(q+4 == result);

}

TEST(QuaternionOperators,SubtractionOperatorQuaternion)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> q2(0,5,8,2);
    Quaternion<int> sub;
    Quaternion<int> result(0,-3,-5,2);

    sub=q-q2;

    EXPECT_TRUE(sub == result);

}

TEST(QuaternionOperators,SubtractionOperatorScalar)
{
    Quaternion<int> q(0,2,3,4);

    Quaternion<int> result(-2,0,1,2);



    EXPECT_TRUE(q-2 == result);

}

TEST(QuaternionOperators,NegativeOperatorScalar)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> result(0,-2,-3,-4);

    EXPECT_TRUE(-q == result);

}

TEST(QuaternionOperators,MultiplyOperatorQuaternion)
{
    Quaternion<float> q(1.0f,0.0f,1.0f,0);
    Quaternion<float> q2(1.0f,0.5f,0.5f,0.75f);
    Quaternion<float> mult;
    Quaternion<float> result(0.5f,1.25f,1.5f,0.25f);

    mult=q*q2;

    EXPECT_TRUE(mult == result);

}

TEST(QuaternionOperators,MultiplyOperatorScalar)
{
    Quaternion<int> q(0,2,3,4);
    Quaternion<int> result(0,6,9,12);

    EXPECT_TRUE(q*3 == result);

}

TEST(QuaternionOperators,DivideOperatorScalar)
{
    Quaternion<float> q(9.0f,13.0f,4.0f,7.0f);
    Quaternion<float> result(2.25f,3.25f,1.0f,1.75f);

    EXPECT_TRUE(q/4 == result);

}

TEST(QuaternionOperators,DivideOperatorZero)
{
    Quaternion<int> q(0,1,2,3);

    EXPECT_THROW(q/0 ,std::out_of_range);

}

TEST(QuaternionFunction,SetDataFunction)
{
    Quaternion<int> q(0,2,4,0);

    q.setData("b",3);


    EXPECT_TRUE(q.getData("b") == 3);

}

TEST(QuaternionFunction,GetDataFunction)
{
    Quaternion<int> q(0,3,4,0);


    EXPECT_TRUE(q.getData("b") == 3);

}

TEST(QuaternionFunction,NormFunction)
{
    Quaternion<int> q(0,3,4,0);


    EXPECT_TRUE(q.norm() == 5);

}

TEST(QuaternionFunction,NormalizeFunction)
{
    Quaternion<float> q(0.0f,3.0f,4.0f,0.0f);
    Quaternion<float> result(0.0f,0.6f,0.8f,0.0f);


    EXPECT_TRUE(q.normalize() == result);

}

TEST(QuaternionFunction,NormalizeFunctionZero)
{
    Quaternion<float> q(0.0f,0.0f,0.0f,0.0f);
    Quaternion<float> result(0.0f,0.0f,0.0f,0.0f);


    EXPECT_TRUE(q.normalize() == result);

}

TEST(QuaternionFunction,ConjugateFunction)
{
    Quaternion<int> q(5,27,83,45);
    Quaternion<int> result(5,-27,-83,-45);


    EXPECT_TRUE(q.conjugate() == result);

}


TEST(QuaternionFunction,InverseFunction)
{

    Quaternion<float> q(0.0f,4.0f,0.0f,3.0f);
    Quaternion<float> result(0.0f,-4.0f/25.0f,0.0f,-3.0f/25.0f);

    EXPECT_TRUE(q.inverse() == result);

}

TEST(QuaternionFunction,InverseFunctionZero)
{

    Quaternion<float> q(0.0f,0.0f,0.0f,0.0f);
    Quaternion<float> result(0.0f,0.0f,0.0f,0.0f);

    EXPECT_TRUE(q.inverse() == result);

}










