#include "fileTable.h"

//here obviously we are writing a new file; as a header row has been passed
fileTable::fileTable(const std::string & filename,const row & header):_fileName(filename),tableAbs(header.getDelim()){//output
//create outFileTable with this constructor ; inherits fileTable
      _columnHeaders=header;
      std::ofstream tmpOutFile;

      tmpOutFile.open(filename, std::ios::out );
      tmpOutFile << _columnHeaders.print();
     if(!tmpOutFile.is_open())
        {
         throw std::runtime_error("Could not open file for writing.\n");
        }
      tmpOutFile.close();

}

//reading
fileTable::fileTable(const std::string & filename,const char delim):_fileName(filename),tableAbs(delim){
//this is an input file
   std::cout << "filname: " << _fileName << std::endl;
        std::ifstream tmpF; 

         tmpF.open(_fileName);
        if(!tmpF.good())
        {
         throw std::runtime_error("No such file exists.\n");
        }
       readHeader();
       tmpF.close();

}

void fileTable::addRow(row & in,tableAbs::FrontBack where){
  std::unique_ptr<std::fstream> tmp( new std::fstream(_fileName,std::fstream::app|std::fstream::out)); 
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
   *tmp << in.printlnToFile();
  }
}

std::string fileTable::printRow(int i){
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
   std::string tmp;
   int count=1;
   while(std::getline((*tmpF),tmp) && count <=i){
      if(count==i )
         return tmp;
      i++;
   };
   return tmp;
}

std::string fileTable::printHeader(){
   return _columnHeaders.print();   
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

//private
void fileTable::readHeader(){//file read
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
   std::string tmp;
   std::getline((*tmpF),tmp);
   row theader(tmp,_delim);
  _columnHeaders=theader; 

}

/*
template <class DT,typename PTYPE>
rowWHeader fileTable::getRowWHeader(double rowNumber,delegate<DT,PTYPE>*){
  std::unique_ptr<std::fstream> tmpF( new std::fstream(_fileName)); 
   std::string tmp;
   int i =0;
   while(std::getline((*tmpF),tmp)){
         if(i==rowNumber)
         {
            rowWHeader tmpRowWHeader(_columnHeaders,row(tmp,_delim));
            return tmpRowWHeader;
         }
         i++;
   }
   return rowWHeader();
}
*/
