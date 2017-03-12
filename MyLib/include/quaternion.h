#ifndef QUARTERNION_H
#define QUARTERNION_H
#include <complex>
#include "matrix.h"


template <typename T>

/// \class Quaternions
/// \brief Creates quaternions using a template type and applies a variety of operations and functions to them
///
class Quaternion
{
private:

    /// Quaternion in the form of a+bi+cj+dk
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

    // returns a,b,c or d
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

    // prints out the quaternion in the form a+bi+cj+dk
    void print();

};

//----------------------------------------------------------------------------------------------
/// @brief Default constructor, sets all values of the quaternion equil to 0
template <typename T>
Quaternion<T>::Quaternion()
{
  m_a=0;
  m_b=0;
  m_c=0;
  m_d=0;

}

//----------------------------------------------------------------------------------------------
/// @brief Constructs and initializes a quaternion
/// param[in] _a, the value m_a will be initialized to
/// param[in] _b, the value m_b will be initialized to
/// param[in] _c, the value m_c will be initialized to
/// param[in] _d, the value m_d will be initialized to
template <typename T>
Quaternion<T>::Quaternion(T _a, T _b, T _c, T _d)
{
  m_a=_a;
  m_b=_b;
  m_c=_c;
  m_d=_d;

}

//----------------------------------------------------------------------------------------------
/// @brief Copy constructor
/// param[in] _rhs, the quaternion whose values are copied into the original quaternion
template <typename T>
Quaternion<T>::Quaternion(const Quaternion<T> &_rhs)
{
  m_a=_rhs.m_a;
  m_b=_rhs.m_b;
  m_c=_rhs.m_c;
  m_d=_rhs.m_d;

}

//----------------------------------------------------------------------------------------------
/// @brief Returns the value of m_a,m_b,m_c or m_d
/// param[in] _data, the value to return
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
/// @brief Assignment operator
/// param[in] _rhs, the quaternion to assign its values to the original quaternion
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
/// @brief Equility operator
/// param[in] _rhs, the quaternion to check if equils the original quaternion
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
/// @brief Addition operator
/// param[in] _rhs, the quaternion the add to the original quaternion
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
/// @brief Addition operator (scalar)
/// param[in] _scalar, the scalar value to add the each value of the quaternion
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
/// @brief Subtraction operator
/// param[in] _rhs, the quaternion to subtract from the original quaternion
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
/// @brief Subtraction operator (scalar)
/// param[in] _scalar, the scalar value to subtract from each value of the quaternion
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
/// @brief Negative operator, returns negative value of the quaternion
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
/// @brief Multiplication operator
/// param[in] _rhs, the quaternion to multiply the first quaternion by
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
/// @brief Multiplication operator (scalar)
/// param[in] _scalar, the scalar value to add to each value of the quaternion
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
/// @brief Division operator (scalar)
/// param[in] _scalar, the scalar value to divide each value of the quaternion by
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
/// @brief Prints out the values of the quaternion in the format a + bi + cj + dk
template <typename T>
void Quaternion<T>::print()
{
  std::cout<<m_a<<" + "<<m_b<<"i + "<<m_c<<"j + "<<m_d<<"k\n";
}

//----------------------------------------------------------------------------------------------
/// @brief Returns the norm of a quaternion (sometimes referred to as legnth)
template <typename T>
T Quaternion<T>::norm()
{
  T norm = sqrt((m_a*m_a)+(m_b*m_b)+(m_c*m_c)+(m_d*m_d));

  return norm;
}

//----------------------------------------------------------------------------------------------
/// Returns the normalized version of the quaternion
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
/// @brief Returns the conjugate of the quaternion
template <typename T>
Quaternion<T>& Quaternion<T>::conjugate()
{
  if(m_b!=0) {m_b= -m_b;}
  if(m_c!=0) {m_c= -m_c;}
  if(m_d!=0) {m_d= -m_d;}

  return *this;
}

//----------------------------------------------------------------------------------------------
/// @brief Returns the inverse of the quaternion
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
