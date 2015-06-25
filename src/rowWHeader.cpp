#include "rowWHeader.h"

rowWHeader::rowWHeader(const row & header, const row & columns):row(columns){
  _header=header.getValues(); 

}

int rowWHeader::getColumnNumber(const std::string & in){
   int i=0;
   for(std::vector<std::string>::const_iterator it=_header.begin();it!=_header.end();++it){
      if(in==*it){
         return i;
      }
		i++;
   }
   return -1;
}

void rowWHeader::addColumn(const std::string & value){


}

void rowWHeader::setColumnValue(const std::string & columnName, const std::string & columnValue){

  int num=getColumnNumber(columnName); 
  row::setColumnValue(num,columnValue);
}

std::string rowWHeader::getColumnValue(const std::string & columnName){
  int num=getColumnNumber(columnName); 
   return getValue(num);
}

row rowWHeader::getRow(){
    row tmpRow(print(),_delim);
   return tmpRow;

}
