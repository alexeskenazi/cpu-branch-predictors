#pragma once
#include <string>
#include "PredictorBase.h"
#include "BinaryToStringUtil.h"

using namespace std;

class GsharePredictor : public PredictorBase {
    public:
      void setGhrBitCount(int size);
      void reset();
      unsigned int getIndex(unsigned long long addr);
      int getPrediction(unsigned long long addr);
      void updatePredictor(unsigned long long addr, int actualBranch);
      void updateGHR(bool actualBranch);
      int getTwobitSaturatedCounterNextValue(int currentState, bool actualBranch);
      int bit_count;
      unsigned int GHR;
};

void GsharePredictor::setGhrBitCount(int size) {
  bit_count = size;
}

void GsharePredictor::reset() {
    PredictorBase::reset();
    GHR = TAKEN; 
}

unsigned int GsharePredictor::getIndex(unsigned long long addr) {
  bool debug = false;
  
  if (debug) {
    cout << "getIndex" << endl;
    cout << "-----GHR: " << intToBinaryString(GHR) << endl;
    cout << "addr:     " << intToBinaryString(addr) << endl;
  }

  // Extract the least significant bit_count from the PC
  unsigned int pc_LSB = addr & ((1 << bit_count) - 1);
  if (debug) {
    cout << "pc_LSB:   " << intToBinaryString(pc_LSB) << endl;
  }

  // XOR the least significant bits of PC with GHR
  unsigned int index_LSB = pc_LSB ^ GHR;
  if (debug) {
    cout << "GHR:      " << intToBinaryString(GHR) << endl;
    cout << "index_LSB:" << intToBinaryString(index_LSB) << endl;
  }

  // Combine the remaining bits of the PC with the XOR result to form the 12-bit index.
  unsigned int index = ((addr >> bit_count) << bit_count) | index_LSB;
  if (debug) {
    cout << "addr>>bit:" << intToBinaryString(addr >> bit_count) << endl;
    cout << "addr<<bit:" << intToBinaryString((addr >> bit_count) << bit_count) << endl;
  }
  if (debug) {
    cout << "index:    " << intToBinaryString(index) << endl;
  }

  // Per TA clarification, the index should be masked to 12 bits
  index &= 0xFFF;

  if (debug) {
    cout << "12-b indx:" << intToBinaryString(index) << endl;
  }

  return index;
}

int GsharePredictor::getPrediction(unsigned long long addr) {
    bool debug = false;

    unsigned int index = getIndex(addr);
    unsigned int sat_counter = history_table[index];
    if (debug) {
      cout << "getPrediction" << endl;
      cout << "addr:    " << intToBinaryString(addr) << endl;
      cout << "index:   " << index << endl;
      cout << "table:   " << intToBinaryString(sat_counter) << endl;
    }

    // 00: Strongly not taken -> not taken
    // 01: Weakly not taken -> not taken
    // 10: Weakly taken -> taken
    // 11: Strongly taken -> taken
    unsigned int prediction = NOT_TAKEN;
    if (sat_counter == STRONGLY_NOT_TAKEN || sat_counter == WEAKLY_NOT_TAKEN) {
         prediction = NOT_TAKEN; // Not taken
    } else {
        prediction = TAKEN; // Taken
    }

    if (debug) {
      cout << "Prediction: " << prediction << endl;
    }
    return prediction;
}

void GsharePredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  bool debug = false;
  if (debug) {
    cout << "updatePredictor" << endl;
    cout << "addr:    " << intToBinaryString(addr) << endl;
    cout << "behavior:" << actualBranch << endl;
  }
  unsigned int index = getIndex(addr);
  int currentState = history_table[index];
  int nextState = getTwobitSaturatedCounterNextValue(currentState, actualBranch);
  history_table[index] = nextState;
  if (debug) {
    cout << "index:   " << index << endl;
    cout << "table:   " << intToBinaryString(history_table[index]) << endl;
  }
  updateGHR(actualBranch);
}

void GsharePredictor::updateGHR(bool actualBranch) {
  bool debug = false;
  if (debug) {
    cout << "actual: " << actualBranch << endl;
    cout << "GHR:     " << intToBinaryString(GHR) << endl;
  }
    // Shift the GHR to the left by 1 bit to make room for the new value
    GHR = (GHR << 1);

    // Add the new branch outcome (0 = Not Taken, 1 = Taken) into the LSB
    GHR |= actualBranch;

    // Mask the GHR to keep only the lower bit_count 
    GHR &= (1 << bit_count) - 1;

    if (debug) {
      cout << "GHR:      " << intToBinaryString(GHR) << endl;
    }
}

int GsharePredictor::getTwobitSaturatedCounterNextValue(int currentState, bool actualBranch) {
    // 00: Strongly not taken
    // 01: Weakly not taken
    // 10: Weakly taken
    // 11: Strongly taken
    if (actualBranch == TAKEN) {
        if (currentState == STRONGLY_NOT_TAKEN) { 
          return WEAKLY_NOT_TAKEN;
        } else if (currentState == WEAKLY_NOT_TAKEN) {
          currentState = WEAKLY_TAKEN;
        } else if (currentState == WEAKLY_TAKEN) {
          currentState = STRONGLY_TAKEN;
        } else if (currentState == STRONGLY_TAKEN) {
          currentState = STRONGLY_TAKEN;
        }
    }

    if (actualBranch == NOT_TAKEN) {
        if (currentState == STRONGLY_NOT_TAKEN) {
          currentState = STRONGLY_NOT_TAKEN;
        } else if (currentState == WEAKLY_NOT_TAKEN) {
          currentState = STRONGLY_NOT_TAKEN;
        } else if (currentState == WEAKLY_TAKEN) {
          currentState = WEAKLY_NOT_TAKEN;
        } else if (currentState == STRONGLY_TAKEN) {
          currentState = WEAKLY_TAKEN;
        }
    }

    return currentState;
}
