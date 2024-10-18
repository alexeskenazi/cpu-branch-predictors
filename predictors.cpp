#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "predictors.h"
#include "BimodalSingleBitPredictor.h"
#include "BimodalTwoBitPredictor.h"
#include "BimodalThreeBitPredictor.h"

using namespace std;


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
  // Creat table of table_size entries and intialize to 0 meaning not taken
  int bimodal_bit_table[MAX_TABLE_SIZE] = {0};

  int sizes[7] = {4, 8, 32, 64, 256, 1024, 4096};

  ////////////////////////////////////////////
  // Bimodal single bit predictor
  BimodalSingleBitPredictor bsbp;

  // Bimodal single bit predictor
  for(int size_index = 0; size_index <7; size_index++) {

      int table_size = sizes[size_index];
      bsbp.setTableSize(table_size);
      bsbp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        bsbp.branchCount++;

        if(bsbp.isCorrectPrediction(addr, behavior)) {
          bsbp.correctCount++;
        }
       
        bsbp.updateTable(addr, behavior);
      }

      outfile << bsbp.correctCount << "," << bsbp.branchCount << ";" ;
      cout    << bsbp.correctCount << "," << bsbp.branchCount << ";" ;

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
  BimodalTwoBitPredictor b2bp;

  for(int size_index = 0; size_index <7; size_index++) {

      int table_size = sizes[size_index];
      b2bp.setTableSize(table_size);
      b2bp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        b2bp.branchCount++;

        if(b2bp.isCorrectPrediction(addr, behavior)) {
          b2bp.correctCount++;
        }
       
        b2bp.updateTable(addr, behavior);
      }

      outfile << b2bp.correctCount << "," << b2bp.branchCount << ";" ;
      cout    << b2bp.correctCount << "," << b2bp.branchCount << ";" ;

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
    BimodalThreeBitPredictor b3bp;
  
    
  for(int size_index = 0; size_index <7; size_index++) {

      int table_size = sizes[size_index];
      b3bp.setTableSize(table_size);
      b3bp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        b3bp.branchCount++;

        if(b3bp.isCorrectPrediction(addr, behavior)) {
          b3bp.correctCount++;
        }
       
        b3bp.updateTable(addr, behavior);
      }

      outfile << b3bp.correctCount << "," << b3bp.branchCount << ";" ;
      cout    << b3bp.correctCount << "," << b3bp.branchCount << ";" ;

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
