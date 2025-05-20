#!/bin/bash

echo -n "Enter filename to create : "
read filename

if [ -e "$filename" ]; then
   echo "file already exists."
else
   touch "$filename"
   echo  "File : '$filename' created"
fi
