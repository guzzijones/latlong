#include "row.h"
#include <iostream>
#include <sstream>

row::row(const std::string & in,const char  Delim):_delim(Delim){
   setValuesArray(in,_delim);
}

void row::setValuesArray(const std::string & in,const char delim){
   std::string token;
   std::stringstream ss(in);
   while(std::getline(ss,token,_delim)){
        _values.push_back(token); 

   }
}

int row::getColumnNumber(const std::string & in){
   int i=0;
   for(std::vector<std::string>::iterator it=_values.begin();it!=_values.end();++it){
         if(*it==in)
         {
            return i;
         }
         i++; 
   }
   return -1;
}
std::string row::printlnToFile(){
	std::string tmp=print();
	tmp="\n"+tmp;
	return tmp;
}
std::string row::print(){
   std::string tmp;
  for(std::vector<std::string>::iterator it=_values.begin();it!=_values.end()-1;++it){
     tmp+=(*it); 
     tmp+=_delim;
  }
  //add last column with no delimiter
  tmp+=*(_values.end()-1); 
  //std::cout << "##########start row########" << tmp << "#######END with line feed" << std::endl;
  return tmp;
}
void row::addColumn(const std::string & value){
   _values.push_back(value);

}
void row::setColumnValue(int num,const std::string & value){
   _values[num]=value;
}
