#include "fileTable.h"



fileTable::fileTable(const std::string & filename,const char delim,bool header):_fileName(filename),tableAbs(delim){
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
  if(tmpF->is_open())
  {
  }
  else
  {
   throw std::runtime_error("No such file exists.\n");
  }
  _header=header;
   if(_header=true){
      setHeader();
   }
}

void fileTable::addRow(row & in,tableAbs::FrontBack where){
  std::unique_ptr<std::fstream> tmp( new std::fstream(_fileName)); 
  if(where ==tableAbs::FRONT){
   /*1. create new file with .new extension
    * 2. output row to new file
    * 3. append original file to the new file
    * 4. delete original file
    * 5. move new file to old file name;
    */
   std::ofstream tmpOutFile;
   std::string tmpNewFileName=_fileName+".new_";
   tmpOutFile.open(tmpNewFileName, std::ios::out | std::ios::app);
   tmpOutFile << in.print();
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
   tmpOutFile << *tmpF;
   tmpOutFile.close();
   std::remove(_fileName.c_str());
   std::rename(tmpNewFileName.c_str(),_fileName.c_str());
  }
  else{
   *tmp << in.print();
  }

}
std::string fileTable::printRow(int i){
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
   std::string tmp;
   int count=1;
   while(std::getline((*tmpF),tmp) && count <=i){
      if(count=i )
         return tmp;
      i++;
   };
   return tmp;
}

std::string fileTable::printHeader(){
   _columnHeaders.print();   
}

void fileTable::dropRowWithColumnValue(const std::string &column, const std::string & value){

/* 1. create a new file
 * output new all data rows with this data to the new file.
 * 2. delete the old file
 * 3. move the new file to the old filename;
 */
}

std::vector<int> fileTable::getRowNum(const std::string & column,const std::string & value){
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
    int columnNum = _columnHeaders.getColumnNumber(column);
    std::vector<int> rowsFound;
   if(columnNum!=-1){ 
    int index=0;
   std::string tmp;
   while(std::getline((*tmpF),tmp)){
         row tmpRow(tmp,_delim);
         if(tmpRow.getValue(columnNum)==value){
               rowsFound.push_back(index);
         }
            index++;
    }
   }
   return rowsFound;

}

void fileTable::setHeader(){
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
   std::string tmp;
   std::getline((*tmpF),tmp);
   row theader(tmp,_delim);
  _columnHeaders=theader; 

}
