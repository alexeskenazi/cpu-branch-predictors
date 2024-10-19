#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalTwoBitPredictor {

  public:
      BimodalTwoBitPredictor();
      void setTableSize(int size);
      void reset();
      unsigned int getIndex(unsigned long long addr);
      int getPrediction(unsigned long long addr);
      bool isCorrectPrediction(int prediction, string behavior);
      void updatePredictor(unsigned long long addr, string behavior);
      int correctCount;
      int branchCount;
    private:
       int bimodal_bit_table[MAX_TABLE_SIZE];
       int table_size;
};

BimodalTwoBitPredictor::BimodalTwoBitPredictor() {
    reset();
}

void BimodalTwoBitPredictor::setTableSize(int size) {
  table_size = size;
}

void BimodalTwoBitPredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      bimodal_bit_table[i] = 0;
    }
}

unsigned int BimodalTwoBitPredictor::getIndex(unsigned long long addr) {
  return addr % table_size;
}

int BimodalTwoBitPredictor::getPrediction(unsigned long long addr){
    unsigned int index = getIndex(addr);

    // 00: Strongly not taken -> not taken
    // 01: Weakly not taken -> not taken
    // 10: Weakly taken -> taken
    // 11: Strongly taken -> taken
    if(bimodal_bit_table[index] == STRONGLY_NOT_TAKEN || bimodal_bit_table[index] == WEAKLY_NOT_TAKEN) {
        return NOT_TAKEN; // Not taken
    }
    else {
        return TAKEN; // Taken
    }
}

bool BimodalTwoBitPredictor::isCorrectPrediction(int prediction, string behavior) {
    if(prediction == NOT_TAKEN && behavior == "NT") {
        return true;
    }

    if(prediction == TAKEN && behavior == "T") {
        return true;
    }

    return false;
}

void BimodalTwoBitPredictor::updatePredictor(unsigned long long addr, string behavior) {
  unsigned int index = getIndex(addr);
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
