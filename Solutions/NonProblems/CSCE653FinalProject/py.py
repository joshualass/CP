'''
PLOTTING FOR THE SECOND TEST OF VARYING N
'''

import matplotlib.pyplot as plt
import numpy as np

# Data
n_values = np.array([1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000])
complete_w = np.array([10599.3, 20091.1, 29366.5, 38617.7, 47644.7, 56470.6, 65299, 74057.6, 82606.3, 91264.3])
complete_t = np.array([1044.03, 4675.42, 10802.1, 18963.6, 30843.4, 44621.1, 64945.7, 80126.5, 103266, 134359])
complete_e = np.array([499500, 1.999e+06, 4.4985e+06, 7.998e+06, 1.24975e+07,
                       1.7997e+07, 2.44965e+07, 3.1996e+07, 4.04955e+07, 4.9995e+07])

knng_kruskal_w = np.array([10855.2, 21236.9, 31002.4, 40756.2, 50282.6, 59913.5, 68754.8, 78376.6, 87786.5, 96727.7])
knng_kruskal_t = np.array([1948.31, 5293.97, 12626.3, 17222.4, 37472.9, 51157, 89697.8, 84101.8, 100957, 120026])
knng_kruskal_e = np.array([163695, 174076, 437830, 667881, 959139, 1.11454e+06, 1.98172e+06,
                           2.10926e+06, 2.08915e+06, 2.96231e+06])

knng_prim_w = knng_kruskal_w
knng_prim_t = np.array([1923.62, 5091.15, 12251.6, 16887, 37032.9, 50785.8, 89645.6, 85696.4, 101172, 120177])
knng_prim_e = knng_kruskal_e

bnng_kruskal_w = np.array([11354, 21697.5, 31985.9, 41836.7, 52041.4, 62088.9, 71950.6, 81193.5, 91178.9, 101019])
bnng_kruskal_t = np.array([625.991, 2207.52, 4461.69, 7992.38, 11657.1, 15889.6, 20890.8, 28567.2, 34288.3, 42053.2])
bnng_kruskal_e = np.array([65932, 197884, 314716, 571254, 690832, 747173, 942859, 1.3938e+06, 1.41226e+06, 1.66743e+06])

bnng_prim_w = bnng_kruskal_w
bnng_prim_t = np.array([618.862, 2233.36, 4545.54, 7922.62, 11541.5, 16707.9, 20896.9, 28678.3, 34430.5, 41923.3])
bnng_prim_e = bnng_kruskal_e

# Compute error: (W' - W) / W
def compute_error(approx, exact):
    return (approx - exact) / exact

# Plot 1: MST weight relative error
plt.figure(figsize=(10, 6))
plt.plot(n_values, compute_error(knng_kruskal_w, complete_w), label='KNNG Kruskal')
plt.plot(n_values, compute_error(knng_prim_w, complete_w), label='KNNG Prim')
plt.plot(n_values, compute_error(bnng_kruskal_w, complete_w), label='BNNG Kruskal')
plt.plot(n_values, compute_error(bnng_prim_w, complete_w), label='BNNG Prim')
plt.axhline(0, color='gray', linestyle='--')
plt.xlabel('Number of nodes (n)')
plt.ylabel('Relative Error in MST Weight')
plt.title('MST Weight Relative Error vs Complete Graph')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot 2: Execution time
plt.figure(figsize=(10, 6))
plt.plot(n_values, complete_t, label='Complete Graph')
plt.plot(n_values, knng_kruskal_t, label='KNNG Kruskal')
plt.plot(n_values, knng_prim_t, label='KNNG Prim')
plt.plot(n_values, bnng_kruskal_t, label='BNNG Kruskal')
plt.plot(n_values, bnng_prim_t, label='BNNG Prim')
plt.xlabel('Number of nodes (n)')
plt.ylabel('Execution Time (ms)')
plt.title('Execution Time vs Number of Nodes')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot 3: Number of edges
plt.figure(figsize=(10, 6))
plt.plot(n_values, complete_e, label='Complete Graph')
plt.plot(n_values, knng_kruskal_e, label='KNNG Kruskal')
plt.plot(n_values, knng_prim_e, label='KNNG Prim')
plt.plot(n_values, bnng_kruskal_e, label='BNNG Kruskal')
plt.plot(n_values, bnng_prim_e, label='BNNG Prim')
plt.xlabel('Number of nodes (n)')
plt.ylabel('Number of Edges')
plt.title('Number of Edges vs Number of Nodes')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()


