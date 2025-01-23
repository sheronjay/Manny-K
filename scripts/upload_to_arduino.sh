#!/bin/bash

# Define variables
# Load environment variables from .env file if it exists
if [ -f .env ]; then
    export $(grep -v '^#' .env | xargs)
fi

SKETCH_PATH=${SKETCH_PATH}  # Path to your sketch folder
BOARD=${BOARD}   # Board identifier (e.g., Arduino Uno)
PORT=${PORT}         # Port your board is connected to
FQBN=$BOARD               # Fully Qualified Board Name

# Check if arduino-cli is installed
if ! command -v arduino-cli &> /dev/null; then
    echo "arduino-cli is not installed. Please install it first."
    exit 1
fi

# Compile the sketch
echo "Compiling sketch..."
arduino-cli compile --fqbn $FQBN $SKETCH_PATH
# arduino-cli compile --fqbn $FQBN --clean $SKETCH_PATH
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Upload the compiled sketch
echo "Uploading sketch..."
arduino-cli upload -p $PORT --fqbn $FQBN $SKETCH_PATH
if [ $? -ne 0 ]; then
    echo "Upload failed."
    exit 1
fi

echo "Sketch uploaded successfully!"
