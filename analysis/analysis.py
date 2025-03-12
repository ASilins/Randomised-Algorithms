import pandas as pd
import matplotlib.pyplot as plt

# Analysis for build and query time
df = pd.read_csv("run1/results.csv")
df["n"] = df["n"].astype(int)
df["build"] = df["build"].astype(int)
df["query"] = df["query"].astype(int)
df = df.sort_values(by=["n"])

plt.figure(figsize=(10, 5))

plt.xscale("log", base=2)
for algorithm, data in df.groupby("algorithm"):
    plt.plot(data["n"], data["build"], marker='o', label=f"{algorithm} - Build")
plt.xlabel("List size: n")
plt.ylabel("Build Time (ms)")
plt.title("Algorithm Build Time")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("algorithm_build_time.png")

plt.figure(figsize=(10, 5))

plt.xscale("log", base=2)
for algorithm, data in df.groupby("algorithm"):
    plt.plot(data["n"], data["query"], marker='o', label=f"{algorithm} - Query")
plt.xlabel("List size: n")
plt.ylabel("Query Time (ms)")
plt.title("Algorithm Query Time")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("algorithm_query_time.png")

# Analysis for largest linked list
df = pd.read_csv("run1/linked_list.csv")
df["n"] = df["n"].astype(int)
df["count"] = df["count"].astype(int)
df = df.sort_values(by=["n"])

plt.figure(figsize=(10, 5))

plt.xscale("log", base=2)
plt.scatter(df["n"], df["count"], marker='o', label="Largest Linked List")
plt.xlabel("List size: n")
plt.ylabel("Linked list size")
plt.title("Largest linked list")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("largest_linked_list.png")