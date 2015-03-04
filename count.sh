#!/bin/bash
find ./draco-scales/ ./draco-utilities/ ./draco-source/ -type f \( -name '*.cc' -o  -name '*.h' \) ! -path '*glew*' ! -path '*assimp*' ! -path '*/DevIL/*' ! -path '*/Voxel/*' ! -path '*fltk*' | xargs wc -l
echo "Final count excluding headers:"
find ./draco-scales/ ./draco-utilities/ ./draco-source/ -type f \( -name '*.cc' \) ! -path '*glew*' ! -path '*/assimp/*' ! -path '*/DevIL/*' ! -path '*/Voxel/*' ! -path '*fltk*' | xargs cat | wc -l
