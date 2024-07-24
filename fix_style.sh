#!/bin/bash

# Fix trailing whitespace
for file in "$@"; do
    sed -i 's/[ \t]*$//' "$file"
done

# Convert spaces to tabs (assuming 4 spaces per tab)
for file in "$@"; do
    unexpand --first-only --tabs=4 "$file" > temp && mv temp "$file"
done

# Ensure lines are not over 80 characters
for file in "$@"; do
    while read -r line; do
        if [ ${#line} -gt 80 ]; then
            echo "Warning: line over 80 characters in $file"
        fi
    done < "$file"
done

