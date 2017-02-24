#include <iostream>
#include <cstdlib>
#include <string>
#include "matrix.h"
#include "quaternion.h"

#include "NGLScene.h"
#include <QtGui/QGuiApplication>

// EDIT NUMBER OF COLS AFTER MULTIPLICATION EG 2X3 AND 3X2 SHOULD RESULT IN 2X2 MATRIX

int main()
{
    //Matrix<int,3,2> myMatrix;
    //myMatrix={1,2,3,4,5,6};

//    Matrix<int,2,3> myMatrix;
//    myMatrix={1,2,3,4,5,6};


//    Matrix<int,3,2> newMatrix;
//    newMatrix={5,6,7,8,9,10};

//    std::cout<<myMatrix.getRows();

//    myMatrix=myMatrix*newMatrix;
//    myMatrix.print();


    Quaternion<int> q(2,3,4,5);
    Quaternion<int> q2;
    q2=q;

    q2.print();



    Matrix<int,1,3> vector= {2,3,4};
    Matrix<int,1,3> vector2= {5,7,5};

    std::cout<<vector.angle(vector2)<<"\n";

    vector=vector.cross(vector2);

    vector.print();





//    vector=vector.cross(vector2);

//    vector.print();

//    Matrix<int,1,25> tom;

//    //std::cout<<tom.m_vector;


//        for(int j =0; j<13; ++j)
//        {
//            tom(1,j) = j;
//        }


    //tom.cross(tom);
    //tom.print();




















}
