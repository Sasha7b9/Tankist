#!/usr/bin/env bash

# Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
function ShowHint {
    echo "    Usage:"
    echo "          ./start.sh [ master | uploader | all ]"
}

function Start {
    if [ $1 -eq 1 ]
    then
        dir=$PWD
        ./stop.sh $3
        cd ../../Tankist/out/debug
        ./$2 &
        cd $dir
    fi
}

# Start here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set -e              # Немедленно выйти, если команда завершается с ненулевым статусом

runMaster=0
runUploader=0

if [[ $# -ne 1 ]]
then
    ShowHint
    exit
fi

case $1 in
    "master"   ) runMaster=1   ;;

    "uploader" ) runUploader=1 ;;

    "all"      ) runMaster=1
                 runUploader=1 ;;

    *          ) ShowHint
                 exit          ;;
esac

Start $runMaster Master master
Start $runUploader Uploader uploader

