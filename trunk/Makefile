########################################################
#						Makefile 
########################################################
CC = g++
CFLAGS =$(GLFLAGS) -I./ -O3 -Os -g $(PROBLENS)

PROBLENS=-Wall -pedantic -fpermissive
UNAME = $(shell uname)
ifeq ($(UNAME),Linux) # Linux OS
	GLFLAGS = -lglut -lglui -lGLU -lGL -lalut  -lopenal
	else
	ifeq ($(UNAME),Darwin) # MAC OS X
		GLFLAGS = -framework OpenGL -framework GLUT
	else #Windows
		GLFLAGS = -lopengl32 -lglu32 -lglut32 -lglee -lalut
	endif
endif

all: 
	if $(MAKE) compiling ;\
	then \
		echo "ok" ;\
	else \
		echo  "Error on compiling! Probably some package is missing"; \
		$(MAKE) check;\
	fi;

compiling:*.cpp
	echo "System: "$(UNAME) "OS"
	echo -n "compiling..."
	$(CC) *.cpp -o prog $(CFLAGS) 
	
clean:
	echo "cleaning..."
	rm -rfv prog *.o

run: all
	echo "Running..."
	./prog
	
valgrind: *.cpp
	$(CC) -g *.cpp -o prog $(GLFLAGS) 
	valgrind --tool=callgrind --dsymutil=yes --trace-jump=yes ./prog -q
	echo "Valgrind files available: (newer first)"
	ls -t| egrep -i grind

check:
	echo "Checking if all dev packages are installed"
#	OPENGL
	echo -n "opengl "
	if dpkg -l | grep -qi "opengl.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	OPENAL
	echo -n "openal "
	if dpkg -l | grep -qi "openal.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	GLUT
	echo -n "glut "
	if dpkg -l | grep -qi "glut.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	GLUI
	echo -n "glui "
	if dpkg -l | grep -qi "glui.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	ALUT
	echo -n "alut "
	if dpkg -l | grep -qi "alut.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	GLEE
	echo -n "glee "
	if dpkg -l | grep -qi "glee.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
	
.SILENT:

#Obs
#
#	Bibliotecas incluidas:
#
#	alut-dev
#	openal-dev
#
#	Descobrindo pacotes instalados:
# $ dpkg -l | grep alut

