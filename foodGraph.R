#first is file then pdf
options(echo=TRUE)
args <- commandArgs(trailingOnly = TRUE)

graph_food <- function(loc) {
  files <- dir(path=loc, pattern="genome0", full.name = T)
  i = 0;
  col=sample(colors(), length(files))
  endCol <-c()
  pdf(paste(args[2], sep=""))

  for (input in files){
    dtmp <- read.table(input, header=T, sep=",")
    d <- aggregate(dtmp, by=list(dtmp$generation), FUN=sum)
    if (i == 0) {
      plot(d$food, main = "Average food eaten", xlim=c(0,1000), ylim=c(0, 10000), xlab = "Gen", ylab = "Food", type="l",col=col[i])
    } else {
      lines(d$food, main = "", xlim=c(0,1000), ylim=c(0, 10000), xlab = "", ylab = "", type="l",col=col[i])
    }
    endCol <- c(endCol, tail(d, 1)$popavg_food)
    i = i + 1;
  }
  dev.off()

}

graph_food(args[1])
