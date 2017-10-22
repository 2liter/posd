#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const{
    if(_elements.empty()) return "[]";
  }
  string value() const;
  bool match(Term & term);

public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const;
  List * tail() const;

private:
  vector<Term *> _elements;

};

#endif
