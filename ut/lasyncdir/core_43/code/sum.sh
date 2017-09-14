#!/bin/bash

sum=0

for file in `find . -name '*.cpp' -o -name '*.h'` ;
do
    count=`wc -l $file |cut -d" " -f1`
    sum=`expr $sum + $count`
done

echo "Sum: " $sum
