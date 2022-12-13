CC:=gcc
#CXX:=g++
SDL2:=`sdl2-config --prefix=/usr/local --cflags --libs`
SDL2STATIC:=`sdl2-config --prefix=/usr/local --cflags --static-libs`
LIBS:=-lSDL2_mixer -lSDL2_image -lSDL2_ttf -lc++
LIBSSTATIC:=-lc++

APPNAME:=app
OS:=`uname`

src:=$(wildcard *.cpp)
obj:=$(src:.cpp=.o)

default: $(obj)
	$(CC) $^ -o $(APPNAME) $(SDL2) $(LIBS)

static: $(obj)
	$(CC) $^ -o $(APPNAME) -L./libs/ -lSDL2_ttf -lSDL2_image $(SDL2STATIC) $(LIBSSTATIC)

%.o: %.cpp
	$(CC) -v $(SDL2) -c -o $@ $< $(LIBS) -I/usr/local/include

.PHONY: clean
clean:
	rm -f $(obj) $(APPNAME)
