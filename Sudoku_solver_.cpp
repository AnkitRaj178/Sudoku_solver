import java.util.*;

public class SudokuSolver {

    // N is the size of the 2D matrix N*N
    static final int N = 9;

    // A utility function to print grid
    static void print(int[][] grid) {
        for (int r = 0; r < N; r++) {
            for (int d = 0; d < N; d++) {
                System.out.print(grid[r][d] + " ");
            }
            System.out.println();
        }
    }

    // Checks whether it will be legal to assign num to the given row, col
    static boolean isSafe(int[][] grid, int row, int col, int num) {

        // Check if we find the same num in the row
        for (int x = 0; x < N; x++) {
            if (grid[row][x] == num) {
                return false;
            }
        }

        // Check if we find the same num in the column
        for (int x = 0; x < N; x++) {
            if (grid[x][col] == num) {
                return false;
            }
        }

        // Check if we find the same num in the 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    // Solves the Sudoku using backtracking
    static boolean solveSudoku(int[][] grid, int row, int col) {
        // If we have reached the 9th row and 9th column, we are done
        if (row == N - 1 && col == N) {
            return true;
        }

        // Move to the next row if we reach the end of the column
        if (col == N) {
            row++;
            col = 0;
        }

        // Skip the cell if it's already filled
        if (grid[row][col] != 0) {
            return solveSudoku(grid, row, col + 1);
        }

        // Try placing numbers 1 to 9 in the cell
        for (int num = 1; num <= N; num++) {
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;

                // Recursively proceed to the next cell
                if (solveSudoku(grid, row, col + 1)) {
                    return true;
                }

                // If the assumption was wrong, backtrack
                grid[row][col] = 0;
            }
        }

        return false; // Trigger backtracking
    }

    public static void main(String[] args) {
        // 0 means unassigned cells
        int[][] grid = {
            {3, 0, 6, 5, 0, 8, 4, 0, 0},
            {5, 2, 0, 0, 0, 0, 0, 0, 0},
            {0, 8, 7, 0, 0, 0, 0, 3, 1},
            {0, 0, 3, 0, 1, 0, 0, 8, 0},
            {9, 0, 0, 8, 6, 3, 0, 0, 5},
            {0, 5, 0, 0, 9, 0, 6, 0, 0},
            {1, 3, 0, 0, 0, 0, 2, 5, 0},
            {0, 0, 0, 0, 0, 0, 0, 7, 4},
            {0, 0, 5, 2, 0, 6, 3, 0, 0}
        };

        if (solveSudoku(grid, 0, 0)) {
            print(grid);
        } else {
            System.out.println("No solution exists");
        }
    }
}
