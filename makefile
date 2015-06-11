# compiler
CC=g++
# compiler options
# -g is debugbaar
# -c geen idee
# wall en wextra zijn extra warnings
# dan nog c++14 standaard
# en optimizer niveau 3
# CFLAGS=-std=c++11 -I/usr/include/freetype2
CFLAGS=-g -Wall -Wextra -std=c++11 -O3 -I/usr/include/freetype2
# Linker flags en zoekpaden (folders waar je moet zoeken naar bestanden)
LDFLAGS=-g
# moet aangepast worden
SOURCES=source/*.cpp source/server/*.cpp source/shapes/*.cpp source/demoMode/*.cpp
# Namen van object bestanden denk ik
# voor alle sources .cpp, zijn er gelijknamige bestanden alleen dan met .o
# een soort van map *.cpp -> *.o I guess
OBJECTS=$(SOURCES:source/.cpp=.o)
# naam van de resulterende executable
EXECUTABLE=onByte

# alle benodigde libraries
LIBS=-lGLESv2 -lEGL -lm -lX11 -lfreetype

# bevestigt dat alle sources en de executable bestaan
all: $(SOURCES) $(EXECUTABLE)

# Bouwt een executable van alle objecten
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

# Bouwt een object file van alle sources
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# # Schoonmaak mevrouw
# clean:
# 	rm *o hello
