LIBS :=
CFLAGS := -Wall -Wconversion -std=c++14
LDFLAGS :=

CFLAGS += -g --coverage
LDFLAGS += -g --coverage

INC_DIRS := include/slim source
OBJ_DIR := obj/lib
TEST_OBJ_DIR := obj/tests
BIN_DIR := bin

SOURCES := $(shell find source/ -name "*.cpp")
TEST_SOURCES := $(shell find tests/ -name "*.cpp")

OBJECTS := $(patsubst %, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_OBJECTS := $(patsubst %, $(TEST_OBJ_DIR)/%.o, $(TEST_SOURCES))

CLEAN_FILES := $(OBJ_DIR) $(TEST_OBJ_DIR) $(BIN_DIR)
DEPS := $(OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

all: build test
clean:
	rm -rf $(CLEAN_FILES) coverage

build: bin/libslim.a

bin/libslim.a: $(OBJECTS)
	@mkdir -p $(@D)
	ar rcs $@ $(filter %.o,$^)

$(OBJ_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	g++ $(CFLAGS) $(addprefix -I, $(INC_DIRS)) -c  -MMD -MP $< -o $@

bin/test: bin/libslim.a $(TEST_OBJECTS)
	@mkdir -p $(@D)
	g++ $(LDFLAGS) $(filter %.o,$^) -Lbin -lslim  $(addprefix -l, $(LIBS)) -o $@
$(TEST_OBJ_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	g++ $(CFLAGS) $(addprefix -I, $(INC_DIRS)) -c  -MMD -MP $< -o $@

test: bin/test
	@mkdir -p coverage
	rm -f coverage/all.info coverage/coverage.info
	rm -f $(shell find $(OBJ_DIR)/ -name "*.gcda")
	bin/test
	lcov --capture --directory obj --base-directory . --output-file coverage/all.info -q
	lcov --extract coverage/all.info $(shell pwd)/include/\* $(shell pwd)/source/\* --output-file coverage/coverage.info -q
	genhtml coverage/coverage.info --output-directory coverage/

-include $(DEPS)

# CMake configuration
CMAKE_BUILD_DIR := cmake_build

cmake_configure:
	@mkdir -p $(CMAKE_BUILD_DIR)
	cd $(CMAKE_BUILD_DIR) && cmake ..

cmake_build:
	cd $(CMAKE_BUILD_DIR) && cmake --build .

cmake_clean:
	rm -rf $(CMAKE_BUILD_DIR)

cmake_test:
	cd $(CMAKE_BUILD_DIR) && ctest
