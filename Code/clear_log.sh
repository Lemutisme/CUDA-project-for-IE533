#!/bin/bash

# Prompt user for confirmation
echo "Are you sure you want to delete all files in the ./log directory?"
read -p "Type 'y' to confirm: " confirm

# Check user confirmation
if [ "$confirm" == "y" ]; then
  # Remove all files in ./log directory
  rm -rf ./log/**


  # Output success message
  echo "All files in ./log directory have been deleted."
else
  # Output cancel message
  echo "Operation canceled."
fi

