set terminal png size 1200,800
set output "graphs/exp2_1/theta.png"

set title "Theta(n)"
set xlabel "n"
set ylabel "Theta"
set grid
set logscale y
set format y "10^{%L}"
set key top right

plot \
"data/exp2_1/theta_mu_1.dat" using 1:2 with lines lw 2 title "mu=1", \
"data/exp2_1/theta_mu_10.dat" using 1:2 with lines lw 2 title "mu=10", \
"data/exp2_1/theta_mu_100.dat" using 1:2 with lines lw 2 title "mu=100", \
"data/exp2_1/theta_mu_1000.dat" using 1:2 with lines lw 2 title "mu=1000"
