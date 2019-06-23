#!/bin/bash
for file in `ls src/*.h`
do
	echo "/////////////////////////////////////////////////////////////////////////////////////////////////////"
	echo $file
	echo "/////////////////////////////////////////////////////////////////////////////////////////////////////"
	n=`sed -n '/ENDHEAD/=' $file`
	head -$n $file
	echo ""
	echo ""
	echo ""
done

nb=0
for file in `ls src/`
do
	nb=$(($nb+`cat src/$file | wc -l`))
	echo $file: `cat src/$file | wc -l`
done
echo ""
echo total: $nb
