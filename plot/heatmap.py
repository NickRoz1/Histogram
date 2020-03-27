
import matplotlib.pyplot as plt
import numpy as np


def plot_heatmap(histogram, height, width, xmin, xmax, ymin, ymax):
    hist = np.array(histogram).reshape(height, width)
    plt.imshow(hist, cmap='viridis', extent=[xmin, xmax, ymax, ymin])
    plt.colorbar()
    plt.show()
    return 1
