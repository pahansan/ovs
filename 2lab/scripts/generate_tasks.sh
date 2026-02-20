#!/bin/bash

mkdir -p tasks
for ((i = 500; i <= 5000; i += 500)); do
    ./build/bin/generate_file_with_tasks tasks "$i" 100 1024
    ./build/bin/generate_file_with_tasks tasks "$i" 100 4096
done
