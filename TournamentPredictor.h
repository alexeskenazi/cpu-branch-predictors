#pragma once
#include <string>
#include "PredictorBase.h"

class TournamentPredictor : public PredictorBase {
public:
    void reset();
    int getPrediction(unsigned long long addr);
    void updateTournamentPredictor(unsigned long long addr, bool gshareCorrect, bool bimodalCorrect);
    int getNextState(int currentState, bool gshareCorrect, bool bimodalCorrect);
};

void TournamentPredictor::reset() {
    PredictorBase::reset();

    // From the teacher's prompt:
    // Initialize the selector’s counters to “Strongly Prefer Bimodal”.
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        history_table[i] = STRONGLY_BIMODAL;
    }
}

int TournamentPredictor::getPrediction(unsigned long long addr) {
    bool debug = true;
    unsigned int index = getIndex(addr);
    int state = history_table[index];
    int prediction = USE_BIMODAL;

    debug = index == 2204;

    if (state == STRONGLY_GSHARE || state == WEAKLY_GSHARE) {
        prediction = USE_GSHARE;
    } else {
        prediction = USE_BIMODAL;
    }
    if(debug) {
        cout << "getPrediction" << endl;
        cout << "   index: " << index << endl;
        cout << "   state: " << state << endl;
        cout << "   prediction: " << (prediction==USE_GSHARE ? "Gshare" : "Bimodal") << endl;
    }

    return prediction;
}

void TournamentPredictor::updateTournamentPredictor(unsigned long long addr, bool gshareCorrect, bool bimodalCorrect) {
    // From the teacher's prompt:
    // If the two predictors provide the same prediction, then the corresponding selector counter remains the same. 
    // If one of the predictors is correct and the other one is wrong, then the selector’s counter is decremented or incremented.
    
    unsigned int index = getIndex(addr);
    int currentState = history_table[index];
    
    bool debug = false;
    debug = index == 2204;
    if (debug) {
        cout << "  updateTournamentPredictor ----------" << endl;
        cout << "   index: " << index << endl;
        
    }

    if (gshareCorrect == bimodalCorrect) {
        if (debug) {
            cout << "   No winner, currentState: " << currentState << endl;
        }    
        return;
    }

    if(debug) {
        cout << "  got a winner: " << (gshareCorrect ? "gshare" : "bimodal") << endl;
    }
    
    int newState = getNextState(currentState, gshareCorrect, bimodalCorrect);
    history_table[index] = newState;

    if (debug) {
        if(newState != currentState) {
            cout << "   State: " << currentState << "->" << newState << endl;
        } else {
            cout << "   State: " << currentState << "-> same" << endl;
        }
    }
}

int TournamentPredictor::getNextState(int currentState, bool gshareCorrect, bool bimodalCorrect) {
    // From the teacher's prompt:
    // If the two predictors provide the same prediction, then the corresponding selector counter remains the same. 
    // If one of the predictors is correct and the other one is wrong, then the selector’s counter is decremented or incremented.

    if (gshareCorrect == bimodalCorrect) {
        return currentState;
    }

    if (gshareCorrect) {
        if (currentState == STRONGLY_BIMODAL) {
            return WEAKLY_BIMODAL;
        } 
        
        if (currentState == WEAKLY_BIMODAL) {
            return WEAKLY_GSHARE;
        } 
        
        if (currentState == WEAKLY_GSHARE) {
            return STRONGLY_GSHARE;
        }
    }

    if (bimodalCorrect) {
        if (currentState == STRONGLY_GSHARE) {
            return WEAKLY_GSHARE;
        }
        
        if (currentState == WEAKLY_GSHARE) {
            return WEAKLY_BIMODAL;
        }
        
        if (currentState == WEAKLY_BIMODAL) {
            return STRONGLY_BIMODAL;
        }
    }

    return currentState;
}
