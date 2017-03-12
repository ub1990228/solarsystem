#
#  Makefile
#
#  Created by Changkun Ou on 16/06/07.
#  Copyright © 2016 Shiyanlou.com. All rights reserved.
#

CXX = g++
EXEC = solarsystem
SOURCES = main.cpp stars.cpp solarsystem.cpp
OBJECTS = main.o stars.o solarsystem.o
LDFLAGS = -lglut -lGL -lGLU -std=c++11

all :
	$(CXX) $(SOURCES) $(LDFLAGS) -o $(EXEC)

clean:
	rm -f $(EXEC) *.gdb *.o
