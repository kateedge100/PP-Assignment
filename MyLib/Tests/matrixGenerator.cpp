#include <iostream>
#include "matrix.h"
#include <fstream>
#include <gtest/gtest.h>

static std::ofstream gstream;

template <typename T, size_t ROWS, size_t COLS>
void writeCtor(const std::string &_name,const Matrix<T,ROWS,COLS> &_m)
{

  gstream<<"Matrix<"<<","<<ROWS<<","<<COLS<<"> "<<_name<<"(";
  for(auto m : _m.m_openGL)
    gstream<<m<<',';
  gstream<<");\n";
}


void writeTest(const std::string &_name)
{
  static int test=0;
  gstream<<"Test "<<test++<<' '<<_name<<'\n';
}


int main()
{


}
