#!/bin/bash
g++ -c ../src/core_dll.cpp -std=gnu++11 -o ../tmp/core.o

g++ -c ../src/osgb_dll.cpp -std=gnu++11 -o ../tmp/osgb.o

g++ -c ../src/os2gps.cpp -std=gnu++11 -o ../tmp/os2gps.o
g++ -o ../bin/os2gps.exe ../tmp/os2gps.o -static-libstdc++ -static-libgcc -L. ../tmp/osgb.o ../tmp/core.o

../bin/os2gps.exe
