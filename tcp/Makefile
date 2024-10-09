# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -pthread

# Executable name
TARGET = app

# Source files
SRCS = server.cpp server/Server.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target to build the server executable
all: $(TARGET)

# Build the executable by linking object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files to .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets are not actual files
.PHONY: all clean
