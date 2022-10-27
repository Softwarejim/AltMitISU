.PHONY: all

targets = "Options: -all -clean -help -format - tidy -lib"
SOURCES=test.cpp
NAME=test
CXXFLAGS= -I.
LIBSRC=

ARCH?=host
#for at builde til target skrives der i terminalen: make ARCH=target
THREADS?=yes
#for at builde en executable, der benytter threads, skrives der i terminalen: make ARCH=host/target THREADS=yes

ifeq (${ARCH},host)
#Er ARCH sat til noget, hvis ikke sættes den til 'host'
ifeq (${THREADS},yes)
#Er THREADS sat til noget, hvis ikke sættes den til 'no'
CXX=g++ -pthread
#compile exe that uses threads to host
else
CXX=g++
#compile exe to host
endif
BUILD_DIR=build/host
#fortaeller om stien der skal gennem i
BIN_DIR=bin/host
#fortaeller om stien der skal gennem i
endif

ifeq (${ARCH},target)
#Er ARCH sat til noget, hvis ikke sættes den til 'host'
ifeq (${THREADS},yes)
#Er THREADS sat til noget, hvis ikke sættes den til 'no'
CXX=arm-rpizw-g++ -pthread
#compile exe that uses threads to target
else
CXX=arm-rpizw-g++
#compile exe to target
endif
BUILD_DIR=build/target
#fortæller om stien der skal gennem i
BIN_DIR=bin/target
#fortæller om stien der skal gennem i
endif

OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
#store .o files in BUILD_DIR
DEPS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
#store .d files in BUILD_DIR
EXE=$(addprefix $(BIN_DIR)/, $(NAME))
#store executable in BIN_DIR
LIBS=$(LIBSRC:.o=.a)
#make lib files from object files
TIDY=$(SOURCES:.cpp=.tidy)
#make tidy files from cpp files
FORMAT=$(SOURCES:.cpp=.format)
#make format files from cpp files

all: $(EXE)
#alle targets

$(EXE): $(DEPS) $(OBJECTS) ${BIN_DIR} 
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) 

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

ifneq ($(filter-out clean format tidy,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS) $(DEPS) $(FORMAT) $(TIDY) $(LIBS)
.PHONY: help
help: 
	@echo $(targets)
	@echo $(OBJECTS)

#added in exercise 4.1
format: $(FORMAT)
%.format: %.cpp
	@echo "Formating file '$<'"...
	@clang-format -i $<
	@echo "" > $@

#added in exercise 4.2
tidy: $(TIDY)
%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@

#added in exercise 5.2
lib: $(LIBS)
%.a: %.o
	@echo "Making lib from files '$<'"...
	@ar rcs $(LIBS)
	@echo "" > $@
