#!/bin/bash

echo -n "Enter a number : "
read n

if((n <= 1)); then
  echo "$n is not a prime"
  exit 0
fi

is_prime=1

for((i=2; i*i<=n; i++))
  do
    if((n%i == 0)); then
      is_prime=0
      break
    fi
done

if ((is_prime)); then
  echo "$n is a prime number"
else
  echo "$n is not a prime number"
fi
 
