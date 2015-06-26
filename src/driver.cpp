#include <string>
#include <iostream>
#include "json/json.h"
#include "tableAbs.h"
#include <vector>
#include "config.h"
#include "mapper.h"
#include "mapAddress.h"
#include "curlwrapper.h"
void output(const Json::Value & value)
{
    // querying the json object is very simple
    std::cout << value["hello"];
    std::cout << value["number"];
    std::cout << value["array"][0] << value["array"][1];
    std::cout << value["object"]["hello"];
}
int writer(char * data,size_t size,size_t nmemb, std::string * buffer){
   int result =0;
   if(buffer!=NULL)
      buffer->append(data,size * nmemb);
   result = size * nmemb;
   return result;
}
int main(int argc, char * argv[]){

Json::Value array;
array.append("hello");
array.append("world");

Json::Value fromScratch;
fromScratch["hello"] = "world";
fromScratch["number"] = 2;
fromScratch["array"] = array;
fromScratch["object"]["hello"] = "world";

std::cout << "write json to output stream" <<std::endl; 
output(fromScratch);
std::cout << std::endl;

// write in a nice readible way
Json::StyledWriter styledWriter;
std::cout << styledWriter.write(fromScratch);

// ---- parse from string ----

// write in a compact way
Json::FastWriter fastWriter;
std::string jsonMessage = fastWriter.write(fromScratch);

Json::Value parsedFromString;
Json::Reader reader;
bool parsingSuccessful = reader.parse(jsonMessage, parsedFromString);
std::cout << "fastwriter string: " << jsonMessage << std::endl;
if (parsingSuccessful)
{
    std::cout << styledWriter.write(parsedFromString) << std::endl;
}
//std::string tmpString= "hello\ta\tcolumn\t\t\t";
//row tmp(tmpString,'\t');
//std::cout << "hello" << std::endl;
//std::cout << "Start of real program" << std::endl;
/*
std::string header = "Column1\tColumn2\tColumn3\n";
std::string row1 = "data11\tdata21\tdata31\n";
std::string row2 = "data12\tdata22\tdata32\n";

row headerRow(header,'\t');
std::cout << "header: " << headerRow.print() << std::endl;
std::vector<row> testStrV;
testStrV.push_back(row(row1,'\t'));
testStrV.push_back(row(row2,'\t'));
*/
/*table aTable(headerRow,testStrV);
std::cout << "table: " << std::endl;
std::cout << aTable.printHeader();
std::cout << aTable.printRow(1);
std::cout << aTable.printRow(2);
*/
//read in contents of config file into stream;
//config class

//std::string jsonConfig; 
//parsingSuccessful = reader.parse(,jsonConfig);
std::string confFile="config.json";

//config tmp(confFile);
//std::cout << "long from config: " << tmp.getLong() << std::endl;
config aConfig(confFile);   
/*
fileTable tmp("inFile.txt",'\t');
std::cout << "try with config" << std::endl;

fileTable tmp2("inFile.txt",aConfig.getDelim());
std::cout << "mapper: " << std::endl;
*/
mapper myMap(confFile);
myMap.mappAddresses();
//std::string buffer;

//std::string url="http://nominatim.openstreetmap.org/search?";
//url=url+="format=json&address&q=682+nw+44th+terr,+deerfield beach,+fl&addressdetails=1&limit=1";
//CURL * mCurl;
//char * outputurl=curl_easy_escape(mCurl,(char*)url.c_str(),url.length());
//std::cout << "outputURL: " << outputurl << std::endl;
//std::cout << "retrieve lat long" << std::endl;
//curl_free(outputurl);
/*
curlwrapper::easy easy;
easy.setOption(CURLOPT_URL,url.c_str());
easy.setOption(CURLOPT_HEADER,0);
easy.setOption(CURLOPT_FOLLOWLOCATION,1);
easy.setOption(CURLOPT_WRITEFUNCTION,writer);
easy.setOption(CURLOPT_WRITEDATA,&buffer);
easy.perform();

std::cout << buffer << std::endl;
*/
/*
std::string address="682 nw 44th terr";
std::string city="deerfield beach";
std::string state="FL";
std::string zip="33442";

mapAddress mapMyHouse(address,city,state,zip);
bool result=mapMyHouse.nominate();
if(result==0){
   std::cout << "Lat: " << mapMyHouse.getLat() << std::endl;
   std::cout << "Long: " << mapMyHouse.getLong() << std::endl;
   std::cout << "nominate succeeded: " << result << std::endl;
   std::cout << "Nominate result: " << mapMyHouse.getResult() << std::endl;
   }
else{
   std::cout << "nominate failed: " << mapMyHouse.getNomError() << std::endl;
   std::cout << "Nominate result: " << mapMyHouse.getResult() << std::endl;
   std::cout << "message: " << mapMyHouse.getNomError() << std::endl;
   }
   */
   return 0;

}
