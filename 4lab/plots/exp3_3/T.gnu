set terminal png size 1200,800
set output "graphs/exp3_3/T.png"

set title "T(n)"
set xlabel "n"
set ylabel "T"
set grid
set key top right
set yrange [0.2:1.4]

plot \
"data/exp3_3/T_m_1.dat" using 1:2 with lines lw 2 title "m=1", \
"data/exp3_3/T_m_2.dat" using 1:2 with lines lw 2 title "m=2", \
"data/exp3_3/T_m_3.dat" using 1:2 with lines lw 2 title "m=3", \
"data/exp3_3/T_m_4.dat" using 1:2 with lines lw 2 title "m=4"
