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

    return raw_lines


def analysis_duplicates(filename):

    # data = pd.read_csv(filename, delimiter='\t', header=None)   # Load
    data = read_csv_file_raw(filename)

    analysis_targets = [
        {
            "extract-name": "duplicate-cdf", 
            "data": data, 
            "summary-name": "",
            "summary-str": ""
        }
    ]
    
    for target in analysis_targets:

        data = [elem[1] for elem in data]
        values = data

        # for index in range(len(reuse_distances)):
        #     if reuse_distances[index] == 0:
        #         reuse_distances[index] = len(values)

        # CDF of reuse distances.
        x_val = values
        x_val = np.sort(x_val)
        y_val = np.arange(1, len(values) + 1) / len(values)

        cdf_df = pd.DataFrame({'val': x_val, 'cdf': y_val})
        cdf_df = cdf_df.groupby('val', as_index=False).max()
        cdf_df = cdf_df.sort_values(by='val')

        raw_filename = Path(filename).stem
        csv_path = f"extract-{target['extract-name']}-{raw_filename}.csv"

        cdf_df.to_csv(csv_path, index=False, header=False, sep='\t')

        print(f"Exported: {csv_path}")

        with open(f"counts-{raw_filename}.csv", "w") as f:
            # for element, count in counter.most_common():
            #     f.write(f"{element}\t{count}\n")
            x_val = reversed(x_val)
            for count in x_val:
                f.write(f"{count}\n")






# 
# 
if __name__ == "__main__":
    
    fprefix_duplicates = "duplicate-"

    file_pref = {}

    file_pref[fprefix_duplicates] = {
        "file-list": get_csv_files_with_prefix(".", fprefix_duplicates, ".csv"),
        "out-prefix": fprefix_duplicates,
        "handler": analysis_duplicates
    }

    for fpref in file_pref.values():
        
        summary = []
        for filename in fpref["file-list"]:
            summary.append(fpref["handler"](filename))

        # Extract summary
        # out_fname = f"{fpref['out-prefix']}-summary.txt"
        # with open(f"{out_fname}", "w") as f:
        #     for fileitem in summary:
        #         for single_summary in fileitem:
        #             f.write(f"{single_summary['summary-name']}\t{single_summary['summary-str']}\n")



