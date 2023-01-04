CXX := g++

DATA_DIR := Data
ALGORITHMS_DIR := Algorithms
RESULTS_DIR := Results
EXPERIMENTS_DIR := Experiments

INCLUDE := -I./$(DATA_DIR)/include -I./$(ALGORITHMS_DIR)/include -I./$(RESULTS_DIR)/include -I./$(EXPERIMENTS_DIR)/include
CXXFLAGS := -std=c++14 -Wall $(INCLUDE)

SOURCE_FILES := $(shell find $(DATA_DIR) $(ALGORITHMS_DIR) -name "*.cpp")
OBJECT_FILES := $(patsubst %.cpp, %.o, $(SOURCE_FILES))

PROJECT_NAMES := $(shell find $(EXPERIMENTS_DIR) -name "*.cpp")
PROJECT_NAMES := $(patsubst %.cpp, %, $(PROJECT_NAMES))

define compile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $1 $2 $1.cpp $(LDLIBS) ;
endef

all_with_objects: clean $(PROJECT_NAMES)

all: all_with_objects
	rm -f $(OBJECT_FILES)

$(PROJECT_NAMES): $(OBJECT_FILES)
	$(foreach project_name, $(PROJECT_NAMES), $(call compile, $(project_name), $(OBJECT_FILES)))

depend: .depend

.depend: $(SOURCE_FILES)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJECT_FILES)

dist-clean: clean
	rm -f *~ .depend

.SILENT:

.PHONY: all all_with_objects depend clean dist-clean

include .depend