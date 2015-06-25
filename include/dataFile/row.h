#ifndef ROW_H
#define ROW_H

#include <sstream>
#include <string>
#include <vector>

class row{
   private:
      void setValuesArray(const std::string &in,const char _delim);
   protected:

   char _delim;
      std::vector<std::string> _values;
   public:
   //data will be tab delimited and only one line
   row(){};
   row(const std::string & in,const char Delim);
   std::vector<std::string> & getRow(){return _values;};

   virtual int getColumnNumber(const std::string & in);

   virtual void addColumn(const std::string & value);
   virtual void setColumnValue(const int num,const std::string & value);
   char getDelim()const{return _delim;};
	std::string printlnToFile();

   int getNumColumns()const{return _values.size();};
   
   const std::string & getValue(int num){return _values[num];};
   std::string print();
   std::vector<std::string> getValues()const{return _values;};
};

#endif
