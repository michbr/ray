#!/bin/bash
find ./draco-scales/ ./draco-utilities/ ./draco-source/ -type f \( -name '*.cc' -o  -name '*.h' \) ! -path '*/Voxel/*' ! -path '*fltk*' | xargs wc -l
