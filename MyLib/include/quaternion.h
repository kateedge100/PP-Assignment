#ifndef QUARTERNION_H
#define QUARTERNION_H
#include <complex>
#include "matrix.h"

/// Quaternion in the form of a+bi+cj+dk

template <typename T>

/// \class Quaternions
/// \brief Creates quaternions using a template type and applies a variety of operations and functions to them
///
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
    Quaternion(const Quaternion<T>& _rhs);

    T getData(const char *_data);


    // assignment operator
    Quaternion& operator= (const Quaternion<T>& _rhs);
    // equility operator
    bool operator== (const Quaternion<T>& _rhs);
    // addition operator
    Quaternion& operator+ (const Quaternion<T>& _rhs);
    // addition operator scalar
    Quaternion& operator+ (T _scalar);
    // subtraction operator
    Quaternion& operator- (const Quaternion<T>& _rhs);
    // subtraction operator scalar
    Quaternion& operator- (T _scalar);
    // negative operator
    Quaternion& operator- ();

    // multiply operator scalar
    Quaternion& operator* (T _scalar);
    // multiply quaternions
    Quaternion& operator* (const Quaternion<T>& _rhs);
    // division operator scalar
    Quaternion& operator/ (T _scalar);

    T norm();
    Quaternion<T>& conjugate();
    Quaternion<T>& normalize();
    Quaternion<T>& inverse();
    void print();

};

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>::Quaternion()
{
  m_a=0;
  m_b=0;
  m_c=0;
  m_d=0;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>::Quaternion(T _a, T _b, T _c, T _d)
{
  m_a=_a;
  m_b=_b;
  m_c=_c;
  m_d=_d;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>::Quaternion(const Quaternion<T> &_rhs)
{
  m_a=_rhs.m_a;
  m_b=_rhs.m_b;
  m_c=_rhs.m_c;
  m_d=_rhs.m_d;

}

//----------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator =(const Quaternion<T>& _rhs)
{
  m_a=_rhs.m_a;
  m_b=_rhs.m_b;
  m_c=_rhs.m_c;
  m_d=_rhs.m_d;

  return *this;
}

//----------------------------------------------------------------------------------------------

template <typename T>
bool Quaternion<T>::operator ==(const Quaternion<T>& _rhs)
{
  if(m_a==_rhs.m_a && m_b==_rhs.m_b&& m_c==_rhs.m_c && m_d==_rhs.m_d)
  {
    return true;
  }
  else
  {
    return false;
  }

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator +(const Quaternion<T>& _rhs)
{
  m_a+=_rhs.m_a;
  m_b+=_rhs.m_b;
  m_c+=_rhs.m_c;
  m_d+=_rhs.m_d;

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator +(T _scalar)
{
  m_a+=_scalar;
  m_b+=_scalar;
  m_c+=_scalar;
  m_d+=_scalar;

  return *this;

}

//----------------------------------------------------------------------------------------------
template <typename T>
Quaternion<T>& Quaternion<T>::operator -(const Quaternion<T>& _rhs)
{
  m_a-=_rhs.m_a;
  m_b-=_rhs.m_b;
  m_c-=_rhs.m_c;
  m_d-=_rhs.m_d;

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator -(T _scalar)
{
  m_a-=_scalar;
  m_b-=_scalar;
  m_c-=_scalar;
  m_d-=_scalar;

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator -()
{
  m_a=-m_a;
  m_b=-m_b;
  m_c=-m_c;
  m_d=-m_d;

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator *(const Quaternion<T>& _rhs)
{

  T tmp[3];
  tmp[0]=(_rhs.m_a*m_a)-(_rhs.m_b*m_b)-(_rhs.m_c*m_c)-(_rhs.m_d*m_d);
  tmp[1]=(_rhs.m_a*m_b)+(_rhs.m_b*m_a)-(_rhs.m_c*m_d)+(_rhs.m_d*m_c);
  tmp[2]=(_rhs.m_a*m_c)+(_rhs.m_b*m_d)+(_rhs.m_c*m_a)-(_rhs.m_d*m_b);
  tmp[3]=(_rhs.m_a*m_d)-(_rhs.m_b*m_c)+(_rhs.m_c*m_b)+(_rhs.m_d*m_a);

  m_a=tmp[0];
  m_b=tmp[1];
  m_c=tmp[2];
  m_d=tmp[3];

  return *this;

}

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::operator *(T _scalar)
{
  m_a*=_scalar;
  m_b*=_scalar;
  m_c*=_scalar;
  m_d*=_scalar;

  return *this;

}

//----------------------------------------------------------------------------------------------

//template <typename T>
//Quaternion<T>& Quaternion<T>::operator /(const Quaternion<T>& _rhs)
//{
//    T tmp[3];

//    tmp[0]=((_rhs.m_a*m_a)+(_rhs.m_b*m_b)+(_rhs.m_c*m_c)+(_rhs.m_d*m_d))/
//            ((_rhs.m_a*_rhs.m_a)+(_rhs.m_b*_rhs.m_b)+(_rhs.m_c*_rhs.m_c)+(_rhs.m_d*_rhs.m_d));

//    tmp[1]=((_rhs.m_a*m_b)+(_rhs.m_b*m_a)+(_rhs.m_c*m_d)+(_rhs.m_d*m_c))/
//            ((_rhs.m_a*_rhs.m_a)+(_rhs.m_b*_rhs.m_b)+(_rhs.m_c*_rhs.m_c)+(_rhs.m_d*_rhs.m_d));

//    tmp[2]=((_rhs.m_a*m_c)+(_rhs.m_b*m_d)+(_rhs.m_c*m_a)+(_rhs.m_d*m_b))/
//            ((_rhs.m_a*_rhs.m_a)+(_rhs.m_b*_rhs.m_b)+(_rhs.m_c*_rhs.m_c)+(_rhs.m_d*_rhs.m_d));

//    tmp[3]=((_rhs.m_a*m_d)+(_rhs.m_b*m_c)+(_rhs.m_c*m_b)+(_rhs.m_d*m_a))/
//            ((_rhs.m_a*_rhs.m_a)+(_rhs.m_b*_rhs.m_b)+(_rhs.m_c*_rhs.m_c)+(_rhs.m_d*_rhs.m_d));

//    m_a=tmp[0];
//    m_b=tmp[1];
//    m_c=tmp[2];
//    m_d=tmp[3];

//    return *this;
//}

//----------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------

template <typename T>
void Quaternion<T>::print()
{
  std::cout<<m_a<<" + "<<m_b<<"i + "<<m_c<<"j + "<<m_d<<"k\n";
}

//----------------------------------------------------------------------------------------------

template <typename T>
T Quaternion<T>::norm()
{
  T norm = sqrt((m_a*m_a)+(m_b*m_b)+(m_c*m_c)+(m_d*m_d));

  return norm;
}

//----------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------

template <typename T>
Quaternion<T>& Quaternion<T>::conjugate()
{
  if(m_b!=0) {m_b= -m_b;}
  if(m_c!=0) {m_c= -m_c;}
  if(m_d!=0) {m_d= -m_d;}

  return *this;
}

//----------------------------------------------------------------------------------------------


template <typename T>
Quaternion<T>& Quaternion<T>::inverse()
{
  // if norm is 0 quaternion must be 0,0,0,0 hence just return the original quaternion
  if(norm()==0)
  {
    return *this;
  }

  T normSqr= norm()*norm();

  m_a=m_a/normSqr;
  if(m_b!=0) {m_b= -m_b/normSqr;}
  if(m_c!=0) {m_c= -m_c/normSqr;}
  if(m_d!=0) {m_d= -m_d/normSqr;}


  return *this;
}

//----------------------------------------------------------------------------------------------
#endif // QUARTERNION_H
