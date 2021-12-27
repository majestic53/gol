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
DIR_SRC=./
DIR_SRC_COMMON=./common/
DIR_SRC_SERVICE=./service/

FILE_LIB=libgol.a

FLAGS=-march=native -mtune=native -std=c99 -Wall -Werror

build: build_base build_common build_service

build_base: base_gol.o
build_common: common_error.o
build_service: service_sdl.o

archive:
	@echo ''
	@echo '--- ARCHIVING LIBRARY ---------------------------------------------------------'
	ar rcs $(DIR_BUILD)$(FILE_LIB) $(DIR_BUILD)base_gol.o \
		$(DIR_BUILD)common_error.o \
		$(DIR_BUILD)service_sdl.o
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

base_gol.o: $(DIR_SRC)gol.c
	$(CC) $(FLAGS) $(FLAGS_BUILD) -c $(DIR_SRC)gol.c -o $(DIR_BUILD)base_gol.o

common_error.o: $(DIR_SRC_COMMON)error.c
	$(CC) $(FLAGS) $(FLAGS_BUILD) -c $(DIR_SRC_COMMON)error.c -o $(DIR_BUILD)common_error.o

service_sdl.o: $(DIR_SRC_SERVICE)sdl.c
	$(CC) $(FLAGS) $(FLAGS_BUILD) -c $(DIR_SRC_SERVICE)sdl.c -o $(DIR_BUILD)service_sdl.o
