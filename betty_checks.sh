#!/bin/bash

# This script helps check our code for style and documentation using Betty

# Function to check code style
style_check() {
  if [ $# -lt 1 ]; then
    echo "Usage: betty-style <filename>"
    exit 1
  fi

  for file in "$@"; do
    echo "Checking style for $file"
    betty-style.pl "$file"
  done
}

# Function to check code documentation
doc_check() {
  if [ $# -lt 1 ]; then
    echo "Usage: betty-doc <filename>"
    exit 1
  fi

  for file in "$@"; do
    echo "Checking documentation for $file"
    betty-doc.pl "$file"
  done
}

# Function to combine both style and documentation checks
betty_check() {
  if [ $# -lt 1 ]; then
    echo "Usage: betty <filename>"
    exit 1
  fi

  for file in "$@"; do
    echo "Running Betty checks for $file"
    betty-style.pl "$file"
    betty-doc.pl "$file"
  done
}

# Check if Betty scripts are available
if ! command -v betty-style.pl &> /dev/null || ! command -v betty-doc.pl &> /dev/null; then
  echo "Betty style or doc script not found in PATH"
  exit 1
fi

# Run the combined Betty check
betty_check "$@"

