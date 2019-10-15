#!/bin/bash
#
g++ generator.cpp -o gen
echo generator compiled
# exe, filename, seed, n_limit, q_limit, k_limit, x_limit
# sample
./gen input01.txt 137 5 5 5 5
./gen input02.txt 452 5 5 5 5
./gen input03.txt 5457 5 5 5 5
echo sample input generated
# small
./gen input04.txt 1457 25 25 25 1000
./gen input05.txt 45357 25 25 25 1000
./gen input06.txt 24557 25 25 25 1000
echo small input generated
# medium
./gen input07.txt 3254 10000 10000 50 100000
./gen input08.txt 35424 10000 10000 50 100000
./gen input09.txt 66542 10000 10000 50 100000
echo medium input generated
# large
./gen input10.txt 5335 100000 100000 50 1000000000
./gen input11.txt 3457 100000 100000 50 1000000000000000000
./gen input12.txt 35357 100000 100000 50 1000000000000000000
./gen input13.txt 784545 100000 100000 50 1000000000000000000
./gen input14.txt 457655 100000 100000 50 1000000000000000000
./gen input15.txt 3589989 100000 100000 50 1000000000000000000
echo large input generated
echo generated input
g++ ajob_commute.cpp -o sol
# g++ ajob_bruteforce.cpp -o sol
echo solution compiled
# sample
./sol < input01.txt > output01.txt
./sol < input02.txt > output02.txt
./sol < input03.txt > output03.txt
echo sample output generated
# small
./sol < input04.txt > output04.txt
./sol < input05.txt > output05.txt
./sol < input06.txt > output06.txt
echo small output generated
# medium
./sol < input07.txt > output07.txt
./sol < input08.txt > output08.txt
./sol < input09.txt > output09.txt
echo medium output generated
# large
./sol < input10.txt > output10.txt
./sol < input11.txt > output11.txt
./sol < input12.txt > output12.txt
./sol < input13.txt > output13.txt
./sol < input14.txt > output14.txt
./sol < input15.txt > output15.txt
echo large output generated
