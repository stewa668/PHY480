#  file: error_log.plt

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Relative Error in Log(10)'
set xlabel 'log10(N)'
set ylabel 'log10(Err)'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
#set xrange [-10:-1]
#set yrange [-14:0]

# fit the curve
f1(x) = a1*x + b1
fit [0.1:5] f1(x) "error_log_bonus.dat" using ($1):($2) via a1, b1
fit_title1 = sprintf("%-+4.1f*x %-+4.1f",a1, b1)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles
plot "error_log_bonus.dat" using ($1):($2) title 'Milne', \
     a1*x + b1 title fit_title1

set out "error_log_bonus.ps"
set term postscript color enhanced
replot
set out "error_log_bonus.pdf"
set term pdf
replot
