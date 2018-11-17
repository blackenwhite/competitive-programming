/*Indian National Olympiad in Informatics 2014

Due to resurfacing work, all north-south traffic on the highway is being diverted through the town of Siruseri. Siruseri is a modern, planned town and the section of roads used for the diversion forms a rectangular grid where all cars enter at the top-left intersection (north- west) and leave at the bottom-right intersection (south-east). All roads within the grid are one-way, allowing traffic to move north to south (up-down) and west to east (left-right) only.

The town authorities are concerned about highway drivers overspeeding through the town. To slow them down, they have made a rule that no car may travel more than d consecutive road segments in the same direction without turning. (Closed-circuit TV cameras have been installed to enforce this rule.)

Of course, there is also repair work going on within the town, so some intersections are blocked and cars cannot pass through these.

You are given the layout of the rectangular grid of roads within Siruseri and the constraint on how many consecutive road segments you may travel in the same direction. Your task is to compute the total number of paths from the entry (top-left) to the exit (bottom-right).

For instance, suppose there are 3 rows and 4 columns of intersec- tions, numbered from (1,1) at the top-left to (3,4) at the bottom-right, as shown on the right. Intersection (2,1) in the second row, first column is blocked, and no car may travel more than 2 consecutive road seg- ments in the same direction.

Here, (1,1) → (1,2) → (2,2) → (3,2) → (3,3) → (3,4) is a valid path from (1,1) to (3,4), but (1,1) → (1,2) → (1,3) → (1,4) → (2,4) → (3,4) is not, because this involves 3 consecutive road segments from left to right. The path (1, 1) → (2, 1) → (2, 2) → (2, 3) → (3, 3) → (3, 4) is ruled out because it goes through a blocked intersection. In this example, you can check that the total number of valid paths is 5.
Input format

• Line 1: Three space-separated integers, R, C and d, where R is the number of rows in the grid, C is the number of columns in the grid and d is the maximum number of consecutive segments you can travel in any direction.

• Lines 2 to R+1: Each line contains C integers, each of which is 0 or 1, describing one row of intersections in the grid. An intersection marked 0 is blocked and an intersection marked 1 is available to pass through. The start (top-left) and finish (bottom-right) intersections are always marked 1.
Output format

A single integer—the number of paths from the top-left intersection to the bottom-right intersection that go only down and right, and obey the d constraint.

Since the final answer may not fit in a variable of type int, report your answer modulo 20011. Be careful to avoid overflows in intermediate computations.
Test Data

The testdata is grouped into three subtasks. In all subtasks, 1 ≤ R ≤ 300, 1 ≤ C ≤ 300 and 1 ≤ d ≤ 300. In addition, each subtask has the following constraints on the inputs.

• Subtask 1 [20 points]: d = max(R, C) − 1. (In other words, there is no limit on the number of consecutive segments you can travel in one direction.)

• Subtask 2 [30 points]: d=2.

• Subtask 3 [50 points]: No additional constraint on d.
Example

Here is the sample input and output corresponding to the example above.
Sample input

3 4 2
1 1 1 1
0 1 1 1
1 1 1 1

Sample output

5
*/

#include <cstdio>
#include <cstring>

#define MOD 20011

int rows, cols, d;
int graph[305][305]; // Adjacency Matrix
int dp[305][305][305][2]; // Dynamic programming table


// Recurrence relation
long solve_recursive(int pos_x, int pos_y, 
                     int count, int direction)
{
    if (pos_x >= rows || pos_y >= cols)
        return 0;
    else if (count > d)
        return 0;
    else if (graph[pos_x][pos_y] == 0)
        return 0;
    else if (pos_x == rows - 1 && pos_y == cols - 1) // Reached the end
        return 1;
    else if (direction == 0) // direction == RIGHT
        return  solve_recursive(pos_x, pos_y+1, count + 1, direction) + 
                solve_recursive(pos_x+1, pos_y, 1, !direction);
    else // direction == DOWN
        return  solve_recursive(pos_x+1, pos_y, count + 1, direction) + 
                solve_recursive(pos_x, pos_y+1, 1, !direction);
}

long solve()
{
    // Base case at end
    for (int i = 0; i <= d; ++i)
        dp[rows-1][cols-1][i][0] = dp[rows-1][cols-1][i][1] = 1;
    
    // Fill table -> recurrence relation expressed above
    for (int i = rows - 1; i >= 0; --i)
    {
        for (int j = cols - 1; j >= 0; --j)
        {
            if (i == rows - 1 && j == cols - 1) continue; // End of matrix
            if (graph[i][j] == 0) continue; // Blocked path
            
            dp[i][j][d][0] = dp[i+1][j][1][1]; // Carry counts from previous iterations
            dp[i][j][d][1] = dp[i][j+1][1][0];
            
            for (int count = 0; count < d; ++count)
            {
                dp[i][j][count][0] = (dp[i][j+1][count+1][0] + dp[i+1][j][1][1]) % MOD;
                dp[i][j][count][1] = (dp[i+1][j][count+1][1] + dp[i][j+1][1][0]) % MOD;
            }
        }
    }
    
    return dp[0][0][0][0];
}

int main()
{
    std::memset(graph, 0, sizeof(int) * 305 * 305);
    std::memset(dp, 0, sizeof(int) * 305 * 305 * 305 * 2);
    
    std::scanf("%d %d %d", &rows, &cols, &d);
    
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            std::scanf("%d", &graph[i][j]);

    // std::printf("%d\n", solve_recursive(0, 0, 0, 0));   
    std::printf("%d\n", solve());
    
    return 0;
}
