#python script to grab all the values 

# i dont know why I did this instead of manually hard coding the data 


import re
import json

def parse_log_file(filename):
    # relevant metrics based on strings from executibles
    pattern_n = re.compile(r"Working on problem size N=(\d+)")
    pattern_mflops = re.compile(r"MFLOP/s: ([\d.]+)")
    pattern_bandwidth = re.compile(r"Memory Bandwidth Utilization: ([\d.]+)%")
    pattern_latency = re.compile(r"Average Memory Latency: ([\deE\.\-]+) ns/access")

    # extracted values
    N = []
    mflops = []
    bandwidth = []
    latency = []

    
    with open(filename, 'r') as f:
        for line in f:
           
            n_match = pattern_n.search(line)
            mflops_match = pattern_mflops.search(line)
            bandwidth_match = pattern_bandwidth.search(line)
            latency_match = pattern_latency.search(line)

            if n_match:
                N.append(int(n_match.group(1)))
            if mflops_match:
                mflops.append(float(mflops_match.group(1)))
            if bandwidth_match:
                bandwidth.append(float(bandwidth_match.group(1)))
            if latency_match:
                latency.append(float(latency_match.group(1)))

    
    metrics = {
        'N': N,
        'MFLOPs': mflops,
        'Mem_Bandwidth': bandwidth,
        'Mem_Latency': latency
    }

    return metrics

def write_metrics_to_json(metrics, output_filename):
    
    with open(output_filename, 'w') as f:
        json.dump(metrics, f, indent=4)

def main():
    input_filename = 'log.log'  
    output_filename = 'parsed_metrics_vector.json'

    metrics = parse_log_file(input_filename)
    write_metrics_to_json(metrics, output_filename)

    print(f"Metrics successfully parsed and saved to {output_filename}")

if __name__ == "__main__":
    main()
