#include "primes_algorithms.h"
#include <omp.h>
#include <cmath>

void run_k4a(long long m, long long n, const bool* primeArray, bool* result) {
    long long limit = (long long)sqrt(n);

    #pragma omp parallel for schedule(runtime)
    for (long long i = 2; i <= limit; i++) {
        if (primeArray[i]) {
            long long firstMultiple = (m / i);
            if (firstMultiple <= 1) firstMultiple = i + i;
            else if (m % i) firstMultiple = (firstMultiple * i) + i;
            else firstMultiple = (firstMultiple * i);

            for (long long j = firstMultiple; j <= n; j += i) { 
                if (result[j - m] == true) {
                    result[j - m] = false; 
                }
            }
        }
    }
}