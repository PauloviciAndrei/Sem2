from graph import *

class UI:

    def __init__(self, graph):
        self.graph = graph

    def get_command(self):
        cmd = int(input('Give command: '))
        print()

        return cmd

    def get_vertices(self):
        x = int(input("Give first vertex: "))
        y = int(input("Give second vertex: "))
        print()

        return x, y

    def get_vertex(self):
        x = int(input("Give vertex: "))
        print()

        return x

    def get_new_cost(self):
        cost = int(input("Give new cost: "))
        print()

        return cost

    def get_vertices_and_edges(self):
        x = int(input("Give number of vertices: "))
        y = int(input("Give number of edges: "))
        print()

        return x, y

    def get_file(self):
        file = input("Give file name: ")
        print()

        return file

    def print_components(self, components):
        '''Prints the components of the graph'''
        for i, component in enumerate(components):
            print(f"Component {i + 1}: {component}")

    def print_menu(self):
        print('1. Load 1k graph')
        print('2. Load 10k graph')
        print('3. Load 100k graph')
        print('4. Get vertices count')
        print('5. Get edge count')
        print('6. Edge between vertices')
        print('7. Get the in degree')
        print('8. Get the out degree')
        print('9. Get cost of an edge')
        print('10. Modify the cost of an edge')
        print('11. Add edge')
        print('12. Remove edge')
        print('13. Remove vertex')
        print('14. Make a copy of the graph')
        print('15. Create a random graph')
        print('16. Read from a file')
        print('17. Write to a file')
        print('18. Print graph')
        print('19. Print components')
        print('20. Dijkstra')
        print('21. Exit')
        print('==============')
        print()

    def run(self):

        while True:
            self.print_menu()
            cmd = self.get_command()

            if cmd == 1:
                self.graph = load_from_file("graph1k.txt")
            if cmd == 2:
                self.graph = load_from_file("graph10k.txt")
            if cmd == 3:
                self.graph = load_from_file("graph100k.txt")
            if cmd == 4:
                print(self.graph.get_vertices_count())
                print()
            if cmd == 5:
                print(self.graph.get_edge_count())
                print()
            if cmd == 6:
                x, y = self.get_vertices()
                if(self.graph.is_edge(x, y) == True):
                    print("There is an edge between the two vertices")
                    print()
                else:
                    print("There is not an edge between the two vertices")
                    print()
            if cmd == 7:
                x = self.get_vertex()
                print(self.graph.get_in_degree(x))
                print()
            if cmd == 8:
                x = self.get_vertex()
                print(self.graph.get_out_degree(x))
                print()

            if cmd == 9:
                x, y = self.get_vertices()
                if(self.graph.is_edge(x, y) == True):
                    print(self.graph.get_cost(x, y))
                    print()
                else:
                    print("Invalid edge!")
                    print()

            if cmd == 10:
                x, y = self.get_vertices()
                cost = self.get_new_cost()
                if(self.graph.modify_edge_cost(x, y, cost) == True):
                    print("Modify successful!")
                    print()
                else:
                    print("Invalid edge!")
                    print()

            if cmd == 11:
                x, y = self.get_vertices()
                cost = self.get_new_cost()

                if self.graph.add_edge(x,y,cost) == True:
                    print("Modify successful!")
                    print()
                else:
                    print("Edge already exists!")
                    print()

            if cmd == 12:
                x, y = self.get_vertices()

                if self.graph.remove_edge(x,y) == True:
                    print("Modify successful!")
                    print()
                else:
                    print("Edge doesn't exists!")
                    print()

            if cmd == 13:
                x = self.get_vertex()

                if self.graph.remove_vertex(x) == True:
                    print("Modify successful!")
                    print()
                else:
                    print("Vertex does not exist!")
                    print()

            if cmd == 14:
                self.graph = self.graph.copy()

            if cmd == 15:
                x, y = self.get_vertices_and_edges()
                self.graph = create_random_graph(x, y)

            if cmd == 16:
                self.graph = load_from_file(self.get_file())

            if cmd == 17:
                write_to_file(self.get_file(), self.graph)

            if cmd == 18:
                print_graph(self.graph)

            if cmd == 19:
                components = self.graph.get_components()
                self.print_components(components)

            if cmd == 20:
                x, y = self.get_vertices()
                print(self.graph.dijkstra(x,y))
                print()

            if cmd == 21:
                break

ui = UI(Graph)
ui.run()

