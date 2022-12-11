CC:=gcc
SDL2:=`sdl2-config --prefix=/usr/local/lib/cflags --cflags --libs` 
APPNAME:=app
LIBS:=-lSDL2_mixer -lSDL2_image -lSDL2_ttf
OS:=`uname`

default:
	@if [ $(OS) = "Darwin" ]; then\
		echo "MacOS detected.";\
		$(CC) -v $(SDL2) main.c $(LIBS) -I/usr/local/include -o$(APPNAME);\
	fi 
	
