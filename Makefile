COMPILE_OPTS = -g -Wall
OUTPUT_NAME = tester

TESTER_DEPS = setenv.o setenv.h unsetenv.o unsetenv.h bool.h errExit.o errExit.h test.c
SETENV_DEPS = setenv.c
UNSETENV_DEPS = unsetenv.c

all: tester
	

tester: $(TESTER_DEPS)
	cc $(COMPILE_OPTS) -o $(OUTPUT_NAME) setenv.o unsetenv.o test.c


test: tester
	./$(OUTPUT_NAME)

setenv.o: $(SETENV_DEPS)
	cc $(COMPILE_OPTS) -c -o setenv.o setenv.c

unsetenv.o: $(SETENV_DEPS)
	cc $(COMPILE_OPTS) -c -o unsetenv.o unsetenv.c

# an alias to make me happy (keep the line below with the tab intact)
errExit: errExit.o


errExit.o: errExit.c errExit.h
	cc $(COMPILE_OPTS) -c -o errExit.o errExit.c

clean:
	rm $(OUTPUT_NAME) *.o