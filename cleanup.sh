#!/bin/bash
for f in *.yaml; do
  d=${f%%\.yaml}
  if [ -d "$d" ]; then
    echo "Cleaning up $d"
    rm -r "$d"
  fi
done