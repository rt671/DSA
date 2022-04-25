#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	// COMM_WORLD is the communicator world
	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);
	printf("Hey there from process %s, rank %d out of %d processes\n\n",
		processor_name, world_rank, world_size);
	if (world_rank == 0)
	{
		int message[] = { 101,202,303 };
		MPI_Send(message, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else
	{
		int  message[3];
		MPI_Recv(message, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Message Successfully Received\n");
		printf("Message Received : ");
		for (int i = 0; i < 3; i++) printf("%d ", message[i]);

	}
	MPI_Finalize();
	return 0;
}