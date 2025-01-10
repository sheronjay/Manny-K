import serial
import time

def connect_to_hc05(port, baudrate=9600, timeout=1):
    try:
        print(f"Connecting to {port} with baudrate {baudrate}...")
        connection = serial.Serial(port, baudrate, timeout=timeout)
        if connection.is_open:
            print("Connection established.")
        return connection
    except serial.SerialException as e:
        print(f"Failed to connect: {e}")
        return None

def update_variables(connection, variables):
    for var_name, var_value in variables.items():
        message = f"{var_name}:{var_value}\n"
        print(f"Sending: {message.strip()}")
        connection.write(message.encode())
        time.sleep(0.1)  # Short delay to allow the HC-05 to process

def read_from_hc05(connection):
    try:
        while True:
            if connection.in_waiting > 0:
                response = connection.readline().decode().strip()
                print(f"Received: {response}")
    except KeyboardInterrupt:
        print("\nStopped reading from HC-05.")

def main():
    port = "/dev/rfcomm0"  # Replace with your HC-05 port
    baudrate = 9600        # Default baud rate for HC-05
    variables_to_update = {
        "var1": 42,
        "var2": 3.14,
        "var3": "Hello"
    }

    connection = connect_to_hc05(port, baudrate)

    if connection:
        try:
            update_variables(connection, variables_to_update)
            print("Listening for responses (press Ctrl+C to stop)...")
            read_from_hc05(connection)
        finally:
            connection.close()
            print("Connection closed.")

if __name__ == "__main__":
    main()
