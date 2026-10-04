# Design Decisions

## 1. Graph Representation

The campus is represented as a weighted undirected graph.

Each campus location is represented as a vertex, and each connection between two locations is represented as an edge.

An adjacency list is used to store the graph because the campus graph is relatively sparse.

Each edge stores an approximate walking distance in metres.

## 2. Primary Algorithm: Dijkstra

Dijkstra's algorithm is used as the primary shortest-path algorithm.

The graph contains weighted edges and all edge weights are non-negative, so Dijkstra is suitable for finding the minimum-cost route.

A priority queue is used to efficiently select the location with the smallest current distance.

Time Complexity:

O((V + E) log V)

Space Complexity:

O(V + E)

## 3. Bonus Algorithm: A*

A* is implemented as an additional shortest-path algorithm.

A* uses the Euclidean distance between the visual coordinates of locations as its heuristic.

Because the visual coordinates and graph edge weights use different scales, the heuristic is multiplied by a scale factor calculated from the graph.

The scale factor is based on the minimum ratio of edge weight to corresponding visual distance.

This keeps the heuristic from overestimating the actual graph cost and allows A* to find an optimal route.

## 4. Algorithm Comparison

The program runs both Dijkstra and A* for the same start and destination.

The following values are compared:

- Shortest route
- Total route cost
- Number of nodes explored

In testing, both algorithms produced the same minimum route cost, while A* explored fewer nodes for several routes.

Example:

Dijkstra:
- Cost: 380 metres
- Nodes explored: 6

A*:
- Cost: 380 metres
- Nodes explored: 4

This demonstrates the advantage of using a heuristic to guide the search.

## 5. Path Reconstruction

A parent array is maintained by both algorithms.

After reaching the destination, the parent array is followed backwards to reconstruct the complete shortest route.

## 6. Visualisation

The program generates an SVG file named `route.svg`.

The campus graph and edge distances are displayed visually, and the selected A* shortest route is highlighted.

The SVG is generated directly using C++ file output, so no external visualization library is required.

## 7. Data Decision

The location names are based on the GGSIPU East Delhi Campus/USAR context.

The graph contains:

- Main Gate
- Admin Block
- USAR Block
- USDI Block
- Library
- Auditorium
- Sports Complex
- Boys Hostel
- Girls Hostel
- Cafeteria

The edge distances are approximate demonstration values used for the project. They are not claimed to be official surveyed walking distances.

## 8. Edge Cases

The program handles:

- Invalid location numbers
- Unreachable destinations
- No valid route
- Same start and destination

## 9. Technology Decision

The project uses only standard C++ and STL.

No external libraries or frameworks are required.

Main STL/data structures used:

- `vector`
- `priority_queue`
- `pair`
- `string`
- `fstream`
- `algorithm`