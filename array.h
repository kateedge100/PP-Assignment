#ifndef ARRAY_H__
#define ARRAY_H__
#include <stdexcept>
#include <algorithm>

template <typename T, size_t ROWS=0, size_t COLS=0>
class Array
{
    private :
        // our array data
        T m_data[COLS][ROWS];

        // function to check for a valid array range.
        void rangeCheck(std::size_t rowidx, std::size_t colidx);

    public :
        // ctor will set the data to zero type
        Array();
        //
        Array(std::initializer_list<T> data);

        // this is constant so can be static
        static size_t size()  {return ROWS,COLS;}
        // access data elements
        T& at(std::size_t rowidx, std::size_t colidx);
        // subscript operators
        T& operator()(std::size_t ridx, std::size_t colidx);
        const T& operator()(std::size_t rowidx, std::size_t colidx) const ;

    // read only data access
    const T* data() const { return m_data; }
    T* data() { return *m_data; }

    void print();

    Array<T,ROWS,COLS>& operator= (const Array<T,ROWS,COLS>& rhs);

//        // types for iterators (boost style definitions)
//        typedef T*  iterator;
//        typedef const T*  const_iterator;
//    // begin iterators
//    iterator        begin()        { return m_data; }
//    const_iterator  begin()  const { return m_data; }
//    const_iterator  cbegin() const { return m_data; }
//    // end iterators
//    iterator        end()        { return m_data+(ROWS*COLS); }
//    const_iterator  end()  const { return m_data+(ROWS*COLS); }
//    const_iterator  cend() const { return m_data+(ROWS*COLS); }

};


template <typename T, size_t ROWS, size_t COLS>
Array<T,ROWS,COLS>& Array< T,ROWS,COLS>::operator= (const Array<T,ROWS,COLS>& rhs)
{
    //std::copy(rhs.begin(),rhs.end(), begin());
    for(int i=0; i<COLS; i++)
    {
        for(int j=0; j<ROWS; j++)
        {
          m_data[i][j]=rhs.m_data[i][j];

        }

    }

    return *this;
}

template <typename T, size_t ROWS, size_t COLS>
Array< T,ROWS,COLS>::Array()
{
    // set to the default ctor value of T
    for(size_t i=0; i<ROWS; ++i)
    {
        for(size_t j=0; j<COLS; ++j)
        {
            m_data[i][j]=T();
        }

    }

}

template <typename T, size_t ROWS, size_t COLS>
Array< T,ROWS,COLS>::Array(std::initializer_list<T> data)
{
    // as initializer_list returns a non constexpr size we cant static assert
// 	static_assert(	data.size()!=SIZE ,"Initialiser must be same size");
    std::copy(data.begin(),data.end(),&m_data[0][0]);

//    for(int i = 0; i<ROWS; i++)
//    {
//        for(int j = 0; j<ROWS; j++)
//        {
//            &m_data[i][j]=data;
    {

        }
//        }

//    }
}

template <typename T, size_t ROWS, size_t COLS>
void Array<T,ROWS,COLS>::rangeCheck(std::size_t rowidx,std::size_t colidx)
{
    if( rowidx>ROWS)
        throw std::out_of_range("index out of range in Array<T>::at");

    if( colidx>COLS)
        throw std::out_of_range("index out of range in Array<T>::at");
}


template <typename T, size_t ROWS, size_t COLS>
T& Array< T,ROWS,COLS>::operator()(std::size_t rowidx,std::size_t colidx)
{
    rangeCheck(rowidx,colidx);
    return m_data[rowidx][colidx];
}

template <typename T, size_t ROWS, size_t COLS>
T& Array< T,ROWS,COLS>::at(std::size_t rowidx,std::size_t colidx)
{
    rangeCheck(rowidx,colidx);
  return m_data[rowidx][colidx];
}



template <typename T, size_t ROWS, size_t COLS>
const T& Array< T,ROWS,COLS>::operator()(std::size_t rowidx,std::size_t colidx) const
{
    rangeCheck(rowidx,colidx);
  return const_cast<T&>(m_data[rowidx][colidx]);
}

template <typename T, size_t ROWS, size_t COLS>
void Array< T,ROWS,COLS>::print()
{
    for(int i = 0; i<ROWS; i++)
      {
          for(int j = 0; j<COLS; j++)
          {
              std::cout<<m_data[i][j]<<" ";

          }
          std::cout<<"\n";

      }
}




#endif // ARRAY_H
