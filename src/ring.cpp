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

  /* Start the sending */
  if (myrank == 0){
      std::cout << myrank << ": sending " << token << std::endl;
      MPI::COMM_WORLD.Send(&token, 1, MPI::INT, 1, 321);
  }

  while(rounds--){
    int to_rank = myrank == mysize-1 ? 0 : myrank+1;
    int from_rank = myrank == 0 ? mysize-1 : myrank-1;

    /* Receive */
    MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, from_rank, 321);
    std::cout << myrank << ": received " << token << std::endl;

    /* Break when we have completed the round and there are no more rounds */
    if (!rounds && myrank == 0) break;
    
    /* Increase */
    ++token;
    
    /* Send */
    std::cout << myrank << ": sending " << token << std::endl;
    MPI::COMM_WORLD.Send(&token, 1, MPI::INT, to_rank, 321);
  }

  MPI::Finalize();

  return 0;
}
