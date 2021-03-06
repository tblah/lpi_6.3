COMPILE_OPTS = -g -Wall -std=c99 -Wno-implicit-function-declaration
OUTPUT_NAME = tester

TESTER_DEPS = setenv.o getKey.o setenv.h unsetenv.o unsetenv.h bool.h errExit.o errExit.h test.c
SETENV_DEPS = setenv.c
UNSETENV_DEPS = unsetenv.c
GETKEY_DEPS = getKey.c

all: tester
	

tester: $(TESTER_DEPS)
	cc $(COMPILE_OPTS) -o $(OUTPUT_NAME) setenv.o errExit.o getKey.o unsetenv.o unsetenv.h setenv.h test.c 


test: tester
	./$(OUTPUT_NAME)

memtest: tester
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$(OUTPUT_NAME)

setenv.o: $(SETENV_DEPS)
	cc $(COMPILE_OPTS) -c -o setenv.o setenv.c

unsetenv.o: $(UNSETENV_DEPS)
	cc $(COMPILE_OPTS) -c -o unsetenv.o unsetenv.c

getKey.o: $(GETKEY_DEPS)
	cc $(COMPILE_OPTS) -c -o getKey.o getKey.c

# an alias to make me happy (keep the line below with the tab intact)
errExit: errExit.o


errExit.o: errExit.c errExit.h
	cc $(COMPILE_OPTS) -c -o errExit.o errExit.c

clean:
	rm $(OUTPUT_NAME) *.o
