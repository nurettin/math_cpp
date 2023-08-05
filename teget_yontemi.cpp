  #include "polinom.hpp"

#include <iostream>
#include <iomanip>

using namespace onur;

//  polinomun kokunu bulmak icin newton-rhapson (teget) yontemi

void teget(polinom<double> const &p, double a, double b)
{
  polinom<double> pt, ptt;

  std::cout<< p<< std::endl;

  double x, xold;

  std::cout<< "interval: ["<< a<< ", "<< b<< "]"<< std::endl;

  pt= derivative(p);  // turevini alma
  ptt= derivative(pt);  // turevin de turevini alma

  std::cout<< pt<< std::endl;
  std::cout<< ptt<< std::endl;

  int sayac= 4;    // 4 iterasyon icin (ayarlamak mumkun)
  if(p(a)*ptt(a)< 0)   // teget ve kiris yontemlerini hangi noktalarda kullanacagimizi belirlemek icin
  {
    std::cout<< "f(a)* fpp(a)< 0"<< std::endl;
    xold= b;
    while(sayac--)
    {
      x= xold- p(xold)/pt(xold);
      std::cout<< std::fixed<< std::setprecision(4)<< "x= "<< x<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x* 10000)!= long(xold* 10000))
        xold= x;
      else
        break;
    }
    std::cout<< "Root X= "<< x<< std::endl;

  }
  else
  {
    std::cout<< "f(a)* fpp(a)>= 0"<< std::endl;
    sayac= 4;
    xold= a;
    while(sayac--)
    {
      x= xold- p(xold)/pt(xold);
      std::cout<< std::fixed<< std::setprecision(4)<< "x= "<< x<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x* 10000)!= long(xold* 10000))
        xold= x;
      else
        break;
    }
    std::cout<< "Root x= "<< x<< std::endl;

  }

}

int main()
{
  polinom<double> p, pt, ptt;

  p[0]= -7;
  p[2]= 1;

  teget(p, 2, 3);   // fonksiyona polinom ve aralik veriliyor. (degisik polinomlarla calisabilir)
  teget(p, -3, -2);
}

