#!/bin/bash

set -e # fail on error

_run()
{
    git checkout master
    git merge development
    git push
    git checkout development
}

_run "$@"
