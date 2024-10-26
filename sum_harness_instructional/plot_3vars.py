import json
import matplotlib.pyplot as plt

# Load data from the JSON file
with open('supposedly.json', 'r') as f:
    data = json.load(f)

# Extract data for each method (direct, vector sum, indirect)
methods = ['direct', 'vector sum', 'indirect']
metrics = {method: data[method] for method in data}

# Function to generate a plot
def plot_metric(metric_name, ylabel, filename):
    plt.figure(figsize=(10, 6))
    
    for method in methods:
        plt.plot(metrics[method]['N'], metrics[method][metric_name], label=method, marker='o')
    
    plt.xscale('log')
    plt.xlabel('Problem Size (N)')
    plt.ylabel(ylabel)
    plt.title(f'Problem Size vs {ylabel}')
    plt.legend(loc='best')
    plt.grid(True)
    plt.savefig(filename, format='png')
    plt.show()

# Plot MFLOPs
plot_metric('MFLOPs', 'MFLOPs', 'mflops.png')

# Plot Memory Bandwidth Utilization
plot_metric('Mem_Bandwidth', '% Memory Bandwidth Utilized', 'memory_bandwidth.png')

# Plot Memory Latency
plot_metric('Mem_Latency', 'Memory Latency (ns/access)', 'memory_latency.png')
