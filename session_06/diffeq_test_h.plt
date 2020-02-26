# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'h'
set ylabel 'y(1) error'

set title 'Comparing Differential Equation Algorithms'


# plot \
#   "diffeq_test.dat" using ($1):($2) title 'Euler', \
#   "diffeq_test.dat" using ($1):($3) title '4th order Runge-Kutta', \
#   "diffeq_test.dat" using ($1):($4) title 'exact'

#f1(x) = (b1) * (x**a1)
#fit [.0001:.1] f1(x) "diffeq_test_h.dat" using (($1)):((abs(($3-$5)/$5))) via a1, b1
#fit_title1 = sprintf("f %-+4.1f*x f %-+4.1f*x",a1,b1)

#set xrange [1e-8:1]
#set yrange [1e-10:1]
set logscale
plot \
  "diffeq_test_h.dat" using (($1)):((abs(($2-$5)/$5))) title "Euler", \
  "diffeq_test_h.dat" using (($1)):((abs(($3-$5)/$5))) title "2nd order RK", \
  "diffeq_test_h.dat" using (($1)):((abs(($4-$5)/$5))) title "4th order RK"
