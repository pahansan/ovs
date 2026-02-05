#include </opt/openmpi-4.1.4/include/mpi.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_size = 1024 * 1024;
int end_size = 1024 * 1024 * 10;
int step = 1024 * 1024;
int nruns = 1000;

int main(int argc, char **argv) {
  int rank, commsize;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &commsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (argc < 2) {
    if (rank == 0)
      fprintf(stderr, "Error: not enought arguments\nUsage: main <output>\n");
    MPI_Finalize();
    return 1;
  }
  if (strlen(argv[1]) > 256) {
    if (rank == 0)
      fprintf(stderr, "Error: Filename too long\n");
    MPI_Finalize();
    return 1;
  }
  char filename[256];
  strcpy(filename, argv[1]);
  uint8_t *sbuf = malloc(sizeof(*sbuf) * end_size);
  uint8_t *rbuf = malloc(sizeof(*rbuf) * end_size);
  MPI_Request requests[2];
  char result_data[1000000] = "";
  char tmp_data[1000] = "";

  for (int size = start_size; size <= end_size; size += step) {
    double t = MPI_Wtime();
    if (rank == 0) {
      for (int i = 0; i < nruns; i++) {
        MPI_Isend(sbuf, size, MPI_UINT8_T, 1, 0, MPI_COMM_WORLD, &requests[0]);
        MPI_Irecv(rbuf, size, MPI_UINT8_T, 1, 0, MPI_COMM_WORLD, &requests[1]);
        MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);
      }
    } else if (rank == 1) {
      for (int i = 0; i < nruns; i++) {
        MPI_Isend(sbuf, size, MPI_UINT8_T, 0, 0, MPI_COMM_WORLD, &requests[0]);
        MPI_Irecv(rbuf, size, MPI_UINT8_T, 0, 0, MPI_COMM_WORLD, &requests[1]);
        MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);
      }
    }
    t = (MPI_Wtime() - t) / nruns;
    sprintf(tmp_data, "%d\t%f\n", size, t);
    strcat(result_data, tmp_data);
  }
  if (rank == 0) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", result_data);
    fclose(file);
  }
  free(sbuf);
  free(rbuf);
  MPI_Finalize();
  return 0;
}
