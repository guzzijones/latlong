#include "tableAbs.h"

class table : public tableAbs{

   private:

   protected:
      std::vector<row> _rows;

   public:
   table(){};   
   table(const row & header, const std::vector<row> & rows,const char delim);
   virtual ~table(){}; 

   void addRow(row & in,tableAbs::FrontBack type=tableAbs::FRONT);
   std::string printRow(int i);
   std::string printHeader();
   void dropRowWithColumnValue(std::string column, std::string value);
   void setHeader();
   std::vector<int> getRowNum(const std::string & column,const std::string & value);
};
