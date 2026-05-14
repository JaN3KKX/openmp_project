#!/bin/bash

CSV_FILE="results.csv"
echo "Variant;M;N;Schedule;BlockSize;Time_sec;Speed_M_per_sec" > $CSV_FILE

RANGES=("2 100000000" "50000000 100000000" "2 50000000")
VARIANTS=("k1" "k2" "k3" "k3a" "k4" "k4a" "k5")

# --- TASK 3: ALL VARIANTS FOR 3 RANGES ---
for range in "${RANGES[@]}"; do
    m=$(echo $range | awk '{print $1}')
    n=$(echo $range | awk '{print $2}')

    for variant in "${VARIANTS[@]}"; do
        sched="static"
        block_size="0"
        
        if [ "$variant" == "k3a" ] || [ "$variant" == "k5" ]; then
            block_size="32768"
        fi

        export OMP_SCHEDULE="$sched"
        echo "Executing: $variant | M=$m | N=$n | Schedule=$sched | BlockSize=$block_size"
        
        output=$(./build/primes $variant $m $n $block_size)
        
        time_val=$(echo "$output" | grep "Czas rzeczywisty" | awk '{print $4}')
        speed_val=$(echo "$output" | grep "PREDKOSC OBLICZEN" | awk '{print $3}')
        
        echo "$variant;$m;$n;$sched;$block_size;$time_val;$speed_val" >> $CSV_FILE
    done
done

# Dodanie pustego wiersza do CSV i konsoli po Zadaniu 3
echo "" >> $CSV_FILE
echo ""

# --- TASKS 4 & 8: LOOP SCHEDULING (k2, k4, k4a) ---
for sched in "static,1024" "dynamic,1024" "guided"; do
    export OMP_SCHEDULE="$sched"
    
    for variant in "k2" "k4" "k4a"; do
        echo "Executing: $variant | M=2 | N=100000000 | Schedule=$sched | BlockSize=0"
        
        output=$(./build/primes $variant 2 100000000 0)
        time_val=$(echo "$output" | grep "Czas rzeczywisty" | awk '{print $4}')
        speed_val=$(echo "$output" | grep "PREDKOSC OBLICZEN" | awk '{print $3}')
        
        echo "$variant;2;100000000;$sched;0;$time_val;$speed_val" >> $CSV_FILE
    done
done

# Dodanie pustego wiersza do CSV i konsoli po Zadaniach 4 i 8
echo "" >> $CSV_FILE
echo ""

# --- TASKS 7 & 9: BLOCK SIZES (k3a, k5) ---
export OMP_SCHEDULE="static"

for block_size in 16384 65536 262144 1048576; do
    for variant in "k3a" "k5"; do
        echo "Executing: $variant | M=2 | N=100000000 | Schedule=static | BlockSize=$block_size"
        
        output=$(./build/primes $variant 2 100000000 $block_size)
        time_val=$(echo "$output" | grep "Czas rzeczywisty" | awk '{print $4}')
        speed_val=$(echo "$output" | grep "PREDKOSC OBLICZEN" | awk '{print $3}')
        
        echo "$variant;2;100000000;static;$block_size;$time_val;$speed_val" >> $CSV_FILE
    done
done

# Dodanie pustego wiersza do CSV i konsoli po Zadaniach 7 i 9
echo "" >> $CSV_FILE
echo ""

# --- TASK 10: PARALLEL DOMAIN SIEVE (k5) WITH DIFFERENT SCHEDULES ---
for sched in "static,1024" "dynamic,1024" "guided"; do
    export OMP_SCHEDULE="$sched"
    
    echo "Executing: k5 | M=2 | N=100000000 | Schedule=$sched | BlockSize=32768"
    
    output=$(./build/primes k5 2 100000000 32768)
    time_val=$(echo "$output" | grep "Czas rzeczywisty" | awk '{print $4}')
    speed_val=$(echo "$output" | grep "PREDKOSC OBLICZEN" | awk '{print $3}')
    
    echo "k5;2;100000000;$sched;32768;$time_val;$speed_val" >> $CSV_FILE
done

echo ""
echo "Execution completed successfully. Results appended to $CSV_FILE."