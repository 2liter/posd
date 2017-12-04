#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "node.h"

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual void set(Term & term) = 0;
  virtual bool isDone() const = 0;
};

class NullIterator :public Iterator{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  void set(Term & term){}
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
  friend class Parser;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  void set(Term &term){
    _s->set(_index, term);
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
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  void set(Term &term){
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};




class DFSIterator :public Iterator {
public:
  DFSIterator(Node *node): _index(0), _node(node) {
    static vector<Term *> _terms1;
    if(node == nullptr)  return;

    if(node->payload == TERM){
      _terms1.push_back(node->term);
    }
    if(node->payload == EQUALITY){ _terms1.push_back(new Atom("=")); }
    if(node->payload == COMMA){ _terms1.push_back(new Atom(",")); }
    if(node->payload == SEMICOLON){ _terms1.push_back(new Atom(";")); }

    DFSIterator(node->left);
    DFSIterator(node->right);

    _terms = _terms1;
  }
  void first() {_index = 0;
    std::cout << _terms.size() << "*\n" ;

  }
  void set(Term &term){}
  Term* currentItem() const {return _terms[_index];}
  bool isDone() const { return _terms.size() == _index + 1 ;}
  void next() { _index++; }

private:
  int _index;
  vector<Term *> _terms;
  Node * _node;
};
  
class BFSIterator :public Iterator {
public:
  BFSIterator(Node *node): _index(0), _node(node) {
    if(_node == nullptr)  return;
    _terms.push_back(_node->term);
    
    BFSIterator(_node->left);
    BFSIterator(_node->right);

  }
  void first() {_index = 0;}
  void set(Term &term){}
  Term* currentItem() const {return _terms[_index];}
  bool isDone() const { return _terms.size() == _index ;}
  void next() { _index++; }

private:
  int _index;
  vector<Term *> _terms;
  Node * _node;

};


#endif