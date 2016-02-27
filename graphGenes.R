#first is file then pdf
options(echo=F)
args <- commandArgs(trailingOnly = TRUE)

graph_weights <- function(loc) {
  f <- dir(path=loc, pattern = "genome0", full.names = T)
  s <- lapply(f, function(i) { d=read.table(i, header=T, sep=","); print(i); aggregate(d, by=list(d$generation), FUN=mean)})
  
  i = 0
  col = sample(colors(), length(s))

  valueRC <- ceiling((ncol(s[[1]])-4)^.5)
  #png(paste(loc, "geneValues.png"), 640,480, res=60)
  pdf(paste(args[2], sep=""))
  
  par(mfrow=c(2, valueRC))
  
  start = 5
  ymin = -100
  ymax = 100
  
  for (i in start:ncol(s[[1]])) {
    tmpCheck =0
    for (r in s) {
      if (tmpCheck == 0) {
        plot(r[,i], ylim=c(ymin, ymax), main=paste("Weights for gene", i-start), xlab = "Gen", ylab = "Gene Weight", col=col[tmpCheck], type="l")
      } else {
        lines(r[,i], ylim=c(ymin, ymax), main="", xlab="", ylab="", col=col[tmpCheck], type="l")
      }
      tmpCheck = tmpCheck + 1
    }
  }
  dev.off()
}


graph_weights(args[1])
