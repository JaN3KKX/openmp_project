#include <iostream>
#include <cmath>
#include <omp.h>
#include <ctime>
#include <cstring>
#include <string>
#include "primes_algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Uzycie: ./build/primes <wariant: k1|k2|k3|k3a|k4|k4a|k5> <m> <n> [blockSize]\n";
        return 1;
    }

    string variant = argv[1];
    long long m = stoll(argv[2]);
    long long n = stoll(argv[3]);
    long long blockSize = (argc >= 5) ? stoll(argv[4]) : 65536;

    bool* result = new bool[n - m + 1];
    memset(result, true, (n - m + 1) * sizeof(bool));

    long long sqrt_n = (long long)sqrt(n);
    bool* primeArray = new bool[sqrt_n + 1];
    memset(primeArray, true, (sqrt_n + 1) * sizeof(bool));
    
    for (long long i = 2; i * i <= sqrt_n; i++) {
        if (primeArray[i]) {
            for (long long j = i * i; j <= sqrt_n; j += i) {
                primeArray[j] = false;
            }
        }
    }

    cout << "--- START EKSPERYMENTU ---\n";
    cout << "Wariant: " << variant << " | Zakres: <" << m << ", " << n << ">\n";
    if (variant == "k3a" || variant == "k5") cout << "Rozmiar bloku: " << blockSize << "\n";

    double sswtime = omp_get_wtime();
    clock_t spstart = clock();

    if (variant == "k1") run_k1(m, n, primeArray, result);
    else if (variant == "k2") run_k2(m, n, primeArray, result);
    else if (variant == "k3") run_k3(m, n, primeArray, result);
    else if (variant == "k3a") run_k3a(m, n, primeArray, result, blockSize);
    else if (variant == "k4") run_k4(m, n, primeArray, result);
    else if (variant == "k4a") run_k4a(m, n, primeArray, result);
    else if (variant == "k5") run_k5(m, n, primeArray, result, blockSize);
    else {
        cout << "Nieznany wariant!\n";
        delete[] result;
        delete[] primeArray;
        return 1;
    }

    clock_t spstop = clock();
    double sewtime = omp_get_wtime();

    double wallclock_time = sewtime - sswtime;
    double cpu_time = ((double)(spstop - spstart) / CLOCKS_PER_SEC);
    long long checked_numbers = n - m + 1;
    double speed_M_per_sec = (checked_numbers / wallclock_time) / 1000000.0;

    long long primes_count = 0;
    for(long long i = 0; i <= (n - m); i++) {
        if(result[i] && (i + m) >= 2) primes_count++;
    }

    printf("Znaleziono liczb pierwszych: %lld\n", primes_count);
    printf("Czas rzeczywisty (Wall-clock): %f s\n", wallclock_time);
    printf("Czas CPU: %f s\n", cpu_time);
    printf("PREDKOSC OBLICZEN: %.3f Mliczb/sek\n", speed_M_per_sec);
    cout << "--------------------------\n";

    delete[] result;
    delete[] primeArray;

    return 0;
}