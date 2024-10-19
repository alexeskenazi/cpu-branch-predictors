#pragma once
#include <string>
#include "PredictorBase.h"

using namespace std;

class BimodalThreeBitPredictor: public PredictorBase {
  public:
    int getPrediction(unsigned long long addr);
    bool isCorrectPrediction(int prediction, int actualBranch);
    void updatePredictor(unsigned long long addr, int actualBranch);
};

int BimodalThreeBitPredictor::getPrediction(unsigned long long addr){
    unsigned int index = getIndex(addr);
    if(history_table[index] == THREE_STRONGLY_TAKEN) { // 
      return TAKEN;
    }
    else if(history_table[index] == THREE_TAKEN) {
      return TAKEN;
    }
    else if(history_table[index] == THREE_WEAKLY_TAKEN) {
      return TAKEN;
    }
    else if(history_table[index] == THREE_STRONGLY_NOT_TAKEN) {
      return NOT_TAKEN;
    }
    else if(history_table[index] == THREE_NOT_TAKEN) {
      return NOT_TAKEN;
    }
    else if(history_table[index] == THREE_WEAKLY_NOT_TAKEN) {
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
      if(history_table[index] == THREE_STRONGLY_TAKEN) { 
        history_table[index] = THREE_STRONGLY_TAKEN;
      }
      else if(history_table[index] == THREE_TAKEN) {
        history_table[index] = THREE_STRONGLY_TAKEN;
      }
      else if(history_table[index] == THREE_WEAKLY_TAKEN) {
        history_table[index] = THREE_TAKEN;
      }
      else if(history_table[index] == THREE_STRONGLY_NOT_TAKEN) {
        history_table[index] = THREE_NOT_TAKEN;
      }
      else if(history_table[index] == THREE_NOT_TAKEN) {
        history_table[index] = THREE_WEAKLY_NOT_TAKEN;
      }
      else if(history_table[index] == THREE_WEAKLY_NOT_TAKEN) {
        history_table[index] = THREE_WEAKLY_TAKEN;
      }
  }
  
  if (actualBranch == NOT_TAKEN) {
      if(history_table[index] == THREE_STRONGLY_TAKEN) {
        history_table[index] = THREE_TAKEN;
      }
      // This one is not symmetric, we need to handle it differently
      // based ont the definition in the doc.
      else if(history_table[index] == THREE_TAKEN) {
        history_table[index] = THREE_WEAKLY_NOT_TAKEN; /// As defined in the doc
      }
      else if(history_table[index] == THREE_WEAKLY_TAKEN) {
        history_table[index] = THREE_WEAKLY_NOT_TAKEN;
      }
      else if(history_table[index] == THREE_STRONGLY_NOT_TAKEN) {
        history_table[index] = THREE_STRONGLY_NOT_TAKEN;
      }
      else if(history_table[index] == THREE_NOT_TAKEN) {
        history_table[index] = THREE_STRONGLY_NOT_TAKEN;
      }
      else if(history_table[index] == THREE_WEAKLY_NOT_TAKEN) {
        history_table[index] = THREE_NOT_TAKEN;
      }
  }
}
