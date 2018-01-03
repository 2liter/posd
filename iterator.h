#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

class NullIterator :public Iterator{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

class StructIterator :public Iterator {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

class ListIterator :public Iterator {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _list2 = _list;
  }

  Term* currentItem() const {
    return _list2->head();
  }

  bool isDone() const {
    if( _list2->tail()->symbol() == "[]" )
      return true ;
    return false ;  
  }

  void next() {
    
    if(!isDone())
      _list2 = dynamic_cast<List*>( _list2->tail());
  }
private:
  int _index;
  List* _list;
  List* _list2;
};
#endif
