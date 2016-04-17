#!/bin/bash
g++ -c ../src/core_dll.cpp -std=gnu++11 -o ../tmp/core.o

g++ -c ../src/osgb_dll.cpp -std=gnu++11 -o ../tmp/osgb.o

g++ -c ../src/gps2os.cpp -std=gnu++11 -o ../tmp/gps2os.o
g++ -o ../bin/gps2os.exe ../tmp/gps2os.o -static-libstdc++ -static-libgcc -L. ../tmp/osgb.o ../tmp/core.o

../bin/gps2os.exe
