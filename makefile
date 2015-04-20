# compiler
CC=g++
# compiler options
CFLAGS=-c -Wall -Wextra -std=C++14 -O3
# Linker flags en zoekpaden (folders waar je moet zoeken naar bestanden)
LDFLAGS=
# moet aangepast worden
SOURCES= source/*.cpp
# Namen van object bestanden denk ik
# voor alle sources .cpp, zijn er gelijknamige bestanden alleen dan met .o
# een soort van map *.cpp -> *.o I guess
OBJECTS=$(SOURCES:source/.cpp=.o)
# naam van de resulterende executable
EXECUTABLE=onByte

# bevestigt dat alle sources en de executable bestaan
all: $(SOURCES) $(EXECUTABLE)

# Bouwt een executable van alle objecten
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Bouwt een object file van alle sources
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# Schoonmaak mevrouw
clean:
	rm *o hello
