# Flags
DEBUG = -g
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lfltk -lfltk_images

# Sources & Build
BUILD_DIR = build
DIST_DIR = dist
TARGET = $(DIST_DIR)/game
SOURCES = $(notdir $(wildcard *.cpp) $(wildcard **/*.cpp) $(wildcard **/**/*.cpp))
OBJECTS = $(addprefix $(BUILD_DIR)/, $(patsubst %.cpp, %.o, $(SOURCES)))
DEPS = $(wildcard *.hpp) $(wildcard **/*.hpp) $(wildcard **/**/*.hpp)

# Add (sub)directories to VPATH

vpath %.cpp ./model/levels
vpath %.cpp ./model
vpath %.cpp ./controller
vpath %.cpp ./view

# Rules
$(BUILD_DIR)/%.o: %.cpp $(DEPS)
	@echo "THIS IS A CPP FILE" $@ $^
	$(CXX) -c $(CXXFLAGS) -o $@ $(DEBUG) $<


.PHONY: setup
setup:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(DIST_DIR)

.PHONY: all
all: setup $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f -r $(BUILD_DIR) 2> /dev/null
	rm -f -r $(DIST_DIR) 2> /dev/null