set term png size 1900,1000 enhanced font "Terminal,10"

set grid

set auto x

set key left top

set ylabel "||Xk - X(k-1)||"
set style data histogram
set style histogram cluster gap 1
set style fill solid
#set boxwidth 1.
set xtic rotate by -45 scale 0
set multiplot layout 2, 2 rowsfirst
set datafile separator ";"
#set xrange [0.00000000001:0.0001]
set yrange [0:0.9]
set xlabel "Valeurs damping"
set ylabel "temps d'éxecution en secondes"
plot "data.dat" u 2:xtic(1) t "" with linespoints   
