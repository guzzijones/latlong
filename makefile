###########
#add new depend files below 
#add new ones here object files relating to .cpp filesF
DEPS=driver.o ./src/json/jsoncpp.o row.o config.o mapper.o fileTable.o curlwrapper.o mapAddress.o \
rowWHeader.o


EXE=driver

#######################
#DO NOT EDIT BELOW
#######################

###########
#variables
###########
CC=g++
#CPPFLAGS= -Wall -c -I./include/  -I./include/dataFile/ -I/usr/include/ -DCURL_STATICLIB
CPPFLAGS= -Wall -c -I./include/  -I./include/dataFile/ -I/usr/include/ 
CPPFLAGS+= -g -MD -MP -std=c++0x 
LFLAGS= -Wall  -lcurl 
#LFLAGS= -static -L/usr/lib/x86_64-linux-gnu/libcurl.a -Wl,-Bsymbolic-functions -Wl,-z,relro -lidn -lgcrypt -llber -lldap -lrt -lgssapi_krb5 -lz -lgnutls -lgcrypt -lrtmp
VPATH=src ./src/json

all: $(EXE)

debug: CC+= -DDEBUG -g 
debug: $(EXE)
###########
#linker
###########
$(EXE): $(DEPS)
	$(CC)  $(DEPS) $(LFLAGS) -o $(EXE).exe

##########
#implicit calls for all object file builds
#########

###########
#include dependency files 
###########
-include $(DEPS:%.o=%.d)

