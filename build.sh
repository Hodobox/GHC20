#!/bin/bash
if [ ! -d "outputs/" ]; then
    mkdir "outputs"
fi

g++ -std=c++17 code/main.cpp code/includes.h -O2 -o sol