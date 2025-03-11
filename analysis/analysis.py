import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")
df["n"] = df["n"].astype(int)
df["build"] = df["build"].astype(int)
df["query"] = df["query"].astype(int)
df = df.sort_values(by=["n"])

plt.figure(figsize=(10, 5))

plt.xscale("log")
for algorithm, data in df.groupby("algorithm"):
    plt.plot(data["n"], data["build"], marker='o', label=f"{algorithm} - Build")
plt.xlabel("List size: n")
plt.ylabel("Build Time (microseconds)")
plt.title("Algorithm Build Time Analysis")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("algorithm_build_time.png")

plt.figure(figsize=(10, 5))

plt.xscale("log")
for algorithm, data in df.groupby("algorithm"):
    plt.plot(data["n"], data["query"], marker='o', label=f"{algorithm} - Query")
plt.xlabel("List size: n")
plt.ylabel("Query Time (microseconds)")
plt.title("Algorithm Query Time Analysis")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("algorithm_query_time.png")
