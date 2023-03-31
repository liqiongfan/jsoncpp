
all: lex grammer build run

lex:
	re2c -bci -t json_scanner.hh --no-generation-date json_scanner.re -o json_scanner.cc

grammer:
	bison json_language.yy -o json_language.cc

build:
	g++ json_scanner.cc json_language.cc main.cpp -std=c++11 -fsanitize=address -fsanitize=leak -o main && strip main

run:
	./main

clean:
	find * | grep -v '\(Makefile\|README.md\|LICENSE\|json_scanner.re\|json_language.yy\|json_type.hpp\|main.cpp\)' | xargs rm -rf
