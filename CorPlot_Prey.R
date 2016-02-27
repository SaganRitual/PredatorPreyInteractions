args <- commandArgs(trailingOnly = T)

corrGraphs <- function(food, genome, i) {
    library(corrplot)
    prey <- read.table(food, header=T, sep=",")
    prey.ag <-  aggregate(prey, by=list(prey$gen), FUN=mean)


    prey.ag$food_num <- NULL
    cors <- cor(prey.ag)
    cors <- cors[,2:12]
    cors <- cors[2:12,]
    png(paste("Gen_Averages_Prey_Coor_Rep_", i, ".png", sep=""))
    corrplot(cors, method="ellipse", type="lower", title=paste("Gen Averages Rep", i))
    dev.off()

}

corrGraphs(args[1], args[2], args[3])
