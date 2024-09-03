	#!/bin/bash

cloc --exclude-dir="CMakeFiles,_deps,thirdparty,.vs" ./ --include-ext=cpp,h,c,glsl
