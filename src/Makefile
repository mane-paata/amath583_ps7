#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2018
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine, Tommaso Buvoli
#

CXX             = mpic++
DEFS		= 
OPTS            = -O3 -DNDEBUG # Also try -Ofast -march=native
LANG            = -std=c++11
PICKY           = -Wall 

CXXFLAGS        = $(LANG) $(OPTS) $(PICKY) $(DEFS)

.PHONY: clean all

all	: hello.exe pingpong.exe ring.exe 
all	: mpi2norm_simple.exe mpi2norm_driver.exe mpi2norm_simple_all.exe

# Generic rules
%.exe	     : %.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o          : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# exe dependencies -- consequent is handled by generic rule
mpi2norm_timer.exe	: Vector.o amath583.o
ring.exe	: Vector.o amath583.o
mpi2norm_driver.exe	: Vector.o amath583.o
mpi2norm_simple.exe	: Vector.o amath583.o
mpi2norm_simple_all.exe	: Vector.o amath583.o

# Object file (.o) dependencies -- consequent is handled by generic rule
Vector.o     : Vector.cpp Vector.hpp amath583.hpp
amath583.o   : amath583.cpp amath583.hpp Vector.hpp 

clean:
	/bin/rm -f a.out *.o *.exe *.gch *~ 
