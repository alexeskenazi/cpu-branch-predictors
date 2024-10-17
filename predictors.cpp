#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;


#define MAX_TABLE_SIZE 4096

// Always taken predictor
int always_taken_predictor_correct = 0;
int always_taken_predictor_branch_count = 0;

// Always not taken predictor
int always_not_taken_predictor_correct = 0;
int always_not_taken_predictor_branch_count = 0;

// Bimodal single bit predictor
int bimodal_single_bit_correct = 0;
int bimodal_single_bit_branch_count = 0;
int bimodal_two_bit_correct = 0;
int bimodal_two_bit_branch_count = 0;


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


  // // The following loop will read a line at a time
  // while (getline(infile, line)) {
  //   // Now we have to parse the line into its two pieces
  //   stringstream s(line);
  //   s >> std::hex >> addr >> behavior;

  //   // Now we can output it to both file and console
  //   // cout << addr;
  //   // outfile << addr;
  //   if (behavior == "T") {
  //     always_taken_predictor_branch_count++;
  //     // cout << " -> taken" << endl;
  //     // outfile << " -> taken" << endl;
  //   } else {
  //     always_taken_predictor_branch_count++;
  //     always_taken_predictor_correct++;
  //     // cout << " -> not taken" << endl;
  //     // outfile << " -> not taken" << endl;
  //   }
  // }

  ////////////////////////////////////////////
  // Always taken predictor
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


  // Close the input and output files
  infile.close();
  outfile.close();

  return 0;
}
