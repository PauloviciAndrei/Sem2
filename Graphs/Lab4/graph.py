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

    def load_small_graph(self):
        g = Graph(6);

        g.add_edge(2, 3,0);
        g.add_edge(2, 1,0);
        g.add_edge(4, 5,0);
        g.add_edge(5, 0,0);
        g.add_edge(3,1,0);
        g.add_edge(0, 2, 0);

        return g;

    def modify_edge_cost(self, x, y, new_cost):
        '''Modifies the cost of the edge from vertex x to vertex y'''
        if (x, y) in self.cost:
            self.cost[(x, y)] = new_cost
            return True
        return False

    def __topological_sort_util(self, v, visited, stack, temp_stack):
        visited[v] = True
        temp_stack[v] = True

        for i in self.parse_nout(v):
            if not visited[i]:
                if not self.__topological_sort_util(i, visited, stack, temp_stack):
                    return False
            elif temp_stack[i]:
                return False

        temp_stack[v] = False
        stack.append(v)
        return True

    def topological_sort(self):
        visited = {v: False for v in self.parse_vertices()}
        temp_stack = {v: False for v in self.parse_vertices()}
        stack = []

        for v in self.parse_vertices():
            if not visited[v]:
                if not self.__topological_sort_util(v, visited, stack, temp_stack):
                    return None  # Graph contains a cycle

        stack.reverse()
        return stack

    def verify_and_sort_activities(self, activities, prerequisites):
        '''Verifies if the graph is a DAG and performs topological sorting.'''
        self.__init__(len(activities))

        earliest_start_times = {v: 0 for v in range(len(activities))}
        critical_activities = []

        for activity, duration in activities:
            self.add_vertex(activity)

        for x, y in prerequisites:
            self.add_edge(x, y, duration)

        topo_sort = self.topological_sort()

        if topo_sort is None:
            return "The graph contains a cycle.", []

        # Calculate earliest start times
        for v in topo_sort:
            for neighbor in self.parse_nout(v):
                earliest_start_times[neighbor] = max(earliest_start_times[neighbor],
                                                     earliest_start_times[v] + activities[v][1])

        total_time = max(earliest_start_times.values())

        latest_start_times = {v: total_time for v in range(len(activities))}

        for v in reversed(topo_sort):
            for neighbor in self.parse_nin(v):
                latest_start_times[v] = min(latest_start_times[v],
                                            latest_start_times[neighbor] - activities[v][1])

        for v in range(len(activities)):
            if earliest_start_times[v] == latest_start_times[v]:
                critical_activities.append(v)

        # Print earliest and latest starting times for each activity
        for v in range(len(activities)):
            print(
                f"Activity {v}: Earliest Start Time = {earliest_start_times[v]}, Latest Start Time = {latest_start_times[v]}")

        return f"Total Project Time: {total_time}", critical_activities


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