'''
PLOTTING FOR FIRST TEST OF VARYING D
'''

# import matplotlib.pyplot as plt

# # Data structured per dimension
# data = {
#     2: {
#         "Complete Graph": [460.852, 22928.8, 1.24975e7],
#         "KNNG Kruskal": [464.164, 19679.3, 868369],
#         "KNNG Prim": [464.164, 19698.6, 868369],
#         "BNNG Kruskal": [470.077, 6728.03, 363009],
#         "BNNG Prim": [470.077, 6666.35, 363009],
#     },
#     4: {
#         "Complete Graph": [4182.49, 24353, 1.24975e7],
#         "KNNG Kruskal": [4310.57, 26579.2, 744978],
#         "KNNG Prim": [4310.57, 26642, 744978],
#         "BNNG Kruskal": [4433.2, 7412.67, 485204],
#         "BNNG Prim": [4433.2, 7536.76, 485204],
#     },
#     8: {
#         "Complete Graph": [15862.4, 25707, 1.24975e7],
#         "KNNG Kruskal": [16548, 21913.4, 969395],
#         "KNNG Prim": [16548, 22035.7, 969395],
#         "BNNG Kruskal": [17319.5, 8631.75, 582549],
#         "BNNG Prim": [17319.5, 8562.28, 582549],
#     },
#     16: {
#         "Complete Graph": [37946.6, 28384.6, 1.24975e7],
#         "KNNG Kruskal": [40044.4, 32089.6, 994614],
#         "KNNG Prim": [40044.4, 31969, 994614],
#         "BNNG Kruskal": [41841.4, 10701.9, 641286],
#         "BNNG Prim": [41841.4, 10804.1, 641286],
#     },
#     32: {
#         "Complete Graph": [72138.3, 33931.1, 1.24975e7],
#         "KNNG Kruskal": [75949.4, 41854, 889921],
#         "KNNG Prim": [75949.4, 41540.1, 889921],
#         "BNNG Kruskal": [75993, 19243.5, 1.48739e6],
#         "BNNG Prim": [75993, 19269.6, 1.48739e6],
#     },
#     64: {
#         "Complete Graph": [120516, 47225.6, 1.24975e7],
#         "KNNG Kruskal": [122441, 91480.5, 4.84391e6],
#         "KNNG Prim": [122441, 90368.9, 4.84391e6],
#         "BNNG Kruskal": [126607, 23498.3, 984386],
#         "BNNG Prim": [126607, 23169.5, 984386],
#     },
#     128: {
#         "Complete Graph": [188458, 65614.3, 1.24975e7],
#         "KNNG Kruskal": [188478, 231991, 1.24277e7],
#         "KNNG Prim": [188478, 234743, 1.24277e7],
#         "BNNG Kruskal": [191369, 85991.3, 4.57048e6],
#         "BNNG Prim": [191369, 87312.6, 4.57048e6],
#     },
#     256: {
#         "Complete Graph": [284795, 108745, 1.24975e7],
#         "KNNG Kruskal": [284808, 370957, 1.24673e7],
#         "KNNG Prim": [284808, 372157, 1.24673e7],
#         "BNNG Kruskal": [284837, 337228, 1.2414e7],
#         "BNNG Prim": [284837, 339988, 1.2414e7],
#     }
# }

# dimensions = sorted(data.keys())
# algorithms = ["Complete Graph", "KNNG Kruskal", "KNNG Prim", "BNNG Kruskal", "BNNG Prim"]

