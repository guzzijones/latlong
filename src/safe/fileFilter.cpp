#include "fileFilter.h"
#include <iostream>
using namespace std;
fileFilter::fileFilter(const std::string &filename){
   setFileHandle(filename);
}

std::unique_ptr<std::fstream> fileFilter::getFileHandle(){
   return std::move(m_file);
}

void fileFilter::setFileHandle(const std::string & filename){
   std::unique_ptr<std::fstream> tmp(new fstream(filename,ios::in));
   m_file=std::move(tmp);
   if (m_file->is_open())
   {
     //   (*m_file)>> m_contents;;
     std::string tmp;
    while ( getline ((*m_file),tmp) )
    {

        m_contents+=tmp+"\n";
    }

  }
//    std::cout <<"mcontents: " << m_contents << std::endl;
}

void fileFilter::saveFile(const std::string & in){
   std::unique_ptr<std::fstream> tmp(new fstream(in,ios::out));

   *tmp<<  m_contents;
}

