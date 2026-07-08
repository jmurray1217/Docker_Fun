# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
LDFLAGS = 

# For static build (uncomment when using Alpine)
# LDFLAGS += -static

# Project settings
TARGET = myapp
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean