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
            line_elem = line.strip().split(' ')
            line_elem = [int(offset) for offset in line_elem]

            raw_lines.append(line_elem)

    return raw_lines


data = read_csv_file_raw('dataset/ms-marco-web-search-click/truth.txt')

print(f"Sample Col Length: {len(data[0])}, {len(data[1])}, {len(data[2])}")
print(f"Row Length: {len(data)}")
# print(f"")
# print(f"")







