from hypercube import Hypercube

class HypercubeColoring(Hypercube):
    def __init__(self, n, red_edge_set):
        """
        :param n: Size of the underlying hypercube
        :param red_edge_set: A set of edges which have the red color, the rest of the edges is blue implicitly.
        """
        super().__init__(n)
        self.red_edge_set = red_edge_set

    def is_red(self, edge):
        u,v=edge
        return (u,v) in self.red_edge_set or (v,u) in self.red_edge_set

    def find_switch_vector(self):
        switch_vector = []
        for v in range(0, 2 ** (self.n - 1)):
            switch_vector.append(self.find_least_switch_path(v, self.antipodal_vertex(v)))
        return switch_vector


    def find_least_switch_path(self, start_vertex, target_vertex):
        best = self.n-1
        for geo in self.enumerate_geodesics(start_vertex, target_vertex):
            val = self.calculate_number_of_switches(geo)
            if val<best:
                best=val
        return best

    def calculate_number_of_switches(self, path):
        switches = 0
        curr_color = None
        for edge in path:
            if curr_color is None:
                curr_color='red' if self.is_red(edge) else 'blue'
                continue
            if self.is_red(edge) and curr_color=='blue':
                switches+=1
                curr_color='red'
            elif not self.is_red(edge) and curr_color=='red':
                switches += 1
                curr_color='blue'
        return switches



