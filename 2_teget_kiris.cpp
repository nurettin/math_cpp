#include "polinom.hpp"

#include <iostream>
#include <iomanip>

using namespace onur;

void teget_kiris(polinom<double> const &p, double a, double b)
{
  polinom<double> pt, ptt;

  std::cout<< p<< std::endl;

  double x1, x2, xold;

  std::cout<< "interval: ["<< a<< ", "<< b<< "]"<< std::endl;

  pt= derivative(p);
  ptt= derivative(pt);

  std::cout<< pt<< std::endl;
  std::cout<< ptt<< std::endl;

  int sayac= 4;
  if(p(a)*ptt(a)< 0)
  {
    std::cout<< "f(a)* fpp(a)< 0"<< std::endl;
    xold= a;
    while(sayac--)
    {
      x1= xold- p(xold)* (xold- b)/ (p(xold)- p(b));
      std::cout<< std::fixed<< std::setprecision(4)<< "x1= "<< x1<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x1* 10000)!= long(xold* 10000))
        xold= x1;
      else
        break;
    }
    std::cout<< "Root X1= "<< x1<< std::endl;

    xold= b;
    sayac= 4;
    while(sayac--)
    {
      x2= xold- p(xold)/ pt(xold);
      std::cout<< std::fixed<< std::setprecision(4)<< "x2= "<< x2<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x2* 10000)!= long(xold* 10000))
        xold= x2;
      else
        break;
    }

    std::cout<< "Root X= "<< (x1+ x2)/ 2.0<< std::endl;
  }
  else
  {
    std::cout<< "f(a)* fpp(a)>= 0"<< std::endl;
    sayac= 4;
    xold= b;
    while(sayac--)
    {
      x1= xold- p(xold)* (xold- a)/ (p(xold)- p(a));
      std::cout<< std::fixed<< std::setprecision(4)<< "x1= "<< x1<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x1* 10000)!= long(xold* 10000))
        xold= x1;
      else
        break;
    }
    std::cout<< "Root X1= "<< x1<< std::endl;

    xold= a;
    sayac= 4;
    while(sayac--)
    {
      x2= xold- p(xold)/ pt(xold);
      std::cout<< std::fixed<< std::setprecision(4)<< "x2= "<< x2<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x2* 10000)!= long(xold* 10000))
        xold= x2;
      else
        break;
    }

    std::cout<< "Root X= "<< (x1+ x2)/ 2.0<< std::endl;

  }

}

int main()
{
  polinom<double> p, pt, ptt;

  p[0]= -3;
  p[1]= 7;
  p[2]= 3;
  
  teget_kiris(p, 0, 1);

}

