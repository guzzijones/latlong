#ifndef FILETABLE_H
#define FILETABLE_H

#include "tableAbs.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <cstdio>
#include "delegate.h"


class fileTable : public tableAbs{

   private:
  protected:
   std::string _fileName;
   int numRows;
      int countRows(); //count rows on initial load
      int countColumns(); //count columns on initial load
      void readHeader(); //set header for an input file
 
   public:
   enum INOUT{
      IN,
      OUT
   };

   std::string getFileName()const{return _fileName;};
   fileTable(){};   
   fileTable(const std::string & filename,const char delim);//input an already existing file
   fileTable(const std::string & filename,const row & header);//output  to a new file, wipe file if exists
   virtual ~fileTable(){}; 

   std::string printRow(int i);
   std::string printHeader();
   void addRow(row & in,tableAbs::FrontBack where=tableAbs::BACK);

   double getNumRows()const{return numRows;};//get number of rows for looping
   double getNumColumns()const{return _columnHeaders.getNumColumns();};//get num columns for looping

   template <class DT,class PT> 
   static bool doStuffAndOutputToFile(fileTable & inFileTable,delegate<DT,PT > & function,fileTable output){
      std::unique_ptr<std::fstream> tmpF( new std::fstream(inFileTable.getFileName())); 
      std::cout << "filename: " << inFileTable.getFileName() << std::endl;
      std::string tmp;
      int i =0;
      bool result=false;
      bool resultFinal=true;
      //do not use getrow as it loops through the whole file to get to the row needed
      //first get header
      std::getline((*tmpF),tmp);
      std::cout << "header: " << tmp << std::endl;
      //now get rows
      while(std::getline((*tmpF),tmp)){
            std::cout << "row: " << tmp << std::endl;
           
               rowWHeader tmpRowWHeader(inFileTable.getHeader(),row(tmp,inFileTable.getDelim()));
               std::cout << "tmprowWheader:***" << tmpRowWHeader.print() <<"****\n"<< std::endl;
               result=function.run(tmpRowWHeader);
               if(result==false){
                  resultFinal=false;
               }
               else{
                  
                  std::cout << "success : " << result << std::endl;
                  row tmpRow = tmpRowWHeader.getRow();
                  std::cout << "tmpRow: " << tmpRow.print() << std::endl;
                  output.addRow(tmpRow);
               }
               i++;
      }
      return resultFinal; 
   }

   row getHeader()const{return _columnHeaders;};//get the header to allow the user to select a column via the column name and pass that to getColumn                           

   std::vector<int> getRowNum(const std::string & column,const std::string & value);
};
#endif
