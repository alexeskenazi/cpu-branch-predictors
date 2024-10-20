# cs-320-project1-fall24

## CS320 Fall 2024: Project 1 - CPU Branch Prediction Simulation with Multiple Algorithms

**Full Name:** Alex Eskenazi  
**GitHub ID:** alexeskenazi  
**BU-ID:** aeskena1  
**B-Number:** B00944943  
**Discord Name:** palexxx

## Notes

- See the Project_Fall24.dox for the teacher's prompt.
_ "sh run_all.sh"  will run for all provided inputs and outputs.
- "sh pack_files.sh" will package the files for submission.
- I noticed that some output files in the `correct_outputs` folder have a newline at the end and some don't. This causes `diff` to fail for some of them.
- Use: diff -bB to ignore the space and new line differences
- All tests pass.

## Overview

This project aims to measure the effectiveness of several branch direction predictors on several traces of conditional branch instructions.
Each trace contains a large number of branch instructions. Each line in the trace contains the following information for each branch: the program counter (expressed as a word address), the actual outcome of the branch. Several trace files are provided for evaluating your predictor designs.

Predictors Implemented

1. Always Taken Predictor
Predicts that every branch is taken.
2. Always Non-Taken Predictor
Predicts that every branch is not taken.
3. Bimodal Predictors:
    - 1-bit Predictor: A simple predictor using 1-bit history for each entry.
    - 2-bit Predictor: A saturating 2-bit counter predictor with four states.
    - 3-bit Predictor: A more complex predictor with a 6-state machine and 3 bits of history.

    The accuracy of the 1-bit, 2-bit, and 3-bit predictors is evaluated with varying table sizes of 4, 8, 32, 64, 256, 1024, and 4096 entries.
    

5. Gshare Predictor
Combines the program counter (PC) with a global history register using XOR to index into the predictor table. The history length is varied between 2 and 12 bits.
6. Tournament Predictor
Selects between Gshare and the 3-bit Bimodal predictor for each branch instruction, using a 2-bit counter to track the preferred predictor.
