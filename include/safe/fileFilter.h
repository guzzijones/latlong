#ifndef FILEFILTER_H
#define FILEFILTER_H
#include <string>
#include <fstream>
#include <memory>
#include <iostream>
class fileFilter{
   private:

   protected:
   std::unique_ptr<std::fstream> m_file;
   std::string m_contents;


   public:
   fileFilter(){};
   ~fileFilter(){m_file->close();};
   fileFilter(const std::string &filename);

   std::unique_ptr<std::fstream> getFileHandle();
   void setFileHandle(const std::string & filename);

   void saveFile(const std::string & in);
   std::string getContents()const{return m_contents;};

};


#endif
