#ifndef MAPPER_H
#define MAPPER_H

#include "fileTable.h"
#include "config.h"
#include "mapAddress.h"
#include "rowWHeader.h"
class mapper{

   private:
      fileTable _input;
      fileTable _output;
      config _configuration;

      bool validateColumns();
       

   protected:

   public:

   mapper(const std::string & in);

   void setInput(const std::string & in,const char delim);
   void setOutput(const std::string & in,const row & header);
   void setConfig(const std::string & in);

   void mappAddresses();
  
   bool addLatLong(rowWHeader & in );
   
   


};

#endif
