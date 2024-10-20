#!/bin/bash

echo "Compiling the code..."
make

echo "short_trace1.txt..."
./predictors traces/short_trace1.txt short_trace1_output.txt

# Check if the files are the same
if diff -bB correct_outputs/short1.txt short_trace1_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for short_trace1_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! short_trace1_output"
fi



echo "short_trace2.txt..."
./predictors traces/short_trace2.txt short_trace2_output.txt

# Check if the files are the same
if diff -bB correct_outputs/short2.txt short_trace2_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for short_trace2_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! short_trace2_output"
fi


echo "short_trace3.txt..."
./predictors traces/short_trace3.txt short_trace3_output.txt

# Check if the files are the same
if diff -bB correct_outputs/short3.txt short_trace3_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for short_trace3_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! short_trace3_output"
fi



echo "long_trace1.txt..."
./predictors traces/long_trace1.txt long_trace1_output.txt

# Check if the files are the same
if diff -bB correct_outputs/long1.txt long_trace1_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for long_trace1_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! long_trace1_output"
fi



echo "long_trace2.txt..."
./predictors traces/long_trace2.txt long_trace2_output.txt

# Check if the files are the same
if diff -bB correct_outputs/long2.txt long_trace2_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for long_trace2_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! long_trace2_output"
fi



echo "long_trace3.txt..."
./predictors traces/long_trace3.txt long_trace3_output.txt

# Check if the files are the same
if diff -bB correct_outputs/long3.txt long_trace3_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for long_trace3_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! long_trace3_output"
fi


echo "sec.txt..."
./predictors traces/sec_trace2.txt sec_trace2_output.txt

# Check if the files are the same
if diff -bB correct_outputs/sec.txt sec_trace2_output.txt > /dev/null; then
    echo "SUCCESS: The output matches! for sec_trace2_output"
else
    echo "FAILURE!!!!!!!!: The output does not match! sec_trace2_output"
fi
