import sys
import os
import csv
import matplotlib.pyplot as plt

if len(sys.argv) < 3:
    print("Usage: plot_results.py <outdir> <n> [measure]")
    sys.exit(2)

outdir = sys.argv[1]
n = sys.argv[2]
measure = sys.argv[3] if len(sys.argv) > 3 else "time"
filename = os.path.join(outdir, f"{n}_stress.csv")
if not os.path.exists(filename):
    print("CSV file not found:", filename)
    sys.exit(1)

runs = []
times = []
throughputs = []
with open(filename, newline='') as csvfile:
    rdr = csv.DictReader(csvfile)
    for row in rdr:
        runs.append(int(row['run']))
        times.append(float(row['time_s']))
        if 'throughput_rows_s' in row:
            throughputs.append(float(row['throughput_rows_s']))

if not runs:
    print("No data in CSV")
    sys.exit(1)

plt.figure(figsize=(8,4))
if measure == "throughput" and len(throughputs) == len(times):
    plt.plot(runs, throughputs, marker='o')
    plt.ylabel('throughput (rows/s)')
else:
    plt.plot(runs, times, marker='o')
    plt.ylabel('time (s)')
plt.xlabel('run')
plt.title(f'Stress test n={n} (measure={measure})')
plt.grid(True)
out_png = os.path.join(outdir, f"{n}_stress.png")
plt.savefig(out_png)
print("Saved plot to", out_png)
