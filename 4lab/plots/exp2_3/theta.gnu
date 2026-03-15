set terminal png size 1200,800
set output "graphs/exp2_3/theta.png"

set title "Theta(n)"
set xlabel "n"
set ylabel "Theta"
set grid
set logscale y
set format y "10^{%L}"
set key top right

plot \
"data/exp2_3/theta_m_1.dat" using 1:2 with lines lw 2 title "m=1", \
"data/exp2_3/theta_m_2.dat" using 1:2 with lines lw 2 title "m=2", \
"data/exp2_3/theta_m_3.dat" using 1:2 with lines lw 2 title "m=3", \
"data/exp2_3/theta_m_4.dat" using 1:2 with lines lw 2 title "m=4"
