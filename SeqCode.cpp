#include <stdio.h>
#include <time.h>
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
    long double upper_k = strtod(argv[1], nullptr);
    long double x = strtod(argv[2], nullptr);
    x = x * 3.14159 / 180;

    clock_t time;
    time = clock();
    long double result = 0;
    for (long double k = 0; k < upper_k; k++)
    {
        //long double powl( long double base, long double exponent );
        result += (long double)(powl(-1, k) * powl(x, 2 * k)) / (long double)(factorial(2 * k));
    }

    printf("cos(%0.3f) = %f \n", x, result);
    time = clock() - time;
    long double time_taken = ((double)time) / CLOCKS_PER_SEC;

    printf("The function took %f seconds \n", time_taken);
}
