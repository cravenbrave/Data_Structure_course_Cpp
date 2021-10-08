#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

size = []
time1 = []
time2 = []
with open("small_size.txt", 'r') as fh:
    row = fh.readlines()
    for i in range(1, len(row)):
        data = row[i].strip().split()
        size.append(int(data[0]))
        time1.append(float(data[1]))
        time2.append(float(data[2]))

plt.figure()
plt.plot(size, time1, 'r.', label="std::binary_search")
plt.plot(size, time2, 'b.', label="compromise_search")
plt.legend()
plt.xlabel("small_size", fontsize=12)
plt.ylabel("Seconds", fontsize=12)
plt.tight_layout()
plt.savefig("small_size.pdf", dpi=300)

