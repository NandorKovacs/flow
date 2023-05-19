#!/bin/bash

for d in */; do
  cd $d
  for f in *; do
    dot -Tsvg "$f"  > ../../textures/$(basename $d)_${f%.*}.svg
  done
  cd ..
done
