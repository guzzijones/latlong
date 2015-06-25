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
CPPFLAGS= -Wall -c -I./include/  -I./include/dataFile/ -Llibs/lib
CPPFLAGS+= -g -MD -MP -std=c++0x
LFLAGS= -Wall   -lcurl
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

