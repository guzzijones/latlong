#include "outFileTable.h"

outFileTable::outFileTable(const std::string & filename,const row & header):_fileName(filename),tableAbs(header.getDelim()){//output
//create outFileTable with this constructor ; inherits fileTable
      _columnHeaders=header;
      std::ofstream tmpOutFile;
      tmpOutFile.open(filename, std::ios::out | std::ios::app);
     if(!tmpOutFile.is_open())
        {
         throw std::runtime_error("Could not open file for writing.\n");
        }
      tmpOutFile.close();
 

}
