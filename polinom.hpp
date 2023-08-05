#ifndef CONTAINER_POLINOM_HPP
#define CONTAINER_POLINOM_HPP

#include <ostream>
#include <istream>
#include <map>
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>



template <typename T, typename N>
T pow(T what, N how)
{
  if(how== 0) return T(1);
  T it(1);
  for(N e= 0; e< how; ++ e)
    it*= what;
  return it;
}

template <typename T>
struct polinom
{
  private:

  public:
  typedef std::map<int, T> data_t;
  data_t coef;

  polinom()
  {
  }

  polinom(T const &d)
  {
    coef[0]= d;
  }

  polinom(polinom const &p)
  {
    coef= p.coef;
  }

  polinom(std::vector<T> const &v)
  {
    for(typename std::vector<T>::size_type each= 0; each< v.size(); ++ each)
      coef[v.size()- each- 1]= v[each];
  }

  polinom &operator= (polinom const &p)
  {
    coef= p.coef;
    return *this;
  }

  ~polinom()
  {
  }

  int degree() const
  {
    return coef.rbegin()-> first;
  }

  T &operator[](int const &i)
  {
    return coef[i];
  }

  T operator[](int const &i) const
  {
    typename data_t::const_iterator where= coef.find(i);

    if(where!= coef.end())
      return where-> second;

    return T();
  }

  T operator()(T const &x) const
  {
    T sum= 0;

    for(typename data_t::const_iterator i= coef.begin();
      i!= coef.end(); ++ i)
      sum+= i-> second* pow(x, i-> first);

    return sum;
  }

  polinom &operator+= (polinom const &p)
  {
    typename data_t::iterator thisit;

    for(typename data_t::const_iterator it= p.coef.begin();
      it!= p.coef.end(); ++ it)
      if((thisit= coef.find(it-> first))!= coef.end())
        thisit-> second+= it-> second;
      else
        coef.insert(std::make_pair(it-> first, it-> second));

    return *this;
  }

  polinom &operator+= (T const &d)
  {
    (*this)[0]+= d;
    return *this;
  }

  polinom &operator-= (polinom const &p)
  {
    typename data_t::iterator thisit;

    for(typename data_t::const_iterator it= p.coef.begin(); it!= p.coef.end(); ++ it)
      if((thisit= coef.find(it-> first))!= coef.end())
        if((thisit-> second-= it-> second)== 0)
          this-> coef.erase(thisit);
      else
        coef.insert(std::make_pair(it-> first, it-> second));

    return *this;
  }

  polinom &operator-= (T const &d)
  {
    (*this)[0]-= d;
    return *this;
  }

  polinom &operator*= (polinom const &p)
  {
    polinom sum;

    for(typename data_t::const_iterator teach= coef.begin();
      teach!= coef.end(); ++ teach)
    {
      polinom temp;

      for(typename data_t::const_iterator peach= p.coef.begin();
        peach!= p.coef.end(); ++ peach)
        if(teach-> second* peach-> second)
          temp.coef[teach-> first+ peach-> first]= teach-> second* peach-> second;

      sum+= temp;
    }

    return *this= sum;
  }

  /**
    Divides the current polynomial with p, returns the remainder
    and makes current polynomial the result of the division.
  */

  T operator/= (polinom const &p)
  {
    polinom remain= *this;
    polinom mult;
    polinom div;

    do
    {
      mult[remain.degree()- p.degree()]=
        (remain.coef.rbegin()-> second)/ (p.coef.rbegin()-> second);
      div+= mult;
      mult*= p;
      remain-= mult;
      mult.clear();
    }
    while(remain.degree());

    *this= div;
    return remain[0];
  }

  polinom &operator*= (T const &d)
  {
    for(typename data_t::iterator each= coef.begin();
      each!= coef.end(); ++ each)
      each-> second*= d;

    return *this;
  }

  polinom &operator/= (T const &d)
  {
    for(typename data_t::iterator each= coef.begin();
      each!= coef.end(); ++ each)
      each-> second/= d;

    return *this;
  }

  polinom &shift(T const &d)
  {
    polinom temp;
    temp[0]= d;
    temp[1]= 1;
    polinom sum;

    for(typename data_t::reverse_iterator e= coef.rbegin();
      e!= coef.rend(); ++ e)
    {

      polinom mult= 1;
      for(int count= e-> first; count> 0; -- count)
        mult*= temp;
      mult*= e-> second;

      sum+= mult;
    }

    return *this= sum;
  }

  void clear()
  {
    coef.clear();
  }

  friend std::ostream &operator<< (std::ostream &o, polinom const &p)
  {
    if(p.coef.empty())
      return o<< "empty";
    typedef std::map<int, T> data_t;
    for(typename data_t::const_reverse_iterator it= p.coef.rbegin();
      it!= p.coef.rend(); ++ it)
    {
      if(it-> second== 0)
        continue;
      if(it-> first!= p.degree())
        o<< ((it-> second>= 0)?" +":" ");
      if(it-> second!= 1)
        o<< it-> second;
      if(it-> first!= 0)
      {
        o<< "x";
        if(it-> first!= 1)
          o<< "^"<< it-> first;
      }
      else if(it-> second== 1)
        o<< 1;
    }

    return o;
  }

};

template <typename T>
polinom<T> operator+ (polinom<T> const &p1, polinom<T> const &p2)
{
  polinom<T> temp= p1;
  temp+= p2;
  return temp;
}

template <typename T>
polinom<T> operator- (polinom<T> const &p1, polinom<T> const &p2)
{
  polinom<T> temp= p1;
  temp-= p2;
  return temp;
}

template <typename T>
polinom<T> operator* (polinom<T> const &p1, polinom<T> const &p2)
{
  polinom<T> temp= p1;
  temp*= p2;
  return temp;
}

template <typename T>
polinom<T> operator* (polinom<T> const &p, T const &d)
{
  polinom<T> temp= p;
  temp*= d;
  return temp;
}

template <typename T>
polinom<T> operator/ (polinom<T> const &p, T const &d)
{
  polinom<T> temp= p;
  temp/= d;
  return temp;
}

template <typename T>
polinom<T> derivative(polinom<T> const &p)
{
  polinom<T> temp;
  typedef std::map<int, T> data_t;
  for(typename data_t::const_reverse_iterator it= p.coef.rbegin();
    it!= p.coef.rend(); ++ it)
  {
    temp[it-> first-1]= it-> first* it-> second;
  }

  return temp;
}


#endif
