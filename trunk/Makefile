########################################################
#						Makefile 
#				Friday 17 August 2012 
########################################################
CC = g++
CFLAGS =$(GLFLAGS) -I./ -O3 -Os -g $(PROBLENS)
CC_WINDOWS = x86_64-linux-gnu-g++

PROBLENS=-Wall -pedantic -fpermissive
UNAME = $(shell uname)
OUTPUT = Amaze.out

SRC = 	button.cpp  \
		defines.cpp   \
		eventos.cpp    \
		minimap.cpp    \
		player.cpp   \
		text.cpp           \
		tile.cpp \
		camera.cpp  \
		entidade.cpp  \
		framerate.cpp  \
		map.cpp          \
		model_obj.cpp  \
		soundAL.cpp  \
		textureloader.cpp

OBJS = ${SRC:.cpp=.o}

.SUFFIXES:.c.o
###
#	libghc-opengl-dev
#	libghc-openal-dev
#	freeglut3-dev
#	libglui-dev
#	libalut-dev
#	glee-dev
####



define PROGRAM_template
$(1): $(addsuffix .o,$(1))
endef
$(foreach t,$(compiling),$(eval $(call PROGRAM_template,$(t))))


ifeq ($(UNAME),Linux) # Linux OS
	GLFLAGS = -lglut -lglui -lGLU -lGL -lalut  -lopenal
	SEARCH = dpkg -l | grep -iq
	else
	ifeq ($(UNAME),Darwin) # MAC OS X
		GLFLAGS = -framework OpenGL -framework GLUT -framework OpenAL
		SEARCH = ls /System/Library/Frameworks | grep -i
	else #Windows
		GLFLAGS = -lopengl32 -lglu32 -lglut32 -lglee -lalut
		SEARCH=
	endif
endif

all: system out

debug: config

system:
	echo "System: "$(UNAME) "OS"
	echo -n "Compiling..."

system_debug:
	echo "System: "$(UNAME) "OS"
	if rm *.o;\
	then \
		echo -n "Cleaning && ";\
	fi;
	echo -n "Compiling..."

config: system_debug
	if $(MAKE) out ;\
	then \
		echo " " ;\
	else \
	echo  "Error on compiling! Probably some package is missing"; \
		$(MAKE) check;\
	fi;

.c.o:
	echo -n "compiling..." $<
	$(CC) $< -c -g $(CFLAGS) $(GLFLAGS)
	echo  "Done"

compiling: $(OBJS)
	
lib: compiling
	echo  "Done"
	echo -n "Making lib..."
	ar rcs libAmaze.a *.o
	
out: lib
	$(CC) gamemanager.cpp -o $(OUTPUT) $(CFLAGS) -L./ -lAmaze $(GLFLAGS)
	echo "Done.\nRun "$(OUTPUT) ;\
	
clean:
	echo "Cleaning all..."
	rm -rfv $(OUTPUT) *.o *.d *.a

run: out
	echo "Running..."
	./$(OUTPUT)	
	
valgrind: *.cpp
	$(CC) -g -c $(SRC) $(CFLAGS) $(GLFLAGS)
	ar rc libAmaze.a *.o
	$(CC) -g gamemanager.cpp -o ToGring $(GLFLAGS) -L./ -lAmaze
#	valgrind --tool=callgrind --dsymutil=yes --trace-jump=yes ./ToGring -q --fullpath-after=string  --show-possibly-lost=yes --trace-children=yes -v --main-stacksize=512MB
	echo "Valgrind files available: (newer first)"
	ls -t| egrep -i grind
	
windows: *.cpp
	echo "Cross compiling to" $@
	$(CC_WINDOWS) *.cpp -c $(CFLAGS)
	$(CC_WINDOWS) *.o -o ./bin/x86-x64-Amaze.exe $(CFLAGS)
	echo "done.\nRun " x86-x64-Amaze.exe "on bin directory"

check:
	echo "Checking if all dev packages are installed"
#	OPENGL
	echo -n "opengl "
	if $(SEARCH) "opengl.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!] - Install libghc-opengl-dev" ;\
	fi;
#	OPENAL
	echo -n "openal "
	if $(SEARCH) "openal.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!] - Install libghc-openal-dev" ;\
	fi;
#	GLUT
	echo -n "glut "
	if $(SEARCH)  "glut.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!] - Install freeglut3-dev" ;\
	fi;
#	GLUI
	echo -n "glui "
	if $(SEARCH)  "glui.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!] - Install libglui-dev" ;\
	fi;
#	ALUT
	echo -n "alut "
#Como deveria de ser pra buscar por suporte para desenvolvedores
#	if $(SEARCH) | grep -qi "alut.*dev" ;\ 
	if $(SEARCH)  "alut.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!] - Install libalut-dev" ;\
	fi;
#	GLEE
	echo -n "glee "
	if $(SEARCH)  "glee.*dev" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!] - Install glee-dev" ;\
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
#
#	No MacOS os Frameworks ficam no diretorio/System/Library/Frameworks
# e possuem a nomeclatura semelhante a:
# OpenAL.framework

