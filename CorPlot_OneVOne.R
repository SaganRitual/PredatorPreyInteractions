

args <- commandArgs(trailingOnly = T)

corrGraphs <- function(food, genome, i) {
    library(corrplot)
    prey <- read.table(food, header=T, sep=",")
    prey.ag <-  aggregate(prey, by=list(prey$gen), FUN=mean)

    pred <- read.table(genome, header=T, sep=",")
    pred.ag <- aggregate(pred, by=list(pred$generation), FUN=mean)

    prey.ag$food_num <- NULL
    pred.ag$creature <- NULL
    cors <- cor(prey.ag, pred.ag)
    cors <- cors[,2:12]
    cors <- cors[2:12,]
    png(paste("Gen_Averages_Pred_Corr_Prey_Rep_", i, ".png", sep=""))
    corrplot(cors, method="ellipse", type="full", title=paste("Gen Averages Rep", i))
    dev.off()

}

corrGraphs(args[1], args[2], args[3])
