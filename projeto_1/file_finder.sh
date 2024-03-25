#!/bin/bash

# Check if the number of input arguments is correct
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory> <seed>"
    exit 1
fi

# Assign the input arguments to variables
dir=$1
seed=$2

# Find all files in the input directory and its subdirectories
files=$(find "$dir" -type f)

# Iterate over each file found
for file in $files; do
  # Skip encrypted files using the wildcard
    if [[ "$file" == *.encrypted ]]; then
        continue  
    fi
    ./otp "$file" "${file}.encrypted" "$seed"
done
