#!/bin/bash

echo -n "How many numbers? :"
read  n

echo "Enter $n numbers:"
read -a arr

max=${arr[0]}

for((i=1; i<n; i++))
do
  if((arr[i] > max));then
  max=${arr[i]}
  fi
done

echo "maximum number $max"



