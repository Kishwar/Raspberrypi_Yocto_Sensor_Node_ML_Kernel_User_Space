# Output binary name
TARGET = application

# Source and include directories
SRC_DIRS := ./main/src
INC_DIRS := ./main/inc  ./core

# Find all .cpp files recursively in SRC_DIRS
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Generate -I include flags for each include directory
INCLUDES := $(foreach dir,$(INC_DIRS),-I$(dir))

# Compiler and flags (use Yocto's environment if set)
CXX ?= $(CROSS_COMPILE)g++
CXXFLAGS := -Wall -Os -fdata-sections -ffunction-sections -Wl,--gc-sections -std=c++17 $(INCLUDES)
LDFLAGS := -static-libstdc++ -static-libgcc -pthread

.PHONY: all clean info

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)
	arm-poky-linux-gnueabi-strip $(TARGET)
clean:
	rm -f $(TARGET)

info:
	@echo "Building: $(TARGET)"
	@echo "Sources: $(SRC)"
	@echo "Includes: $(INCLUDES)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
