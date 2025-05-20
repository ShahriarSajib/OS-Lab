#!/bin/bash
echo "Enter a number : "
read n
fact=1
if ((n < 0)); then
  echo "Factorial is not defined for negative numbers."
  exit 1
fi
for ((i=1; i<=n; i++))
do
  fact=$((fact*i))
done
echo "Factorial of $n is = $fact"
