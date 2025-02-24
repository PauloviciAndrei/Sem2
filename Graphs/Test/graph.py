import random
from copy import deepcopy
import heapq

class Graph:
    def __init__(self, n=0):
        '''Constructs a graph with n vertices numbered from 0 to n and no edges
        '''
        self.__n = n
        self.__in_edges = {}
        for i in range(n):
            self.__in_edges[i] = set()
        self.__out_edges = {}
        for i in range(n):
            self.__out_edges[i] = set()
        self.cost = {}

    def add_vertex(self, x):
        '''Inserts the vertex into the graph.
        Precondition: x is not already a vertex.
        '''
        self.__in_edges[x] = set()
        self.__out_edges[x] = set()

    def remove_vertex(self, x):
        '''Removes the vertex x from the graph and all associated edges'''
        if x in self.__in_edges:
            # Remove inbound edges
            for vertex in self.__in_edges[x]:
                self.__out_edges[vertex].discard(x)
                del self.cost[(vertex, x)]
            del self.__in_edges[x]

        if x in self.__out_edges:
            # Remove outbound edges
            for vertex in self.__out_edges[x]:
                self.__in_edges[vertex].discard(x)
                del self.cost[(x, vertex)]
            del self.__out_edges[x]

    def add_edge(self, x, y, cost):
        '''Adds an edge from vertex x to vertex y and returns True.
            If the edge already exists, nothing happens and the function returns False.
            Precondition: x and y are valid vertices of the graph.
        '''
        if x == y:
            return False
        if y in self.__out_edges[x]:
            return False
        self.__out_edges[x].add(y)
        self.__in_edges[y].add(x)
        self.cost[(x,y)] = cost
        return True

    def is_edge(self, x, y):
        '''Returns True if there is an edge from x to y in the graph, and False otherwise.
            Precondition: x and y are valid vertices of the graph.
        '''
        return y in self.__out_edges[x]

    def parse_nout(self, x):
        '''Returns something iterable that contains all the outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return set(self.__out_edges[x])

    def parse_nin(self, x):
        '''Returns something iterable that contains all the inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
        '''
        return set(self.__in_edges[x])

    def parse_vertices(self):
        '''Return something iterable that contains all the vertices of the graph
        '''
        return set(self.__in_edges.keys())

    def  get_vertices_count(self):
        '''Returns the total number of vertices in the graph'''
        return self.__n

    def get_edge_count(self):
        '''Returns the total number of edges in the graph'''
        count = 0
        for vertex in self.__out_edges:
            count += len(self.__out_edges[vertex])
        return count

    def get_in_degree(self, vertex):
        '''Returns the in-degree of the given vertex'''
       # if vertex in self.__in_edges:
        return len(self.__in_edges[vertex])
        #else:
        return None

    def get_out_degree(self, vertex):
        '''Returns the out-degree of the given vertex'''
       # if vertex in self.__out_edges:
        return len(self.__out_edges[vertex])
       # else:
        return None

    def get_cost(self, x, y):
        '''Returns the cost of a given edge'''
        return self.cost[x, y]

    def modify_edge_cost(self, x, y, new_cost):
        '''Modifies the cost of the edge from vertex x to vertex y'''
        if (x, y) in self.cost:
            self.cost[(x, y)] = new_cost
            return True
        return False

    def add_edge(self, x, y, cost):
        '''Adds an edge from vertex x to vertex y and returns True.
            If the edge already exists, nothing happens and the function returns False.
            Precondition: x and y are valid vertices of the graph.
        '''
        if x not in self.__in_edges or y not in self.__in_edges:
            return False

        if y in self.__out_edges[x]:
            return False

        self.__out_edges[x].add(y)
        self.__in_edges[y].add(x)
        self.cost[(x, y)] = cost
        return True

    def remove_edge(self, x, y):
        '''Removes the edge from vertex x to vertex y if it exists'''
        if self.is_edge(x, y):
            self.__out_edges[x].remove(y)
            self.__in_edges[y].remove(x)
            del self.cost[(x, y)]
            return True
        return False

    def copy(self):
        '''Returns a copy of the graph'''
        return deepcopy(self)

    def dfs(self, vertex, visited, component):
        '''Performs DFS starting from the given vertex'''
        visited.add(vertex)
        component.append(vertex)
        for neighbor in self.__out_edges[vertex]:
            if neighbor not in visited:
                self.dfs(neighbor, visited, component)

    def get_components(self):
        '''Returns a list of components, each component is a list of vertices'''
        visited = set()
        components = []
        for vertex in self.parse_vertices():
            if vertex not in visited:
                component = []
                self.dfs(vertex, visited, component)
                components.append(component)
        return components

    def dijkstra(self, start, end):
        '''Finds the lowest cost walk between two vertices using a simple version of Dijkstra's algorithm.'''
        distances = {vertex: float('inf') for vertex in self.parse_vertices()}
        distances[start] = 0
        visited = set()
        unvisited = list(self.parse_vertices())
        previous_nodes = {vertex: None for vertex in self.parse_vertices()}

        while unvisited:
            # Find the vertex with the smallest distance
            current_vertex = min((vertex for vertex in unvisited if vertex not in visited), key=lambda vertex: distances[vertex], default=None)
            if current_vertex is None:
                break

            visited.add(current_vertex)
            unvisited.remove(current_vertex)

            # If we reached the end vertex, reconstruct the path
            if current_vertex == end:
                path = []
                while previous_nodes[current_vertex] is not None:
                    path.append(current_vertex)
                    current_vertex = previous_nodes[current_vertex]
                path.append(start)
                path.reverse()
                return path, distances[end]

            # Update the distances to the neighbors
            for neighbor in self.__out_edges[current_vertex]:
                if neighbor in visited:
                    continue
                new_distance = distances[current_vertex] + self.cost[(current_vertex, neighbor)]
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance
                    previous_nodes[neighbor] = current_vertex

        return None, float('inf')

def create_small_graph():
    g = Graph(5)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(2, 0)
    g.add_edge(2, 3)
    return g


def create_random_graph(n, m):
    g = Graph(n)
    while m > 0:
        x = random.randrange(n)
        y = random.randrange(n)
        if x == y:
            continue
        cost = random.randint(1,100)
        if g.add_edge(x, y, cost):
            m = m - 1
    return g

def print_graph(g):
    print("Outbound:")
    for x in g.parse_vertices():
        print(f"{x}:", end='')
        for y in g.parse_nout(x):
            print(f" {y}", end='')
        print()
    print("Inbound:")
    for x in g.parse_vertices():
        print(f"{x}:", end='')
        for y in g.parse_nin(x):
            print(f" {y}", end='')
        print()

def test_basic_graph():
    # g = create_small_graph()
    g = create_random_graph(4, 1)
    print_graph(g)

def load_from_file(filename):
    with open(filename, 'r') as f:
        s = f.readline()
        x = str.split(s)
        n = int(x[0])
        m = int(x[1])

        g = Graph(n)

        for i in range(0, m):
            s = f.readline()
            x = str.split(s)
            v1 = int(x[0])
            v2 = int(x[1])
            c = int(x[2])
            g.add_edge(v1, v2, c)

    return g

def write_to_file(filename, graph):
    with open(filename, 'w') as f:
        f.write(str(graph.get_vertices_count()))
        f.write(" ")
        f.write(str(graph.get_edge_count()) + '\n')

        for x in graph.parse_vertices():
            for y in graph.parse_nout(x):
                f.write(str(x) + ' ' + str(y) + ' ' + str(graph.cost[x,y]) + '\n')
