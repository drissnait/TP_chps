set term png size 1900,1000 enhanced font "Terminal,10"

set grid

set auto x

set key left top

set ylabel "||Xk - X(k-1)||"
set style data histogram
#set style fill solid border -1
#set boxwidth 0.9
#set xtic rotate by -45 scale 0
set multiplot layout 2, 2 rowsfirst
set datafile separator ";"
set yrange [0:0.9]
set xrange [0:10]
set xlabel "iteration"
set ylabel "||Xk - X(k-1)||"
set title "'||Xk - X(k-1)||' selon les itérations"
plot "data.dat" u 2:xtic(1) t "" with linespoints
