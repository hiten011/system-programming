#!/bin/bash

cli="find ."
while getopts "n:t:s:h" opt
do
    case $opt in
        n)
            cli+=" -name '*$OPTARG*'"
            ;;
        t)
            cli+=" -name '*.$OPTARG'"
            ;;
        s)
            cli+=" -size +${OPTARG}c"
            ;;
        h)
            echo "Usage: $0 [-n name_pattern] [-t extension] [-s min_size_in_bytes] [-h]"
            exit 0
            ;;
        *)
            echo "Invalid option. Use -h for help."
            exit 1
            ;;
    esac
done

# Show and run the command
echo "Running: $cli"
eval "$cli"
