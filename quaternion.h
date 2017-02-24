#ifndef QUARTERNION_H
#define QUARTERNION_H
#include <complex>
#include "matrix.h"

/// Quaternion in the form of a+bi+cj+dk

template <typename T>

class Quaternion
{
private:
    T m_a;
    T m_b;
    T m_c;
    T m_d;


public:

    // default constructor
    Quaternion();
    // constructs and initializes quaternion
    Quaternion(T _a, T _b, T _c, T _d);
    // copy constructor
    Quaternion(const Quaternion<T>& rhs);

    
    float i = sqrt(-1);
    float j = sqrt(-1);
    float k = sqrt(-1);



    // assignment operator
    Quaternion& operator= (const Quaternion<T>& rhs);
    // addition operator
    Quaternion& operator+ (const Quaternion<T>& rhs);
    // addition operator scalar
    Quaternion& operator+ (T scalar);
    // subtraction operator
    Quaternion& operator- (const Quaternion<T>& rhs);
    // subtraction operator scalar
    Quaternion& operator- (T scalar);
    // negative operator
    Quaternion& operator- ();

    // multiply operator scalar
    Quaternion& operator* (T scalar);
    // division operator scalar
    Quaternion& operator/ (T scalar);

    void print();

};

template <typename T>
Quaternion<T>::Quaternion()
{
    m_a=0;
    m_b=0;
    m_c=0;
    m_d=0;

}

template <typename T>
Quaternion<T>::Quaternion(T _a, T _b, T _c, T _d)
{
    m_a=_a;
    m_b=_b;
    m_c=_c;
    m_d=_d;

}

template <typename T>
Quaternion<T>::Quaternion(const Quaternion<T> &rhs)
{

}

template <typename T>
void Quaternion<T>::print()
{
    std::cout<<m_a<<" + "<<m_b<<"i + "<<m_c<<"j + "<<m_d<<"\n";
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator =(const Quaternion<T>& rhs)
{
    m_a=rhs.m_a;
    m_b=rhs.m_b;
    m_c=rhs.m_c;
    m_d=rhs.m_d;

    return *this;


}




#endif // QUARTERNION_H
