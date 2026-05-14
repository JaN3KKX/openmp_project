#include "primes_algorithms.h"

void run_k1(long long m, long long n, const bool* primeArray, bool* result) {
    for (long long i = m; i <= n; i++) {
        for (long long j = 2; j * j <= i; j++) {
            if (primeArray[j] && (i % j == 0)) {
                result[i - m] = false; 
                break;
            }
        }
    }
}