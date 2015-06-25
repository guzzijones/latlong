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
   _totalURL=baseURL+"format=json&address&q="+_address+","+_city+","+state+","+zip+"&addressdetails=1&limit=1";
   std::cout << "totalurl: " << _totalURL << std::endl;
}

void mapAddress::setAddress(const std::string & in){
   _address=in;
}

void mapAddress::setCity(const std::string & in){
   _city=in;
}

void mapAddress::setState(const std::string & in){
   _state=in;
}
void mapAddress::setZip(const std::string & in){
   _zip=in;
}

int mapAddress::writer(char * data,size_t size,size_t nmemb, std::string * buffer){
   int result =0;
   if(buffer!=NULL)
      buffer->append(data,size * nmemb);
   result = size * nmemb;
   return result;
}
int mapAddress::nominate(){

	std::cout << "nominate funct" << std::endl;
   easy.setOption(CURLOPT_URL,_totalURL.c_str());
   easy.setOption(CURLOPT_HEADER,0);
   easy.setOption(CURLOPT_FOLLOWLOCATION,1);
   easy.setOption(CURLOPT_WRITEFUNCTION,writer);
   easy.setOption(CURLOPT_WRITEDATA,&_result);

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
