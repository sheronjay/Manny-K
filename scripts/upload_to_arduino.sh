#!/bin/bash

# Load environment variables from .env file if it exists
if [ -f .env ]; then
    export $(grep -v '^#' .env | xargs)
fi

SKETCH_PATH=${SKETCH_PATH}  # Path to your sketch folder
BOARD=${BOARD}              # Board identifier (e.g., Arduino Uno)
PORT=${PORT}                # Port your board is connected to
FQBN=$BOARD                 # Fully Qualified Board Name

# Check if arduino-cli is installed
if ! command -v arduino-cli &> /dev/null; then
    echo "arduino-cli is not installed. Please install it first."
    exit 1
fi

# Compile the sketch
echo "Compiling sketch..."
arduino-cli compile --fqbn $FQBN --output-dir build $SKETCH_PATH
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Locate the compiled .hex file
HEX_FILE=$(find build -name "*.hex" | head -n 1)
if [ -z "$HEX_FILE" ]; then
    echo "Compiled .hex file not found!"
    exit 1
fi

# Check if avrdude is installed
if ! command -v avrdude &> /dev/null; then
    echo "avrdude is not installed. Please install it first."
    exit 1
fi

# Define avrdude parameters based on the board type
case $BOARD in
    "arduino:avr:uno")
        MCU="atmega328p"
        PROGRAMMER="arduino"
        ;;
    "arduino:avr:nano")
        MCU="atmega328p"
        PROGRAMMER="arduino"
        ;;
    "arduino:avr:mega")
        MCU="atmega2560"
        PROGRAMMER="wiring"
        ;;
    *)
        echo "Unsupported board: $BOARD"
        exit 1
        ;;
esac

# Upload using avrdude
echo "Uploading sketch with avrdude..."
avrdude -c $PROGRAMMER -p $MCU -P $PORT -b 115200 -U flash:w:$HEX_FILE:i
if [ $? -ne 0 ]; then
    echo "Upload failed."
    exit 1
fi

echo "Sketch uploaded successfully!"
