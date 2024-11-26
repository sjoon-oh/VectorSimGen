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

def compute_similarity_for_row(row_idx, data, result_matrix):

    # Calculate the Jaccard similarity for one row (against all other sets)
    for col_idx, compared_set in enumerate(data):
        if len(data[row_idx]) != len(compared_set):
            print(f"List size does not match for col({col_idx}) in processing row({row_idx}): {len(data[row_idx])}, {len(compared_set)}")

        else:
            result_matrix[row_idx][col_idx] = jaccard_similarity(data[row_idx], compared_set)

def jaccard_similarity(list1, list2):

    set1 = set(list1)
    set2 = set(list2)

    intersection = len(set1.intersection(set2))
    union = len(set1.union(set2))

    return intersection


def main():
    # Read input data
    filename = sys.argv[1]

    data = read_csv_file_raw(filename)

    print(f"Raw data size: {len(data)}, {len(data[0])}")
    
    # Initialize matrix for storing results
    matrix = [[0] * len(data) for _ in range(len(data))]
    
    # Create a ThreadPoolExecutor to parallelize the task
    # with ThreadPoolExecutor() as executor:
    with ThreadPoolExecutor(max_workers=16) as executor:

        # Submit tasks for each row in the matrix
        futures = []
        for row_idx in range(len(data)):
            futures.append(executor.submit(compute_similarity_for_row, row_idx, data, matrix))

            print(f"Row {row_idx} submitted.")

        # index = 0
        # Wait for all threads to finish
        # for future in as_completed(futures):
        #     future.result()  # We can ignore the result because it's directly updating the matrix

        #     index += 1
        #     print(f"Row {index} completed.")

        print(f"Waiting for the futures objects.")
        wait(futures)

    # for row_idx in range(len(data)):
    #     print(f"Row {row_idx} done.")
    #     compute_similarity_for_row(row_idx, data, matrix)

    output_name = sys.argv[2]

    # Write the result to a CSV file
    with open(f"{output_name}", "w") as f:
        for row_idx in range(len(matrix)):
            for col_idx in range(len(matrix[row_idx])):
                f.write(f"{matrix[row_idx][col_idx]}\t")
            f.write("\n")


if __name__ == "__main__":
    main()





# if __name__ == "__main__":

#     data = read_csv_file_raw("truth-human-readable.csv")

#     matrix = []

#     for idx, truth_set in enumerate(data):
#         matrix.append([])

#         for compared_set in data:
#             matrix[-1].append(jaccard_similarity(truth_set, compared_set))

#         print(f"{idx} done.")

#     with open("jaccard-gt.csv", "w") as f:
#         for row_idx, row in enumerate(matrix):
#             for col_idx, col in enumerate(row):
#                 f.write(f"{matrix[row_idx][col_idx]}\t")
#             f.write("\n")
            


