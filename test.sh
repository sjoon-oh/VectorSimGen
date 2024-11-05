#!/bin/bash

./build/bin/vsg-testbin \
    ./dataset/bigann/query.public.10K.u8bin \
    128 \
    0 \
    | grep duplicates

mv duplicate-file.csv duplicate-file-bigann.csv

# ./build/bin/vsg-testbin \
#     ./dataset/sift1m/sift_query.fvecs \
#     128 \
#     2 \
#     | grep duplicates

./build/bin/vsg-testbin \
    ./dataset/spacev1b/query.bin \
    100 \
    1 \
    | grep duplicates

mv duplicate-file.csv duplicate-file-spacev1b.csv

./build/bin/vsg-testbin \
    ./dataset/spacev1b/query_log.bin \
    100 \
    1 \
    | grep duplicates

mv duplicate-file.csv duplicate-file-spacev1b-log.csv

