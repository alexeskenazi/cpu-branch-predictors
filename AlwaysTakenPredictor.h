#pragma once
#include "PredictorBase.h"

class AlwaysTakenPredictor : public PredictorBase {
  public:
    unsigned int getIndex(unsigned long long addr);
    int getPrediction(unsigned long long addr);
    void updatePredictor(unsigned long long addr, int actualBranch);
};

unsigned int AlwaysTakenPredictor::getIndex(unsigned long long addr) {
  return 0;
}

int AlwaysTakenPredictor::getPrediction(unsigned long long addr) {
  return TAKEN;
}

void AlwaysTakenPredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  return;
}
