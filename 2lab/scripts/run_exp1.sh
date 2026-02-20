#!/bin/bash

TASKS_DIR=tasks
FIRST_EM=1024
SECOND_EM=4096

mkdir -p exp1_result

scripts/generate_tasks.sh
./build/bin/exp1 $TASKS_DIR "$FIRST_EM" NFDH > exp1_result/NFDH_"$FIRST_EM".txt
./build/bin/exp1 $TASKS_DIR "$SECOND_EM" NFDH > exp1_result/NFDH_"$SECOND_EM".txt
./build/bin/exp1 $TASKS_DIR "$FIRST_EM" FFDH > exp1_result/FFDH_"$FIRST_EM".txt
./build/bin/exp1 $TASKS_DIR "$SECOND_EM" FFDH > exp1_result/FFDH_"$SECOND_EM".txt

source venv/bin/activate
python3 scripts/draw.py exp1_result/ a.png
