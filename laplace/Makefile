#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2018
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine, Tommaso Buvoli
#

CXX             = c++
DEFS		= 
OPTS            = -O3 -DNDEBUG # Also try -Ofast -march=native
LANG            = -std=c++11
PICKY           = -Wall 

CXXFLAGS        = $(LANG) $(OPTS) $(PICKY) $(DEFS)

.PHONY: clean all

all	: jacobi_driver.exe ir_driver.exe

# Generic rules
%.exe	     : %.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o          : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# exe dependencies -- consequent is handled by generic rule
jacobi_driver.exe  	: Grid.o 
ir_driver.exe  	   	: Grid.o Stencil.o

# Object file (.o) dependencies -- consequent is handled by generic rule
Grid.o       : Grid.cpp Grid.hpp Stencil.hpp
Stencil.o    : Stencil.cpp Stencil.hpp Grid.hpp 

clean:
	/bin/rm -f a.out *.o *.exe *.gch *~ 
