#pragma once
#include <string>
#include "predictors.h"
#include "BinaryToStringUtil.h"

using namespace std;

class GsharePredictor {

    public:
      GsharePredictor();
      void setTableSize(int size);
      void setGhrBitCount(int size);
      void reset();
      unsigned int getIndex(unsigned long long addr);
      int getPrediction(unsigned long long addr);
      bool isCorrectPrediction(int prediction, int actualBranch);
      void updatePredictor(unsigned long long addr, int actualBranch);
      void updateGHR(bool actualBranch);
      int getTwobitSaturatedCounterNextValue(int currentState,bool actualBranch);
      int correctCount;
      int branchCount;
      int bit_count;
      unsigned int GHR;
    private:
       int table[MAX_TABLE_SIZE];
       int table_size;
};

GsharePredictor::GsharePredictor() {
    reset();
}

void GsharePredictor::setTableSize(int size) {
  // table_size = size;
}


void GsharePredictor::setGhrBitCount(int size) {
  bit_count = size;
}

void GsharePredictor::reset() {
    correctCount = 0;
    branchCount = 0;
    // The global history register should be initialized to one (where 0=NT and 1=T). 
    // For example, for 2bits history register, it’s 01, for 5bits, it’s 00001, for 10bits it’s 0000000001. 
    GHR = TAKEN; 
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
      table[i] = STRONGLY_NOT_TAKEN;
    }
}

unsigned int GsharePredictor::getIndex(unsigned long long addr) {
  bool debug = false;

  // addr = 0xAAAAAAAA;
  
  // GHR =  (1 << bit_count) - 1;
  // Extract the least significant 12 bits of the PC  (12-bit index)
  if(debug) {
    cout << "getIndex" << endl;
    cout << "-----GHR: "  << intToBinaryString(GHR) << endl;
    cout << "addr:     " << intToBinaryString(addr) << endl;
  }

  // Extract the least significant bit_count from the PC
  unsigned int pc_LSB = addr & ((1 << bit_count) - 1);
  if(debug) {
    cout << "pc_LSB:   " << intToBinaryString(pc_LSB) << endl;
  }

  // XOR the least significant bits of PC with GHR
  unsigned int index_LSB = pc_LSB ^ GHR;
  if(debug) {
    cout << "GHR:      " << intToBinaryString(GHR) << endl;
    cout << "index_LSB:" << intToBinaryString(index_LSB) << endl;
  }


  // Combine the remaining bits of the PC with the XOR result to form the 12-bit index.
  // Teacher:
  // "For example  if the global history is 4 bits, then you XOR 4 least significant bits 
  // of the PC with the 4 bits of global history register to generate 4 least 
  // significant bits of the index. The remaining 8 bits of the index come directly from PC."
  // My understanding:
  // 1. Shift the PC to the right by the number of bits.
  // 2. Shift the result to the left by the number of bits.
  // 3. OR the result with the XOR result.
  unsigned int index = ((addr >> bit_count) << bit_count) | index_LSB;
  if(debug) {
    cout << "addr>>bit:" << intToBinaryString(addr >> bit_count) << endl;
    cout << "addr<<bit:" << intToBinaryString((addr >> bit_count) << bit_count) << endl;
  }
  if(debug) {
    cout << "index:    " << intToBinaryString(index) << endl;
  }

  
  // Per TA clarification, the index should be masked to 12 bits
  // Mask the index to ensure it's 12 bits long
  index &= 0xFFF;

  if(debug) {
    cout << "12-b indx:" << intToBinaryString(index) << endl;
  }

  return index;
}

int GsharePredictor::getPrediction(unsigned long long addr){
    bool debug = false;

    unsigned int index = getIndex(addr);
    unsigned int sat_counter = table[index];
    if(debug) {
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
    if(sat_counter == STRONGLY_NOT_TAKEN || sat_counter == WEAKLY_NOT_TAKEN) {
         prediction = NOT_TAKEN; // Not taken
    }
    else {
        prediction = TAKEN; // Taken
    }

    if(debug) {
      cout << "Prediction: " << prediction << endl;
    }
    return prediction;
}

bool GsharePredictor::isCorrectPrediction(int prediction, int actualBranch) {
  return (prediction == actualBranch);
}

void GsharePredictor::updatePredictor(unsigned long long addr, int actualBranch) {
  bool debug = false;
  if(debug) {
    cout << "updatePredictor" << endl;
    cout << "addr:    " << intToBinaryString(addr) << endl;
    cout << "behavior:" << actualBranch << endl;
  }
  unsigned int index = getIndex(addr);
  int currentState = table[index];
  int nextState = getTwobitSaturatedCounterNextValue(currentState, actualBranch);
  table[index] = nextState;
  if(debug) {
    cout << "index:   " << index << endl;
    cout << "table:   " << intToBinaryString(table[index]) << endl;
  }
  updateGHR(actualBranch);
}


void GsharePredictor::updateGHR(bool actualBranch) {
  bool debug = false;
  if(debug) {
    cout << "actual: " << actualBranch << endl;
    cout << "GHR:     " << intToBinaryString(GHR) << endl;
  }
    // Shift the GHR to the left by 1 bit to make room for the new value
    GHR = (GHR << 1);

    // Add the new branch outcome (0 = Not Taken, 1 = Taken) into the LSB
    GHR |= actualBranch;

    // Mask the GHR to keep only the lower bit_count 
    GHR &= (1 << bit_count) - 1;

    if(debug) {
      cout << "GHR:      " << intToBinaryString(GHR) << endl;
    }
}



int GsharePredictor::getTwobitSaturatedCounterNextValue(int currentState, bool actualBranch) {
    // 00: Strongly not taken
    // 01: Weakly not taken
    // 10: Weakly taken
    // 11: Strongly taken
    if(actualBranch == TAKEN) {
        if(currentState == STRONGLY_NOT_TAKEN) { // 
          return WEAKLY_NOT_TAKEN;
        }
        else if(currentState == WEAKLY_NOT_TAKEN) {
        currentState = WEAKLY_TAKEN;
        }
        else if(currentState == WEAKLY_TAKEN) {
        currentState = STRONGLY_TAKEN;
        }
        else if(currentState == STRONGLY_TAKEN) {
        currentState =  STRONGLY_TAKEN;
        }
    }
    
    if(actualBranch == NOT_TAKEN) {
        if(currentState == STRONGLY_NOT_TAKEN) {
        currentState =  STRONGLY_NOT_TAKEN;
        }
        else if(currentState == WEAKLY_NOT_TAKEN) {
        currentState = STRONGLY_NOT_TAKEN;
        }
        else if(currentState == WEAKLY_TAKEN) {
        currentState = WEAKLY_NOT_TAKEN;
        }
        else if(currentState == STRONGLY_TAKEN) {
        currentState = WEAKLY_TAKEN;
        }
  }

  return currentState;
}

