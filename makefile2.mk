CC=g++

SOURCES=source/*.cpp source/server/*.cpp source/shapes/*.cpp source/demoMode/*.cpp

all: $(SOURCES)
g++ -O $(SOURCES)