# # Initialize plots
# times = {alg: [] for alg in algorithms}
# errors = {alg: [] for alg in algorithms if alg != "Complete Graph"}
# edges = {alg: [] for alg in algorithms}

# # Fill in data
# for d in dimensions:
#     W = data[d]["Complete Graph"][0]
#     for alg in algorithms:
#         w, t, e = data[d][alg]
#         times[alg].append(t)
#         edges[alg].append(e)
#         if alg != "Complete Graph":
#             errors[alg].append((w - W) / W)

# import numpy as np

# # Plot 1: Time vs d (log2 x-axis)
# plt.figure(figsize=(10, 6))
# for alg in algorithms:
#     plt.plot(dimensions, times[alg], label=alg)
# plt.xscale("log", base=2)
# plt.xticks(dimensions, labels=[f"$2^{int(np.log2(d))}$" for d in dimensions])
# plt.xlabel("Dimension (d)")
# plt.ylabel("Time (ms)")
# plt.title("MST Construction Time vs Dimension. N = 5000")
# plt.legend()
# plt.grid(True, which='both', linestyle='--')
# plt.tight_layout()
# plt.show()

# # Plot 2: Weight Error vs d (log2 x-axis)
# plt.figure(figsize=(10, 6))
# for alg in errors:
#     plt.plot(dimensions, errors[alg], label=alg)
# plt.xscale("log", base=2)
# plt.xticks(dimensions, labels=[f"$2^{int(np.log2(d))}$" for d in dimensions])
# plt.xlabel("Dimension (d)")
# plt.ylabel("Weight Error ((W' - W) / W)")
# plt.title("MST Weight Error vs Dimension. N = 5000")
# plt.legend()
# plt.grid(True, which='both', linestyle='--')
# plt.tight_layout()
# plt.show()

# # Plot 3: Edge Count vs d (log2 x-axis)
# plt.figure(figsize=(10, 6))
# for alg in algorithms:
#     plt.plot(dimensions, edges[alg], label=alg)
# plt.xscale("log", base=2)
# plt.xticks(dimensions, labels=[f"$2^{int(np.log2(d))}$" for d in dimensions])
# plt.xlabel("Dimension (d)")
# plt.ylabel("# Edges in Graph")
# plt.title("Edge Count vs Dimension. N = 5000")
# plt.legend()
# plt.grid(True, which='both', linestyle='--')
# plt.tight_layout()
# plt.show()




# import matplotlib.pyplot as plt

# pts = [
# 	5.91201, 4.64855, 
# 	9.12172, 2.90601, 
# 	7.09388, 6.63661, 
# 	6.45425, 5.3939, 
# 	8.31781, 7.87348, 
# 	5.55889, 3.31859, 
# 	6.56776, 0.773525, 
# 	3.88738, 0.419506, 
# 	3.47934, 0.709639, 
# 	0.154957, 2.16077, 
# 	0.729346, 3.5365, 
# 	1.08005, 7.30126, 
# 	3.74876, 5.63297, 
# 	2.86998, 5.05958, 
# 	4.6424, 7.83084, 
# 	1.85234, 9.87075, 
# 	2.85647, 9.54225, 
# 	5.56044, 8.72544, 
# 	5.32245, 9.49947, 
# 	8.00403, 9.30908
# ]
# part = [0, 2, 5, 9, 11, 14, 17, 20]

# # Convert pts into list of (x, y) points
# points = list(zip(pts[::2], pts[1::2]))

# # Color list to cycle through
# colors = ['red', 'blue', 'green', 'purple', 'orange']

# # Plot
# plt.figure(figsize=(8, 6))
# for i in range(len(part) - 1):
#     start, end = part[i], part[i + 1]
#     group = points[start:end]
#     if not group:
#         continue
#     x, y = zip(*group)
#     plt.scatter(x, y, label=f'Group {i}', color=colors[i % len(colors)])
#     for idx, (xi, yi) in enumerate(group, start=start):
#         plt.text(xi, yi, str(idx), fontsize=9, ha='right')

