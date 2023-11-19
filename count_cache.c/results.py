import pandas as pd
import matplotlib.pyplot as plt

# Read data from CSV file
df = pd.read_csv('results_private.csv')

# Calculate Correctness Rate as a percentage
df['Correctness Rate (%)'] = (df['Verified'] / df['Test'].nunique()) * 100

# Plotting
plt.figure(figsize=(10, 6))

# Plot Time vs Number of Threads
plt.subplot(2, 1, 1)
for num_threads in df['Threads'].unique():
    data = df[df['Threads'] == num_threads]
    plt.plot(data['Test'], data['Time'], marker='o', label=f'Threads: {num_threads}')

plt.xlabel('Test')
plt.ylabel('Time (seconds)')
plt.title('Runtime vs Test for Different Number of Threads')
plt.legend()
plt.grid(True)

# Plot Correctness Rate vs Number of Threads
plt.subplot(2, 1, 2)
correctness_rate = df.groupby('Threads')['Correctness Rate (%)'].mean()
plt.bar(correctness_rate.index, correctness_rate.values, color='green')
plt.xlabel('Number of Threads')
plt.ylabel('Correctness Rate (%)')
plt.title('Average Correctness Rate vs Number of Threads')
plt.ylim(0, 100)  # Set the y-axis limit to 0-100%
plt.grid(True)

plt.tight_layout()
plt.savefig('plot_results.png')
plt.show()