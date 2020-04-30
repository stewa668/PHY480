#
set term x11
set title "Boxas"
set auto x
set yrange [0:6000]
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.9
set xtic rotate by -45 scale 0
#set bmargin 10 
plot 'random_histogram.dat' using 3:xtic(1) ti col, '' u 4 ti col, '' u 6 ti col, '' u 7 ti col
#

set out "boxas.pdf"
set term pdf
replot 
