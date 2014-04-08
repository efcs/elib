#!/bin/bash

set -e # fail on error

_run()
{
    git checkout staging
    git merge development
    git push
    git checkout development
}

_run "$@"
