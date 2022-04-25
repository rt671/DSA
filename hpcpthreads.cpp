//HELLO WORLD PROGRAM
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int thread_count; // global variable is shared by all threads
// compiling information -
// gcc name_of_file.c -o name_of_exe -lpthread (link p thread)
// this function is what we want to parallelize
void *Hello(void *rank);
// main driver function of the program
int main(int argc, char *argv[])
{
long thread;
// /∗ Use long in case of a 64−bit system ∗/
pthread_t *thread_handles;
thread_count = strtol(argv[1], NULL, 10);
// get the thread handles equal to total num of threads
thread_handles = malloc(thread_count * sizeof(pthread_t));
for (thread = 0; thread < thread_count; thread++)
pthread_create(&thread_handles[thread], NULL, Hello, (void *)thread);
// Thread placement on cores is done by OS
printf("Hello from the main thread\n");
for (thread = 0; thread < thread_count; thread++)
pthread_join(thread_handles[thread], NULL);
free(thread_handles);
return 0;
}
// /∗ main ∗/
void *Hello(void *rank) // void * means a pointer, can be of any type
{
long my_rank = (long)rank;
printf("Hello from thread %ld of %d\n", my_rank, thread_count);
return NULL;
}

//process synchronization
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int thread_count; // this global variable is shared by all threads
// compiling information -
// gcc name_of_file.c -o name_of_exe -lpthread (link p thread)
// necessary for referencing in the thread
struct arguments
{
int size;
int* arr1;
int* arr2;
int* dot;
};
// function to parallelize`
void* add_into_one(void* arguments);
// util
void print_vector(int n, int* arr)
{
printf("[ ");
for (int i = 0; i < n; i++)
22
printf("%d ", arr[i]);
printf("] \n");
}
// main driver function of the program
int main(int argc, char* argv[])
{
long thread;
// /∗ Use long in case of a 64−bit system ∗/
pthread_t* thread_handles;
thread_count = 2; // using 2 threads only
// get the thread handles equal to total num
// of threads
thread_handles = malloc(thread_count * sizeof(pthread_t));
printf("Enter the size of the vectors : ");
int n;
scanf("%d", &n);
printf("Enter the max_val of the vectors : ");
int max_val;
scanf("%d", &max_val);
struct arguments* args[2]; // array of pointer to structure
// each element is a pointer
for (int i = 0; i < 2; i++)
{
// allocate for the struct
args[i] = malloc(sizeof(struct arguments) * 1);
// allocate for the arrays
args[i]->size = n;
args[i]->arr1 = malloc(sizeof(int) * n);
args[i]->arr2 = malloc(sizeof(int) * n);
args[i]->dot = malloc(sizeof(int) * n);
for (int j = 0; j < n; j++)
{
args[i]->arr1[j] = rand() % max_val;
args[i]->arr2[j] = rand() % max_val;
}
}
printf("Vectors are : \n");
print_vector(n, args[0]->arr1);
print_vector(n, args[0]->arr2);
print_vector(n, args[1]->arr1);
print_vector(n, args[1]->arr2);
int result[n];
memset(result, 0, n * sizeof(int));
// note : we need to manually startup our threads
// for a particular function which we want to execute in
// the thread
for (thread = 0; thread < thread_count; thread++)
{
printf("Multiplying %ld and %ld with thread %ld...\n", thread + 1,
thread + 2,
thread);
pthread_create(&thread_handles[thread], NULL, add_into_one,
(void*)args[thread]);
}
printf("Hello from the main thread\n");
// wait for completion
for (thread = 0; thread < thread_count; thread++)
pthread_join(thread_handles[thread], NULL);
for (int i = 0; i < 2; i++)
{
printf("Multiplication for vector %d and %d \n", i + 1, i + 2);
print_vector(n, args[i]->dot);
printf("\n");
}
free(thread_handles);
// now compute the summation of results
for (int i = 0; i < n; i++)
result[i] = args[0]->dot[i] + args[1]->dot[i];
printf("Result is : \n");
print_vector(n, result);
return 0;
}
void* add_into_one(void* argument)
{
// de reference the argument
struct arguments* args = argument;
// compute the dot product into the
// array dot
int n = args->size;
for (int i = 0; i < n; i++)
args->dot[i] = args->arr1[i] * args->arr2[i];
return NULL;
}



