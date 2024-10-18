#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalSingleBitPredictor {

    public:
      BimodalSingleBitPredictor();
      void setTableSize(int size);
      void reset();
      int getIndex(unsigned long long addr);
      int getPrediction(unsigned long long addr);
      bool isCorrectPrediction(int prediction, string behavior);
      void updateTable(unsigned long long addr, string behavior);
      int correctCount;
      int branchCount;
    private:
       int bimodal_bit_table[MAX_TABLE_SIZE];
       int table_size;
};

BimodalSingleBitPredictor::BimodalSingleBitPredictor() {
    reset();
}

void BimodalSingleBitPredictor::setTableSize(int size) {
  this->table_size = size;
}

void BimodalSingleBitPredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      bimodal_bit_table[i] = 0;
    }
}

int BimodalSingleBitPredictor::getIndex(unsigned long long addr) {
  return addr % table_size;
}

int BimodalSingleBitPredictor::getPrediction(unsigned long long addr){
  int index = getIndex(addr);
  return bimodal_bit_table[index];
}

bool BimodalSingleBitPredictor::isCorrectPrediction(int prediction, string behavior) {

  if(prediction == NOT_TAKEN && behavior == "NT") {
    return true;
  }
  
  if(prediction == TAKEN && behavior == "T") {
    return true;
  }
  return false; 
}

void BimodalSingleBitPredictor::updateTable(unsigned long long addr, string behavior) {
  int index = getIndex(addr);
  if(behavior == "T") {
    bimodal_bit_table[index] = TAKEN;
  }
  else {
    bimodal_bit_table[index] = NOT_TAKEN;
  }
}
