import numpy as np
import pandas as pd

from collections import Counter

def generate_zipf_distribution(N, alpha, max_value=1_000_000):
    # Step 1: Generate ranks from 1 to 1 billion
    ranks = np.arange(1, max_value + 1)
    
    # Step 2: Calculate Zipf distribution probabilities for all ranks
    zipf_probs = ranks**(-alpha)
    
    # Normalize the probabilities so they sum to 1
    zipf_probs /= np.sum(zipf_probs)
    
    # Step 3: Sample N requests based on the Zipf probabilities (from the full 1 billion base)
    requests = np.random.choice(ranks, size=N, p=zipf_probs)
    
    return requests, zipf_probs[:N]


if __name__ == "__main__":

    N = 1_000_000
    alpha = 0.99

    requests, zipf_probs = generate_zipf_distribution(N, alpha)

    request_counts = Counter(requests)

    # Sort by occurrences in descending order
    sorted_counts = request_counts.most_common()

    for rank, count in sorted_counts:
        print(f"{rank}\t{count}")
        


