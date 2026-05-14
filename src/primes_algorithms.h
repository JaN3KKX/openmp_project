#ifndef PRIMES_ALGORITHMS_H
#define PRIMES_ALGORITHMS_H

void run_k1(long long m, long long n, const bool* primeArray, bool* result);
void run_k2(long long m, long long n, const bool* primeArray, bool* result);
void run_k3(long long m, long long n, const bool* primeArray, bool* result);
void run_k3a(long long m, long long n, const bool* primeArray, bool* result, long long blockSize);
void run_k4(long long m, long long n, const bool* primeArray, bool* result);
void run_k4a(long long m, long long n, const bool* primeArray, bool* result);
void run_k5(long long m, long long n, const bool* primeArray, bool* result, long long blockSize);

#endif