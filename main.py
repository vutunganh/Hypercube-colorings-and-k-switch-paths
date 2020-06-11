from hypercube import Hypercube
from hypercube_coloring import HypercubeColoring


"""
n=4
h = Hypercube(n)
print(h.enumerate_edges())
for g in h.generate_all_colorings():
    col = HypercubeColoring(n,g)
    switch_vec = col.find_switch_vector()
    print(switch_vec)
"""


n=4
h = Hypercube(n)
for i in range(100):
    col = h.generate_random_coloring()
    col = HypercubeColoring(n, col)
    switch_vec = col.find_switch_vector()
    print(switch_vec)




print("la ende")