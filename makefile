CC=g++
# CC_FLAGS=-g -Wall -Wextra -std=c++11 -O3 -I/usr/include/freetype2
CC_FLAGS=-g -O3 -Wall -Wextra -std=c++11 -I/usr/include/freetype2


LDFLAGS=-g

#FILE NAMES
EXEC = OnByte

SOURCES = $(wildcard source/*.cpp source/server/*.cpp source/shapes/*.cpp source/demoMode/*.cpp source/handbal/*.cpp source/hockey/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


# alle benodigde libraries
LIBS=-lGLESv2 -lEGL -lm -lX11 -lfreetype -lftgl

all: $(OBJECTS)
	$(CC) $(CC_FLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(EXEC)

#to obtain object files
%.o: %.cpp
	$(CC) $(CC_FLAGS) -c $< -o $@

# # Schoonmaak mevrouw
clean:
	rm $(OBJECTS) $(EXEC)
