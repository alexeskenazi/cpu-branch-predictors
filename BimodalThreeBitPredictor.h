#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalThreeBitPredictor {

    public:
    BimodalThreeBitPredictor();
    void setTableSize(int size);
        void reset();
      unsigned int getIndex(unsigned long long addr);
        int getPrediction(unsigned long long addr);
        bool isCorrectPrediction(int prediction, int actualBranch);
        void updatePredictor(unsigned long long addr, int actualBranch);
        int correctCount;
        int branchCount;
    private:
        int bimodal_bit_table[MAX_TABLE_SIZE];
        int table_size;
};

BimodalThreeBitPredictor::BimodalThreeBitPredictor() {
    reset();
}

void BimodalThreeBitPredictor::setTableSize(int size) {
  table_size = size;
}

void BimodalThreeBitPredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      bimodal_bit_table[i] = 0;
    }
}

unsigned  BimodalThreeBitPredictor::getIndex(unsigned long long addr) {
  return addr % table_size;
}

int BimodalThreeBitPredictor::getPrediction(unsigned long long addr){
    unsigned int index = getIndex(addr);
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

bool BimodalThreeBitPredictor::isCorrectPrediction(int prediction, int actualBranch) {
  return (prediction == actualBranch);
}

void BimodalThreeBitPredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  unsigned int index = getIndex(addr);
  if(actualBranch == TAKEN) {
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
  
  if (actualBranch == NOT_TAKEN) {
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
