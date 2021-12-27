# Game of Life (GOL)
# Copyright (C) 2021 David Jolly
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
# AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

DIR_BUILD=../build/
DIR_INCLUDE=../include/
DIR_ROOT=./
DIR_SRC=./src/

FILE_BIN=gol

FLAGS=-march=native -mtune=native -std=c99 -Wall -Werror
FLAGS_LIB=-lgol -lSDL2 -lSDL2main

build: build_tool link
build_tool: tool_main.o

link:
	@echo ''
	@echo '--- LINKING MAIN --------------------------------------------------------------'
	$(CC) $(FLAGS) $(FLAGS_BUILD) $(DIR_BUILD)tool_main.o -L$(DIR_BUILD) $(FLAGS_LIB) -o $(DIR_BUILD)$(FILE_BIN)
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

tool_main.o: $(DIR_ROOT)main.c
	$(CC) $(FLAGS) $(FLAGS_BUILD) -I$(DIR_INCLUDE) -c $(DIR_ROOT)main.c -o $(DIR_BUILD)tool_main.o
