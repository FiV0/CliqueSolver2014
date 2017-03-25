# script for generation of plots

import numpy
import matplotlib
import matplotlib.pyplot as plt

timesLargeFMC = [ 1.27, 2861.26, 2425.66, 53.64, 1.51, 4.06, 3.17];
memLargeFMC = [ 55888, 339384 ,429500 ,800508 ,58908 ,270132 ,131476];
timesSmallFMC = [7.22, 139.34, 1.85, 1888.18, 54.67, 58.05];

timesLargeRMC = [4.11 , 0, 0, 112.86, 12.92 , 12.78 ,26.07];
memLargeRMC = [66576 , 0, 0, 2116044, 179860, 490284, 256884];
timesSmallRMC = [ 00.07 , 88.48, 11.23, 623.20, 09.05, 24.51 ];


timesLargeEMMCE = [3.57, 4802, 2712.01, 971.65, 29.13, 41.35, 60.88 ];
memLargeEMMCE = [ 31228, 227348, 175112, 168600, 79396, 113516, 119672];
timesSmallEMMCE = [33.43, 203.05, 6.81, 812.66, 29.56, 29.26];


timesLargeTomita = [3.99, 2965.81, 1115.11, 120.47, 13.27, 18.06, 33.86];
memLargeTomita = [29580 , 194160, 212088, 384132, 51496, 133864, 95844];
timesSmallTomita = [00.12, 137.47, 14.05, 621.21, 46.96, 19.19];

timesLargeMode_Solver = [0,0,0,0,0,0,0];
memLargeMode_Solver =[0,0,0,0,0,0,0];
timesSmallMode_Solver = [0,0,0,0,0,0,0];

plt.plot(timesLargeFMC, 'r', label= 'FMC')
plt.plot(timesLargeRMC, 'g', label= 'RMC')
plt.plot(timesLargeEMMCE, 'b',label = 'EMMCE')
plt.plot(timesLargeTomita, 'y', label = 'Tomita')
plt.yscale('log')
plt.xlim( xmin= -0.25,xmax = 6.25)
plt.ylabel('time in seconds ')
plt.xticks(numpy.arange(7),['dblp\n13.9mb','wiki\n66.5mb',
'as-skitter\n149mb','cit-patents\n280.5mb','amazon\n47.9mb', 
'road-Net\n87.8mb','google\n75.5mb'])
plt.legend()
plt.savefig('large_graphs_running_times.png')

plt.clf()

plt.plot(memLargeFMC, 'r', label= 'FMC')
plt.plot(memLargeRMC, 'g', label= 'RMC')
plt.plot(memLargeEMMCE, 'b',label = 'EMMCE')
plt.plot(memLargeTomita, 'y', label = 'Tomita')
plt.yscale('log')
plt.xlim( xmin= -0.25,xmax = 6.25)
plt.ylabel('Maximum resident size in KB')
plt.xticks(numpy.arange(7),['dblp\n13.9mb','wiki\n66.5mb',
'as-skitter\n149mb','cit-patents\n280.5mb','amazon\n47.9mb', 
'road-Net\n87.8mb','google\n75.5mb'])
plt.legend()
plt.savefig('large_graphs_max_memory.png')

plt.clf()

plt.plot(timesSmallFMC, 'r', label= 'FMC')
plt.plot(timesSmallRMC, 'g', label= 'RMC')
plt.plot(timesSmallEMMCE, 'b',label = 'EMMCE')
plt.plot(timesSmallTomita, 'y', label = 'Tomita')
plt.yscale('log')
plt.xlim( xmin= -0.25,xmax = 5.25)
plt.ylabel('time in seconds')
plt.xticks(numpy.arange(6),['c-fat\n18.59%','brock\n65.77%',
'hamming\n90.48%','p-hat\n48.89%','keller\n64.84%', 
'johnson\n76.45%'])
plt.legend()
plt.savefig('small_graphs_running_time.png')

