#first is file then pdf
options(echo=TRUE)
args <- commandArgs(trailingOnly = TRUE)

graph_food <- function(loc) {
  files <- dir(path=loc, pattern="foodavgavg", full.name = T)
  i = 0;
  col=sample(colors(), length(files))
  endCol <-c()
  pdf(paste(args[2], sep=""))

  for (input in files){
    d <- read.table(input, header=T, sep=",")
    if (i == 0) {
      plot(d$popavg_food, main = "Average food eaten", xlim=c(0,1000), ylim=c(0, 100), xlab = "Gen", ylab = "Food", type="l",col=col[i])
    } else {
      lines(d$popavg_food, main = "", xlim=c(0,1000), ylim=c(0, 100), xlab = "", ylab = "", type="l",col=col[i])
    }
    endCol <- c(endCol, tail(d, 1)$popavg_food)
    i = i + 1;
  }
  dev.off()

}

graph_food(args[1])
