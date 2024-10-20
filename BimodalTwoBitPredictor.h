#pragma once
#include <string>
#include "PredictorBase.h"

using namespace std;

class BimodalTwoBitPredictor: public PredictorBase {
  public:
    int getPrediction(unsigned long long addr);
    void updatePredictor(unsigned long long addr, int actualBranch);
};

int BimodalTwoBitPredictor::getPrediction(unsigned long long addr){
    unsigned int index = getIndex(addr);

    // 00: Strongly not taken -> not taken
    // 01: Weakly not taken -> not taken
    // 10: Weakly taken -> taken
    // 11: Strongly taken -> taken
    if(history_table[index] == STRONGLY_NOT_TAKEN || history_table[index] == WEAKLY_NOT_TAKEN) {
        return NOT_TAKEN; // Not taken
    }
    
    return TAKEN; // Taken
}

void BimodalTwoBitPredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  unsigned int index = getIndex(addr);
    // 00: Strongly not taken
    // 01: Weakly not taken
    // 10: Weakly taken
    // 11: Strongly taken
    if(actualBranch == TAKEN) {
        if(history_table[index] == STRONGLY_NOT_TAKEN) { // 
        history_table[index] = WEAKLY_NOT_TAKEN;
        }
        else if(history_table[index] == WEAKLY_NOT_TAKEN) {
        history_table[index] = WEAKLY_TAKEN;
        }
        else if(history_table[index] == WEAKLY_TAKEN) {
        history_table[index] = STRONGLY_TAKEN;
        }
        else if(history_table[index] == STRONGLY_TAKEN) {
        history_table[index] =  STRONGLY_TAKEN;
        }
    }
    
    if(actualBranch == NOT_TAKEN) {
        if(history_table[index] == STRONGLY_NOT_TAKEN) {
        history_table[index] =  STRONGLY_NOT_TAKEN;
        }
        else if(history_table[index] == WEAKLY_NOT_TAKEN) {
        history_table[index] = STRONGLY_NOT_TAKEN;
        }
        else if(history_table[index] == WEAKLY_TAKEN) {
        history_table[index] = WEAKLY_NOT_TAKEN;
        }
        else if(history_table[index] == STRONGLY_TAKEN) {
        history_table[index] = WEAKLY_TAKEN;
        }
  }
}
