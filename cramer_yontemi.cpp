#include "matrix.hpp"
#include <iostream>
#include <vector>

using namespace pwned;

int main()
{
  matrix<double> A(3, 3), Atemp;

  A(1, 1)= 8;
  A(1, 2)= 2;
  A(1, 3)= 3;
  A(2, 1)= 1;
  A(2, 2)= -9;
  A(2, 3)= 2;
  A(3, 1)= 2;
  A(3, 2)= 3;
  A(3, 3)= 6;

  Atemp= A;

  A.pretty_print("A", 0, 5, std::cout);
  double Adet, A1det, A2det, A3det;

  Adet= A.det();

  std::cout<< "det(A)= "<< Adet<< std::endl;

  std::vector<double> B;
  B.push_back(30);
  B.push_back(1);
  B.push_back(31);

  Atemp.change_col(B, 1);

  Atemp.pretty_print("\nA1", 0, 5, std::cout);

  A1det= Atemp.det();
  std::cout<< "x1= det(A1)/det(A)= "<< A1det/ Adet<< std::endl;
  Atemp= A;
  Atemp.change_col(B, 2);
  Atemp.pretty_print("\nA2", 0, 5, std::cout);
  A2det= Atemp.det();
  std::cout<< "x2= det(A2)/det(A)= "<< A2det/ Adet<< std::endl;

  Atemp= A;
  Atemp.change_col(B, 3);
  Atemp.pretty_print("\nA3", 0, 5, std::cout);
  A3det= Atemp.det();
  std::cout<< "x3= det(A3)/det(A)= "<< A3det/ Adet<< std::endl;

}
