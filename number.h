#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include "atom.h"



using std::string;



class Number : public Term{
  public:
    Number(double s) : _value(s)
    {
      std::ostringstream strs;
      strs << _value;
      _str = strs.str();
    }
    double _value;
    string _str;
    string symbol() const{ return _str; }

};

#endif 