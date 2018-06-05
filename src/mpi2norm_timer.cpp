//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <cmath>
#include <iostream>
#include <mpi.h>
#include <string>
#include <ctime>
#include "Vector.hpp"
#include "amath583.hpp"


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

  double seq = 0, seq_time = 0;
  double mpi =0, mpi_time = 0;
  unsigned long global_size = 0;


  if (0 == myrank){
    
    /* Inits */
    global_size = local_size * mysize;
    Vector x(global_size);
    randomize(x);

    /* Time the seq norm */
    std::clock_t  start_time = std::clock();
    for (int i=0; i < 100 ; i++){
      seq = std::sqrt(dot(x, x));
    }
    seq_time = (std::clock() - start_time) / 100;

    /* Scatter */
    MPI::COMM_WORLD.Scatter(&x(0), local_size, MPI::DOUBLE, &y(0), local_size, MPI::DOUBLE, 0);    
  }
  else {
    /* Get scattered data */
    MPI::COMM_WORLD.Scatter(0, 0, MPI::DOUBLE, &y(0), local_size, MPI::DOUBLE, 0);
  }

  /* Time the mpi norm */
  std::clock_t start_time = std::clock();
  for (int i=0; i < 100 ; i++){
    mpi = mpiTwoNorm(y);
  }
  mpi_time = (std::clock() - start_time) / 100;
  
  /* print results */
  if (0 == myrank) {
    double speed_up = seq_time / mpi_time;
    double norm_diff = std::abs(seq-mpi);
    std::cout <<   "#"  << "\t" <<  "vec_dim"  << "\t" << "seq_time" << "\t" <<  "mpi_time" <<  "\t" << "speed_up"  << "\t" << "norm_diff" << std::endl;
    std::cout << mysize << "\t" << global_size << "\t" <<  seq_time  << "\t" <<   mpi_time  <<  "\t" <<  speed_up  << "\t"  <<  norm_diff  << std::endl;
  }


  MPI::Finalize();

  return 0;
}
