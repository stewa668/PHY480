# plot file for diffeq_oscillations

#Undamped
set term x11 1 title "Undamped"
set timestamp
set title 'Van der Pol Oscilator'
set xlabel 'x'
set ylabel 'v'
plot \
"ode_test_x0_0.1_v0_0.dat" using ($2):($3) title 'x0 = 0.1', \
"ode_test_x0_1_v0_0.dat" using ($2):($3) title 'x0 = 1.0', \
"ode_test_x0_-1.5_v0_2.dat" using ($2):($3) title 'x0 = -1.5'


set out "ode_test.ps"
set term postscript color enhanced
replot

set out "ode_test.pdf"
set term pdf
replot
