#ifndef ROWHEADER_H
#define ROWHEADER_H

#include "row.h"

class rowWHeader: public row {
   private:
      std::vector<std::string> _header;

   public:

   rowWHeader(){};
   rowWHeader(const row & header, const row & columns);

   virtual int getColumnNumber(const std::string & in);
   virtual void addColumn(const std::string & value);
   void setColumnValue(const std::string & columnName, const std::string & columnValue);

   std::string getColumnValue(const std::string & columnName);
   row getRow();

};


#endif
