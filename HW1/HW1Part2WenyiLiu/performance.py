#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

#%% plot all performances
size = []
time1 = []
time2 = []
time3 = []
time4 = []
time5 = []
with open("code_performance.txt", 'r') as fh:
    row = fh.readlines()
    for i in range(1, len(row)):
        data = row[i].strip().split()
        size.append(int(data[0]))
        time1.append(float(data[1]))
        time2.append(float(data[2]))
        time3.append(float(data[3]))
        time4.append(float(data[4]))
        time5.append(float(data[5]))

plt.figure()
plt.plot(size, time1, 'r.', label="std::binary_search")
plt.plot(size, time2, 'b.', label="compromise low")
plt.plot(size, time3, 'g.', label="compromise mid")
plt.plot(size, time4, 'c.', label="compromise high")
plt.plot(size, time5, 'm.', label="std::find")
plt.legend()
plt.xlabel("Array length", fontsize=12)
plt.ylabel("Seconds", fontsize=12)
plt.tight_layout()
plt.savefig("performance1.pdf", dpi=300)

#%% plot two performances
plt.figure()
plt.plot(size, time1, 'r.', label="std::binary_search")
plt.plot(size, time2, 'b.', label="compromise low")
plt.legend()
plt.xlabel("Array length", fontsize=12)
plt.ylabel("Seconds", fontsize=12)
plt.tight_layout()
plt.savefig("performance2.pdf", dpi=300)
