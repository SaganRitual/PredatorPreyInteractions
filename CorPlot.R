

args <- commandArgs(trailingOnly = T)

corrGraphs <- function(loc) {
    library(corrplot)
    prey <- dir(path=loc, pattern = "foodGenome_0", full.names = T)
    prey.ag <- lapply(prey, function(i) { d=read.table(i, header=T, sep=","); print(i); aggregate(d, by=list(d$gen), FUN=mean)})

    pred <- dir(path=loc, pattern = "genome_0", full.names = T)
    pred.ag <- lapply(pred, function(i) { d=read.table(i, header=T, sep=","); print(i); aggregate(d, by=list(d$generation), FUN=mean)})

    for (i in 1:length(pred)) {
        prey.ag[i]$food_num <- NULL
        pred.ag[i]$creature <- NULL
        cors <- cor(prey.ag[i], pred.ag[i])
        cors <- cors[,2:12]
        cors <- cors[2:12,]
        png(paste("Gen_Averages_Pred_Corr_Prey_Rep_", i, ".png", sep=""))
        corrplot(cors, method="ellipse", type="full", title=paste("Gen Averages Rep", i))
        dev.off()
    }
}
corrGraphs(args[1])
