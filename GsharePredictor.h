#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class GsharePredictor {

    public:
      GsharePredictor();
      void setTableSize(int size);
      void reset();
      int getIndex(unsigned long long addr);
      int getPrediction(unsigned long long addr);
      bool isCorrectPrediction(int prediction, string behavior);
      void updateTable(unsigned long long addr, string behavior);
      int correctCount;
      int branchCount;
      unsigned int ghr;
    private:
       int bimodal_bit_table[MAX_TABLE_SIZE];
       int table_size;
};

GsharePredictor::GsharePredictor() {
    reset();
}

void GsharePredictor::setTableSize(int size) {
  this->table_size = size;
}


void GsharePredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    // The global history register should be initialized to one (where 0=NT and 1=T). 
    // For example, for 2bits history register, it’s 01, for 5bits, it’s 00001, for 10bits it’s 0000000001. 
    ghr = TAKEN; 
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      bimodal_bit_table[i] = 0;
    }
}

int GsharePredictor::getIndex(unsigned long long addr) {
  return addr % table_size;
}

int GsharePredictor::getPrediction(unsigned long long addr){
  int index = getIndex(addr);
  return bimodal_bit_table[index];
}

bool GsharePredictor::isCorrectPrediction(int prediction, string behavior) {
  if(prediction == NOT_TAKEN && behavior == "NT") {
    return true;
  }
  
  if(prediction == TAKEN && behavior == "T") {
    return true;
  }
  return false; 
}

void GsharePredictor::updateTable(unsigned long long addr, string behavior) {
  int index = getIndex(addr);
  if(behavior == "T") {
    bimodal_bit_table[index] = TAKEN;
  }
  else {
    bimodal_bit_table[index] = NOT_TAKEN;
  }
}
