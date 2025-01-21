#!/bin/bash

if [ -f .env ]; then
    export $(grep -v '^#' .env | xargs)
fi

PORT=${PORT} 
BAUD_RATE="9600"
FQBN=${BOARD}

# Run the arduino-cli monitor command
arduino-cli monitor -p $PORT -b $BAUD_RATE --fqbn $FQBN