#include "table.h"

table::table(const row & header, const std::vector<row> & rows,const char delim):tableAbs(header,delim){
   _rows=rows;
  _header=true; 
}

void table::setHeader(){


}
void table::addRow(row & in,FrontBack where){

  _rows.push_back(in);
  //if thie value should go first
  if(where ==tableAbs::FRONT){
      row tmpFront=_rows[0];
    _rows[0]=_rows[_rows.size()];
    _rows[_rows.size()]=tmpFront;
   }

};

void table::dropRowWithColumnValue(std::string column, std::string value){

   std::vector<int> rowNum=getRowNum(column,value); 
   for(std::vector<int>::iterator it=rowNum.begin();it!=rowNum.end();++it){
      _rows.erase(_rows.begin()+(*it));
    }
};

std::vector<int> table::getRowNum(const std::string & column,const std::string & value){
    int columnNum = _columnHeaders.getColumnNumber(column);
    std::vector<int> rowsFound;
   if(columnNum!=-1){ 
    int index=0;
    for(std::vector<row>::iterator it=_rows.begin();it!=_rows.end();++it){
            if(it->getValue(columnNum)==value)
            {
               rowsFound.push_back(index);
            }
            index++;
    }
   }
   return rowsFound;
}

std::string table::printRow(int i){
   int row=i-1;
   std::string tmp;
   if(i > _rows.size() || i < 1){

   }
   else{

   tmp=_rows[row].print();
   }
   return tmp;
}

std::string table::printHeader(){
   std::string tmp;
   tmp=_columnHeaders.print();
   return tmp;

}
 
