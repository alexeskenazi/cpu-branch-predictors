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

  ////////////////////////////////////////////
  // Bimodal single bit predictor

  // Creat table of table_size entries and intialize to 0 meaning not taken
  int max_table_size = MAX_TABLE_SIZE;
  int bimodal_single_bit_table[MAX_TABLE_SIZE] = {0};

  int sizes[7] = {4, 8, 32, 64, 256, 1024, 4096};

  for(int size_index = 0; size_index <7; size_index++) {

      bimodal_single_bit_correct = 0;
      bimodal_single_bit_branch_count = 0;
      bimodal_two_bit_correct = 0;
      bimodal_two_bit_branch_count = 0;
    
      // Initialize the table
      int table_size = sizes[size_index];
      for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        bimodal_single_bit_table[i] = 0;
      }

      infile.clear();
      infile.seekg(0, ios::beg);
      while (infile >> std::hex >> addr >> behavior) {
        bimodal_single_bit_branch_count++;

        // Get the index of the table
        int index = addr % table_size;

        // cout << addr;
        // outfile << addr;
        // cout << " Index: " << index << endl;

        // Check if the prediction is correct
        if (bimodal_single_bit_table[index] == 0 && behavior == "NT") {
          bimodal_single_bit_correct++;
        } else if (bimodal_single_bit_table[index] == 1 && behavior == "T") {
          bimodal_single_bit_correct++;
        }
        // Update the table
        if (behavior == "T") {
          bimodal_single_bit_table[index] = 1;
        } else {
          bimodal_single_bit_table[index] = 0;
        }

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

  // Close the input and output files
  infile.close();
  outfile.close();

  return 0;
}
