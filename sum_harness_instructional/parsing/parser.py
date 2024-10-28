#python script to grab all the values 

# i dont know why I did this instead of manually hard coding the data 


import re
import json

def parse_log_file(filename):
    # relevant patterns based on strings from executibles
    pattern_n = re.compile(r"Working on problem size N=(\d+)")
    mflop_patterns = re.compile(r"MFLOP/s: ([\d.]+)")
    pattern_bandwidth = re.compile(r"Memory Bandwidth Utilization: ([\d.]+)%")
    pattern_latency = re.compile(r"Average Memory Latency: ([\deE\.\-]+) ns/access")

    # extracted values
    N = []
    mflops = []
    bandwidth = []
    latency = []

    
    with open(filename, 'r') as file_for_parsing:
        for line in file_for_parsing:
           
            n_match = pattern_n.search(line)
            mflops_match = mflop_patterns.search(line)
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

    
    patterns = {
        'N': N,
        'MFLOPs': mflops,
        'Mem_Bandwidth': bandwidth,
        'Mem_Latency': latency
    }

    return patterns

def write_patterns_to_json(patterns, output_filename):
    
    with open(output_filename, 'w') as f:
        json.dump(patterns, f, indent=4)

def main():
    input_filename = 'out_vector.log'  
    output_filename = 'parsed_patterns_vector.json'

    patterns = parse_log_file(input_filename)
    write_patterns_to_json(patterns, output_filename)

    print('parsing done')

if __name__ == "__main__":
    main()
