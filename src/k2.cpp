#include "primes_algorithms.h"
#include <omp.h>

void run_k2(long long m, long long n, const bool* primeArray, bool* result) {
    #pragma omp parallel for schedule(runtime)
    for (long long i = m; i <= n; i++) {
        for (long long j = 2; j * j <= i; j++) {
            if (primeArray[j] && (i % j == 0)) { 
                result[i - m] = false; 
                break;
            }
        }
    }
}