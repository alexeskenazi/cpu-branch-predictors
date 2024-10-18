#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class BimodalThreeBitPredictor {

    public:
    BimodalThreeBitPredictor();
    void setTableSize(int size);
        void reset();
        int getPrediction(unsigned long long addr);
        bool isCorrectPrediction(int prediction, string behavior);
        void updateTable(unsigned long long addr, string behavior);
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
  this->table_size = size;
}

void BimodalThreeBitPredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      bimodal_bit_table[i] = 0;
    }
}

int BimodalThreeBitPredictor::getPrediction(unsigned long long addr){
    int index = addr % table_size;
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

bool BimodalThreeBitPredictor::isCorrectPrediction(int prediction, string behavior) {
    if(prediction== NOT_TAKEN && behavior == "NT") {
        return true;
    }
    
    if(prediction == TAKEN && behavior == "T") {
        return true;
    }
    return false;
}

void BimodalThreeBitPredictor::updateTable(unsigned long long addr, string behavior) {
  int index = addr % table_size;
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
