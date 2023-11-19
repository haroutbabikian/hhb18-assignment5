import pandas as pd
import matplotlib.pyplot as plt

# Read data from CSV file
df = pd.read_csv('results.csv')

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(df['Threads'], df['Time'], marker='o', label='Runtime')
plt.xlabel('Number of Threads')
plt.ylabel('Time (seconds)')
plt.title('Runtime vs Number of Threads')
plt.legend()
plt.grid(True)
plt.savefig('runtime_plot.png')
plt.show()