#include "config.h"
void config::checkJson(){
   //check all the json values
   if(!_config["address"]){
      throw std::runtime_error("Missing adddress");
   }
   if(!_config["outFile"]){
      throw std::runtime_error("Missing outFile");
   }
   if(!_config["inFile"]){
      throw std::runtime_error("Missing inFile");
   }
   if(!_config["city"]){
      throw std::runtime_error("Missing city");
   }
   if(!_config["state"]){
      throw std::runtime_error("state");
   }
   if(!_config["zip"]){
      throw std::runtime_error("zip");
   }
   if(!_config["long"]){
      throw std::runtime_error("long");
   }
   if(!_config["lat"]){
      throw std::runtime_error("lat");
   }
 
   if(!_config["delim"]){
      throw std::runtime_error("delim");
   }
  std::stringstream delim;
  delim << _config["delim"];
  std::string delimS=delim.str();
  if(delimS.length() !=1)
      throw std::runtime_error("delim must be one char");
}
config::config(const std::string & filename){
   std::ifstream inFile(filename);
   if(inFile.is_open()==false){
      throw std::runtime_error("File does not exist or is not readable\n");
   }
   std::stringstream buffer;
   buffer << inFile.rdbuf();
   std::string total = buffer.str();
   inFile.close();
   Json::Reader reader;
   bool parsingSuccessful = reader.parse(total, _config);
   if (!parsingSuccessful)
   {
      throw std::runtime_error("could not parse config file");
   }
    
//   std::stringstream city;
//  city << _config["city"];
//  std::cout << "city: " << city.str() << std::endl;
//  _config=parsedFromString;
//   checkJson(); 

}
char  config::getDelim()const{
   std::stringstream delim;
   delim << _config["delim"];
   
   std::string sDelim=nstring::trim(delim.str(),"\"");
   if(sDelim=="\\t")
      return '\t';
   if(sDelim==",")
      return ',';
   if(sDelim=="|")
      return '|';
   if(sDelim==";")
      return ';';
   return '\t';
}
std::string config::getInFile()const{
   std::stringstream infile;
   infile << _config["inFile"];
   std::string tmp=nstring::trim(infile.str(),"\"");
   return tmp;
}
std::string config::getOutFile()const{
   std::stringstream outFile;
   outFile << _config["outFile"];
   return nstring::trim(outFile.str(),"\"");
}
std::string config::getLong()const{
   std::stringstream longitude;
   longitude<< _config["long"];
   return nstring::trim(longitude.str(),"\"");
}
std::string config::getLat()const{
   std::stringstream lat;
   lat<< _config["lat"];
   return nstring::trim(lat.str(),"\"");
}
std::string config::getCity()const{
   std::stringstream city;
   city << _config["city"];
   return nstring::trim(city.str(),"\"");
}
std::string config::getAddress()const{
//std::cout << "getting address " << std::endl;
   std::stringstream Address;
   Address << _config["address"];
   return nstring::trim(Address.str(),"\"");
}
std::string config::getState()const{
   std::stringstream State;
   State << _config["state"];
   return nstring::trim(State.str(),"\"");
}
std::string config::getZipCode()const{
   std::stringstream zip;
   zip << _config["zip"];
   return nstring::trim(zip.str(),"\"");
}

void config::setZipCode(const std::string &in){
      _config["zip"]=in;
}
void config::setState(const std::string &in){
      _config["state"]=in;
}
void config::setAddress(const std::string &in){
      _config["address"]=in;
}
void config::setCity(const std::string &in){
      _config["city"]=in;
}
void config::setInFile(const std::string & in){
      _config["inFile"]=in;
}
void config::setOutFile(const std::string & in){
   _config["outFile"]=in;
}
void config::setDelim(const std::string & in){
   _config["delim"]=in;
}
void config::setLong(const std::string & in){
   _config["long"]=in;
}
void config::setLat(const std::string & in){
   _config["lat"]=in;
}
std::vector<std::string> config::getColumnNames()const{
   std::vector<std::string> tmp;
   tmp.push_back(getAddress());
   tmp.push_back(getCity());
   tmp.push_back(getZipCode());
   tmp.push_back(getState());
   tmp.push_back(getLat());
   tmp.push_back(getLong());
   return tmp;
}
