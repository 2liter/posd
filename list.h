#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
using std::vector;

class List : public Term {
public:

  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}

  std::string symbol() const;
  std::string value() const;
  bool match(Term & term);


  Term * head() const;
  List * tail() const;

private:
  vector<Term *> _elements;

};

#endif
