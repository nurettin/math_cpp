#include "polinom.hpp"

#include <iostream>
#include <iomanip>

using namespace onur;

//  polinomun kokunu bulmak icin teget-kiris yontemi

void teget_kiris(polinom<double> const &p, double a, double b)
{
  polinom<double> pt, ptt;

  std::cout<< p<< std::endl;

  double x1, x2, xold;

  std::cout<< "interval: ["<< a<< ", "<< b<< "]"<< std::endl;

  pt= derivative(p);  // turevini alma
  ptt= derivative(pt);  // turevin de turevini alma

  std::cout<< pt<< std::endl;
  std::cout<< ptt<< std::endl;

  int sayac= 4;    // 4 iterasyon icin (ayarlamak mumkun)
  if(p(a)*ptt(a)< 0)   // teget ve kiris yontemlerini hangi noktalarda kullanacagimizi belirlemek icin
  {
    std::cout<< "f(a)* fpp(a)< 0"<< std::endl;
    xold= a;
    while(sayac--)
    {
      x1= xold- p(xold)* (xold- b)/ (p(xold)- p(b));    //  regula-falsi yontemiyle
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
      x2= xold- p(xold)/ pt(xold);  // newton-rhapson yontemiyle
      std::cout<< std::fixed<< std::setprecision(4)<< "x2= "<< x2<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x2* 10000)!= long(xold* 10000))
        xold= x2;
      else
        break;
    }

    std::cout<< "Root X= "<< (x1+ x2)/ 2.0<< std::endl;  // koklerin ortalamasi
  }
  else
  {
    std::cout<< "f(a)* fpp(a)>= 0"<< std::endl;
    sayac= 4;
    xold= b;
    while(sayac--)
    {
      x1= xold- p(xold)* (xold- a)/ (p(xold)- p(a));    //  regula-falsi yontemiyle
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
      x2= xold- p(xold)/ pt(xold);  // newton-rhapson yontemiyle
      std::cout<< std::fixed<< std::setprecision(4)<< "x2= "<< x2<< std::endl;
      std::cout<< "xold= "<< xold<< std::endl;
      if(long(x2* 10000)!= long(xold* 10000))
        xold= x2;
      else
        break;
    }

    std::cout<< "Root X= "<< (x1+ x2)/ 2.0<< std::endl;  // koklerin ortalamasi.

  }

}

int main()
{
  polinom<double> p, pt, ptt;

  p[0]= -3;
  p[1]= 7;
  p[2]= 3;

  teget_kiris(p, 0, 1);   // fonksiyona polinom ve aralik veriliyor. (degisik polinomlarla calisabilir)

}

