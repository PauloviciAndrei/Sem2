from graph import *

class UI:

    def __init__(self, graph):
        self.graph = graph

    def get_command(self):
        cmd = int(input('Give command: '))
        print()

        return cmd

    def print_menu(self):
        print('1. Load small graph')
        print('2. Print graph')
        print('3. Topological sort')

    def run(self):

        while True:
            self.print_menu()
            cmd = self.get_command()

            if cmd == 1:
                self.graph = self.graph.load_small_graph(self);
            if cmd == 2:
                print_graph(self.graph);
            if cmd == 3:
                activities = [(0, 2), (1, 1), (2, 4), (3, 3), (4, 2), (5, 1)]
                prerequisites = [(0, 2), (1, 2), (1, 3), (3, 4), (2, 4), (4, 5)]
                print(self.graph.verify_and_sort_activities(activities,prerequisites))