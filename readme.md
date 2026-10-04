# Campus Navigation System

A graph-based campus navigation system that finds the shortest route between locations in a small campus graph.

The system implements Dijkstra's algorithm as the primary solution and A* as an optional bonus algorithm.

## Objective

Build a navigation system that represents campus locations and connections as a graph, allows the user to select a starting location and destination, and finds the shortest route between them.

## Features

- Weighted campus graph
- Adjacency list representation
- User-selected start location
- User-selected destination
- Dijkstra shortest-path algorithm
- A* shortest-path algorithm
- Path reconstruction
- Total route cost
- Nodes-explored comparison
- SVG visualisation
- Invalid input handling
- Unreachable-route handling
- No external libraries required

## Campus Locations

The current graph contains 10 locations:

1. Main Gate
2. Admin Block
3. USAR Block
4. USDI Block
5. Library
6. Auditorium
7. Sports Complex
8. Boys Hostel
9. Girls Hostel
10. Cafeteria

## Graph Representation

The campus is represented as a weighted undirected graph.

Vertices represent campus locations.

Edges represent connections between locations.

Each edge has an approximate walking distance in metres.

An adjacency list is used to store the graph.

Example:

```text
Admin Block
    |
    | 190m
    |
USDI Block
    |
    | 190m
    |
Cafeteria