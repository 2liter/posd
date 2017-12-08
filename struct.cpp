
#include "struct.h"
#include "iterator.h"
Iterator<Term> * Struct::createIterator()
{
  return new StructIterator(this);
}

Iterator<Term*> * Struct::createDFSIterator()
{
  return new DFSIterator(new Node(TERM,this,nullptr,nullptr));
}

Iterator<Term*> * Struct::createBFSIterator()
{
  return new BFSIterator(new Node(TERM,this,nullptr,nullptr));
}

