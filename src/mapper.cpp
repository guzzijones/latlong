#include "mapper.h"
mapper::mapper(const std::string & inConfigName){
   setConfig(inConfigName);
   std::string inputStr=_configuration.getInFile();
//   std::cout << "inputStr: " << inputStr << std::endl;
   std::string outputStr=_configuration.getOutFile();
 //  std::cout << "outputStr: " << outputStr << std::endl;
   char delim = _configuration.getDelim();
   
   setInput(inputStr,delim);
   //first row if file should be the column header
   row header=_input.getHeader();
   //set output
   setOutput(outputStr,header);
   bool configColumnsOK=validateColumns();
   if(configColumnsOK==false)
      throw std::runtime_error("All columns from configuration not found in inputfile");
}
void mapper::setInput(const std::string & in,const char delim){
   fileTable tmp(in,delim);
   _input=tmp;
}
void mapper::setOutput(const std::string & in,const row & header){
 std::cout << "setting output" << std::endl;
 fileTable tmp(in,header);  
 _output=tmp;

}
void mapper::setConfig(const std::string & in){
   config tmp(in);
   _configuration=tmp;
}
void mapper::mappAddresses(){
      //call dostuff with adlatlong function
      delegate<mapper,rowWHeader> aDelegate;
      std::cout << "inside mapaddresses" << std::endl;
      aDelegate.connectToDelegate(this,&mapper::addLatLong);
      fileTable::doStuffAndOutputToFile(_input,aDelegate,_output);
      std::cout << "done w mappaddresses" << std::endl;
   
}
//this is the function that will be sent inside a delegate
bool mapper::addLatLong(rowWHeader & in){
      std::cout << "inside latlong" << std::endl;
      std::string longV = in.getColumnValue(_configuration.getLong());

      std::string city =  in.getColumnValue(_configuration.getCity());
      std::string state =  in.getColumnValue(_configuration.getState()) ;
      std::string zipCode= in.getColumnValue(_configuration.getZipCode()) ;
      std::string address=  in.getColumnValue(_configuration.getAddress()) ;
      std::string latv= in.getColumnValue(_configuration.getLat()) ;

   if(latv=="" || longV==""){
      std::cout << "mapaddress " << std::endl;
      std::cout << "address: " << address<<std::endl;
      std::cout << "city: " << city<<std::endl;
      std::cout << "state: " << state<<std::endl;
      std::cout << "zip: " << zipCode<<std::endl;
      
      mapAddress mapMyHouse(address,city,state,zipCode);
      std::cout << "TotalURL: " <<mapMyHouse.getTotalURL() << std::endl;
  		int result=mapMyHouse.nominate();
      if(result==0 && mapMyHouse.getLat()=="null"){//if full address fails try with just street and zip
         mapMyHouse.setCity("");
         mapMyHouse.setState("");
         result=mapMyHouse.nominate();
         std::cout << "Lat with address and Zip only: " << mapMyHouse.getLat();
         std::cout << "Result: " << result;
         std::cout << "TotalURL: " <<mapMyHouse.getTotalURL() << std::endl;
      }
      if(result==0 && mapMyHouse.getLat()=="null"){//if above fails then try with just zip
         mapMyHouse.setAddress("");
         mapMyHouse.setCity("");
         mapMyHouse.setState("");
         result=mapMyHouse.nominate();
         std::cout << "Zip only: " << mapMyHouse.getLat();
         std::cout << "Result: " << result;
         std::cout << "TotalURL: " <<mapMyHouse.getTotalURL() << std::endl;
      }
   
      if(result==0&&mapMyHouse.getLat()!=""){//now set the values

         in.setColumnValue(_configuration.getLat(),mapMyHouse.getLat());
         in.setColumnValue(_configuration.getLong(),mapMyHouse.getLong());
			std::cout << "mapMyHouse.getLat(): " << mapMyHouse.getLat()<<std::endl;
			std::cout << "mapMyHouse.getLong(): " << mapMyHouse.getLong()<<std::endl;
         std::cout << "Nominate result: " << mapMyHouse.getResult() << std::endl;
         return true;
         }
      else{
         std::cout << "libcurl Error: " << curl_easy_strerror((CURLcode)result) << std::endl;
         std::cout << "nominate failed, LibCurl Error: " << mapMyHouse.getNomError()<< std::endl;
         return false;
         }
       
   }
   //never here
   return false;

}
bool mapper::validateColumns(){
   std::vector<std::string> configColumns=_configuration.getColumnNames();
   int numConfigColumns=configColumns.size();
   int countColumns=0;

   row header=_input.getHeader();
   std::vector<std::string> headerValues=header.getValues();

   for(std::vector<std::string>::const_iterator itC=configColumns.begin();itC!=configColumns.end();itC++){
      for(std::vector<std::string>::const_iterator itH=headerValues.begin();itH!=headerValues.end();itH++){
         if((*itC)==(*itH)){
            countColumns++;
         }
            
      }
   }
   if(countColumns==numConfigColumns){
      return true;
   }
   return false;
}
