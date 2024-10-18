#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalSingleBitPredictor {

  public:
      BimodalSingleBitPredictor();
      void resetCounters();
      int getPrediction(int *bimodal_bit_table, int index);
      bool isCorrectPrediction(int *bimodal_bit_table, int index, string behavior);
      void updateTable(int *bimodal_bit_table, int index, string behavior);
      int correctCount;
      int branchCount;
};

BimodalSingleBitPredictor::BimodalSingleBitPredictor() {
    resetCounters();
}

void BimodalSingleBitPredictor::resetCounters() {
    correctCount = 0;
    branchCount = 0;
}

int BimodalSingleBitPredictor::getPrediction(int *bimodal_bit_table, int index){
  return bimodal_bit_table[index];
}

bool BimodalSingleBitPredictor::isCorrectPrediction(int *bimodal_bit_table, int index, string behavior) {
  int prediction = getPrediction(bimodal_bit_table, index);
  if(prediction == NOT_TAKEN && behavior == "NT") {
    return true;
  }
  
  if(prediction == TAKEN && behavior == "T") {
    return true;
  }
  return false; 
}

void BimodalSingleBitPredictor::updateTable(int *bimodal_bit_table, int index, string behavior) {
  if(behavior == "T") {
    bimodal_bit_table[index] = TAKEN;
  }
  else {
    bimodal_bit_table[index] = NOT_TAKEN;
  }
}
