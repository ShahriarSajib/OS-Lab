#!/bin/bash
echo "enter 3 numbers : "
read a b c
sum=$((a+b+c))
avg=$(awk "BEGIN {printf \"%.2f\", $sum/3}")
echo "avg is : $avg"
 
