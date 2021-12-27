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

DIR_BUILD=./build/
DIR_ROOT=./
DIR_SRC=./src/
DIR_TOOL=./tool/

FLAGS_DEBUG=FLAGS_BUILD=-g\ -DDEBUG\ -D$(SERVICE)
FLAGS_RELEASE=FLAGS_BUILD=-O3\ -D$(SERVICE)

# Set service layer (default=SDL)
SERVICE?=SDL

# Set job slot count (default=8)
SLOTS?=8

all: release
debug: setup library_debug tool_debug
release: setup library_release tool_release

clean:
	@echo ''
	@echo '--- CLEANUP -------------------------------------------------------------------'
	rm -rf $(DIR_BUILD)
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

library_debug:
	@echo ''
	@echo '--- BUILDING LIBRARY ----------------------------------------------------------'
	cd $(DIR_SRC) && make $(FLAGS_DEBUG) build -j$(SLOTS) && make archive
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

library_release:
	@echo ''
	@echo '--- BUILDING LIBRARY ----------------------------------------------------------'
	cd $(DIR_SRC) && make $(FLAGS_RELEASE) build -j$(SLOTS) && make archive
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

setup:
	@echo ''
	@echo '--- SETUP ---------------------------------------------------------------------'
	rm -rf $(DIR_BUILD)
	mkdir -p $(DIR_BUILD)
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

tool_debug:
	@echo ''
	@echo '--- BUILDING TOOL -------------------------------------------------------------'
	cd $(DIR_TOOL) && make $(FLAGS_DEBUG) build
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''

tool_release:
	@echo ''
	@echo '--- BUILDING TOOL -------------------------------------------------------------'
	cd $(DIR_TOOL) && make $(FLAGS_RELEASE) build
	@echo '--- DONE ----------------------------------------------------------------------'
	@echo ''
