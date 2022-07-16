#!/bin/bash

rougefonce='\e[0;31m'
vertfonce='\e[0;32m'
vertclair='\e[1;32m'
bleufonce='\e[0;34m'
neutre='\e[0;m'

declare err=(
3 4 6 7 10 14
)

x=0
echo -e "${rougefonce}Start print tests${neutre}\n"
ls ./SourceTest/ | while read -r line;
do
    echo -e "${bleufonce}Test $x ${neutre}$line"
    ../abstractVM ./SourceTest/$line &> test.txt
    diff test.txt ./ExpectedTest/$line
    if [ $? -eq 0 ]; then
        echo -e "${vertclair}Test $x ${vertfonce}OK${neutre}"
    else
        echo -e "${vertclair}Test $x ${rougefonce}KO\\n${neutre}"
    fi
    # if (( x == 10 )); then
    #     break
    # else
        x=$((x+1))
    # fi
done
echo -e "\n${rougefonce}Start return tests${neutre}\n"
x=0
in=0
ret=0
ls ./SourceTest/ | while read -r line;
do
    in=0
    echo -e "${bleufonce}Test $x ${neutre}$line"
    ../abstractVM ./SourceTest/$line &> test.txt
    ret=$?
    for key in "${!err[@]}"; do
        if [[ "${x}" == "${err[${key}]}" ]]; then
            in=1
        fi
    done
    if ((in == 1)); then
        if ((ret == 84)); then
            echo -e "${vertclair}Test $x ${vertfonce}OK${neutre}"
        else
            echo -e "${vertclair}Test $x ${rougefonce}KO\\n${neutre}"
        fi
        in=0
    else
        if ((ret == 0)); then
            echo -e "${vertclair}Test $x ${vertfonce}OK${neutre}"
        else
            echo -e "${vertclair}Test $x ${rougefonce}KO\\n${neutre}"
        fi
    fi
    # if (( x == 10 )); then
    #     break
    # else
        x=$((x+1))
    # fi
done
total=0
act=0
x=0
in=0
preced=0
echo -e "\n${rougefonce}Start valgrind tests${neutre}\n"
ls ./SourceTest/ | while read -r line;
do
    echo -e "${bleufonce}Test $x ${neutre}$line"
    rest=$(valgrind ../abstractVM ./SourceTest/test00.txt 2>&1 | grep "total heap usage:")
    parsed=$(echo $rest | tr " " "\n")
    for i in $parsed; do
        if [[ "$i" == "allocs," ]]; then
            total=$preced
        elif [[ "$i" == "frees," ]]; then
            act=$preced
        fi
        preced=$i
    done
    if [[ "$act" == "$total" ]]; then
        echo -e "${vertclair}Test $x ${vertfonce}OK${neutre}"
    else
        echo -e "${vertclair}Test $x ${rougefonce}KO $act frees $total allocs\\n${neutre}"
    fi
    x=$((x+1))
done
echo -e "\nEnd of tests"