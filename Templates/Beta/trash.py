import numpy as np
import matplotlib.pyplot as plt

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def plot_decision_boundary(X, y, W, b):
    '''Plots the decision boundary for a 2D dataset and labels.'''
    
    # Scatter plot of the data
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.RdYlBu, s=30)
    
    # Create a grid of points to evaluate the decision boundary
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100),
                         np.linspace(y_min, y_max, 100))
    
    # Calculate decision boundary: w1*x1 + w2*x2 + b = 0
    Z = W[0] * xx + W[1] * yy + b
    Z = sigmoid(Z)  # Apply sigmoid function to decision boundary
    
    # Plot decision boundary using contour plot (where Z = 0.5)
    plt.contour(xx, yy, Z, levels=[0.5], colors='black', linewidths=2)
    
    # Show plot
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.title('Decision Boundary (Logistic Regression)')
    plt.show()

# Example usage
X = np.array([[1, 2], [2, 3], [3, 3], [4, 5], [5, 6]])  # 2D feature array
y = np.array([1, 1, -1, -1, 1])  # Labels (+1 or -1)

# Example parameters learned via gradient descent
W = np.array([1, -1])  # Parameters (weights)
b = -1  # Bias term

plot_decision_boundary(X, y, W, b)
