#!/bin/bash
echo Executing  $1 challenge with input $2.in ...

if [ -z "$1" ]; then
    echo "Syntax: ./execute.sh <Challenge - REQUIRED> <Test number - OPTIONAL>"
else
    if [ -d "../$1" ]; then
        if [[ -f "../$1/src/$1.cpp" ]]; then
            g++ "../$1/src/$1.cpp" -o "../bin/$1" -Wall "${@:3}"

            if [ -z "$2" ]; then
                "../bin/$1" < "../$1/input/0.in" > "../$1/output/0.out"
            else
                "../bin/$1" < "../$1/input/$2.in" > "../$1/output/$2.out"
            fi

        else
            if [[ -f "../$1/src/$1.c" ]]; then
                gcc "../$1/src/$1.c" -o "../bin/$1" -Wall "${@:3}"

                if [ -z "$2" ]; then
                    "../bin/$1" < "../$1/input/0.in" > "../$1/output/0.out"
                else
                    "../bin/$1" < "../$1/input/$2.in" > "../$1/output/$2.out"
                fi
            else
                echo "Could not find a C/C++ source file for $1."
                ls -la "../$1/src/"
            fi
        fi
    else
        echo "$1 does not exist." 
    fi
fi