#ifndef TABLEABS_H
#define TABLEABS_H

#include "rowWHeader.h"
class tableAbs{
   private:
   protected:
      row _columnHeaders;
      char _delim;
      bool _header;


   public:
   enum FrontBack{
      theFRONT,
      theBACK
   };

   static const FrontBack FRONT=theFRONT;
   static const FrontBack BACK=theBACK;
   char getDelim()const{return _delim;};
   tableAbs():_delim('0'){};
   tableAbs(const row & header,const char delim):_columnHeaders(header),_delim(delim){};
   tableAbs(const char in):_delim(in){};

   virtual std::string printRow(int i)=0;
   virtual std::string printHeader()=0;
   
   virtual ~tableAbs(){};   
};
#endif
