CC = g++
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
CFLAGS = -c -O3 -std=c++11 -Wall -I. -ldl $(GTK_FLAGS)
LDFLAGS = -I. -ldl $(GTK_FLAGS)
SOURCES = util.cpp gui.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(addprefix objects/,$(OBJECTS))
EXECUTABLE = elearn

all: objects $(SOURCES) $(EXECUTABLE)

objects:
	@mkdir -p objects

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

objects/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf objects/*.o $(EXECUTABLE)
