#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "predictors.h"

using namespace std;


bool isBimodalSingleBitPredictionCorrect(int *bimodal_bit_table, int index, string behavior) {
  if(bimodal_bit_table[index] == NOT_TAKEN && behavior == "NT") {
    return true;
  }
  else if(bimodal_bit_table[index] == TAKEN && behavior == "T") {
    return true;
  }
  else {
    return false;
  }
}

void updateBimodalSingleBitTable(int *bimodal_bit_table, int index, string behavior) {
  if(behavior == "T") {
    bimodal_bit_table[index] = TAKEN;
  }
  else {
    bimodal_bit_table[index] = NOT_TAKEN;
  }
}


int getBimodalTwoBitPrediction(int *bimodal_bit_table, int index) {
  // 00: Strongly not taken
  // 01: Weakly not taken
  // 10: Weakly taken
  // 11: Strongly taken
  if(bimodal_bit_table[index] == 0 || bimodal_bit_table[index] == 1) {
    return 0; // Not taken
  }
  else {
    return 1; // Taken
  }
}

bool isBimodalTwoBitPredictionCorrect(int *bimodal_bit_table, int index, string behavior) {
  if(getBimodalTwoBitPrediction(bimodal_bit_table, index) == 0 && behavior == "NT") {
    return true;
  }
  else if(getBimodalTwoBitPrediction(bimodal_bit_table, index) == 1 && behavior == "T") {
    return true;
  }
 
  return false;
}

void updateBimodalTwoBitTable(int *bimodal_bit_table, int index, string behavior) {
  // 00: Strongly not taken
  // 01: Weakly not taken
  // 10: Weakly taken
  // 11: Strongly taken
  if(behavior == "T") {
    if(bimodal_bit_table[index] == STRONGLY_NOT_TAKEN) { // 
      bimodal_bit_table[index] = WEAKLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == WEAKLY_NOT_TAKEN) {
      bimodal_bit_table[index] = WEAKLY_TAKEN;
    }
    else if(bimodal_bit_table[index] == WEAKLY_TAKEN) {
      bimodal_bit_table[index] = STRONGLY_TAKEN;
    }
    else if(bimodal_bit_table[index] == STRONGLY_TAKEN) {
      bimodal_bit_table[index] =  STRONGLY_TAKEN;
    }
  }
  
  
  if(behavior == "NT") {
    if(bimodal_bit_table[index] == STRONGLY_NOT_TAKEN) {
      bimodal_bit_table[index] =  STRONGLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == WEAKLY_NOT_TAKEN) {
      bimodal_bit_table[index] = STRONGLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == WEAKLY_TAKEN) {
      bimodal_bit_table[index] = WEAKLY_NOT_TAKEN;
    }
    else if(bimodal_bit_table[index] == STRONGLY_TAKEN) {
      bimodal_bit_table[index] = WEAKLY_TAKEN;
    }
  }
}


