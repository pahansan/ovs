set terminal png size 1200,800
set output "graphs/exp3_2/T.png"

set title "T(n)"
set xlabel "n"
set ylabel "T"
set grid
set key top right
set yrange [0.95:1.2]

plot \
"data/exp3_2/T_lambda_1e-05.dat" using 1:2 with lines lw 2 title "lambda=1e-05", \
"data/exp3_2/T_lambda_1e-06.dat" using 1:2 with lines lw 2 title "lambda=1e-06", \
"data/exp3_2/T_lambda_1e-07.dat" using 1:2 with lines lw 2 title "lambda=1e-07", \
"data/exp3_2/T_lambda_1e-08.dat" using 1:2 with lines lw 2 title "lambda=1e-08", \
"data/exp3_2/T_lambda_1e-09.dat" using 1:2 with lines lw 2 title "lambda=1e-09"
