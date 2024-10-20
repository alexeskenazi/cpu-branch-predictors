#!/bin/bash

# Replace this with your BU-ID
BU_ID="aeskena1"

# Step 1: Create a new directory with your BU-ID
mkdir $BU_ID

# Step 2: Copy all relevant files into this directory, excluding .o files, executables, and traces
# Replace 'source_directory' with the directory where your code files are located
cp ./*.c ./*.h $BU_ID/


# Step 3: Create a tar/gzipped archive of the directory
tar -czvf $BU_ID.tar.gz $BU_ID/

# Confirmation message
echo "Files have been packaged into $BU_ID.tar.gz"
