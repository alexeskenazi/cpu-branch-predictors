#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalSingleBitPredictor {

    public:
      BimodalSingleBitPredictor();
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

BimodalSingleBitPredictor::BimodalSingleBitPredictor() {
    reset();
}

void BimodalSingleBitPredictor::setTableSize(int size) {
  table_size = size;
}

void BimodalSingleBitPredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      bimodal_bit_table[i] = 0;
    }
}

unsigned int BimodalSingleBitPredictor::getIndex(unsigned long long addr) {
  return addr % table_size;
}

int BimodalSingleBitPredictor::getPrediction(unsigned long long addr){
  unsigned int index = getIndex(addr);
  return bimodal_bit_table[index];
}

bool BimodalSingleBitPredictor::isCorrectPrediction(int prediction, int actualBranch) {
  return (prediction == actualBranch);
}

void BimodalSingleBitPredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  unsigned int index = getIndex(addr);
  bimodal_bit_table[index] = actualBranch;
}
