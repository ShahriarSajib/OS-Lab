#!/bin/bash

# Read number of terms
read -p "Enter the number of terms: " n

# First two terms
a=0
b=1

echo "Fibonacci series up to $n terms:"
for (( i=0; i<n; i++ ))
do
    echo -n "$a "
    fn=$((a + b))
    a=$b
    b=$fn
done

echo # for newline
