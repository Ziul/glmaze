########################################################
#						Makefile 
########################################################
CC = g++
CFLAGS =$(GLFLAGS) -I./ -O3 -Os -g $(PROBLENS)

PROBLENS=-Wall -pedantic -fpermissive
UNAME = $(shell uname)
ifeq ($(UNAME),Linux) # Linux OS
	GLFLAGS = -lglut -lglui -lGLU -lGL 
	else
	ifeq ($(UNAME),Darwin) # MAC OS X
		GLFLAGS = -framework OpenGL -framework GLUT
	else #Windows
		GLFLAGS = -lopengl32 -lglu32 -lglut32 -lglee
	endif
endif

all:*.cpp
	echo "System: "$(UNAME) "OS"
	echo -n "compiling..."
	$(CC) *.cpp -o prog $(CFLAGS) 
	echo "ok" 
	
clean:
	echo "cleaning..."
	rm -rfv prog *.o

run: all
	echo "Running..."
	./prog

check:
	echo "Nothing to be check."
	
.SILENT:
