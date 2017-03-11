#include <iostream>
#include "quaternion.h"
#include <gtest/gtest.h>



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
    Quaternion<float> q(1,0,1,0);
    Quaternion<float> q2(1,0.5,0.5,0.75);
    Quaternion<float> mult;
    Quaternion<float> result(0.5,1.25,1.5,0.25);

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
    Quaternion<float> q(9,13,4,7);
    Quaternion<float> result(2.25,3.25,1,1.75);

    EXPECT_TRUE(q/4 == result);

}

TEST(QuaternionOperators,DivideOperatorZero)
{
    Quaternion<float> q(0,1,2,3);

    EXPECT_THROW(q/0 ,std::out_of_range);

}

TEST(QuaternionFunction,NormFunction)
{
    Quaternion<float> q(0,3,4,0);


    EXPECT_TRUE(q.norm() == 5);

}

TEST(QuaternionFunction,NormalizeFunction)
{
    Quaternion<float> q(0,3,4,0);
    Quaternion<float> result(0,0.6,0.8,0);


    EXPECT_TRUE(q.normalize() == result);

}

TEST(QuaternionFunction,NormalizeFunctionZero)
{
    Quaternion<float> q(0,0,0,0);
    Quaternion<float> result(0,0,0,0);


    EXPECT_TRUE(q.normalize() == result);

}

TEST(QuaternionFunction,ConjugateFunction)
{
    Quaternion<float> q(5,27,83,45);
    Quaternion<float> result(5,-27,-83,-45);


    EXPECT_TRUE(q.conjugate() == result);

}

// fix inverse -0 error
//TEST(QuaternionFunction,InverseFunction)
//{
//    Quaternion<float> q(1.0f,0.0f,1.0f,0.0f);
//    Quaternion<float> q2;
//    Quaternion<float> result(0.5f,0.0f,-0.5f,0.0f);


////    q2=q.inverse();
////    q.print();


//    EXPECT_TRUE(q.inverse() == result );

//}

TEST(QuaternionFunction,InverseFunction)
{

    Quaternion<float> q(1.0f,2.0f,-1.0f,-3.0f);
    Quaternion<float> q2;
    Quaternion<float> error(0.00001f,0.00001f,0.00001f,0.00001f);
    Quaternion<float> result(1.0f/15.0f,-2.0f/15.0f,1.0f/15.0f,3.0f/15.0f);



    EXPECT_TRUE(q.inverse()==result);

}










