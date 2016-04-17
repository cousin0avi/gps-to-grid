#!/bin/bash
g++ -c -DBUILDING_CORE_DLL ../src/core_dll.cpp -std=gnu++11 -o ../tmp/core_dll.o
g++ -shared -o ../bin/core.dll ../tmp/core_dll.o

g++ -c -DBUILDING_OSGB_DLL ../src/osgb_dll.cpp -std=gnu++11 -o ../tmp/osgb_dll.o
g++ -shared -o ../bin/osgb.dll ../tmp/osgb_dll.o  -L. ../bin/core.dll

g++ -c -DBUILDING_HIGH_PRECISION_OSGB_DLL ../src/high_precision_osgb_dll.cpp -std=gnu++11 -o ../tmp/high_precision_osgb_dll.o
g++ -shared -o ../bin/high_precision_osgb.dll ../tmp/high_precision_osgb_dll.o

g++ -c ../src/gps2os.cpp -std=gnu++11 -o ../tmp/gps2os.o
g++ -o ../bin/gps2os.exe ../tmp/gps2os.o -L. ../bin/osgb.dll ../bin/core.dll

../bin/gps2os.exe
