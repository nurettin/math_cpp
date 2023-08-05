#include "polinom.hpp"

#include <iostream>
#include <iomanip>

using namespace onur;

int main()
{
  polinom<double> p, pt, ptt;

  p[0]= 2;
  p[2]= -4;
  p[3]= 1;

  std::cout<< p<< std::endl;

  double a= 0, b= 1, x, xold;

  std::cout<< "interval: ["<< a<< ", "<< b<< "]"<< std::endl;

  pt= derivative(p);
  ptt= derivative(pt);

  std::cout<< pt<< std::endl;
  std::cout<< ptt<< std::endl;

  int sayac= 0;
  if(ptt(a)< 0)
  {
    xold= b;
    while(1)
    {
      x= xold- p(xold)* (xold- a)/ (p(xold)- p(a));
      std::cout<< std::fixed<< std::setprecision(3)<< "x= "<< x<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x* 1000)!= long(xold* 1000))
        xold= x;
      else
        break;
    }

    std::cout<< "Root X= "<< x<< std::endl;
  }
  else
  {
    xold= a;
    while(1)
    {
      x= xold- p(xold)* (xold- b)/ (p(xold)- p(b));
      std::cout<< std::fixed<< std::setprecision(3)<< "x= "<< x<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x* 1000)!= long(xold* 1000))
        xold= x;
      else
        break;
    }

    std::cout<< "Root X= "<< x<< std::endl;

  }

}

