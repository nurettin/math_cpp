#ifndef CONTAINER_MATRIX_HPP
#define CONTAINER_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <ostream>
#include <istream>
#include <iomanip>
#include <fstream>

namespace pwned
{

template <typename T>
struct matrix
{
  typedef typename std::vector<T> col_t;
  typedef typename std::vector<col_t> row_t;

  private:
  typename row_t::size_type row_size;
  typename col_t::size_type col_size;

  T det(matrix const &) const;

  row_t data;

  public:
  matrix(std::size_t= 0, std::size_t= 0, T const & = T());
  std::vector<T> row(std::size_t) const;
  std::vector<T> col(std::size_t) const;
  void resize(std::size_t, std::size_t, T const & = T());
  void resize_col(std::size_t, T const & = T());
  void resize_row(std::size_t, T const & = T());
  void del_col(std::size_t);
  void del_row(std::size_t);
  void change_col(std::vector<T> const &, std::size_t);
  bool compare(matrix const &) const;
  std::ostream &print(std::size_t, std::size_t, std::ostream &) const;
  std::ostream &pretty_print(char const*, std::size_t, std::size_t, std::ostream &) const;
  std::istream &input(std::istream &);
  T const &operator()(std::size_t, std::size_t) const;
  T &operator()(std::size_t, std::size_t);
  T det() const;
  matrix &operator*= (T const &);
  matrix &operator/= (T const &);
  matrix &operator*= (matrix const &);
  matrix &operator+= (matrix const &);
  matrix &operator-= (matrix const &);
  matrix minor_matrix(std::size_t, std::size_t) const;
  matrix cofactor_matrix() const;
  matrix transpose() const;
  matrix inverse() const;
  matrix identity() const;
  matrix adj() const;
};

template <typename T>
matrix<T> operator* (matrix<T> const &, T const &);

template <typename T>
matrix<T> operator* (matrix<T> const &, matrix<T> const &);

template <typename T>
matrix <T> operator+ (matrix<T> const &, matrix<T> const &);

template <typename T>
matrix <T> operator- (matrix<T> const &, matrix<T> const &);

template <typename T>
bool operator== (matrix<T> const &, matrix<T> const &);

template <typename T>
std::istream &operator>> (std::istream &, matrix<T> &);

template <typename T>
std::ostream &operator<< (std::ostream &, matrix<T> &);

}

#include "matrix_def.hpp"

#endif
