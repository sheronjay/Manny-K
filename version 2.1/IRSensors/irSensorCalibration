//use this code to calibrate ir sensors.
//how the calibration is done,
    //this code will read the value at the analog pin every 4 seconds
    //increment the distance to the wall physically every four seconds from 4cm till 20cm

    #define sensorPin 34  // Pin number

    int sensorValue;
    int valueList[17];
    int index = 0;
    
    void setup(){
        Serial.begin(9600);
        pinMode(sensorPin, INPUT);  
        Serial.println("IR Distance Sensor Calibration");
        delay(2000);
        Serial.println("Start");
    }
    
    void loop(){
        sensorValue = analogRead(sensorPin);
        valueList[index] = sensorValue;
        Serial.print("Raw Value: ");  
        Serial.println(sensorValue);  // Print sensor value
        
        index++;  
        
        delay(4000);
        if(index == 17){  
            printValues();  
    }
    
    // Added missing function to print values
    void printValues() {
        Serial.println("All calibration values:");
        for(int i = 0; i < 17; i++) {
            Serial.print(i + 4);  
            Serial.print("cm: ");
            Serial.println(valueList[i]);
        }
        
        while(1) {
            // Infinite loop to stop execution after calibration
        }
    }
    }