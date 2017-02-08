#ifndef MATRIX_H
#define MATRIX_H

template <typename T, int ROWS=0, int COLS=0>

class Matrix
{
private:

    // row size
    int m_rows=ROWS;
    // column size
    int m_cols=COLS;

    T m_data[ROWS][COLS];

public:
    // contructor will set data to zero
    Matrix();

    // read only returns number of rows
    const T* rows() const { return m_rows; }
    // read only returns number of cols
    const T* cols() const { return m_cols; }

    // read only data
    const T* data() const;
    // accessible data
    T* data();


    //code referenced from http://www.learncpp.com/cpp-tutorial/99-overloading-the-parenthesis-operator/
    // overload operator
    T& operator()(T rowValue, T colValue);
    const T& operator()(T rowValue, T colValue) const; // for const objects





};

#endif // MATRIX_H