# plt.title('Partitioned Points')
# plt.grid(True)
# plt.gca().set_aspect('equal', adjustable='box')
# plt.legend()
# plt.show()


# import matplotlib.pyplot as plt

# # Updated data
# pts = [
#     8.02162, 4.50166,
#     6.16649, 3.06063,
#     1.33916, 9.17279,
#     2.73888, 2.56232,
#     0.509545, 5.32519,
#     4.38159, 4.99995,
#     2.76456, 5.56798,
#     8.18545, 3.46805,
#     2.93462, 7.69157,
#     1.28179, 0.693097
# ]

# part = [0, 1, 10]  # This means: [0,0], [1,9]

# # Convert flat pts list into list of (x, y) tuples
# points = list(zip(pts[::2], pts[1::2]))

# # Define colors for partitions
# colors = ['red', 'blue', 'green', 'purple', 'orange']

# # Plot each partition
# plt.figure(figsize=(8, 6))
# for i in range(len(part) - 1):
#     start, end = part[i], part[i + 1]
#     group = points[start:end]
#     if not group:
#         continue  # Skip empty partitions
#     x, y = zip(*group)
#     plt.scatter(x, y, label=f'Group {i}', color=colors[i % len(colors)])
#     for idx, (xi, yi) in enumerate(group, start=start):
#         plt.text(xi, yi, str(idx), fontsize=9, ha='right')

# plt.title('Partitioned Points')
# plt.grid(True)
# plt.gca().set_aspect('equal', adjustable='box')
# plt.legend()
# plt.show()


# import matplotlib.pyplot as plt

# # Given data
# pts = [
#     0.107653, 0.407405,
#     0.32503, 3.30044,
#     0.575977, 5.9359,
#     0.872452, 2.87706,
#     2.99943, 6.67876,
#     2.2821, 9.07021,
#     7.93197, 3.43718,
#     9.78848, 5.05806,
#     7.17287, 6.99055,
#     2.73179, 8.03614
# ]

# part = [0, 6, 10]  # partition indices

# # Convert flat pts list into list of (x, y) tuples
# points = list(zip(pts[::2], pts[1::2]))

# # Define colors for partitions
# colors = ['red', 'blue', 'green', 'purple', 'orange']

# # Plot each partition
# plt.figure(figsize=(8, 6))
# for i in range(len(part) - 1):
#     start, end = part[i], part[i + 1]
#     group = points[start:end]
#     x, y = zip(*group)
#     plt.scatter(x, y, label=f'Group {i}', color=colors[i % len(colors)])
#     for idx, (xi, yi) in enumerate(group, start=start):
#         plt.text(xi, yi, str(idx), fontsize=9, ha='right')

# plt.title('Partitioned Points')
# plt.grid(True)
# plt.gca().set_aspect('equal', adjustable='box')
# plt.legend()
# plt.show()



# import matplotlib.pyplot as plt

# # Input
# pts = [
#     7.27588, 7.2347,  8.10748, 6.30048,  8.7838, 2.7149,
#     3.82757, 2.68017,  1.71824, 1.25591,  3.9157, 8.2149,
#     9.63885, 2.89596,  0.745694, 2.48579,  6.38021, 0.622421,
#     4.02891, 1.11759
# ]
# part = [0, 4, 5, 10]  # Corrected: [0–3], [4], [5–9]

# # Parse points
# points = [(pts[i], pts[i + 1]) for i in range(0, len(pts), 2)]

# # Safety check
# if part[-1] > len(points):
#     raise ValueError("Partition index out of range.")

# # Partition
# partitions = []
# for i in range(len(part) - 1):
#     start, end = part[i], part[i + 1]
#     partitions.append(points[start:end])

# # Plot
# colors = ['red', 'blue', 'green', 'purple', 'orange']
# for i, group in enumerate(partitions):
#     if not group:
#         continue
#     x, y = zip(*group)
#     plt.scatter(x, y, color=colors[i % len(colors)], label=f'Part {i}')

