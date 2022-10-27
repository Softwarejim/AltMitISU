.PHONY: all

targets = "Option: -all -clean -help -main -part1 -part2"
SOURCES=opg2_semaphores.cpp
NAME=opg2_semaphores
CXXFLAGS= -I.
LIBSCR=

ARCH?=host
THREADS=yes
#Er ARCH sat til noget, hvis ikke sættes den til host
#for at builde en executable, der benytter threads, skrives der i terminalen: make ARCH=host/target THREADS=yes
ifeq (${ARCH},host)
ifeq (${THREADS},yes)
CXX=g++ -pthread
else
CXX=g++
#compiler
endif
BUILD_DIR=build/host
#fortaeller om stien der skal gennem i
BIN_DIR=bin/host
#fortaeller om stien der skal gennem i
endif

ifeq (${ARCH},target)
ifeq (${THREADS},yes)
#for at builde til target skrives der i terminalen make ARCH=target
CXX=arm-rpizw-g++ -pthread
else
CXX=arm-rpizw-g++
#compiler
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

all: ${BUILD_DIR} ${BIN_DIR} $(EXE)
#alle targets

$(EXE): $(DEPS) $(OBJECTS) 
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) 

${BUILD_DIR}/%.o: %.cpp 
	echo "Comping: "$@
	$(CXX) -c $< $(CXXFLAGS) -o $@

${BUILD_DIR}:
	mkdir -p $@

${BIN_DIR}:
	mkdir -p $@

${BUILD_DIR}/%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS) $(DEPS)
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
