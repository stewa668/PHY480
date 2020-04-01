#  file: derivative_test.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
# 
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Test of Numerical Derivatives using ax^b'
set xlabel 'log10(mesh size)'
set ylabel 'relative error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-10:1]
set yrange [-14:0.5]

# fit the curve
f1(x) = a1*x + b1
f2(x) = a2*x + b2
f3(x) = a3*x + b3
f4(x) = a4*x + b4
fit [-7:-1] f1(x) "derivative_test.dat" using ($1):($2) via a1,b1 
fit_title1 = sprintf("f %-+4.1f*x %-+4.1f",a1,b1)
fit [-4:-1] f2(x) "derivative_test.dat" using ($1):($3) via a2,b2
fit_title2 = sprintf("c %-+4.1f*x %-+4.1f",a2,b2)
fit [-2:-1] f3(x) "derivative_test.dat" using ($1):($4) via a3,b3
fit_title3 = sprintf("ex %-+4.1f*x %-+4.1f",a3,b3)
fit [-1.4:0] f4(x) "derivative_test.dat" using ($1):($5) via a4,b4
fit_title4 = sprintf("ex2 %-+4.1f*x %-+4.1f",a4,b4)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "derivative_test.dat" using ($1):($2) title 'forward difference', \
     "derivative_test.dat" using ($1):($3) title 'central derivative', \
     "derivative_test.dat" using ($1):($4) title 'ex central derivat' ,\
     "derivative_test.dat" using ($1):($5) title 'ex2 central derivat' ,\
     a1*x + b1 title fit_title1, a2*x + b2 title fit_title2, a3*x + b3 title fit_title3, a4*x + b4 title fit_title4

# output the plot to the file derivative_test_plt.ps   
set out "derivative_test_plt.ps"
set term postscript color enhanced
replot
