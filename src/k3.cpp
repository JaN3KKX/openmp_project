#include "primes_algorithms.h"

void run_k3(long long m, long long n, const bool* primeArray, bool* result) {
    for (long long i = 2; i * i <= n; i++) {
        if (primeArray[i]) {
            long long firstMultiple = (m / i);
            if (firstMultiple <= 1) firstMultiple = i + i;
            else if (m % i) firstMultiple = (firstMultiple * i) + i;
            else firstMultiple = (firstMultiple * i);
            
            for (long long j = firstMultiple; j <= n; j += i) { 
                result[j - m] = false; 
            }
        }
    }
}