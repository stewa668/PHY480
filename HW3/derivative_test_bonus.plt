# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'DERIVATIVE TEST'
set xlabel 'log h'
set ylabel 'log error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-10:0]
set yrange [-15:0]
# set the terminal type to be the screen (which is x11 here)
set term x11

set key right top
eps = 2**-52
set arrow 1 from -4.757778,-15 to -4.757778,0 nohead
# plot the data as well as the fit, with appropriate titles 
plot "derivative_test_bonus.dat" using ($1):($2) title 'b=1 d=1', \
log10( eps/10**x) title 'round-off error trend', \
log10( (1./24.) * 10**(2*x) ) title "approx error trend"

# output the plot to the file derivative_test_plt.ps   
set out "derivative_test_bonus.ps"
set term postscript color enhanced
replot
