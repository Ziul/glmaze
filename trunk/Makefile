CC = gcc
CFLAGS = -Wall -pedantic $(GLFLAGS) -I./

ifeq ($(USER),luiz)
#Linux OS
GLFLAGS = -lglut -lglui -lGLU -lGL
else
# Mac OS X: OpenGL and GLUT are frameworks, override GLFLAGS above with these
#GLFLAGS = -framework OpenGL -framework GLUT
GLFLAGS = -lopengl32 -lglu32 -lglut32 -lglee
endif

all:*.c
	echo -n "compillando..."
	$(CC) *.c -o prog $(CFLAGS) 
	echo "ok" 

#	$(CC) *.c -c $(CFLAGS) 
	
clean:
	rm -rfv prog *.o

run: all
	echo "executando..."
	./prog *.ply
	
.SILENT:
