#!/bin/bash

# Temporary folder to store processed files
temp_dir=$(mktemp -d)
trap "rm -rf $temp_dir" EXIT

# Extract all student numbers
for file in "$@"; do
    tail -n +2 "$file" | cut -d',' -f1
done | sort -u > "$temp_dir/student_ids"

# Start building output
# First, extract header line
header="number"
for file in "$@"; do
    label=$(head -1 "$file" | cut -d',' -f2)
    header+=",$label"
done

echo "$header"

# For each student ID, build their line
while read -r id; do
    line="$id"
    for file in "$@"; do
        mark=$(grep "^$id," "$file" | cut -d',' -f2)
        [[ -z "$mark" ]] && mark="-"  # replace empty with dash
        line+=",$mark"
    done
    echo "$line"
done < "$temp_dir/student_ids"
