#!/bin/sh

# Check if exactly 2 arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile=$1
writestr=$2

# Extract directory path from writefile
writedir=$(dirname "$writefile")

# Create directory path if it doesn't exist
mkdir -p "$writedir"
if [ $? -ne 0 ]; then
    echo "Error: Could not create directory path $writedir"
    exit 1
fi

# Create/overwrite the file with content
echo "$writestr" > "$writefile"
if [ $? -ne 0 ]; then
    echo "Error: Could not create or write to file $writefile"
    exit 1
fi

