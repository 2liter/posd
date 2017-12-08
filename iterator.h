#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "node.h"
#include <queue>

using namespace std;

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual void set(Term & term) = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class TermIterator :public Iterator<T> {
public:
  friend class Struct;
  friend class Parser;
  friend class List;
  TermIterator(T *s): _index(0), _s(s) {}
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

  int _index;
  T* _s;
};

class StructIterator :public Iterator<Term> {
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

class NullIterator :public Iterator<Term>{
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



class ListIterator :public Iterator<Term> {
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






class DFSIterator :public Iterator<Term*> {
public:
  DFSIterator(Node *node): _index(0), _node(node) {
    dfs(_node,false);
  }
  void dfs(Node *node,bool reset) {
    static vector<Term *> _terms1;
    if(reset) _terms1.clear();
    if(node == nullptr)  return;

    if(node->payload == TERM){ _terms1.push_back(node->term);}
    if(node->payload == EQUALITY){ _terms1.push_back(new Atom("=")); }
    if(node->payload == COMMA){ _terms1.push_back(new Atom(",")); }
    if(node->payload == SEMICOLON){ _terms1.push_back(new Atom(";")); }

    DFSIterator(node->left);
    DFSIterator(node->right);

    _terms = _terms1;
  }
  void first() {
    dfs(nullptr,true);
    _index = 0;
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
  
class BFSIterator :public Iterator<Term*> {
public:
  BFSIterator(Node *node): _index(0), _node(node) {
    breadthFirst(node);
  }

  void breadthFirst(Node* tree)
  {
      queue<Node*> queue;
      queue.push(tree);
      while (!queue.empty())
      {
          Node* tmpTree = queue.front();
          queue.pop();

            if(tmpTree->payload == TERM){ _terms.push_back(tmpTree->term);}
            if(tmpTree->payload == EQUALITY){ _terms.push_back(new Atom("=")); }
            if(tmpTree->payload == COMMA){ _terms.push_back(new Atom(",")); }
            if(tmpTree->payload == SEMICOLON){ _terms.push_back(new Atom(";")); }

          if (tmpTree->left != nullptr)
              queue.push(tmpTree->left);
          if (tmpTree->right != nullptr)
              queue.push(tmpTree->right);
      }
  }

  void first() {_index = 0;}
  void set(Term &term){}
  Term* currentItem() const {return _terms[_index];}
  bool isDone() const { return _terms.size() == _index + 1 ;}
  void next() { _index++; }

private:
  int _index;
  vector<Term *> _terms;
  Node * _node;

};


#endif