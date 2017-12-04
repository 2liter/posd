
#include "iterator.h"
#include "node.h"


bool Node::evaluate(){
    if(this->payload == EQUALITY){
      return (*(this->left->term)).match(*(this->right->term));
    }
    else{

      bool ret = this->left->evaluate();
      ret = ret && this->right->evaluate();

      return ret ;

    }

    return true;

}


Iterator * Node::createDFSIterator(){
    return (new DFSIterator(this));
}
Iterator * Node::createBFSIterator(){

}