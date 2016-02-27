#first is file then pdf
options(echo=TRUE)
args <- commandArgs(trailingOnly = TRUE)


graph_food <- function(loc) {
  files <- dir(path=loc, pattern="foodavgavg", full.name = T)
  i = 0;
  col=sample(colors(), 1)
  endCol <-c()
  pdf(paste(args[2], ".pdf", sep=""), 25, 25)
  par(mfrow=c(5,5))

  for (input in files){
    print(input);
    inputReg <- input
    inputReg2 <- input
    inputBrown <- gsub("food", "brownain", inputReg);
    inputRandom <- gsub("food", "random", inputReg2); 

    d <- read.table(input, header=T, sep=",")
    b <- read.table(inputBrown, header=T, sep=",")
    r <- read.table(inputRandom, header = T, sep=",")

      plot(d$popavg_food, main = paste("Replicate", i , "Food Compare"), xlim=c(0,1000), ylim=c(0, 100), xlab = "Gen", ylab = "Food", type="l",col=col[1])
      #lines(r$popavg_food, main = "", xlim=c(0,1000), ylim=c(0, 100), xlab = "", ylab = "", type="l",col=col[2])
      #lines(b$popavg_food, main = "", xlim=c(0,1000), ylim=c(0, 100), xlab = "", ylab = "", type="l",col=col[3])
      #legend("bottomright", c("NN", "Random", "Brown"), col=col, lty=c(1,1))
      legend("bottomright", c("NN"), col=col, lty=c(1,1))
    i = i + 1
  }

  dev.off()

}

graph_food(args[1]);
