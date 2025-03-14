import os
import pandas as pd
import matplotlib.pyplot as plt

run = "./run_final/"
os.makedirs(run, exist_ok=True)

# Load and process results.csv
df = pd.read_csv("results.csv")
df["n"] = df["n"].astype(int)
df["build"] = df["build"].astype(int)
df["query"] = df["query"].astype(int)

# Compute averages
df = df.groupby(["algorithm", "n"], as_index=False).mean()

# Normalize by n
df["build"] /= df["n"]
df["query"] /= df["n"]

# Plot Build Time per element
plt.figure(figsize=(10, 5))
plt.xscale("log", base=2)

for algorithm, data in df.groupby("algorithm"):
    plt.plot(data["n"], data["build"], marker='o', label=f"{algorithm} - Insertion time")
plt.xlabel("List size: n")
plt.ylabel("Insertion Time per Element (μs)")
plt.title("Algorithm Insertion Time per Element")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig(run + "algorithm_insertion_time_per_element.png")

# Plot Query Time per element
plt.figure(figsize=(10, 5))
plt.xscale("log", base=2)

for algorithm, data in df.groupby("algorithm"):
    plt.plot(data["n"], data["query"], marker='o', label=f"{algorithm} - Query time")
plt.xlabel("List size: n")
plt.ylabel("Query Time per Element (μs)")
plt.title("Algorithm Query Time per Element")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig(run + "algorithm_query_time_per_element.png")

# Plot Total Time per element
plt.figure(figsize=(10, 5))
plt.xscale("log", base=2)

for algorithm, data in df.groupby("algorithm"):
    total_time = (data["build"] + data["query"])  # Already divided by n
    plt.plot(data["n"], total_time, marker='o', linestyle='-', label=f"{algorithm} - Total time")
plt.xlabel("List size: n")
plt.ylabel("Total Time per Element (μs)")
plt.title("Algorithm Total Time per Element (Insertion + Query)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig(run + "algorithm_total_time_per_element.png")

# Load and process linked_list.csv
df_linked = pd.read_csv("linked_list.csv")
df_linked["n"] = df_linked["n"].astype(int)
df_linked["count"] = df_linked["count"].astype(int)

# Compute average linked list size
df_linked = df_linked.groupby("n", as_index=False).mean()

plt.figure(figsize=(10, 5))
plt.xscale("log", base=2)
plt.plot(df_linked["n"], df_linked["count"], marker='o', linestyle='-', label="Largest Linked List")  # Line added
plt.xlabel("List size: n")
plt.ylabel("Linked list size")
plt.title("Largest Linked List")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig(run + "largest_linked_list.png")