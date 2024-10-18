#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalThreeBitPredictor {

  public:
      BimodalThreeBitPredictor();
      void resetCounters();
      int getPrediction(int *bimodal_bit_table, int index);
      bool isCorrectPrediction(int *bimodal_bit_table, int index, string behavior);
      void updateTable(int *bimodal_bit_table, int index, string behavior);
      int correctCount;
      int branchCount;
};

BimodalThreeBitPredictor::BimodalThreeBitPredictor() {
    resetCounters();
}

void BimodalThreeBitPredictor::resetCounters() {
    correctCount = 0;
    branchCount = 0;
}

int BimodalThreeBitPredictor::getPrediction(int *bimodal_bit_table, int index){
    if(bimodal_bit_table[index] == THREE_STRONGLY_TAKEN) { // 
      return TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_TAKEN) {
      return TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_WEAKLY_TAKEN) {
      return TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_STRONGLY_NOT_TAKEN) {
      return NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_NOT_TAKEN) {
      return NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_WEAKLY_NOT_TAKEN) {
      return NOT_TAKEN;
    }
    return NOT_TAKEN;
}

bool BimodalThreeBitPredictor::isCorrectPrediction(int *bimodal_bit_table, int index, string behavior) {
    int prediction = getPrediction(bimodal_bit_table, index);
    if(prediction== NOT_TAKEN && behavior == "NT") {
        return true;
    }
    
    if(prediction == TAKEN && behavior == "T") {
        return true;
    }
    return false;
}

void BimodalThreeBitPredictor::updateTable(int *bimodal_bit_table, int index, string behavior) {
     if(behavior == "T") {
    if(bimodal_bit_table[index] == THREE_STRONGLY_TAKEN) { 
      bimodal_bit_table[index] = THREE_STRONGLY_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_TAKEN) {
      bimodal_bit_table[index] = THREE_STRONGLY_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_WEAKLY_TAKEN) {
      bimodal_bit_table[index] = THREE_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_STRONGLY_NOT_TAKEN) {
      bimodal_bit_table[index] = THREE_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_NOT_TAKEN) {
      bimodal_bit_table[index] = THREE_WEAKLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_WEAKLY_NOT_TAKEN) {
      bimodal_bit_table[index] = THREE_WEAKLY_TAKEN;
    }
  }
  
  if (behavior == "NT") {
    if(bimodal_bit_table[index] == THREE_STRONGLY_TAKEN) {
      bimodal_bit_table[index] = THREE_TAKEN;
    }
    // This one is not symmetric, we need to handle it differently
    // based ont the definition in the doc.
    else if(bimodal_bit_table[index] == THREE_TAKEN) {
      bimodal_bit_table[index] = THREE_WEAKLY_NOT_TAKEN; /// As defined in the doc
    }
    else if(bimodal_bit_table[index] == THREE_WEAKLY_TAKEN) {
      bimodal_bit_table[index] = THREE_WEAKLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_STRONGLY_NOT_TAKEN) {
      bimodal_bit_table[index] = THREE_STRONGLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_NOT_TAKEN) {
      bimodal_bit_table[index] = THREE_STRONGLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == THREE_WEAKLY_NOT_TAKEN) {
      bimodal_bit_table[index] = THREE_NOT_TAKEN;
    }
  }
}
