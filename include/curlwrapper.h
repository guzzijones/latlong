#ifndef CURLWRAPPER_H
#define CURLWRAPPER_H
#include <memory>
#include <string>
#include "curl/curl.h"


namespace curlwrapper{

   class easy
   {
      public:
      easy();
      ~easy();

      void init();
      void cleanup();
      void reset();
      void perform();
      int isOK();
      CURLcode getError();
      std::string getErrorMessage();

      template <typename T, typename V>
      void setOption(T option , V param){
         curl_easy_setopt(mCurl,option,param);
      }

      protected:

      private:

     CURL * mCurl;
      char mErrorBuffer[CURL_ERROR_SIZE+1];
      CURLcode mCode;
      void errorBuffer(char* buffer);
   };
}
#endif
