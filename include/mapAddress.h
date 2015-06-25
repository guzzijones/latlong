#ifndef MAPADDRESS_H
#define MAPADDRESS_H
#include "./json/json.h"
#include "curlwrapper.h"
#include <string>
#include "nstring.h"
#include <sstream>

class mapAddress{

public:
   static std::string baseURL;

   static int writer(char * data,size_t size,size_t nmemb, std::string * buffer);
  curlwrapper::easy easy;
  mapAddress(const std::string & Address,
               const std::string & city,
               const std::string & state,const std::string & zip);

   void setAddress(const std::string & in);
   void setCity(const std::string & in);
   void setState(const std::string & in);
   void setZip(const std::string & in);

   std::string getLat();
   std::string getLong();
   int nominate();
   std::string getNomError();

   std::string getResult()const{ return _result;};


protected:

private:

   std::string _result;
   std::string _address;
   std::string _city;
   std::string _state;
   std::string _zip;

   std::string _lat;
   std::string _long;
   std::string _totalURL; 

   Json::Value _resultJson;
   void replaceSpecialChars();

   void setLatFromJson();
   void setLongFromJson();
};

#endif
