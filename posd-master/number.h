#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include "atom.h"



using std::string;



class Number : public Term{
  public:
    Number(double s) ;
    double _value;
    string _str;
    string symbol() const;

    bool match(Term &term);
};

#endif 