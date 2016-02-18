#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int printTime()
{
  time_t current_time;
  char* c_time_string;

  current_time = time(NULL);

  if (current_time == ((time_t)-1)) {
    fprintf(stderr, "Failure to obtain the current time.\n");
    return EXIT_FAILURE;
  }

  c_time_string = ctime(&current_time);

  if (c_time_string == NULL) {
    fprintf(stderr, "Failure to convert the current time.\n");
    return EXIT_FAILURE;
  }

  printf("Current time is %s", c_time_string);

  return EXIT_SUCCESS;
}

int main(int argc, char** argv) 
{
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  printTime();

  // Print off a hello world message
  printf("Hello world from processor %s, rank %d"
         " out of %d processors\n",
         processor_name, world_rank, world_size);

  // Finalize the MPI environment.
  MPI_Finalize();

  return 0;
}

