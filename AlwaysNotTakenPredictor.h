#pragma once
#include "PredictorBase.h"

class AlwaysNotTakenPredictor : public PredictorBase {
  public:
    unsigned int getIndex(unsigned long long addr);
    int getPrediction(unsigned long long addr);
    void updatePredictor(unsigned long long addr, int actualBranch);
};

unsigned int AlwaysNotTakenPredictor::getIndex(unsigned long long addr) {
  return 0;
}

int AlwaysNotTakenPredictor::getPrediction(unsigned long long addr) {
  return NOT_TAKEN;
}

void AlwaysNotTakenPredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  return;
}
