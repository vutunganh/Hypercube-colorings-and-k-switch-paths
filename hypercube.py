import queue
from random import randint
from itertools import chain, combinations, permutations


def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))


class Hypercube:
    """
    Of a given size n. Vertices represented by integers corresponding to bitsets of 0s and 1s, e.g. for n=4 the "first"
    vertex is 0=0000_2 and the "last one" is 15=1111_2=2^n-1. Edges are implicit by flipping a corresponding bit.
    """
    def __init__(self, n):
        self.n = n
        self.max_vertex=2**n-1

    def antipodal_vertex(self, v):
        return self.max_vertex-v

    def geodesics_continuations(self, curr_vertex, target_vertex):
        """
        Returns a list of vertices one can go to from a vertex towards a given target_vertex while following the
        shortest path possible. Complexity is n.
        :param curr_vertex: The vertex we are in.
        :param target_vertex: The vertex we are trying to get to.
        :return: A list of vertices connected by an edge to curr_vertex, which are on some shortest path from curr_vertex
        to target_vertex. If curr_vertex == target_vertex, an empty set is returned.
        """
        continuations = []
        i=0
        bits_to_flip = curr_vertex ^ target_vertex
        for i in range(self.n):
            if bits_to_flip & (1<<i):
                continuations.append(curr_vertex ^ (1<<i))
        return continuations


    def enumerate_geodesics(self,start_vertex, target_vertex):
        """
        A generator which for a given start and end vertices, yields all shortest paths connecting them in the hypercube
        in the list of pairs form [(start_vertex,v1),(v1,v2),....,(v45,target_vertex)]. Complexity is n!*n
        """
        bits_to_flip = start_vertex ^ target_vertex
        positions_of_ones = [i for i in range(self.n) if bits_to_flip & (1<<i)]

        for perm in permutations(positions_of_ones):
            curr_vertex = start_vertex
            path = []
            for i in perm:
                #flip ith bit
                new_vertex=curr_vertex ^ (1<<i)
                path.append((curr_vertex,new_vertex))
                curr_vertex = new_vertex
            yield path


    def enumerate_edges(self):
        """
        Lists all edges in a hypercube in a unique format by traversing the hypercube by BFS from 0000 to 1111.
        :return: A list of all edges in the hypercube. Each edge is represented by a pair (v,u). For n=3 returns:
        [(0, 1), (0, 2), (0, 4), (1, 3), (1, 5), (2, 3), (2, 6), (4, 5), (4, 6), (3, 7), (5, 7), (6, 7)]
        Complexity is n*2^(n-1) as that is the number of edges.
        """
        q = queue.Queue()
        seen = [False for _ in range(self.max_vertex+1)]
        list_of_edges = []
        q.put(0)
        while not q.empty():
            v = q.get()
            if seen[v]:
                continue
            seen[v]=True
            for u in self.geodesics_continuations(v, self.max_vertex):
                q.put(u)
                list_of_edges.append((v,u))
        return list_of_edges



    def generate_all_colorings(self):
        """
        A generator which yields edge 2-colorings for the hypercube. The set of red edges for the coloring is returned
        """
        number_of_edges = self.n*2**(self.n-1)
        edges = self.enumerate_edges()
        #enumerate all subsets using bitmasks
        for bitmask in range(2**(number_of_edges)):
            red_edge_set = set()
            for i in range(number_of_edges):
                if bitmask & (1<<i):
                    red_edge_set.add(edges[i])
            yield red_edge_set

    def generate_random_coloring(self):
        """
        A yields a random edge 2-colorings for the hypercube. Each edge is uniformly red or blue.
        The set of red edges for the coloring is returned
        """
        number_of_edges = self.n*2**(self.n-1)
        edges = self.enumerate_edges()
        #enumerate all subsets using bitmasks
        random_bitset = [randint(0,1) for _ in range(number_of_edges)]
        red_edge_set = set()
        for i in range(number_of_edges):
            if random_bitset[i]:
                red_edge_set.add(edges[i])
        return red_edge_set


