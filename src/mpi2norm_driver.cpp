//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "Vector.hpp"
#include "amath583.hpp"
#include <cmath>
#include <iostream>
#include <mpi.h>
#include <string>


double mpiTwoNorm(const Vector& local_x) {
  double rho = dot(local_x, local_x), sigma = 0;
  /* write me */
  return std::sqrt(sigma);
}


int main(int argc, char* argv[]) {
  if(argc != 2){
    std::cout << "Usage : " << argv[0] << " [dimension] " << std::endl;
  }
  MPI::Init();

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  unsigned long local_size = stol[argv[1]];
  Vector y(local_size);

  if (myrank == 0){
    Vector x(local_size*mysize);
    randomize(x);

    MPI_Scatter(x, local_size, MPI::DOUBLE, &y, local_size, MPI::DOUBLE, 0, MPI::COMM_WORLD);

  }

  MPI::Finalize();

  return 0;
}
