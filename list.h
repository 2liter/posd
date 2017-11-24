#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <vector>
#include <string>
#include <typeinfo>
#include "variable.h"
#include <iostream>
using std::vector;


class List : public Term {
public:
  string symbol() const ;
  string value() const ;
  bool match(Term & term) ;
public:
  List (): _elements(0) {}
  List (vector<Term *> const & elements):_elements(elements){}
  vector<Term *> getEle() { return _elements;}
  Term * getEleArg(int i) { return _elements[i];}
  Term * head() const;
  List * tail() const;
private:
  vector<Term *> _elements;
};

#endif
