#!/bin/bash

BUILD_DIR=build
FILE=GameOfLife

[ ! -d $BUILD_DIR ] && mkdir $BUILD_DIR ; cd build || exit

cmake ..
make

if [ $? -eq 0 ]
  then
    printf "./%s/%s built successfully. Run with default values? (Y/n) " $BUILD_DIR $FILE
    read -r answer
    case $answer in
      y|yes|"") ./$FILE 11 55 55 ;;
      n|no) exit ;;
    esac
fi
