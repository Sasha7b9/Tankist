#!/usr/bin/env bash

function ShowHint {
    echo "Usage :"
    echo "       assembly.sh [make|build|full] [debug|release|all]"
}

set -e

if [[ $# -ne 2 ]]
then
    ShowHint
    exit
fi
