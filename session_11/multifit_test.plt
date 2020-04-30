# plot file for diffeq_oscillations

#Undamped
set term x11 1 title "Cubic Spline"
set timestamp
set title 'Multifit'
set xlabel 't'
set ylabel 'f'
f(x) = 5.04536 * exp(0.10405 * -x) + 1.01925
plot \
"multifit_test.dat" using ($1):($2):($3) title 'data' with yerrorbars, \
f(x) title 'fit'

set out "multifit_test.ps"
set term postscript color enhanced
replot

set out "multifit_test.pdf"
set term pdf
replot
