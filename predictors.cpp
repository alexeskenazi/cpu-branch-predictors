#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "predictors.h"
#include "BimodalSingleBitPredictor.h"
#include "BimodalTwoBitPredictor.h"
#include "BimodalThreeBitPredictor.h"
#include "GsharePredictor.h"
#include "TournamentPredictor.h"

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
  BimodalSingleBitPredictor b1bp;

  // Bimodal single bit predictor
  for(int size_index = 0; size_index <7; size_index++) {

      int table_size = sizes[size_index];
      b1bp.setTableSize(table_size);
      b1bp.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        b1bp.branchCount++;

        int prediction = b1bp.getPrediction(addr);
        if(b1bp.isCorrectPrediction(prediction, behavior)) {
          b1bp.correctCount++;
        }
       
        b1bp.updateTable(addr, behavior);
      }

      outfile << b1bp.correctCount << "," << b1bp.branchCount << ";" ;
      cout    << b1bp.correctCount << "," << b1bp.branchCount << ";" ;

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

        int prediction = b2bp.getPrediction(addr);
        if(b2bp.isCorrectPrediction(prediction, behavior)) {
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

        int prediction = b3bp.getPrediction(addr);
        if(b3bp.isCorrectPrediction(prediction, behavior)) {
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
  

  ////////////////////////////////////////////
  // Gshare three bit predictor

  cout << "Gshare three bit predictor" << endl;
  GsharePredictor gshare;
    
  for(int bits = 2; bits <=12; bits++) {

      gshare.setTableSize(MAX_TABLE_SIZE);
      gshare.reset();

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        gshare.branchCount++;

        int prediction = gshare.getPrediction(addr);
        if(gshare.isCorrectPrediction(prediction, behavior)) {
          gshare.correctCount++;
        }

        gshare.updateTable(addr, behavior);
      }

      outfile << gshare.correctCount << "," << gshare.branchCount << ";" ;
      cout    << gshare.correctCount << "," << gshare.branchCount << ";" ;

      // we need to print a space after every output except the last one
      if(bits != 12) {
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