void updateBimodalThreeBitTable(int *bimodal_bit_table, int index, string behavior) {
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

int getBimodalThreeBitPrediction(int *bimodal_bit_table, int index) {
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


bool isBimodalThreeBitPredictionCorrect(int *bimodal_bit_table, int index, string behavior) {
  if(getBimodalThreeBitPrediction(bimodal_bit_table, index) == NOT_TAKEN && behavior == "NT") {
    return true;
  }
  else if(getBimodalThreeBitPrediction(bimodal_bit_table, index) == TAKEN && behavior == "T") {
    return true;
  }
  return false;
}


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
  // Always taken predictor
  int always_taken_predictor_correct = 0;
  int always_taken_predictor_branch_count = 0;
  while (infile >> std::hex >> addr >> behavior) {
    always_taken_predictor_branch_count++;
    if (behavior == "T") {
      always_taken_predictor_correct++;
    } 
  }

  outfile << always_taken_predictor_correct << "," << always_taken_predictor_branch_count << ";" << endl;
  cout    << always_taken_predictor_correct << "," << always_taken_predictor_branch_count << ";" << endl;


  ////////////////////////////////////////////
  // Always not taken predictor
  // Always not taken predictor
  int always_not_taken_predictor_correct = 0;
  int always_not_taken_predictor_branch_count = 0;
  infile.clear();
  infile.seekg(0, ios::beg);
  while (infile >> std::hex >> addr >> behavior) {
    always_not_taken_predictor_branch_count++;
    if (behavior == "NT") {
      always_not_taken_predictor_correct++;
    } 
  }
  
  outfile << always_not_taken_predictor_correct << "," << always_not_taken_predictor_branch_count << ";" << endl;
  cout    << always_not_taken_predictor_correct << "," << always_not_taken_predictor_branch_count << ";" << endl;

  ////////////////////////////////////////////
  // Bimodal single bit predictor
  int bimodal_single_bit_correct = 0;
  int bimodal_single_bit_branch_count = 0;

  // Creat table of table_size entries and intialize to 0 meaning not taken
  int max_table_size = MAX_TABLE_SIZE;
  int bimodal_bit_table[MAX_TABLE_SIZE] = {0};

  int sizes[7] = {4, 8, 32, 64, 256, 1024, 4096};

  // Bimodal single bit predictor
  for(int size_index = 0; size_index <7; size_index++) {

      bimodal_single_bit_correct = 0;
      bimodal_single_bit_branch_count = 0;
    
      // Initialize the table
      int table_size = sizes[size_index];
      for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        bimodal_bit_table[i] = 0;
      }

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        bimodal_single_bit_branch_count++;

        // Get the index of the table
        int index = addr % table_size;

        if(isBimodalSingleBitPredictionCorrect(bimodal_bit_table, index, behavior)) {
          bimodal_single_bit_correct++;
        }
       
        updateBimodalSingleBitTable(bimodal_bit_table, index, behavior);

      }

      outfile << bimodal_single_bit_correct << "," << bimodal_single_bit_branch_count << ";" ;
      cout    << bimodal_single_bit_correct << "," << bimodal_single_bit_branch_count << ";" ;

      // we need to print a space after every output except the last one
      if(size_index != 6) {
        outfile << " ";
        cout    << " ";
      }

  }
  outfile << endl;
  cout    << endl;

  ////////////////////////////////////////////
  // Bimodal two bit predictor
  int bimodal_two_bit_correct = 0;
  int bimodal_two_bit_branch_count = 0;

  for(int size_index = 0; size_index <7; size_index++) {

      bimodal_two_bit_correct = 0;
      bimodal_two_bit_branch_count = 0;
    
      // Initialize the table
      int table_size = sizes[size_index];
      for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        bimodal_bit_table[i] = 0;
      }

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        bimodal_two_bit_branch_count++;

        // Get the index of the table
        int index = addr % table_size;

        if(isBimodalTwoBitPredictionCorrect(bimodal_bit_table, index, behavior)) {
          bimodal_two_bit_correct++;
        }
       
        updateBimodalTwoBitTable(bimodal_bit_table, index, behavior);

      }

      outfile << bimodal_two_bit_correct << "," << bimodal_two_bit_branch_count << ";" ;
      cout    << bimodal_two_bit_correct << "," << bimodal_two_bit_branch_count << ";" ;

      // we need to print a space after every output except the last one
      if(size_index != 6) {
        outfile << " ";
        cout    << " ";
      }

  }
  outfile << endl;
  cout    << endl;



  ////////////////////////////////////////////
  // Bimodal three bit predictor
  int bimodal_three_bit_correct = 0;
  int bimodal_three_bit_branch_count = 0;

  for(int size_index = 0; size_index <7; size_index++) {

      bimodal_three_bit_correct = 0;
      bimodal_three_bit_branch_count = 0;
    
      // Initialize the table
      int table_size = sizes[size_index];
      for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        bimodal_bit_table[i] = 0;
      }

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        bimodal_three_bit_branch_count++;

        // Get the index of the table
        int index = addr % table_size;

        if(isBimodalThreeBitPredictionCorrect(bimodal_bit_table, index, behavior)) {
          bimodal_three_bit_correct++;
        }
       
        updateBimodalThreeBitTable(bimodal_bit_table, index, behavior);

      }

      outfile << bimodal_three_bit_correct << "," << bimodal_three_bit_branch_count << ";" ;
      cout    << bimodal_three_bit_correct << "," << bimodal_three_bit_branch_count << ";" ;

      // we need to print a space after every output except the last one
      if(size_index != 6) {
        outfile << " ";
        cout    << " ";
      }

  }
  outfile << endl;
  cout    << endl;

  // Close the input and output files
  infile.close();
  outfile.close();

  return 0;
}
