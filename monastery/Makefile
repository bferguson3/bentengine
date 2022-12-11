CC:=gcc
#CXX:=g++
SDL2:=`sdl2-config --prefix=/usr/local/lib/cflags --cflags --libs` 
LIBS:=-lSDL2_mixer -lSDL2_image -lSDL2_ttf

APPNAME:=app
OS:=`uname`

src:=$(wildcard *.cpp)
obj:=$(src:.cpp=.o)

default: $(obj)
	$(CC) $^ -o $(APPNAME) $(SDL2)

%.o: %.cpp
	$(CC) -v $(SDL2) -c -o $@ $< $(LIBS) -I/usr/local/include

.PHONY: clean
clean:
	rm -f $(obj) $(APPNAME)
