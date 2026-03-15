set terminal png size 1200,800
set output "graphs/exp2_2/theta.png"

set title "Theta(n)"
set xlabel "n"
set ylabel "Theta"
set grid
set logscale y
set format y "10^{%L}"
set key top right

plot \
"data/exp2_2/theta_lambda_1e-05.dat" using 1:2 with lines lw 2 title "lambda=1e-05", \
"data/exp2_2/theta_lambda_1e-06.dat" using 1:2 with lines lw 2 title "lambda=1e-06", \
"data/exp2_2/theta_lambda_1e-07.dat" using 1:2 with lines lw 2 title "lambda=1e-07", \
"data/exp2_2/theta_lambda_1e-08.dat" using 1:2 with lines lw 2 title "lambda=1e-08", \
"data/exp2_2/theta_lambda_1e-09.dat" using 1:2 with lines lw 2 title "lambda=1e-09"
