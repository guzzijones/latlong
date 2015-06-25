#ifndef ADDRESSBASE_H
#define ADDRESSBASE_H
class addressBase{
   private:
   std::string _fullAddress;
   std::string _city;
   std::string _zipcode;
   std::string _state;

   protected: 

   public:
   addressBase(std::string addy,std::string city,std::string zip, std::string state);
   virtual ~addressBase();

};
#endif
