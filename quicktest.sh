#!/bin/bash

# ./build/bin/vsg-regen-test \
#     ./dataset/spacev1b/query_log.bin \
#     ./dataset/spacev1b/query_log_truth.bin int8 100 1000000

./build/bin/vsg-regen-test \
    ./dataset/spacev1b/query.bin \
    ./dataset/spacev1b/truth.bin int8 100 1000000

mv extended-query-set.bin spacev1b-query-extended-1M-zipf.bin
mv extended-truth-set.bin spacev1b-truth-extended-1M-zipf.bin


./build/bin/vsg-regen-test \
    ./dataset/spacev1b/query.bin \
    ./dataset/spacev1b/truth.bin int8 100 10000000

mv extended-query-set.bin spacev1b-query-extended-10M-zipf.bin
mv extended-truth-set.bin spacev1b-truth-extended-10M-zipf.bin


./build/bin/vsg-regen-test \
    ./dataset/spacev1b/query.bin \
    ./dataset/spacev1b/truth.bin int8 100 100000000

mv extended-query-set.bin spacev1b-query-extended-100M-zipf.bin
mv extended-truth-set.bin spacev1b-truth-extended-100M-zipf.bin

# 
./build/bin/vsg-regen-test \
    ./dataset/spacev1b/query_log.bin \
    ./dataset/spacev1b/query_log_truth.bin int8 100 1000000

mv extended-query-set.bin spacev1b-query-log-extended-1M-zipf.bin
mv extended-truth-set.bin spacev1b-truth-log-extended-1M-zipf.bin


./build/bin/vsg-regen-test \
    ./dataset/spacev1b/query_log.bin \
    ./dataset/spacev1b/query_log_truth.bin int8 100 10000000

mv extended-query-set.bin spacev1b-query-log-extended-10M-zipf.bin
mv extended-truth-set.bin spacev1b-truth-log-extended-10M-zipf.bin


./build/bin/vsg-regen-test \
    ./dataset/spacev1b/query_log.bin \
    ./dataset/spacev1b/query_log_truth.bin int8 100 100000000

mv extended-query-set.bin spacev1b-query-log-extended-100M-zipf.bin
mv extended-truth-set.bin spacev1b-truth-log-extended-100M-zipf.bin