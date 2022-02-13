#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

long double factorial(long double n)
{
	long double res = 1, i;
	for (i = 2; i <= n; i++)
		res *= i;
	return res;
}

int main(int argc, char** argv)
{
	int  upper_k, PNum;
	long double x = 0;
	long double StartTime, EndTime, Duration, TotalDuration;
	long double cosine = 0, Globalcosine;
	int rank;

	if (argc == 3) {
		x = strtod(argv[1], nullptr);
		upper_k = strtod(argv[2], nullptr);
	}
	else
	{
		x = 1.0471;
		upper_k = 500;
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &PNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Bcast(&upper_k, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&x, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);


	MPI_Barrier(MPI_COMM_WORLD);

	StartTime = MPI_Wtime();

	for (long double k = rank; k < upper_k; k += PNum)
	{
		cosine += (powl(-1, k) * powl(x, 2 * (long double)k) / factorial(2 * (long double)k));
	}

	MPI_Reduce(&cosine, &Globalcosine, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("Cos(%f) =  %.4f \n", x, Globalcosine);
	}
	EndTime = MPI_Wtime();
	Duration = EndTime - StartTime;


	MPI_Reduce(&Duration, &TotalDuration, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("Runtime is = %f\n", TotalDuration);
	}

	MPI_Finalize();
}
