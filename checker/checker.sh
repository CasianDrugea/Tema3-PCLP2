#!/bin/bash

test_all()
{
    cp -r task-1/ ../src/
    cp -r task-2/ ../src/
    cp -r task-3/ ../src/
    cp -r task-4/ ../src/

    python3 checker.py --all
}

test_all

