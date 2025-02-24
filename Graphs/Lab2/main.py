class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, u, v):
        if u not in self.adj_list:
            self.adj_list[u] = []
        if v not in self.adj_list:
            self.adj_list[v] = []

        self.adj_list[u].append(v)
        self.adj_list[v].append(u)

    def dfs(self, vertex, visited, component):
        visited[vertex] = True
        component.add_vertex(vertex)
        for neighbor in self.adj_list[vertex]:
            if not visited[neighbor]:
                self.dfs(neighbor, visited, component)

    def connected_components(self):
        visited = {vertex: False for vertex in self.adj_list}
        components = []
        for vertex in self.adj_list:
            if not visited[vertex]:
                component = Graph()  # Create a new graph object for the component
                self.dfs(vertex, visited, component)
                components.append(component)
        return components

    def add_vertex(self, vertex):
        if vertex not in self.adj_list:
            self.adj_list[vertex] = []

    def print_graph(self):
        for vertex in self.adj_list:
            print(vertex, end=" ")
        print()


def print_components(components):
    nr = 0
    for component in components:
        print("Component " + str(nr + 1) + ":", end=" ")
        nr = nr + 1
        component.print_graph()


def main():
    graph = Graph()
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)

    # Second component: 4 -> 5
    graph.add_edge(4, 5)

    # Third component: 6 -> 7 -> 8
    graph.add_edge(6, 7)
    graph.add_edge(7, 8)

    while True:
        print("\nMenu:")
        print("1. Add an edge")
        print("2. Print connected components")
        print("3. Exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            u = int(input("Enter source vertex: "))
            v = int(input("Enter destination vertex: "))
            graph.add_edge(u, v)
        elif choice == '2':
            components = graph.connected_components()
            print_components(components)
        elif choice == '3':
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please enter a valid option.")


if __name__ == "__main__":
    main()
