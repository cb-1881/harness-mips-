import json
import matplotlib.pyplot as plt

# get json data
with open('perlmutter_data.json', 'r') as f:
    data = json.load(f)

# data from the perlmutte json above
methods = ['direct', 'vector sum', 'indirect']
metrics = {method: data[method] for method in data}

# generating our plot 
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

# mflops
plot_metric('MFLOPs', 'MFLOPs', 'mflops.png')

# mem bandwith
plot_metric('Mem_Bandwidth', '% Memory Bandwidth Utilized', 'memory_bandwidth.png')

# latency 
plot_metric('Mem_Latency', 'Memory Latency (ns/access)', 'memory_latency.png')
