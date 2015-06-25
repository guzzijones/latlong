#ifndef DELEGATE_H
#define DELEGATE_H
#include <iostream>
#include <algorithm>
template <class DT,class PT>
class delegate{

   public:
   bool (DT::*_delegateFunction)(PT &);
   DT * _delegateInstance;

   public:
   void connectToDelegate(DT* delegateInstanceIn, bool (DT::*delegateFunctionIn)(PT & in)){
      _delegateInstance=delegateInstanceIn;
      _delegateFunction=delegateFunctionIn;
   };
   bool run(PT & in){
      std::cout << "running function in delegate" << std::endl;
      bool result = (_delegateInstance->*_delegateFunction)(in);
      return result; 
   }
};

#endif
