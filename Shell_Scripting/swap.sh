#!/bin/bash

echo -n "Enter 2 numbers : "
read a b

echo "Before Swapping : a=$a, b=$b"

#swapping without tem variable

a=$((a+b))
b=$((a-b))
a=$((a-b))

echo "After swapping : a=$a, b=$b"
