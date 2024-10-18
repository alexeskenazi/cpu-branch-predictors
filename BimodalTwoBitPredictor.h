#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalTwoBitPredictor {

  public:
      BimodalTwoBitPredictor();
      void resetCounters();
      int getPrediction(int *bimodal_bit_table, int index);
      bool isCorrectPrediction(int *bimodal_bit_table, int index, string behavior);
      void updateTable(int *bimodal_bit_table, int index, string behavior);
      int correctCount;
      int branchCount;
};

BimodalTwoBitPredictor::BimodalTwoBitPredictor() {
    resetCounters();
}

void BimodalTwoBitPredictor::resetCounters() {
    correctCount = 0;
    branchCount = 0;
}

int BimodalTwoBitPredictor::getPrediction(int *bimodal_bit_table, int index){
    // 00: Strongly not taken
    // 01: Weakly not taken
    // 10: Weakly taken
    // 11: Strongly taken
    if(bimodal_bit_table[index] == 0 || bimodal_bit_table[index] == 1) {
        return 0; // Not taken
    }
    else {
        return 1; // Taken
    }
}

bool BimodalTwoBitPredictor::isCorrectPrediction(int *bimodal_bit_table, int index, string behavior) {
    int prediction = getPrediction(bimodal_bit_table, index);
    if(prediction == NOT_TAKEN && behavior == "NT") {
        return true;
    }

    if(prediction == TAKEN && behavior == "T") {
        return true;
    }

    return false;
}

void BimodalTwoBitPredictor::updateTable(int *bimodal_bit_table, int index, string behavior) {
    // 00: Strongly not taken
    // 01: Weakly not taken
    // 10: Weakly taken
    // 11: Strongly taken
    if(behavior == "T") {
        if(bimodal_bit_table[index] == STRONGLY_NOT_TAKEN) { // 
        bimodal_bit_table[index] = WEAKLY_NOT_TAKEN;
        }
        else if(bimodal_bit_table[index] == WEAKLY_NOT_TAKEN) {
        bimodal_bit_table[index] = WEAKLY_TAKEN;
        }
        else if(bimodal_bit_table[index] == WEAKLY_TAKEN) {
        bimodal_bit_table[index] = STRONGLY_TAKEN;
        }
        else if(bimodal_bit_table[index] == STRONGLY_TAKEN) {
        bimodal_bit_table[index] =  STRONGLY_TAKEN;
        }
    }
    
    
    if(behavior == "NT") {
        if(bimodal_bit_table[index] == STRONGLY_NOT_TAKEN) {
        bimodal_bit_table[index] =  STRONGLY_NOT_TAKEN;
        }
        else if(bimodal_bit_table[index] == WEAKLY_NOT_TAKEN) {
        bimodal_bit_table[index] = STRONGLY_NOT_TAKEN;
        }
        else if(bimodal_bit_table[index] == WEAKLY_TAKEN) {
        bimodal_bit_table[index] = WEAKLY_NOT_TAKEN;
        }
        else if(bimodal_bit_table[index] == STRONGLY_TAKEN) {
        bimodal_bit_table[index] = WEAKLY_TAKEN;
        }
  }
}
