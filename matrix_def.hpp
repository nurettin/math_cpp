#ifndef ONUR_CONTAINER_MATRIX_DEF_HPP
#define ONUR_CONTAINER_MATRIX_DEF_HPP

#include <cstddef>
#include <vector>
#include <iostream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <vector>
#include <iostream> // temporarily

namespace pwned
{

// MEMBER

template <typename T>
matrix<T>::matrix(std::size_t row, std::size_t col, T const &init)
: row_size(row), col_size(col)
{
  resize(row, col, init);
}

template <typename T>
std::vector<T> matrix<T>::row(std::size_t r) const
{
  typename row_t::const_iterator which= data.begin();
  std::advance(which, r);
  return *which;
}

template <typename T>
std::vector<T> matrix<T>::col(std::size_t r) const
{
  std::vector<T> col_vec;
  col_vec.reserve(row_size);
  for(typename row_t::const_iterator each= data.begin(); each!= data.end(); ++ each)
    col_vec.push_back(*(each-> begin()+ r));
  return col_vec;
}

template <typename T>
void matrix<T>::resize(std::size_t row, std::size_t col, T const &init)
{
  resize_row(row, init);
  resize_col(col, init);
}

template <typename T>
void matrix<T>::resize_col(std::size_t len, T const &init)
{
  for(typename row_t::iterator i= data.begin(); i!= data.end(); ++ i)
    i-> resize(len, init);
  col_size= len;
}

template <typename T>
void matrix<T>::resize_row(std::size_t len, T const &init)
{
  data.resize(len, std::vector<T>(col_size, init));
  row_size= len;
}

template <typename T>
void matrix<T>::del_row(std::size_t r)
{
  data.erase(data.begin()+ r);
  -- row_size;
}

template <typename T>
void matrix<T>::del_col(std::size_t c)
{
  for(typename row_t::iterator row= data.begin(); row!= data.end(); ++ row)
    row-> erase(row-> begin()+ c);
  -- col_size;
}

template <typename T>
void matrix<T>::change_col(std::vector<T> const &v, std::size_t c)
{
	for(std::size_t r= 0; r< row_size; ++ r)
		data[r][c- 1]= v[r];
}

template <typename T>
std::ostream &matrix<T>::print(std::size_t p, std::size_t w, std::ostream &o) const
{
  for(typename row_t::const_iterator i1= data.begin(); i1!= data.end(); ++ i1)
  {
    for(typename col_t::const_iterator i2= i1-> begin(); i2!= i1-> end(); ++ i2)
      o<< std::setw(w)<< std::setprecision(p)<< std::fixed<< *i2;
    o<< "\n";
  }
  return o;
}

template <typename T>
std::ostream &matrix<T>::pretty_print(char const* p, std::size_t precision, std::size_t width, std::ostream &o) const
{
  o<< p<< " ["<< row_size<< "x"<< col_size<< "]:\n";
  return print(precision, width, o);
}

template <typename T>
std::istream &matrix<T>::input(std::istream &i)
{
  for(typename row_t::iterator i1= data.begin(); i1!= data.end(); ++ i1)
    for(typename col_t::iterator i2= i1-> begin(); i2!= i1-> end(); ++ i2)
      i>> *i2;
  return i;
}

template <typename T>
T const &matrix<T>::operator()(std::size_t row, std::size_t col) const
{
  return data[row- 1][col- 1];
}

template <typename T>
T &matrix<T>::operator()(std::size_t row, std::size_t col)
{
  return data[row- 1][col- 1];
}

template <typename T>
matrix<T> &matrix<T>::operator*= (T const &s)
{
  for(typename row_t::iterator i1= data.begin(); i1!= data.end(); ++ i1)
    for(typename col_t::iterator i2= i1-> begin(); i2!= i1-> end(); ++ i2)
      (*i2)*= s;
  return *this;
}


template <typename T>
matrix<T> &matrix<T>::operator/= (T const &s)
{
  for(typename row_t::iterator i1= data.begin(); i1!= data.end(); ++ i1)
    for(typename col_t::iterator i2= i1-> begin(); i2!= i1-> end(); ++ i2)
      (*i2)/= s;
  return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator*= (matrix const &B)
{
  if(col_size!= B.row_size)
    return *this;

  matrix<T> C(row_size, B.col_size);

  T sum;

  for(std::size_t i= 0; i< row_size; ++ i)
    for(std::size_t j= 0; j< B.col_size; ++ j)
    {
      sum= 0;
      for(std::size_t k= 0; k< col_size; ++ k)
        sum+= data[i][k]* B.data[k][j];
      C.data[i][j]= sum;
    }

  return *this= C;
}

template <typename T>
matrix<T> &matrix<T>::operator+= (matrix const &B)
{
  if((row_size!= B.row_size) || (col_size!= B.col_size))
    return *this;

  for(std::size_t ey= 0; ey< row_size; ++ ey)
    for(std::size_t ex= 0; ex< col_size; ++ ex)
      data[ey][ex]+= B.data[ey][ex];

  return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator-= (matrix const &B)
{
  if((row_size!= B.row_size) || (col_size!= B.col_size))
    return *this;

  for(std::size_t ey= 0; ey< row_size; ++ ey)
    for(std::size_t ex= 0; ex< col_size; ++ ex)
      data[ey][ex]-= B.data[ey][ex];

  return *this;
}

template <typename T>
bool matrix<T>::compare(matrix const &B) const
{
  return data== B.data;
}

template <typename T>
matrix<T> matrix<T>::transpose() const
{
  matrix<T> AT(col_size, row_size);
  for(std::size_t rA= 0; rA< row_size; ++ rA)
    for(std::size_t cA= 0; cA< col_size; ++ cA)
      AT.data[cA][rA]= data[rA][cA];
  return AT;
}

template <typename T>
matrix<T> matrix<T>::minor_matrix(std::size_t row, std::size_t col) const
{
  matrix<T> temp(*this);
  temp.del_col(col);
  temp.del_row(row);
  return temp;
}

template <typename T>
T matrix<T>::det() const
{
  matrix<T> m(*this);
  return det(m);
}

template <typename T>
T matrix<T>::det(matrix<T> const &mat) const
{
  row_t const &m= mat.data;
  if(m.size()== 2)
    return m[1][1]* m[0][0]- m[0][1]* m[1][0];

  T result(0);
  int sign;
  for(std::size_t col= 0; col< m.begin()-> size(); ++ col)
  {
    sign= 2* ((col+ 1)%2)- 1;
    result+= sign* m[0][col]* mat.det(mat.minor_matrix(0, col));
  }
  return result;
}

template <typename T>
matrix<T> matrix<T>::cofactor_matrix() const
{
  matrix<T> mCF(*this);
  row_t &m= mCF.data;
  int sign;
  for(std::size_t row= 0; row< m.size(); ++ row)
    for(std::size_t col= 0; col< m.begin()-> size(); ++ col)
    {
      sign= 2* ((col+ ((row+ 1)% 2))%2)- 1;
      m[row][col]= sign* minor_matrix(row, col).det();
    }
  return mCF;
}

template <typename T>
matrix<T> matrix<T>::adj() const
{
  return cofactor_matrix().transpose();
}

template <typename T>
matrix<T> matrix<T>::inverse() const
{
  return adj()/ T(det());
}

template <typename T>
matrix<T> matrix<T>::identity() const
{
  matrix<T> i(row_size, col_size, 0);
  for(std::size_t row= 0; row< i.row_size; ++ row)
    i.data[row][row]= 1;
  return i;
}

// FREESTANDING

template <typename T>
matrix<T> operator* (matrix<T> const &m, T const &s)
{
  matrix<T> temp(m);
  return temp*= s;
}

template <typename T>
matrix<T> operator/ (matrix<T> const &m, T const &s)
{
  matrix<T> temp(m);
  return temp/= s;
}

template <typename T>
matrix<T> operator* (matrix<T> const &m1, matrix<T> const &m2)
{
  matrix<T> temp(m1);
  return temp*= m2;
}

template <typename T>
matrix<T> operator+ (matrix<T> const &m1, matrix<T> const &m2)
{
  matrix<T> temp(m1);
  return temp+= m2;
}

template <typename T>
matrix<T> operator- (matrix<T> const &m1, matrix<T> const &m2)
{
  matrix<T> temp(m1);
  return temp-= m2;
}

template <typename T>
bool operator== (matrix<T> const &m1, matrix<T> const &m2)
{
  return m1.compare(m2);
}

template <typename T>
std::istream &operator>> (std::istream &i, matrix<T> &m)
{
  return m.input(i);
}

}

#endif
