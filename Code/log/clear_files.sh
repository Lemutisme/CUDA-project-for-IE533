#!/bin/bash

# Prompt user for confirmation
echo "Are you sure you want to delete all files in the current directory?"
read -p "Type 'y' to confirm: " confirm

# Check user confirmation
if [ "$confirm" == "y" ]; then
  # Remove all files in current directory
  rm -f *

  # Output success message
  echo "All files in current directory have been deleted."
else
  # Output cancel message
  echo "Operation canceled."
fi
