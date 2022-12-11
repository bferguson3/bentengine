default: sdl
sdl:
	gcc -DSDLVERSION ./bentengine.c -o app 

pc88:
	sdcc -DPC88VERSION ./bentengine.c -o app

clean:
	rm app 
	rm app.asm 
	rm app.lk 
	rm app.lst 
	rm app.map 
	rm app.noi 
	rm app.rel 
	rm app.sym 
	