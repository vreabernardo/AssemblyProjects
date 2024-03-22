#!/usr/bin/bash


dir=$1
seed=$2

#opens directory in input;
cd $dir

#for each file in the directory creates a new seed, concatenating the filename to the seed (seed_file)
#creates a dedicated output file, file.encripted
#executes the encription .c file 
for file in $dir/*
do
  seed_file = $seed${file##*/}
  gcc -o $encript.c $file ${file##*/}.encripted $seed_file

done

