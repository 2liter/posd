#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>

class Variable;
class Atom;


using std::string;

class Number
{
  public:
    Number(int s) ;
    int _value;
    string _str;
    string value() ;
    string symbol() ;
    bool match( int s ) ;

    bool match(Atom tom);

    bool match(Variable &X);


};

#endif 