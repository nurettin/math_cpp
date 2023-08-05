#include "polinom.hpp"

#include <iostream>
#include <iomanip>

using namespace onur;

int main()
{
  // basit iterasyon yontemiyle kok bulma programi.



  polinom<double> f, Fpay, Fpayda, Ftpay, Ftpayda; // Ft turev

  f[0]= 1;
  f[1]= 3;
  f[2]= 2;
  f[3]= 1;

  std::cout<< f<< std::endl;
  std::cout<< "Burada herhangi bir x'i yanliz birakalim."<< std::endl;

  std::cout<< "Varsayalim x = F(x) = -1/ (x^2 + 2x + 3)"<< std::endl; // (Fpay / Fpayda)


  Fpay[0]= -1;

  Fpayda[0]= 3;
  Fpayda[1]= 2;
  Fpayda[2]= 1;

  Ftpay= derivative(Fpayda);
  Ftpayda= (Fpayda* Fpayda);

  std::cout<< "Ft= ("<< Ftpay<< ") / ("<< Ftpayda<< ")"<< std::endl;

  double Fta, Ftb;
  double a, b, x, xold;
  a= -1; b= 0;
  Ftb= Ftpay(b)/ Ftpayda(b);
  Fta= Ftpay(a)/ Ftpayda(a);
  std::cout<< "Ft(a)= "<< Fta<< std::endl;
  std::cout<< "Ft(b)= "<< Ftb<< std::endl;

  if(Fta< 1 && Ftb< 1)
  {
    xold= b;

    while(1)
    {
      x= Fpay(xold)/ Fpayda(xold);
      std::cout<< std::fixed<< std::setprecision(5)<< "xold: "<< xold<< std::endl;
      std::cout<< "x: "<< x<< std::endl;

      if(long(x* 10000)!= long(xold* 10000))
        xold= x;
      else
        break;

    }

    std::cout<< "Root x= "<< x<< std::endl;
  }


}
