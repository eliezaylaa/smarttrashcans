# BFS Pathfinding Algorithm - Unity Implementation

## What is BFS?

BFS (Breadth First Search) is a graph traversal algorithm that explores
nodes level by level from a starting point.
It always finds the shortest path between two points.
This makes it perfect for our garbage truck navigation.

## How it works in our project

### Setup

- The road map is drawn on paper with grey roads
- AR Foundation detects the grey road color on the map
- Each trashcan is placed physically on the map
- AR detects each trashcan position in real space
- The garbage truck spawns at a random point on the grey road

### Step by Step Algorithm

1. Truck spawns at random position on grey road
2. Unity polls API every 2 seconds via GET /status_all
3. Unity receives all 3 trashcan states
4. Unity filters only ABNORMAL trashcans
5. BFS calculates distance from truck to each abnormal can
6. Truck moves to the NEAREST abnormal can first
7. Truck arrives and WAITS at that position
8. Unity keeps polling API every 2 seconds
9. When that can returns to NORMAL state
10. BFS recalculates remaining abnormal cans
11. Truck moves to next nearest abnormal can
12. Repeats until all cans are normal
13. Truck returns to random road position and parks

### Truck Skipping Logic

```
Can 1 = empty (normal) → SKIP
Can 2 = tilted (abnormal) → VISIT
Can 3 = open (abnormal) → VISIT
Truck path: Can 2 → Can 3 (skips Can 1)
```

### Real-time Updates

The truck reacts to live sensor changes:

- Trashcan becomes abnormal while truck is moving → added to path
- Trashcan becomes normal before truck arrives → removed from path
- All cans normal → truck parks immediately

### Road Detection

- AR Foundation detects the flat map surface
- Camera samples pixel colors on detected surface
- Grey pixels = road area
- Truck is constrained to only move on grey road pixels
- Random spawn point is always on a grey road pixel

## Why BFS?

- Simple to implement
- Always finds shortest path
- Works perfectly with only 3 trashcan nodes
- Easy to update dynamically as states change
