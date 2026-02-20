#!/bin/bash

mkdir -p tasks

start=1
for ((i = 500; i <= 5000; i += 500)); do
    python3 scripts/convert_data.py data/LLNL-Thunder-2007-1.1-cln.swf tasks "$i" "$start"
    ((start += i))
done
