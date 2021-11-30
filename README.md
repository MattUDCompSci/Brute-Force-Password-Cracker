# Brute-Force-Password-Cracker

Authors: Matthew Weis, Joe Bilotta, Zhenhao Shao

This is for educational purposes for CISC372-011 class. Credit to users rusheb and syb0rg on codereview.stackexchange.com for all source code used in this project. Links to their codes:
https://codereview.stackexchange.com/questions/203778/brute-force-passwords-in-c-cs50-exercise 
https://codereview.stackexchange.com/questions/38474/brute-force-algorithm-in-c

# Project Details
This project is a Brute Force Password Checker Used in our CISC372 Final Project. The primary goal of this project was to create serial code for a Brute Force Password Checker and then use parallelization to speed up the runtime. Speed-up was done via OpenMP on multicore CPUs, OpenACC on multicore CPUs, and OpenACC on GPUs. The serial code (passwordCracker.c) uses an alphabet character array and a buffer string to go iterate through all possible strings from 1 character to 12 characters (which can be changed in the code by changing the MAX_LENGTH variable).

For our project, the following passwords were used
 - CuDa
 - GpU13
 - nViDiA

# Running the Code

All code provided in this Github repository has been run on the bridges2 supercomputer. To run this code on your machine, being by loading the NVHPC 21.7 Compiler onto your system. For Bridges2 systems, this command is:

```
module load nvhpc/21.7
```

To compile this code on the bridges2 super computer, begin by moving all 3 passwordCracker c files to the remote server (This can be done using the scp command or using WinSCP for Windows users). When files are in the desired location on bridges2 and nvhpc 21.7 is loaded, code can be compiled for running as follows. 

For serial code:
```
nvc passwordCracker.c -o passwordCracker
```
> Output will vary among password lengths (4 character: 0-0.1 seconds, 5 characters: 6.5-8 seconds, 6 characters: 2.5-3 minutes)  

For OpenMP on multicores:

```
nvc passwordCrackerMP.c -mp -o passwordCrackerOMP
```

> Output will vary among password lengths (4 character: 0-0.3 seconds, 5 characters: 7-16 seconds, 6 characters: 10-30 minutes)  

For OpenACC on multicores:

```
nvc -acc -Minfo=accel passwordCrackerACC.c -o passwordCrackerACCMultiCore
```

> Output will vary among password lengths (4 character: 0-0.09 seconds, 5 characters: 1-2 seconds, 6 characters: 1-2 minutes)  

For OpenACC on GPUs:
```
nvc -acc -ta=tesla -Minfo=accel passwordCrackerACC.c -o passwordCrackerACCGPU
```

or

```
nvc -acc -gpu=cc70 -Minfo=accel passwordCrackerACC.c -o passwordCrackerACCGPU
```

> Output will vary among password lengths (4 character: 0-0.09 seconds, 5 characters: 1-1.5 seconds, 6 characters: 1-1.5 minutes)  
