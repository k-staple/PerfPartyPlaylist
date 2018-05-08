#!/bin/sh

TIMES="10 20 50 100 200 500 1000"

    
echo '| N               | Elapsed Time    | Memory     |'
echo '|-----------------|-----------------|------------|'

for nitem in $TIMES; do
    CREATEFILE=$(./data/generate_map.py $TIMES > outputfile.txt)
     
    MEASURE=$(measure

for backend in $BACKENDS; do
    	if [ $backend = "unsorted" -o $backend = "sorted" ] && [ $nitem -gt 10000 ]; then
	    insert="INFINITY"
	    search="INFINITY"
	else
	    benchs=$(./timeout.py -t $TIMEOUT ./map_bench -b $backend -n $nitem)
	    if [ $? -eq 0 ]; then
		insert=$(echo $benchs | awk '/Insert/ { print $2 }')
		search=$(echo $benchs | awk '/Search/ { print $5 }')
	    else
		insert="INFINITY"
		search="INFINITY"
	    fi
	fi
	printf "| %15s | %15 d | %10.4f | \n" $backend $nitem $insert $search
    done
done
