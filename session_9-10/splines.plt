# plot file for diffeq_oscillations

#Undamped
set term x11 1 title "Cubic Spline"
set timestamp
set title 'Splines'
set xlabel 'E (MeV)'
set ylabel 'sigma'
plot \
"splines.dat" using ($1):($2) title 'Exact' with lines, \
"splines.dat" using ($1):($3) title 'Linear Spline', \
"splines.dat" using ($1):($4) title 'Poly Spline', \
"splines.dat" using ($1):($5) title 'Cubic Spline' with linespoints


set out "splines.ps"
set term postscript color enhanced
replot

set out "splines.pdf"
set term pdf
replot
