#!/bin/bash

# Check if the number of input arguments is correct
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory> <seed>"
    exit 1
fi
# Assign the input arguments to variables
directory=$1
seed=$2

# Find all files in the input directory and its subdirectories
files=$(find "$directory" -type f)

# Iterate over each file found
for file in $files; do
  # Skip encrypted files using the wildcard
    if [[ "$file" == *.encrypted ]]; then
        continue  
    fi
    
    # Call the C program with the specified arguments
    original_name=$(basename "$file")
    dir_name=$(dirname "$file")
    output_name="${dir_name}/${original_name}.encrypted"
    new_seed="${seed}${original_name}"
    
    ./otp "$file" "$output_name" "$new_seed"
done