# plt.title("Partitioned Points")
# plt.legend()
# plt.axis('equal')
# plt.grid(True)
# plt.show()


# import matplotlib.pyplot as plt

# # Example 1
# pts = [
#     7.27588, 7.2347,
#     8.10748, 6.30048,
#     8.7838, 2.7149,
#     3.82757, 2.68017,
#     1.71824, 1.25591,
#     3.9157, 8.2149,
#     9.63885, 2.89596,
#     0.745694, 2.48579,
#     6.38021, 0.622421,
#     4.02891, 1.11759
# ]
# # part = [4, 5, 10]
# part = [0, 4, 5, 10]

# # Convert flat list into list of (x, y) pairs
# points = [(pts[i], pts[i + 1]) for i in range(0, len(pts), 2)]
# # points = [(0, 4), (4, 5), (5, 10)]

# # Determine partition groups
# partitions = []
# for i in range(len(part)):
#     start = part[i]
#     end = part[i + 1] if i + 1 < len(part) else len(points)
#     partitions.append(points[start:end])

# # Plot
# colors = ['red', 'blue', 'green', 'purple', 'orange']
# for i, group in enumerate(partitions):
#     x, y = zip(*group)
#     plt.scatter(x, y, color=colors[i % len(colors)], label=f'Part {i}')

# plt.title("Partitioned Points")
# plt.legend()
# plt.axis('equal')
# plt.grid(True)
# plt.show()

'''
First test Output

Using n = 5000 and trying several d
MST w, time taken, # edges of graph
d : 2
Complete Graph : [460.852, 22928.8, 1.24975e+07]
KNNG Kruskal : [464.164, 19679.3, 868369]
KNNG Prim : [464.164, 19698.6, 868369]
BNNG Kruskal : [470.077, 6728.03, 363009]
BNNG Prim : [470.077, 6666.35, 363009]
d : 4
Complete Graph : [4182.49, 24353, 1.24975e+07]
KNNG Kruskal : [4310.57, 26579.2, 744978]
KNNG Prim : [4310.57, 26642, 744978]
BNNG Kruskal : [4433.2, 7412.67, 485204]
BNNG Prim : [4433.2, 7536.76, 485204]
d : 8
Complete Graph : [15862.4, 25707, 1.24975e+07]
KNNG Kruskal : [16548, 21913.4, 969395]
KNNG Prim : [16548, 22035.7, 969395]
BNNG Kruskal : [17319.5, 8631.75, 582549]
BNNG Prim : [17319.5, 8562.28, 582549]
d : 16
Complete Graph : [37946.6, 28384.6, 1.24975e+07]
KNNG Kruskal : [40044.4, 32089.6, 994614]
KNNG Prim : [40044.4, 31969, 994614]
BNNG Kruskal : [41841.4, 10701.9, 641286]
BNNG Prim : [41841.4, 10804.1, 641286]
d : 32
Complete Graph : [72138.3, 33931.1, 1.24975e+07]
KNNG Kruskal : [75949.4, 41854, 889921]
KNNG Prim : [75949.4, 41540.1, 889921]
BNNG Kruskal : [75993, 19243.5, 1.48739e+06]
BNNG Prim : [75993, 19269.6, 1.48739e+06]
d : 64
Complete Graph : [120516, 47225.6, 1.24975e+07]
KNNG Kruskal : [122441, 91480.5, 4.84391e+06]
KNNG Prim : [122441, 90368.9, 4.84391e+06]
BNNG Kruskal : [126607, 23498.3, 984386]
BNNG Prim : [126607, 23169.5, 984386]
d : 128
Complete Graph : [188458, 65614.3, 1.24975e+07]
KNNG Kruskal : [188478, 231991, 1.24277e+07]
KNNG Prim : [188478, 234743, 1.24277e+07]
BNNG Kruskal : [191369, 85991.3, 4.57048e+06]
BNNG Prim : [191369, 87312.6, 4.57048e+06]
d : 256
Complete Graph : [284795, 108745, 1.24975e+07]
KNNG Kruskal : [284808, 370957, 1.24673e+07]
KNNG Prim : [284808, 372157, 1.24673e+07]
BNNG Kruskal : [284837, 337228, 1.2414e+07]
BNNG Prim : [284837, 339988, 1.2414e+07]
'''

