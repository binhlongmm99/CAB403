# CAB403 - Practical 8 notes

## Materials
- Round-Robin vs Shortest Job First: [Geeks](https://www.geeksforgeeks.org/difference-between-shortest-job-first-sjf-and-round-robin-rr-scheduling-algorithms/)

## Notes
### 1. 'reference' folder:
- The 'reference' folder contains the solutions provided on Canvas. The solutions in this repository, however, use more descriptive variable names (in my opinion).

### 2. Gannt chart explanation
- Example 2
  
|            |         |           t| 0  | 1  | 2  | 3  | 5  | 10 | 17 | 26 |
|------------|---------|------------|----|----|----|----|----|----|----|----|
| Process no | Arrival | Burst time |    |    |    |    |    |    |    |    |
| 1          | 0       | 8          | 8  | 7  | 7  | 7  | 7  | 7  | 0  | x  |
| 2          | 1       | 4          |    | 4  | 3  | 2  | 0  | x            |
| 3          | 2       | 9          |    |    | 9  | 9  | 9  | 9  | 9  | 0  |
| 4          | 3       | 5          |    |    |    | 5  | 5  | 0  | x       |


| Process no   | Finish time     | Turnaround time | Waiting time |
|--------------|-----------------|-----------------|--------------|
| 1            | 17              | 17              | 9            |
| 2            | 5               | 4               | 0            |
| 3            | 26              | 24              | 15           |
| 4            | 10              | 7               | 2            |
