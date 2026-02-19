CC=mpicc
CFLAGS=-Wall

all: main

draw: draw.py output_oak/output_net.txt output_oak/output_qpi.txt output_oak/output_sm.txt output_pine/output_net.txt output_pine/output_qpi.txt output_pine/output_sm.txt
	python3 draw.py output_oak/output_net.txt png_oak/net.png
	python3 draw.py output_oak/output_qpi.txt png_oak/qpi.png
	python3 draw.py output_oak/output_sm.txt png_oak/sm.png
	python3 draw.py output_pine/output_net.txt png_pine/net.png
	python3 draw.py output_pine/output_qpi.txt png_pine/qpi.png
	python3 draw.py output_pine/output_sm.txt png_pine/sm.png

clean:
	rm -rf main
