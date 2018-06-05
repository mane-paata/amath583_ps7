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
  MPI::COMM_WORLD.Allreduce(&rho, &sigma, 1, MPI::DOUBLE, MPI::SUM);
  return std::sqrt(sigma);
}

int main(int argc, char* argv[]) {

  MPI::Init();

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  unsigned long local_size = 1024;
  
  if (0 == myrank) {
    if (argc >= 2) local_size = std::stol(argv[1]);
  }

  /* Local stuff */
  Vector y(local_size);

  double seq = 0;
  double mpi = 0;


  if (0 == myrank){
    
    /* Inits */
    unsigned long global_size = local_size * mysize;
    Vector x(global_size);
    randomize(x);

    /* Compute and broadcast the seq norm */
    seq = std::sqrt(dot(x, x));
    MPI::COMM_WORLD.Bcast(&seq, 1, MPI::DOUBLE, 0);

    /* Scatter */
    MPI::COMM_WORLD.Scatter(&x(0), local_size, MPI::DOUBLE, &y(0), local_size, MPI::DOUBLE, 0);    
  }
  else {
    /* Get sequential norm computed in procress 0 */
    MPI::COMM_WORLD.Bcast(&seq, 1, MPI::DOUBLE, 0);

    /* Get scattered data */
    MPI::COMM_WORLD.Scatter(0, local_size, MPI::DOUBLE, &y(0), local_size, MPI::DOUBLE, 0);
  }

  /* Get mpi norm */
  mpi = mpiTwoNorm(y);

  /* print header */
  if (0 == myrank) std::cout <<   "#"  << "\t" << "seq" << "\t" << "mpi" << "\t" <<       "diff"      << std::endl;

  /* print results in order */
  for(int i = 0; i < mysize; i++) {
    MPI::COMM_WORLD.Barrier();
    if (i == myrank) {
      std::cout << myrank << "\t" <<  seq  << "\t" <<  mpi  << "\t" << std::abs(seq-mpi) << std::endl;
    }
  }

  MPI::Finalize();

  return 0;
}
