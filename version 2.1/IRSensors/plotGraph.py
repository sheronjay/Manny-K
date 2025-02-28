import matplotlib.pyplot as plt

distance = [4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
sensorValues = []

plt.plot(distance, sensorValues, linesyle='-', color='b')

plt.xlabel("Distance")
plt.ylabel("Sensor Values")
plt.title("Distance Vs Sensor Value")

plt.grid(True)
plt.show()
