#ifndef MAPADDRESS_H
#define MAPADDRESS_H
#include "./json/json.h"
#include "curlwrapper.h"
#include <string>
#include "nstring.h"
#include <sstream>

class mapAddress{

public:

   static int writer(char * data,size_t size,size_t nmemb, std::string * buffer);
  curlwrapper::easy easy;
  mapAddress(const std::string & Address,
               const std::string & city,
               const std::string & state,const std::string & zip,const std::string & url);

   void setAddress(const std::string & in);
   void setCity(const std::string & in);
   void setState(const std::string & in);
   void setZip(const std::string & in);

   std::string getLat();
   std::string getLong();
   int nominate();
   std::string getNomError();

   std::string getResult()const{ return _result;};

   std::string getTotalURL()const{return _totalURL;};

protected:

private:
   std::string _baseURL;
   std::string _result;
   std::string _address;
   std::string _city;
   std::string _state;
   std::string _zip;

   std::string _email;
   std::string _website;

   std::string _lat;
   std::string _long;
   std::string _totalURL; 

   Json::Value _resultJson;

   std::string fix(std::string in);
   void replaceSpecialChars();
   void setTotalURL();
   void setLatFromJson();
   void setLongFromJson();
};

#endif
