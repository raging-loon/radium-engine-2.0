#!/bin/bash

cloc --exclude-dir="CMakeFiles,_deps,thirdparty" ./ --include-ext=cpp,h,c 
