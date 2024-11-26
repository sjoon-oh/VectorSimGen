# Sukjoon Oh,
# Refinement

import argparse
import math
import numpy as np
import pandas as pd

import json

import sys, os

from pathlib import Path
import math
from concurrent.futures import ThreadPoolExecutor, as_completed

# 
# Get files
def get_csv_files_with_prefix(directory, prefix, ext):
    
    # List to store matching file names
    matching_files = []

    # Loop through all files in the specified directory
    for filename in os.listdir(directory):
        
        # Check if the file starts with the specified prefix and ends with .csv
        if filename.startswith(prefix) and filename.endswith(ext):
            matching_files.append(filename)
            
    return matching_files


def read_csv_file_raw(filename):

    raw_lines = []
    with open(filename, 'r') as file:
        
        for line in file:
            # Split the line by tab
            line_elem = line.strip().split('\t')
            line_elem = [int(offset) for offset in line_elem]

            raw_lines.append(line_elem)

    return raw_line


# Sukjoon Oh,
# Refinement

import argparse
import math
import numpy as np
import pandas as pd

import json

import sys, os

from pathlib import Path
import math
from concurrent.futures import ThreadPoolExecutor, as_completed

# 
# Get files
def get_csv_files_with_prefix(directory, prefix, ext):
    
    # List to store matching file names
    matching_files = []

    # Loop through all files in the specified directory
    for filename in os.listdir(directory):
        
        # Check if the file starts with the specified prefix and ends with .csv
        if filename.startswith(prefix) and filename.endswith(ext):
            matching_files.append(filename)
            
    return matching_files


def read_csv_file_raw(filename):

    raw_lines = []
    with open(filename, 'r') as file:
        
        for line in file:
            # Split the line by tab
            line_elem = line.strip().split('\t')
            line_elem = [float(offset) for offset in line_elem]

            raw_lines.append(line_elem)

    return raw_lines



if __name__ == "__main__":

    if len(sys.argv) != 3:
        sys.exit(1)

    filename = sys.argv[1]
    max_dup = int(sys.argv[2])
    
    truth_size = max_dup
    print(f"Truth size: {truth_size}")

    data = read_csv_file_raw(filename)

    jaccard_nonzero_count = []
    jaccard_zero_idx = []

    for elem in data:
        jaccard_nonzero_count.append(sum(1 for x in elem if x != 0))
        jaccard_nonzero_count[-1] -= 1

        # print(f"{jaccard_nonzero_count[-1]}")

    for idx, elem in enumerate(jaccard_nonzero_count):
        if elem == 0:
            jaccard_zero_idx.append(idx)

    # Test
    # print(jaccard_zero_idx)
    
    matrix = np.array(data)

    updated_matrix = np.delete(matrix, jaccard_zero_idx, axis = 0)
    updated_matrix = np.delete(updated_matrix, jaccard_zero_idx, axis = 1)

    updated_matrix[updated_matrix == truth_size] = 0

    print(updated_matrix)
    print(updated_matrix.shape)
    
    with open(f"record-{filename}.txt", "w") as f:
        for count_elem in jaccard_nonzero_count:
            f.write(f"{count_elem}\n")

    df = pd.DataFrame(updated_matrix)
    df.to_csv(f"record-nonzero-raw-{filename}.txt", sep='\t', index=False, header=False)

    enumerated_columns = [data.tolist() for col, data in df.items()]
    only_values = []

    with open(f"record-only-nonzero-{filename}.txt", "w") as f:
        output = []
        for row in enumerated_columns:
            line = []
            for elem in row:
                if elem != 0:
                    line.append(elem)
                    only_values.append(elem)

            for elem in line:
                f.write(f"{elem}\t")

            if len(line) != 0:
                f.write(f"\n")

            del line


    x_val = np.sort(only_values)
    y_val = np.arange(1, len(x_val) + 1) / len(x_val)

    cdf_df = pd.DataFrame({'val': x_val, 'cdf': y_val})
    cdf_df = cdf_df.groupby('val', as_index=False).max()
    cdf_df = cdf_df.sort_values(by='val')

    csv_path = f"extract-{filename}.csv"

    cdf_df.to_csv(csv_path, index=False, header=False, sep='\t')

    from collections import Counter
    counts = Counter(x_val)
    sorted_counter = sorted(counts.items(), key=lambda x: x[0])

    with open(f"overlap-counts-histo-{filename}.txt", "w") as f:
        # for elem in counts:
        #     f.write(f"{elem}\n")
        key_list = sorted_counter
        for item, count in sorted_counter:
            f.write(f'{item}\t{count/2}\n')


    # np.savetxt(f"record-nonzero-raw-{filename}.txt", updated_matrix, delimiter='\t', fmt='%f')

    # nonzero_raw_data = []
    # with open(f"record-nonzero-raw-{filename}.txt", "w") as f:

    #     for idx, line in enumerate(updated_matrix):
    #         for elem in line:
    #             f.write(f"{elem:8.4f}\t")
    #         f.write(f"\n")
    