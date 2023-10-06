#!/bin/bash

which bash
echo flex compilation done below 
flex test.l

echo yacc compilation done below
yacc -d -v test.y

echo gcc compilation done below
gcc y.tab.c -o test

echo syntax analysis of the code below

./test < code.c