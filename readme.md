# Game of Life (GOL)

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/gol/blob/master/LICENSE) [![Build Status](https://github.com/majestic53/gol/workflows/Build/badge.svg)](https://github.com/majestic53/gol/actions/workflows/build.yml)

Conway's Game of Life, written in C.

![Demo](https://github.com/majestic53/gol/blob/master/docs/demo.png)

## Building from source

This project is tested under GNU/Linux, using the GCC C compiler. Some modifications will be required to build with a different OS/compiler.

### Preparing to build

The following libraries are required to build this project:
* [Simple Display Layer](https://www.libsdl.org/)

#### On Debian-based systems

Update apt and install the following packages:

```
sudo apt-get install libsdl2-dev
```

#### On Arch-based systems

Update pacman and install the following packages:

```
sudo pacman -S sdl2
```

### Building

#### Cloning the project

Run the following command to clone the project:

```
git clone https://github.com/majestic53/gol
```

#### Build the project

Run the following commands to build the project:

```
cd gol
```
```
export CC=<COMPILER>
```
```
make [<BUILD>]
```

|Field   |Supported values          |Description                                              |
|:-------|:-------------------------|:--------------------------------------------------------|
|COMPILER|```gcc```                 |Specifies the compiler to be used                        |
|BUILD   |```debug```, ```release```|Optionally specifies the build type (defaults to release)|

If the build succeeds, the binary files can be found under ```build/```.

#### Build example

To compile the GOL release build using GCC, run the following commands:

```
export CC=gcc
```
```
make release
```

## Using the Library

This project is implemented in C and exposes a simple API, described in [include/gol.h](https://github.com/majestic53/gol/blob/master/include/gol.h):

### Available routines

|Name     |Signature                                  |Description              |
|:--------|:------------------------------------------|:------------------------|
|gol      |```int gol(unsigned long, unsigned long)```|Run GOL                  |
|gol_error|```const char *gol_error(void)```          |Retrieve GOL error string|


For an example, see the [launcher](https://github.com/majestic53/gol/tree/master/tool) under ```tool/```

## License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
