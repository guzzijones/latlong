# latlong
Geocode the latitude and longitude for a given address, city, state, and zip. This program is written in c++.

#os 
linux

#code
c++ 

#dependencies
libcurl - available as an aptitude repository for ubuntu

#installation
source code: https://github.com/guzzijones/latlong.git

build instructions:
1. make - will build driver.exe

#usage:
1. edit config.json to contain correct variable values for your input file.  
each value on the right must be enclosed in quotes.  
The final value should NOT have a comma after it.

config.json value definitons:
   1. "inFile" : "[input file name]",
   2. "delim" : "[delimiter]",
   3. "outFile" : "[output file name]",
   4. "address" : "[address column name from input file]",
   5. "city" : "[city column name from input file]",
   6. "state" : "[state column name from input file]",
   7. "zip" : "[zipcode column name from input file]",
   8. "long" : "[longitude column name from input file]",
   9. "lat" : "[latitude column name from input file]",
   10. "url" : "[URL of the nominatim server]"

2. run driver.exe


#info
This program uses nominatim to geocode an address and return the latitude and longitude.  It is written in c++ with a dependency of libcurl.
It is important to not overload the server so you should
not map every address every day if possible.  You should save lat and long for addresses already mapped.  
Currently the program will not map an address if the lat column is already filled in.  At this time there is 
no column to define how old a mapping was and remap that address, but it could be added in a future version.
Usage of nominatim requires that you only map one address at a time so as not to overload the server.  
This program follows that guidline.


#useful links:

1.  http://wiki.openstreetmap.org/wiki/Nominatim
2.  http://curl.haxx.se/libcurl/c/libcurl-tutorial.html


