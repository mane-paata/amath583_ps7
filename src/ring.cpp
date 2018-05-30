//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <iostream>
#include <string>
#include <mpi.h>


int main(int argc, char* argv[]) {
  MPI::Init();

  int token     = 0;
  size_t rounds = 1;
  if (argc >= 2) rounds = std::stol(argv[1]);

  int myrank = MPI::COMM_WORLD.Get_rank();
  int mysize = MPI::COMM_WORLD.Get_size();

  /* write me */

  MPI::Finalize();

  return 0;
}
