#!/bin/bash

#Looking for the directory
WhereToGo=${1}

[[ ! -d ${WhereToGo} ]] && echo "Not a valid directory!" && return 6

source Splitter.sh $1 && echo "******************** Done with Splitter.sh ********************" || return 5
source Filter.sh $1 && echo "******************** Done with Filter.sh ********************" || return 4
source Transfer.sh $1 && echo "******************** Done with Transfer.sh ********************" || return 3
source Analysis.sh $1 && echo "******************** Done with Analysis.sh ********************" || return 2

return 0
