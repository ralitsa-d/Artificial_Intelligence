showPlot = function(N = 2, filenames)
{
  par(mfrow=c(1,2))
  for(i in 1:N){
    cl = read.csv(filenames[i], header = FALSE, sep = " ", dec = ".")
    plot(cl)
  }
}

#showPlot(8, c('cl1.txt', 'cl2.txt', 'cl3.txt', 'cl4.txt', 'cl5.txt', 'cl6.txt', 'cl7.txt', 'cl8.txt'))
#showPlot(2, c('cluster1.txt', 'cluster2.txt'))
#showPlot(3, c('c1.txt', 'c2.txt', 'c3.txt'))
#showPlot(2, c('b1.txt', 'b2.txt'))
showPlot(4, c('d1.txt', 'd2.txt', 'd3.txt', 'd4.txt'))
#showPlot(8, c('e1.txt', 'e2.txt', 'e3.txt', 'e4.txt', 'e5.txt', 'e6.txt', 'e7.txt', 'e8.txt'))

