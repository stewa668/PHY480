# plot file for diffeq_oscillations

#Undamped
set term x11 1 title "Undamped"
set timestamp
set title 'Undamped Position'
set xlabel 't'
set ylabel 'theta'
plot "simple_pendulum_0.dat" using ($1):($2) title 'V(x)' with lines

set term x11 2 title "Undamped_P"
set timestamp
set title 'Undamped Phase'
set xlabel 'theta'
set ylabel 'd_theta'
plot "simple_pendulum_0.dat" using ($2):($3) title 'V(x)' with lines

#Damped
set term x11 3 title "Damped"
set timestamp
set title 'Damped Position'
set xlabel 't'
set ylabel 'theta'
plot "simple_pendulum_0.25.dat" using ($1):($2) title 'V(x)' with lines

set term x11 4 title "Damped_P"
set timestamp
set title 'Damped Phase'
set xlabel 'theta'
set ylabel 'd_theta'
plot "simple_pendulum_0.25.dat" using ($2):($3) title 'V(x)' with lines

#Critdamped
set term x11 5 title "Critdamped"
set timestamp
set title 'Critdamped Position'
set xlabel 't'
set ylabel 'theta'
plot "simple_pendulum_2.dat" using ($1):($2) title 'V(x)' with lines

set term x11 6 title "Critdamped_P"
set timestamp
set title 'Critdamped Phase'
set xlabel 'theta'
set ylabel 'd_theta'
plot "simple_pendulum_2.dat" using ($2):($3) title 'V(x)' with lines

#Overdamped
set term x11 7 title "Overdamped"
set timestamp
set title 'Overdamped Position'
set xlabel 't'
set ylabel 'theta'
plot "simple_pendulum_4.dat" using ($1):($2) title 'V(x)' with lines

set term x11 8 title "Overdamped_P"
set timestamp
set title 'Overdamped Phase'
set xlabel 'theta'
set ylabel 'd_theta'
plot "simple_pendulum_4.dat" using ($2):($3) title 'V(x)' with lines
