#include "curlwrapper.h"
#include <iostream>

curlwrapper::easy::easy():mCurl(curl_easy_init()),mCode(CURLE_OK){

}
curlwrapper::easy::~easy(){

   curl_easy_cleanup(mCurl);
}

void curlwrapper::easy::init(){

}
void curlwrapper::easy::cleanup(){
   curl_easy_cleanup(mCurl);
}
void curlwrapper::easy::reset(){
   curl_easy_reset(mCurl);
   std::fill(mErrorBuffer,mErrorBuffer + CURL_ERROR_SIZE +1,0);
   errorBuffer(mErrorBuffer);
   mCode=CURLE_OK;
}

void curlwrapper::easy::errorBuffer(char* buffer){
   setOption(CURLOPT_ERRORBUFFER,(void*)buffer);

}
void curlwrapper::easy::perform(){
   mCode=curl_easy_perform(mCurl);
  // std::cout << "easy::isok: " << mCode << std::endl;
}

int curlwrapper::easy::isOK(){
  // std::cout << "easy::isok: " << mCode << std::endl;
   return mCode;
}

CURLcode curlwrapper::easy::getError()
{
   return mCode;
}
std::string curlwrapper::easy::getErrorMessage(){
   return std::string(mErrorBuffer);
}
