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

    T getData(const char *_data);


    // assignment operator
    Quaternion& operator= (const Quaternion<T>& rhs);
    // equility operator
    bool operator== (const Quaternion<T>& rhs);
    // addition operator
    Quaternion& operator+ (const Quaternion<T>& rhs);
    // addition operator scalar
    Quaternion& operator+ (T _scalar);
    // subtraction operator
    Quaternion& operator- (const Quaternion<T>& rhs);
    // subtraction operator scalar
    Quaternion& operator- (T _scalar);
    // negative operator
    Quaternion& operator- ();

    // multiply operator scalar
    Quaternion& operator* (T _scalar);
    // multiply quaternions
    Quaternion& operator* (const Quaternion<T>& rhs);
    // division operator scalar
    Quaternion& operator/ (T _scalar);
    // division operator scalar
//    Quaternion& operator/ (const Quaternion<T>& rhs);

    T norm();
    Quaternion<T>& conjugate();
    Quaternion<T>& normalize();
    Quaternion<T>& inverse();
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
    m_a=rhs.m_a;
    m_b=rhs.m_b;
    m_c=rhs.m_c;
    m_d=rhs.m_d;

}

template <typename T>
T Quaternion<T>::getData(const char* _data)
{
    switch(_data)
    {
        case "a": m_a=_data;
               return m_a;
        case "b": m_b=_data;
               return m_b;
        case "c": m_c=_data;
               return m_c;
        case "d": m_d=_data;
               return m_d;
    }



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

template <typename T>
bool Quaternion<T>::operator ==(const Quaternion<T>& rhs)
{


    if(m_a==rhs.m_a && m_b==rhs.m_b&& m_c==rhs.m_c && m_d==rhs.m_d)
    {
        return true;
    }
    else
    {
        return false;

    }

}

template <typename T>
Quaternion<T>& Quaternion<T>::operator +(const Quaternion<T>& rhs)
{
    m_a+=rhs.m_a;
    m_b+=rhs.m_b;
    m_c+=rhs.m_c;
    m_d+=rhs.m_d;


    return *this;

}

template <typename T>
Quaternion<T>& Quaternion<T>::operator +(T _scalar)
{
    m_a+=_scalar;
    m_b+=_scalar;
    m_c+=_scalar;
    m_d+=_scalar;


    return *this;

}
template <typename T>
Quaternion<T>& Quaternion<T>::operator -(const Quaternion<T>& rhs)
{
    m_a-=rhs.m_a;
    m_b-=rhs.m_b;
    m_c-=rhs.m_c;
    m_d-=rhs.m_d;


    return *this;

}

template <typename T>
Quaternion<T>& Quaternion<T>::operator -(T _scalar)
{
    m_a-=_scalar;
    m_b-=_scalar;
    m_c-=_scalar;
    m_d-=_scalar;


    return *this;

}

template <typename T>
Quaternion<T>& Quaternion<T>::operator -()
{
    m_a=-m_a;
    m_b=-m_b;
    m_c=-m_c;
    m_d=-m_d;


    return *this;

}

template <typename T>
Quaternion<T>& Quaternion<T>::operator *(const Quaternion<T>& rhs)
{

    T tmp[3];
    tmp[0]=(rhs.m_a*m_a)-(rhs.m_b*m_b)-(rhs.m_c*m_c)-(rhs.m_d*m_d);
    tmp[1]=(rhs.m_a*m_b)+(rhs.m_b*m_a)-(rhs.m_c*m_d)+(rhs.m_d*m_c);
    tmp[2]=(rhs.m_a*m_c)+(rhs.m_b*m_d)+(rhs.m_c*m_a)-(rhs.m_d*m_b);
    tmp[3]=(rhs.m_a*m_d)-(rhs.m_b*m_c)+(rhs.m_c*m_b)+(rhs.m_d*m_a);



    m_a=tmp[0];
    m_b=tmp[1];
    m_c=tmp[2];
    m_d=tmp[3];


    return *this;

}

template <typename T>
Quaternion<T>& Quaternion<T>::operator *(T _scalar)
{
    m_a*=_scalar;
    m_b*=_scalar;
    m_c*=_scalar;
    m_d*=_scalar;


    return *this;

}

//template <typename T>
//Quaternion<T>& Quaternion<T>::operator /(const Quaternion<T>& rhs)
//{
//    T tmp[3];

//    tmp[0]=((rhs.m_a*m_a)+(rhs.m_b*m_b)+(rhs.m_c*m_c)+(rhs.m_d*m_d))/
//            ((rhs.m_a*rhs.m_a)+(rhs.m_b*rhs.m_b)+(rhs.m_c*rhs.m_c)+(rhs.m_d*rhs.m_d));

//    tmp[1]=((rhs.m_a*m_b)+(rhs.m_b*m_a)+(rhs.m_c*m_d)+(rhs.m_d*m_c))/
//            ((rhs.m_a*rhs.m_a)+(rhs.m_b*rhs.m_b)+(rhs.m_c*rhs.m_c)+(rhs.m_d*rhs.m_d));

//    tmp[2]=((rhs.m_a*m_c)+(rhs.m_b*m_d)+(rhs.m_c*m_a)+(rhs.m_d*m_b))/
//            ((rhs.m_a*rhs.m_a)+(rhs.m_b*rhs.m_b)+(rhs.m_c*rhs.m_c)+(rhs.m_d*rhs.m_d));

//    tmp[3]=((rhs.m_a*m_d)+(rhs.m_b*m_c)+(rhs.m_c*m_b)+(rhs.m_d*m_a))/
//            ((rhs.m_a*rhs.m_a)+(rhs.m_b*rhs.m_b)+(rhs.m_c*rhs.m_c)+(rhs.m_d*rhs.m_d));

//    m_a=tmp[0];
//    m_b=tmp[1];
//    m_c=tmp[2];
//    m_d=tmp[3];

//    return *this;
//}

template <typename T>
Quaternion<T>& Quaternion<T>::operator /(T _scalar)
{
    if(_scalar==0)
    {
        throw std::out_of_range("Cannot divide by 0");
    }

    m_a/=_scalar;
    m_b/=_scalar;
    m_c/=_scalar;
    m_d/=_scalar;


    return *this;

}

template <typename T>
void Quaternion<T>::print()
{
    std::cout<<m_a<<" + "<<m_b<<"i + "<<m_c<<"j + "<<m_d<<"k\n";
}

template <typename T>
T Quaternion<T>::norm()
{
    T length = sqrt((m_a*m_a)+(m_b*m_b)+(m_c*m_c)+(m_d*m_d));

    return length;
}

template <typename T>
Quaternion<T>& Quaternion<T>::normalize()
{
    // if norm is 0 quaternion must be 0,0,0,0 hence just return the original quaternion
    if(norm()==0)
    {
        return *this;
    }
    else
    {

    T n =norm();

    m_a=m_a/n;
    m_b=m_b/n;
    m_c=m_c/n;
    m_d=m_d/n;

    return *this;
    }

}

template <typename T>
Quaternion<T>& Quaternion<T>::conjugate()
{
    m_b=-m_b;
    m_c=-m_c;
    m_d=-m_d;

    return *this;
}


template <typename T>
Quaternion<T>& Quaternion<T>::inverse()
{
    // if norm is 0 quaternion must be 0,0,0,0 hence just return the original quaternion
    if(norm()==0)
    {
        return *this;
    }

    T normSqr= norm()*norm();

    //Quaternion Inv = conjugate()/normSqr;


    return conjugate()/normSqr;
}
#endif // QUARTERNION_H
