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
set title 'eigen boiz'
set xlabel 'log10(dim)'
set ylabel 'time log'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
#set xrange [-10:-1]
#set yrange [-14:0]

# fit the curve
f1(x) = a1*x + b1
fit [2:4] f1(x) "eigen_test.dat" using ($1):($2) via a1, b1
fit_title1 = sprintf("f %-+4.1f*x",a1)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "eigen_test.dat" using ($1):($2) title 'hsfhsfh', \
     a1*x + b1 title fit_title1

# output the plot to the file derivative_test_plt.ps   
set out "eigen_test_plt.ps"
set term postscript color enhanced
replot
