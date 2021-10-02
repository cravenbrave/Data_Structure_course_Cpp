#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

x = []
y = []
with open("output.txt", 'r') as fh:
    row = fh.readlines()
    for i in range(1, len(row)):
        data = row[i].strip().split()
        x.append(int(data[0]))
        y.append(float(data[1]))

plt.plot(x, y, 'b.')
plt.xlabel("Array length", fontsize=12)
plt.ylabel("Seconds per insert", fontsize=12)
plt.tight_layout()
plt.savefig("profile.pdf", dpi=300)

