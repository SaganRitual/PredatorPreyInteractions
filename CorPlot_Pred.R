

args <- commandArgs(trailingOnly = T)

corrGraphs <- function(food, genome, i) {
    library(corrplot)

    pred <- read.table(genome, header=T, sep=",")
    pred.ag <- aggregate(pred, by=list(pred$generation), FUN=mean)

    pred.ag$creature <- NULL
    cors <- cor(pred.ag)
    cors <- cors[,2:12]
    cors <- cors[2:12,]
    png(paste("Gen_Averages_Pred_Corr_Rep_", i, ".png", sep=""))
    corrplot(cors, method="ellipse", type="lower", title=paste("Gen Averages Rep", i))
    dev.off()

}

corrGraphs(args[1], args[2], args[3])
