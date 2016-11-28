#!/bin/bash

# set the number of nodes and processes per node
#PBS -l ncpus=4

# set max wallclock time
#PBS -l walltime=006:00:00

# set name of job
#PBS -N PageRank

# Set the queu
#PBS -q routing

# compilamos para generar binario
make

# Elminar el pagerankresult.txt
rm -rf /home/julian/pageRank/pagerankresult.txt

# run through the mpirun launcher
mpirun -np 4 /home/julian/pageRank/bin/pagerank 1000 0.5 > /home/julian/pageRank/pagerankresult.txt 
