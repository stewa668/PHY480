# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'WAVEFUNCTIONS'
set xlabel 'r'
set ylabel 'Psi'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [0:10]
set yrange [0:1]
# set the terminal type to be the screen (which is x11 here)
set term x11

set key right top
# plot the data as well as the fit, with appropriate titles 
plot "b1_1.dat" using ($1):($2) title 'b=1 d=1', \
"b1_5.dat" using ($1):(-$2) title 'b=1 d=5', \
"b1_10.dat" using ($1):(-$2) title 'b=1 d=10', \
"b1_20.dat" using ($1):($2) title 'b=1 d=20', \
"b5_1.dat" using ($1):($2) title 'b=5 d=1', \
"b5_5.dat" using ($1):($2) title 'b=5 d=5', \
"b5_10.dat" using ($1):($2) title 'b=5 d=10', \
"b5_20.dat" using ($1):(-$2) title 'b=5 d=20', \
2*x*exp(-x) title 'exact'
# output the plot to the file derivative_test_plt.ps   
set out "eigen_basis.ps"
set term postscript color enhanced
replot
