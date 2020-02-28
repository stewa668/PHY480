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
fit [0.3:5] f1(x) "error_log.dat" using ($1):($2) via a1, b1
fit_title1 = sprintf("%-+4.1f*x %-+4.1f",a1, b1)
f2(x) = a2*x + b2
fit [0.3:5] f2(x) "error_log.dat" using ($1):($3) via a2, b2
fit_title2 = sprintf("%-+4.1f*x %-+4.1f",a2, b2)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles
plot "error_log.dat" using ($1):($2) title 'Simpson', \
     "error_log.dat" using ($1):($3) title 'Melne', \
     "error_log.dat" using ($1):($4) title 'GSL', \
     a1*x + b1 title fit_title1, \
     a2*x + b2 title fit_title2

set out "error_log.ps"
set term postscript color enhanced
replot
set out "error_log.pdf"
set term pdf
replot
