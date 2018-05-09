#!/bin/bash


echo '|# SONGS |  PARTY(MIN) | DURATION(ns)|'
echo '|------------------------------------|'

for numSongs in 200 500 1000 1800; do
    for partyLength in 30 60 180 300; do
        begin=$(date +%s%N)
        #echo $begin
        echo $partyLength $numSongs | ./inputs 1> /dev/null
        end=$(date +%s%N)
        duration=$(( end - begin))
        echo '|' $numSongs '|' $partyLength '|' $duration '|'
        #echo '****' 
    done
done    

echo '|-------|-------------|----------|'
