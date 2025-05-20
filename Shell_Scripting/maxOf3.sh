#!/bin/bash

echo -n "enter 3 numbers : "
read a b c

max=$a

if((b>max)); then max=$b 
fi

if((c>max)); then max=$c
fi

echo "maximum number is : $max"
