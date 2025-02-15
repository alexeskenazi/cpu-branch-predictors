# Specifiy the target
all: predictors

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
predictors: predictors.o 
	g++ predictors.o -o predictors

# Specify how the object files should be created from source files
predictors.o: predictors.cpp predictors.h \
    BimodalSingleBitPredictor.h BimodalTwoBitPredictor.h \
    BimodalThreeBitPredictor.h GsharePredictor.h \
    TournamentPredictor.h BinaryToStringUtil.h \
    PredictorBase.h AlwaysTakenPredictor.h \
    AlwaysNotTakenPredictor.h
	g++ -c predictors.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o predictors
