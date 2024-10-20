#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "predictors.h"
#include "AlwaysTakenPredictor.h"
#include "AlwaysNotTakenPredictor.h"
#include "BimodalSingleBitPredictor.h"
#include "BimodalTwoBitPredictor.h"
#include "BimodalThreeBitPredictor.h"
#include "GsharePredictor.h"
#include "TournamentPredictor.h"

using namespace std;

bool enableBimodalPredictors = true;
bool enableGsharePredictor = true;
bool enableTournamentPredictor = true;

bool doCout = false;

int main(int argc, char *argv[]) {
  // Check if the correct number of arguments are provided
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return 1;
  }

  // Get the input and output file names from command-line arguments
  string input_file = argv[1];
  string output_file = argv[2];

  // Temporary variables
  unsigned long long addr;
  string behavior, line;

  // Open file for reading
  ifstream infile(input_file);
  if (!infile) {
    cerr << "Error: Could not open input file " << input_file << endl;
    return 1;
  }

  // Open file for writing
  ofstream outfile(output_file);
  if (!outfile) {
    cerr << "Error: Could not open output file " << output_file << endl;
    return 1;
  }

  ////////////////////////////////////////////
  // Always taken predictor
  AlwaysTakenPredictor atp;
  atp.reset();

  infile.clear();
  infile.seekg(0, ios::beg);
  while (infile >> std::hex >> addr >> behavior) {
    atp.branchCount++;
    int actualBranch = behavior == "T";
    int prediction = atp.getPrediction(addr);
    if (atp.isCorrectPrediction(prediction, actualBranch)) {
      atp.correctCount++;
    }
    atp.updatePredictor(addr, actualBranch);
  }
  outfile << atp.correctCount << "," << atp.branchCount << ";" << endl;
  if (doCout) cout << atp.correctCount << "," << atp.branchCount << ";" << endl;

  ////////////////////////////////////////////
  // Always not taken predictor
  AlwaysNotTakenPredictor antp;
  antp.reset();

  infile.clear();
  infile.seekg(0, ios::beg);
  while (infile >> std::hex >> addr >> behavior) {
    antp.branchCount++;
    int actualBranch = behavior == "T";
    int prediction = antp.getPrediction(addr);
    if (antp.isCorrectPrediction(prediction, actualBranch)) {
      antp.correctCount++;
    }
    antp.updatePredictor(addr, actualBranch);
  }
  outfile << antp.correctCount << "," << antp.branchCount << ";" << endl;
  if (doCout) cout << antp.correctCount << "," << antp.branchCount << ";" << endl;

  ////////////////////////////////////////////
  // Creat table of table_size entries and intialize to 0 meaning not taken
  int history_table[MAX_TABLE_SIZE] = {0};

  int sizes[7] = {4, 8, 32, 64, 256, 1024, 4096};

  if (enableBimodalPredictors) {
    ////////////////////////////////////////////
    // Bimodal single bit predictor
    BimodalSingleBitPredictor b1bp;

    for (int size_index = 0; size_index < 7; size_index++) {
      int table_size = sizes[size_index];
      b1bp.setTableSize(table_size);
      b1bp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        b1bp.branchCount++;
        int actualBranch = behavior == "T";
        int prediction = b1bp.getPrediction(addr);
        if (b1bp.isCorrectPrediction(prediction, actualBranch)) {
          b1bp.correctCount++;
        }
        b1bp.updatePredictor(addr, actualBranch);
      }

      outfile << b1bp.correctCount << "," << b1bp.branchCount << ";";
      if (doCout) cout << b1bp.correctCount << "," << b1bp.branchCount << ";";

      if (size_index != 6) {
        outfile << " ";
        if (doCout) cout << " ";
      }
    }
    outfile << endl;
    if (doCout) cout << endl;
  }

  if (enableBimodalPredictors) {
    ////////////////////////////////////////////
    // Bimodal two bit predictor
    BimodalTwoBitPredictor b2bp;

    for (int size_index = 0; size_index < 7; size_index++) {
      int table_size = sizes[size_index];
      b2bp.setTableSize(table_size);
      b2bp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        b2bp.branchCount++;
        int actualBranch = behavior == "T";
        int prediction = b2bp.getPrediction(addr);
        if (b2bp.isCorrectPrediction(prediction, actualBranch)) {
          b2bp.correctCount++;
        }
        b2bp.updatePredictor(addr, actualBranch);
      }

      outfile << b2bp.correctCount << "," << b2bp.branchCount << ";";
      if (doCout) cout << b2bp.correctCount << "," << b2bp.branchCount << ";";

      if (size_index != 6) {
        outfile << " ";
        if (doCout) cout << " ";
      }
    }
    outfile << endl;
    if (doCout) cout << endl;
  }

  if (enableBimodalPredictors) {
    ////////////////////////////////////////////
    // Bimodal three bit predictor
    BimodalThreeBitPredictor b3bp;

    for (int size_index = 0; size_index < 7; size_index++) {
      int table_size = sizes[size_index];
      b3bp.setTableSize(table_size);
      b3bp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        b3bp.branchCount++;
        int actualBranch = behavior == "T";

        int prediction = b3bp.getPrediction(addr);
        if (b3bp.isCorrectPrediction(prediction, actualBranch)) {
          b3bp.correctCount++;
        }
        b3bp.updatePredictor(addr, actualBranch);
      }

      outfile << b3bp.correctCount << "," << b3bp.branchCount << ";";
      if (doCout) cout << b3bp.correctCount << "," << b3bp.branchCount << ";";

      if (size_index != 6) {
        outfile << " ";
        if (doCout) cout << " ";
      }
    }
    outfile << endl;
    if (doCout) cout << endl;
  }

  if (enableGsharePredictor) {
    ////////////////////////////////////////////
    // Gshare bit predictor
    GsharePredictor gshare;

    int bits_lower_bound = 2;  // 2;
    int bits_upper_bound = 12; // 12;

    for (int bits = bits_lower_bound; bits <= bits_upper_bound; bits++) {
      gshare.setTableSize(MAX_TABLE_SIZE);
      gshare.reset();
      gshare.setGhrBitCount(bits);

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        gshare.branchCount++;
        int actualBranch = behavior == "T";

        int prediction = gshare.getPrediction(addr);
        if (gshare.isCorrectPrediction(prediction, actualBranch)) {
          gshare.correctCount++;
        }
        gshare.updatePredictor(addr, actualBranch);
      }

      outfile << gshare.correctCount << "," << gshare.branchCount << ";";
      if (doCout) cout << gshare.correctCount << "," << gshare.branchCount << ";";

      if (bits != 12) {
        outfile << " ";
        if (doCout) cout << " ";
      }
    }

    outfile << endl;
    if (doCout) cout << endl;
  }

  if (enableTournamentPredictor) {
    ////////////////////////////////////////////
    // Tournament bit predictor
    TournamentPredictor tp;
    tp.setTableSize(MAX_TABLE_SIZE);
    tp.reset();

    // Gshare setup
    GsharePredictor tp_gshare;
    tp_gshare.setTableSize(MAX_TABLE_SIZE);
    tp_gshare.reset();
    tp_gshare.setGhrBitCount(12);
    tp_gshare.GHR = 0;

    // Bimodal setup
    BimodalThreeBitPredictor tp_3bit_bimodal;
    tp_3bit_bimodal.setTableSize(MAX_TABLE_SIZE);
    tp_3bit_bimodal.setInitiaHistoryTablelValue(THREE_STRONGLY_NOT_TAKEN);
    tp_3bit_bimodal.reset();

    infile.clear();
    infile.seekg(0, ios::beg);
    while (infile >> std::hex >> addr >> behavior) {
      tp.branchCount++;
      int actualBranch = behavior == "T";
      bool gshareCorrect = false;
      bool bimodalCorrect = false;

      // Do the Gshare business
      tp_gshare.branchCount++;
      int gshare_prediction = tp_gshare.getPrediction(addr);
      if (tp_gshare.isCorrectPrediction(gshare_prediction, actualBranch)) {
        tp_gshare.correctCount++;
        gshareCorrect = true;
      }
      tp_gshare.updatePredictor(addr, actualBranch);

      // Do the Bimodal business
      tp_3bit_bimodal.branchCount++;
      int bimodal_prediction = tp_3bit_bimodal.getPrediction(addr);
      if (tp_3bit_bimodal.isCorrectPrediction(bimodal_prediction, actualBranch)) {
        tp_3bit_bimodal.correctCount++;
        bimodalCorrect = true;
      }
      tp_3bit_bimodal.updatePredictor(addr, actualBranch);

      // Do the Tournament business
      int predictorToUse = tp.getPrediction(addr);
      int prediction = predictorToUse == USE_GSHARE ? gshare_prediction : bimodal_prediction;
      if (tp.isCorrectPrediction(prediction, actualBranch)) {
        tp.correctCount++;
      }

      tp.updateTournamentPredictor(addr, gshareCorrect, bimodalCorrect);
    }

    if (doCout) cout << "tp_gshare:" << endl;
    if (doCout) cout << tp_gshare.correctCount << "," << tp_gshare.branchCount << ";" << endl;
    if (doCout) cout << "tp_3bit_bimodal:" << endl;
    if (doCout) cout << tp_3bit_bimodal.correctCount << "," << tp_3bit_bimodal.branchCount << ";" << endl;
    if (doCout) cout << "tp:" << endl;
    outfile << tp.correctCount << "," << tp.branchCount << ";";
    if (doCout) cout << tp.correctCount << "," << tp.branchCount << ";";

  }

  // Close the input and output files
  infile.close();
  outfile.close();

  return 0;
}
