set terminal png size 1200,800
set output "graphs/exp3_1/T.png"

set title "T(n)"
set xlabel "n"
set ylabel "T"
set grid
set logscale y
set format y "10^{%L}"
set key top right

plot \
"data/exp3_1/T_mu_1.dat" using 1:2 with lines lw 2 title "mu=1", \
"data/exp3_1/T_mu_2.dat" using 1:2 with lines lw 2 title "mu=2", \
"data/exp3_1/T_mu_4.dat" using 1:2 with lines lw 2 title "mu=4", \
"data/exp3_1/T_mu_6.dat" using 1:2 with lines lw 2 title "mu=6"
