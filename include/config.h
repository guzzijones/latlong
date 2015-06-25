#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "json/json.h"
#include <stdexcept>
#include <vector>
#include "nstring.h"
class config{
   private:
      Json::Value _config;
      void checkJson();
   protected:

   public:
     config(const std::string & filename);
     config(){};

     std::string getCity()const;
      std::string getAddress()const;
      std::string getState()const;
      std::string getZipCode()const;
      std::string getInFile()const;
      std::string getOutFile()const;
      std::string getLat()const;
      std::string getLong()const;
      char getDelim()const;

      void setZipCode(const std::string &);
      void setLat(const std::string &);
      void setLong(const std::string &);
      void setState(const std::string &);
      void setAddress(const std::string &);
      void setCity(const std::string &);
      void setInFile(const std::string & in);
      void setOutFile(const std::string & in);
      void setDelim(const std::string & in);

      std::vector<std::string> getColumnNames()const;//used to check if each column is set
};

#endif
