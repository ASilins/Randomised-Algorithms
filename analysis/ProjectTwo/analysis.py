import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams.update({'font.size': 16})

#Exercise 7
# Helper function to read and process data
def load_data(filename):
    df = pd.read_csv(filename, sep=r'\s+|,', engine='python')  # handles both tabs and commas
    df.columns = ['n', 'time']
    df['avg_time'] = df['time'] / 1e9
    return df

# Load each dataset
hashing = load_data('ex7_hashing_with_chaining.csv')
sketch_128 = load_data('ex7_sketch_7.csv')
sketch_1024 = load_data('ex7_sketch_10.csv')
sketch_1048576 = load_data('ex7_sketch_20.csv')

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(hashing['n'], hashing['avg_time'], label='Hashing with Chaining', marker='o')
plt.plot(sketch_128['n'], sketch_128['avg_time'], label='Sketch r=2^7', marker='s')
plt.plot(sketch_1024['n'], sketch_1024['avg_time'], label='Sketch r=2^10', marker='^')
plt.plot(sketch_1048576['n'], sketch_1048576['avg_time'], label='Sketch r=2^20', marker='x')

plt.xscale('log', base=2)
plt.xlabel('n (log scale)')
plt.ylabel('Average update time (μs)')
plt.title('Average Update Time')
plt.legend()
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.savefig('ex_7_timings')

#Exercise 8:
import pandas as pd
import matplotlib.pyplot as plt

# Load data, explicitly setting the separator and skipping the header if needed
data = pd.read_csv('ex8_relative_error_4wise.csv', sep=',', names=['r', 'error'], skiprows=1)

# Convert r and error to numeric (in case any extra whitespace or parsing issues)
data['r'] = pd.to_numeric(data['r'], errors='coerce')
data['error'] = pd.to_numeric(data['error'], errors='coerce')

# Drop any rows with NaN values (could happen if there are malformed lines)
data = data.dropna()

# Group by r and compute average error
avg_error_by_r = data.groupby('r')['error'].mean().reset_index()

# Plotting
plt.figure(figsize=(10, 6))
plt.xscale('log', base=2)
plt.plot(avg_error_by_r['r'], avg_error_by_r['error'], marker='o', linestyle='-')
plt.title('Average Relative Error as Function of r')
plt.xlabel('r')
plt.ylabel('Average Relative Error')
plt.grid(True)
plt.xticks(avg_error_by_r['r'], fontsize=18)  # Larger x-axis ticks
plt.tight_layout()
plt.savefig('ex_8_avg_error_plot')

# Compute maximum error per r
max_error_by_r = data.groupby('r')['error'].max().reset_index()

# Plot
plt.figure(figsize=(10, 6))
plt.xscale('log', base=2)
plt.plot(max_error_by_r['r'], max_error_by_r['error'], marker='o', linestyle='-', color='red')
plt.title('Maximum Relative Error as Function of r')
plt.xlabel('r')
plt.ylabel('Maximum Relative Error')

plt.grid(True)
plt.xticks(max_error_by_r['r'], fontsize=18)
plt.tight_layout()

# Save the plot
plt.savefig('ex_8_max_error_plot.png')


#Exercise 9:
import pandas as pd
import matplotlib.pyplot as plt

# Load data, explicitly setting the separator and skipping the header if needed
data = pd.read_csv('ex9_relative_error_2wise.csv', sep=',', names=['r', 'error'], skiprows=1)

# Convert r and error to numeric (in case any extra whitespace or parsing issues)
data['r'] = pd.to_numeric(data['r'], errors='coerce')
data['error'] = pd.to_numeric(data['error'], errors='coerce')

# Drop any rows with NaN values (could happen if there are malformed lines)
data = data.dropna()

# Group by r and compute average error
avg_error_by_r = data.groupby('r')['error'].mean().reset_index()

# Plotting
plt.figure(figsize=(10, 6))
plt.xscale('log', base=2)
plt.plot(avg_error_by_r['r'], avg_error_by_r['error'], marker='o', linestyle='-')
plt.title('Average Relative Error as Function of r')
plt.xlabel('r')
plt.ylabel('Average Relative Error')
plt.grid(True)
plt.xticks(avg_error_by_r['r'], fontsize=18)  # Larger x-axis ticks
plt.tight_layout()
plt.savefig('ex_9_avg_error_plot')

# Compute maximum error per r
max_error_by_r = data.groupby('r')['error'].max().reset_index()

# Plot
plt.figure(figsize=(10, 6))
plt.xscale('log', base=2)
plt.plot(max_error_by_r['r'], max_error_by_r['error'], marker='o', linestyle='-', color='red')
plt.title('Maximum Relative Error as Function of r')
plt.xlabel('r')
plt.ylabel('Maximum Relative Error')

plt.grid(True)
plt.xticks(max_error_by_r['r'], fontsize=18)
plt.tight_layout()

# Save the plot
plt.savefig('ex_9_max_error_plot.png')