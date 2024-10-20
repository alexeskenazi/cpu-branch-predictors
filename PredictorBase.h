#pragma once
#include <string>
#include "predictors.h"

using namespace std;

class PredictorBase {
  public:
    PredictorBase();
    void setInitiaHistoryTablelValue(int value);
    void setTableSize(int size);
    void reset();
    unsigned int getIndex(unsigned long long addr);
    int getPrediction(unsigned long long addr);
    bool isCorrectPrediction(int prediction, int actualBranch);
    void updatePredictor(unsigned long long addr, int actualBranch);
    int correctCount;
    int branchCount;
  protected:
    int history_table[MAX_TABLE_SIZE];
    int table_size;
    int initialHistoryTableValue;
};

PredictorBase::PredictorBase() {
  initialHistoryTableValue = 0;
  reset();
}

void PredictorBase::setInitiaHistoryTablelValue(int value) {
  initialHistoryTableValue = value;
}

void PredictorBase::setTableSize(int size) {
  table_size = size;
}

void PredictorBase::reset() {
  correctCount = 0;
  branchCount = 0;
  for (int i = 0; i < MAX_TABLE_SIZE; i++) {
    history_table[i] = initialHistoryTableValue;
  }

  // cout << "reset" << endl;
  // cout << "table_size: " << table_size << endl;
  // cout << "initialHistoryTableValue: " << initialHistoryTableValue << endl;
  // cout << "history_table[0]: " << history_table[0] << endl;
}

unsigned int PredictorBase::getIndex(unsigned long long addr) {
  return addr % table_size;
}

int PredictorBase::getPrediction(unsigned long long addr) {
  unsigned int index = getIndex(addr);
  return history_table[index];
}

bool PredictorBase::isCorrectPrediction(int prediction, int actualBranch) {
  return (prediction == actualBranch);
}

void PredictorBase::updatePredictor(unsigned long long addr, int actualBranch) {
  unsigned int index = getIndex(addr);
  history_table[index] = actualBranch;
}
