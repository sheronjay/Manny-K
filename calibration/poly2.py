import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression

# Step 1: Read data from CSV file
# Make sure the CSV file has two columns: 'Sensor' and 'Actual'
csv_file = 'sensor_data.csv'  # Replace this with your CSV file path
data = pd.read_csv(csv_file)
print(data)

# Extract sensor readings and actual distances
sensor_readings = data['Sensor'].values
print(sensor_readings)
actual_distances = data['Actual'].values
print(actual_distances)

# Step 2: Choose the degree of the polynomial
degree = 2 

# Step 3: Create polynomial features
poly = PolynomialFeatures(degree=degree)
sensor_readings_poly = poly.fit_transform(sensor_readings.reshape(-1, 1))

# Step 4: Train the polynomial regression model
model = LinearRegression()
model.fit(sensor_readings_poly, actual_distances)

# Step 5: Get the polynomial coefficients
coefficients = model.coef_
intercept = model.intercept_

# Step 6: Define the polynomial equation as a function
def polynomial_equation(x):
    return sum(coeff * (x ** i) for i, coeff in enumerate([intercept] + list(coefficients[1:])))

# Step 7: Test the model and visualize the fit
sensor_readings_test = np.linspace(min(sensor_readings), max(sensor_readings), 100)
predicted_distances = model.predict(poly.transform(sensor_readings_test.reshape(-1, 1)))

def plot_polynomial_regressions(sensor_readings, actual_distances, degrees):
    """
    Plots polynomial regression fits for multiple degrees.

    Parameters:
    - sensor_readings: Array-like, the sensor readings.
    - actual_distances: Array-like, the actual distances.
    - degrees: List of integers, the degrees of the polynomials to test.
    """
    plt.figure(figsize=(10, 6))
    
    # Scatter the original data
    plt.scatter(sensor_readings, actual_distances, color='blue', label='Actual Data')
    
    # Generate test points for plotting
    sensor_readings_test = np.linspace(min(sensor_readings), max(sensor_readings), 100).reshape(-1, 1)
    
    for degree in degrees:
        # Create polynomial features
        poly = PolynomialFeatures(degree=degree)
        sensor_readings_poly = poly.fit_transform(sensor_readings.reshape(-1, 1))
        sensor_readings_test_poly = poly.transform(sensor_readings_test)
        
        # Train the model
        model = LinearRegression()
        model.fit(sensor_readings_poly, actual_distances)
        
        # Predict values
        predicted_distances = model.predict(sensor_readings_test_poly)
        
        # Plot the polynomial regression line
        plt.plot(sensor_readings_test, predicted_distances, label=f'Degree {degree}')
        
        # Extract the coefficients
        coefficients = model.coef_
        intercept = model.intercept_
        
        # Print the polynomial equation
        equation_terms = " + ".join(
            [f"{coeff:.3f}*x^{i}" if i > 0 else f"{intercept:.3f}" 
             for i, coeff in enumerate([intercept] + list(coefficients[1:]))]
        )
        print(f"Degree {degree} Polynomial Equation: y = {equation_terms}")
    # Add labels and legend
    plt.xlabel('Sensor Reading')
    plt.ylabel('Actual Distance')
    plt.title('Polynomial Regression Fits')
    plt.legend()
    plt.show()

# Plot the results
plot_polynomial_regressions(sensor_readings, actual_distances, [1, 2, 3])

# Output the polynomial equation
equation_terms = " + ".join([f"{coeff:.3f}*x^{i}" if i > 0 else f"{intercept:.3f}" 
                             for i, coeff in enumerate([intercept] + list(coefficients[1:]))])
print(f"Polynomial Equation: y = {equation_terms}")
