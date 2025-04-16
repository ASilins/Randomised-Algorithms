import pandas as pd
import matplotlib.pyplot as plt

# Load the data
file_path = 'ex8_relative_error_4wise.csv'
df = pd.read_csv(file_path, header=None, names=['r', 'error'], sep='\t')

# Compute average error for each r
average_errors = df.groupby('r')['error'].mean()

# Plotting
plt.figure(figsize=(8, 5))
plt.plot(average_errors.index, average_errors.values, marker='o')
plt.title('Average Relative Error vs r')
plt.xlabel('r')
plt.ylabel('Average Relative Error')
plt.grid(True)
plt.tight_layout()
plt.show()
