#include "elevator.h"

int main(void){
  int floors;
  int start;
  int goal;
  int up;
  int down;

  // User input
  printf("Enter 5 integer values: f s g u d\n");
  if (!scanf("%d %d %d %d %d", &floors, &start, &goal, &up, &down)){
    fprintf(stderr, "Invalid input. Ensure there are 5 inputted integers separated by spaces and no extra spaces.");
    exit(1);
  }
  else {
    if (floors == 0 || floors > 100){
      fprintf(stderr, "Invalid f input. use the stairs\n");
      exit(1);
    }
    if (start < 1 || start > 100){
      fprintf(stderr, "Invalid s input. use the stairs\n");
      exit(1);
    }
    if (goal < 1 || goal > 100 || goal > floors){
      fprintf(stderr, "Invalid g input. use the stairs\n");
      exit(1);
    }
    if (up < 0 || up > floors){
      fprintf(stderr, "Invalid u input. use the stairs\n");
      exit(1);
    }
    if (down > 100 || down > floors){
      fprintf(stderr, "Invalid d input. use the stairs\n");
      exit(1);
    }
  }

  Graph* graph = createGraph(floors, start, up, down);

  //printGraph(graph);

  bfs_shortest_path(graph, start, goal);

  // Rough Notes
  // Determine all edges based on input with some algorithm?

  // I think I need to initialize all nodes (floors) and then connect them based on start floor and go up up amount of floors and make an edge each time then go down down amount of floors and make more edges for that
  // Then I will have my completed graph that I can perform DFS on starting from the starting floor!

  // Init graph from input and edges to make a graph
  // Make a graph from ALL EDGES!!!!! So if u = 2 and d = 1 then all edges will go from s (starting) to 2 floors above that until the floor doesn't exist and there will be edges going down 1 from that all the way back to the starting floor
  //createGraph()

  // Find minimum number of pushes to get from start to goal, output "use the stairs" if not possible
  // If possible, output sequence of pushes separated by arrows (Finding an MST -- traversal of MST? -- Prim's algorithm? and then BFS?)
  // Or actually you probably need DFS to find the fastest (shortest) path to the goal floor
  return 0;
}