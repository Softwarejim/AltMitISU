.PHONY: all

# Quick and dirty (does not handle changes in h-file)
SRCS=parkalot2000_ver5.cpp EntryGuardThread.cpp ExitGuardThread.cpp CarThread.cpp outputMessages.cpp
NAME=parkalot2000_ver5
BASEPATH=OSApiStudent
THREADS=-lpthread
AR=-ar
CXXFLAGS= -I.

ARCH?=host
#for at builde til target skrives der i terminalen: make ARCH=target
THREADS?=yes
#for at builde en executable, der benytter threads, skrives der i terminalen: make ARCH=host/target THREADS=yes

ifeq (${ARCH},host)
#Er ARCH sat til noget, hvis ikke sættes den til 'host'
CXX=g++
AR=-ar
BUILD_DIR=build/host
BIN_DIR=bin/host
LIBPATH=$(BASEPATH)/lib/host/release
else
CXX=arm-rpizw-g++
AR=arm-poky-linux-gnueabi-ar
BUILD_DIR=build/target
BIN_DIR=bin/target
LIBPATH=$(BASEPATH)/lib/target/release
endif

ifeq (${THREADS},yes)
#Er THREADS sat til noget, hvis ikke sættes den til 'no'
CXX+= -lpthread
#compile exe that uses threads
endif

# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS=-O2 -Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc -I.

OBJS=$(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
#store .o files in BUILD_DIR
DEPS=$(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.d))
#store .d files in BUILD_DIR
EXE=$(addprefix $(BIN_DIR)/, $(NAME))
#store executable in BIN_DIR

all: $(EXE)

$(EXE): $(DEPS) $(OBJS) $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) -L$(LIBPATH) -lOSApi -lrt $(THREADS)

${BUILD_DIR}/%.o: %.cpp ${BUILD_DIR}
	@echo "Compiling: "$@
	$(CXX) -c $< $(CXXFLAGS) -o $@

${BUILD_DIR}:
	mkdir -p $@

${BIN_DIR}:
	mkdir -p $@

${BUILD_DIR}/%.d: %.cpp ${BUILD_DIR}
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@


clean: $(OBJS)
	rm -f $(EXE) $(OBJS) $(DEPS)