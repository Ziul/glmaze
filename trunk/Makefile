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
#		SEARCH = pkgutil --pkgs	#¬¬ inutil
		SEARCH = ls /System/Library/Frameworks | grep -i
	else #Windows
		GLFLAGS = -lopengl32 -lglu32 -lglut32 -lglee -lalut
		SEARCH=
	endif
endif

all: *.cpp
	if $(MAKE) compiling ;\
	then \
		echo -n "ok\nCleaning..." ;\
		rm *.o ;\
		echo "done.\nRun "$(OUTPUT) ;\
	else \
		echo  "Error on compiling! Probably some package is missing"; \
		$(MAKE) check;\
	fi;

compiling:*.cpp
	echo "System: "$(UNAME) "OS"
	echo -n "Compiling..."
	$(CC) *.cpp -c $(CFLAGS)
	$(CC) *.cpp -MM $(CFLAGS) > depends.d
	$(CC) *.o -o $(OUTPUT) $(CFLAGS) 
	
clean:
	echo "Cleaning all..."
	rm -rfv $(OUTPUT) *.o *.d

run: all
	echo "Running..."
	./$(OUTPUT)	
	
valgrind: *.cpp
	$(CC) -g *.cpp -o prog $(GLFLAGS) 
	valgrind --tool=callgrind --dsymutil=yes --trace-jump=yes ./prog -q
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
	if $(SEARCH) "opengl" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	OPENAL
	echo -n "openal "
	if $(SEARCH) "openal" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	GLUT
	echo -n "glut "
	if $(SEARCH)  "glut" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	GLUI
	echo -n "glui "
	if $(SEARCH)  "glui" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	ALUT
	echo -n "alut "
#	if $(SEARCH) | grep -qi "alut.*dev" ;\ #Como deveria de ser pra ficar otimo!
	if $(SEARCH)  "alut" ;\
	then \
		echo "[OK]";\
	else \
		echo "[MISSING!]" ;\
	fi;
#	GLEE
	echo -n "glee "
	if $(SEARCH)  "glee" ;\
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
#
#	No MacOS os Frameworks ficam no diretorio/System/Library/Frameworks
# e possuem a nomeclatura semelhante a:
# OpenAL.framework

