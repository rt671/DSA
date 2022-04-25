//ADDITION WITH TWO PROCESSORS
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// size of array
#define n 10

int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// Temporary array for slave process
int a2[1000];

int main(int argc, char* argv[])
{
    int proc_id, elements_to_send, n_elements_received;

    MPI_Status status;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    elements_to_send = n / 2 + (n%2);

    if (proc_id == 0) {
        printf("The array is ");
        for (int i = 0; i < 10; i++) printf("%d ", a[i]);
        printf("\n");

        int index = n - elements_to_send;
        MPI_Send(&elements_to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&a[n/2], elements_to_send, MPI_INT, 1, 1, MPI_COMM_WORLD);

        int sum = 0;
        for (int i = 0; i < n / 2; i++) sum += a[i];
        printf("First half sum calculated by processor 0 is %d\n", sum);

        //RECEIVING THE PARTIAL SUM
        int tmp;
        MPI_Recv(&tmp, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        sum += tmp;
        printf("Second half sum received by processor 1 is %d\n", tmp);
        printf("Sum of array is : %d\n", sum);

    }
    else
    {
        MPI_Recv(&n_elements_received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, n_elements_received, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        int sum = 0;
        for (int i = 0; i < n_elements_received; i++) sum += a[i];

        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // cleans up all MPI state before exit of process
    MPI_Finalize();

    return 0;
}


//ADDITION WITH P PROCESSORS
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// size of array
#define n 10

int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// Temporary array for slave process
int a2[1000];

int main(int argc, char* argv[])
{
    int proc_id, num_proc, elements_per_process, n_elements_received;

    MPI_Status status;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    elements_per_process = n / num_proc;

    // SEND BLOCK
    if (proc_id == 0) {
        printf("The array is ");
        for (int i = 0; i < 10; i++) printf("%d ", a[i]);
        printf("\n");

        int index, i;

        for (i = 1; i < num_proc - 1; i++) {

            int index = elements_per_process * i;
            MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&a[index], elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // last process adds remaining elements
        index = i * elements_per_process;
        int elements_left = n - index;
        MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(&a[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);

    } //RECEIVE BLOCK
    else
    {
        MPI_Recv(&n_elements_received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, n_elements_received, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    //COMPUTATION BLOCK
    if (proc_id == num_proc - 1) elements_per_process += n % num_proc;
    int sum = 0;
    for (int i = 0; i < elements_per_process; i++)
        sum += a[i];
    

    //SENDING RESULTS
    if (proc_id != 0)
    {
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else //RECEIVING RESULTS AND PRINTING
    {
        printf("The sum produced by process 0 is %d", sum);
        printf("\n");
        int tmp;
        for (int i = 1; i < num_proc; i++) {
            MPI_Recv(&tmp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            int sender = status.MPI_SOURCE;
            printf("The partial sum received by %d is %d\n", i, tmp);
            sum += tmp;
        }
        // prints the final sum of array
        printf("Sum of array is : %d\n", sum);
    }

    // cleans up all MPI state before exit of process
    MPI_Finalize();

    return 0;
}


