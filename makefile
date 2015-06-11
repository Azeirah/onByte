CC=g++
# CC_FLAGS=-g -Wall -Wextra -std=c++11 -O3 -I/usr/include/freetype2
CC_FLAGS=-g -Wall -Wextra -std=c++11 -I/usr/include/freetype2


LDFLAGS=-g

#FILE NAMES
EXEC = OnByte

SOURCES = $(wildcard source/*.cpp source/server/*.cpp source/shapes/*.cpp source/demoMode/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


# alle benodigde libraries
LIBS=-lGLESv2 -lEGL -lm -lX11 -lfreetype

all:   $(OBJECTS)
	$(CC) $(CC_FLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(EXEC)

#to obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@


# # Schoonmaak mevrouw
clean:
	rm $(OBJECTS) $(EXEC)
