
all: testTextbuffer

testTextbuffer: testTextbuffer.o textbuffer.c textbuffer.h
	gcc -Wall -Werror -std=c11 -g -lm testTextbuffer.o textbuffer.c -o testTextbuffer

clean:
	rm -rf testTextbuffer

