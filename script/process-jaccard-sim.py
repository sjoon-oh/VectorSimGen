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
            line_elem = [int(offset) for offset in line_elem]

            raw_lines.append(line_elem)

    return raw_lines


def jaccard_similarity(list1, list2):

    set1 = set(list1)
    set2 = set(list2)

    intersection = len(set1.intersection(set2))
    union = len(set1.union(set2))

    return intersection / union




if __name__ == "__main__":

    data = read_csv_file_raw("truth-human-readable.csv")

    matrix = []

    for idx, truth_set in enumerate(data):
        matrix.append([])

        for compared_set in data:
            matrix[-1].append(jaccard_similarity(truth_set, compared_set))

        print(f"{idx} done.")

    with open("jaccard-gt.csv", "w") as f:
        for row_idx, row in enumerate(matrix):
            for col_idx, col in enumerate(row):
                f.write(f"{matrix[row_idx][col_idx]:3.5f}\t")
            f.write("\n")
            


