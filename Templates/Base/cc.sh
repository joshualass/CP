#!/bin/bash

# Usage:
# bash cc.sh CF 2086 F
# bash cc.sh ABC 400 G
# bash cc.sh ARC 200 F
# bash cc.sh AGC 070 E

# Check if the correct number of arguments are passed
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <prefix> <number> <last_file_letter>"
    echo "Prefixes: CF, ABC, ARC, AGC"
    exit 1
fi

# Extract arguments
PREFIX=$(echo "$1" | tr '[:lower:]' '[:upper:]')
NUMBER=$2
LAST_FILE=$(echo "$3" | tr '[:lower:]' '[:upper:]')
FOLDER="$PREFIX$NUMBER"

# Set target directory based on the prefix
if [ "$PREFIX" == "CF" ]; then
    BASE_DIR="/Users/dishwasherbob/Desktop/CP/Solutions/Contests/CodeForces"
elif [ "$PREFIX" == "ABC" ] || [ "$PREFIX" == "ARC" ] || [ "$PREFIX" == "AGC" ]; then
    BASE_DIR="/Users/dishwasherbob/Desktop/CP/Solutions/Contests/AC/$PREFIX"
else
    echo "Unknown prefix: $PREFIX. Please use CF, ABC, ARC, or AGC."
    exit 1
fi

TARGET_DIR="$BASE_DIR/$FOLDER"

# Create the target directory
mkdir -p "$TARGET_DIR"

# Generate files from A<number>.cpp to <LAST_FILE><number>.cpp
for LETTER in $(seq "$(printf "%d" "'A")" "$(printf "%d" "'$LAST_FILE")"); do
    FILE_NAME="$(printf "\\$(printf '%03o' "$LETTER")")$NUMBER.cpp"
    touch "$TARGET_DIR/$FILE_NAME"
done

echo "Created folder $FOLDER with files A$NUMBER.cpp to $LAST_FILE$NUMBER.cpp in $BASE_DIR"