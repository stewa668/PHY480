# plot file for diffeq_test_exp_back
set timestamp

set xlabel 't'
set ylabel 'y(t)'

set title 'Comparing Differential Equation Algorithms'


# plot \
#   "diffeq_test.dat" using ($1):($2) title 'Euler', \
#   "diffeq_test.dat" using ($1):($3) title '4th order Runge-Kutta', \
#   "diffeq_test.dat" using ($1):($4) title 'exact'

# set xrange [0.1:3]
plot \
  "diffeq_test_x.dat" using 1:2 title "4RK", \
  "diffeq_test_x.dat" using 1:3 title "Exact"
