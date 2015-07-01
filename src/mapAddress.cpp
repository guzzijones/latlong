#include "mapAddress.h"
std::string mapAddress::baseURL="http://nominatim.openstreetmap.org/search?";

mapAddress::mapAddress(const std::string & Address,
               const std::string & city,
               const std::string & state,const std::string & zip){
               _address=Address;
               _city=city;
               _state=state;
               _zip=zip;
               std::cout << "in map address constructor" << std::endl;
//  _address.replace(_address.find(" "), 1, "+");
  std::replace(_address.begin(),_address.end(),' ','+');
  std::replace(_city.begin(),_city.end(),' ','+');
  std::replace(_state.begin(),_state.end(),' ','+');
  std::replace(_zip.begin(),_zip.end(),' ','+');
  setTotalURL();
}
void mapAddress::setTotalURL(){

   _totalURL=baseURL+"format=json&address&q=";
   if(_address!="")
      _totalURL+=_address;
   if(_city!="")
      _totalURL+=","+_city;
   if(_state!="")
      _totalURL+=","+_state;
   if(_zip!="")
      _totalURL+=","+_zip.substr(0,5);

   _totalURL+="&addressdetails=1&limit=1";
}
void mapAddress::setAddress(const std::string & in){
   _address=in;
   setTotalURL();
}

void mapAddress::setCity(const std::string & in){
   _city=in;
   setTotalURL();
}

void mapAddress::setState(const std::string & in){
   _state=in;
   setTotalURL();
}
void mapAddress::setZip(const std::string & in){
   _zip=in;
   setTotalURL();
}

int mapAddress::writer(char * data,size_t size,size_t nmemb, std::string * buffer){
   int result =0;
   if(buffer!=NULL){
      *buffer="";
      buffer->append(data,size * nmemb);
   }
   result = size * nmemb;
   return result;
}
int mapAddress::nominate(){

	std::cout << "nominate funct" << std::endl;
   struct curl_slist * list = NULL;
   list=curl_slist_append(list,"From: ajonen@mailcan.com");
   easy.setOption(CURLOPT_HTTPHEADER,list);
   easy.setOption(CURLOPT_URL,_totalURL.c_str());
//   easy.setOption(CURLOPT_HEADER,1);
   easy.setOption(CURLOPT_FOLLOWLOCATION,1);
   easy.setOption(CURLOPT_USERAGENT, "ajonen@mailcan.com");
   easy.setOption(CURLOPT_WRITEFUNCTION,writer);
   easy.setOption(CURLOPT_WRITEDATA,&_result);
   easy.setOption(CURLOPT_REFERER,"http://dimins.com");

	std::cout << "ready " << std::endl;
   easy.perform();
	std::cout << "done" << std::endl;
   if(easy.isOK()==0){
      Json::Reader reader;
      if(reader.parse(_result,_resultJson)){
//         std::cout << "lat: " << _resultJson[0]["lat"] << std::endl;
         setLatFromJson();
         setLongFromJson();
         return easy.isOK();
      }
   }
   sleep(1);
   return easy.isOK();

}
std::string mapAddress::getLat(){
   return _lat;
}
std::string mapAddress::getLong(){
   return _long;
}
std::string mapAddress::getNomError(){
//   return easy.getErrorMessage();
   return "test";
}

void mapAddress::setLatFromJson(){
   std::stringstream tmpLat;
   tmpLat << _resultJson[0]["lat"];
  _lat=nstring::trim(tmpLat.str(),"\""); 
}
void mapAddress::setLongFromJson(){
   std::stringstream tmpLong;
   tmpLong << _resultJson[0]["lon"];
  _long=nstring::trim(tmpLong.str(),"\""); 

}

