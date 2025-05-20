#!/bin/bash

echo -n "size of array : "
read n 

declare -a arr

echo "Enter $n elements:"

for((i=0;i<n;i++))
do
  read value
  arr[i]=$value
done

echo "Elemets are :"
for((i=0;i<n;i++))
do
  echo "Element [$i] = ${arr[i]}"
done