'''
Second test Output

Using d = 20 and trying several n
MST w, time taken, # edges of graph
n : 1000
Complete Graph : [10599.3, 1044.03, 499500]
KNNG Kruskal : [10855.2, 1948.31, 163695]
KNNG Prim : [10855.2, 1923.62, 163695]
BNNG Kruskal : [11354, 625.991, 65932]
BNNG Prim : [11354, 618.862, 65932]
n : 2000
Complete Graph : [20091.1, 4675.42, 1.999e+06]
KNNG Kruskal : [21236.9, 5293.97, 174076]
KNNG Prim : [21236.9, 5091.15, 174076]
BNNG Kruskal : [21697.5, 2207.52, 197884]
BNNG Prim : [21697.5, 2233.36, 197884]
n : 3000
Complete Graph : [29366.5, 10802.1, 4.4985e+06]
KNNG Kruskal : [31002.4, 12626.3, 437830]
KNNG Prim : [31002.4, 12251.6, 437830]
BNNG Kruskal : [31985.9, 4461.69, 314716]
BNNG Prim : [31985.9, 4545.54, 314716]
n : 4000
Complete Graph : [38617.7, 18963.6, 7.998e+06]
KNNG Kruskal : [40756.2, 17222.4, 667881]
KNNG Prim : [40756.2, 16887, 667881]
BNNG Kruskal : [41836.7, 7992.38, 571254]
BNNG Prim : [41836.7, 7922.62, 571254]
n : 5000
Complete Graph : [47644.7, 30843.4, 1.24975e+07]
KNNG Kruskal : [50282.6, 37472.9, 959139]
KNNG Prim : [50282.6, 37032.9, 959139]
BNNG Kruskal : [52041.4, 11657.1, 690832]
BNNG Prim : [52041.4, 11541.5, 690832]
n : 6000
Complete Graph : [56470.6, 44621.1, 1.7997e+07]
KNNG Kruskal : [59913.5, 51157, 1.11454e+06]
KNNG Prim : [59913.5, 50785.8, 1.11454e+06]
BNNG Kruskal : [62088.9, 15889.6, 747173]
BNNG Prim : [62088.9, 16707.9, 747173]
n : 7000
Complete Graph : [65299, 64945.7, 2.44965e+07]
KNNG Kruskal : [68754.8, 89697.8, 1.98172e+06]
KNNG Prim : [68754.8, 89645.6, 1.98172e+06]
BNNG Kruskal : [71950.6, 20890.8, 942859]
BNNG Prim : [71950.6, 20896.9, 942859]
n : 8000
Complete Graph : [74057.6, 80126.5, 3.1996e+07]
KNNG Kruskal : [78376.6, 84101.8, 2.10926e+06]
KNNG Prim : [78376.6, 85696.4, 2.10926e+06]
BNNG Kruskal : [81193.5, 28567.2, 1.3938e+06]
BNNG Prim : [81193.5, 28678.3, 1.3938e+06]
n : 9000
Complete Graph : [82606.3, 103266, 4.04955e+07]
KNNG Kruskal : [87786.5, 100957, 2.08915e+06]
KNNG Prim : [87786.5, 101172, 2.08915e+06]
BNNG Kruskal : [91178.9, 34288.3, 1.41226e+06]
BNNG Prim : [91178.9, 34430.5, 1.41226e+06]
n : 10000
Complete Graph : [91264.3, 134359, 4.9995e+07]
KNNG Kruskal : [96727.7, 120026, 2.96231e+06]
KNNG Prim : [96727.7, 120177, 2.96231e+06]
BNNG Kruskal : [101019, 42053.2, 1.66743e+06]
BNNG Prim : [101019, 41923.3, 1.66743e+06]
'''