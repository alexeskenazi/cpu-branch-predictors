#pragma once
#include <string>
#include <bitset>
#include <sstream>
using namespace std;

string intToBinaryString(unsigned int num) {
  // Convert the number to a binary string using bitset
  bitset<32> bits(num);  // Assuming 32-bit unsigned int

  // Create a string stream to format the output
  stringstream ss;

  // Prefix with '0x'
  ss << "0x";

  // Output the bits in groups of 4 for readability, simulating a hex-like look
  for (int i = 31; i >= 0; i--) {
    ss << bits[i];
    if (i % 4 == 0 && i != 0) {
      ss << '_'; // Optional separator for readability (you can remove this if not needed)
    }
  }

  return ss.str();
}
