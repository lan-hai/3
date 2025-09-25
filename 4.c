#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9
#define BOX_SIZE 3

// Position structure
typedef struct {
    int row;
    int col;
} pos;

// Sudoku structure
typedef struct {
    int grid[SIZE][SIZE];        // Current sudoku grid
    int initial[SIZE][SIZE];     // Initial sudoku grid (unmodifiable parts)
    bool fixed[SIZE][SIZE];      // Mark which positions are fixed (initial numbers)
    int empty_cells;             // Count of empty cells
} Sudoku;

// Function declarations
Sudoku* NewEmptySudoku();
Sudoku* GenerateSudoku(int difficulty);
int Set(Sudoku* s, int row, int col, int value);
int Remove(Sudoku* s, int row, int col);
int Judge(Sudoku* s, int row, int col);
bool IsValidMove(Sudoku* s, int row, int col, int value);
bool IsSolved(Sudoku* s);
void Reset(Sudoku* s);
void PrintSudoku(Sudoku* s);
bool SolveSudoku(Sudoku* s);
bool FindEmptyCell(Sudoku* s, pos* position);
bool IsSafe(Sudoku* s, int row, int col, int num);
void RemoveNumbers(Sudoku* s, int cells_to_remove);

// Create a new empty sudoku
Sudoku* NewEmptySudoku() {
    Sudoku* s = (Sudoku*)malloc(sizeof(Sudoku));
    if (s == NULL) {
        return NULL;
    }
    
    // Initialize all cells to 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            s->grid[i][j] = 0;
            s->initial[i][j] = 0;
            s->fixed[i][j] = false;
        }
    }
    s->empty_cells = SIZE * SIZE;
    
    return s;
}

// Generate a random sudoku puzzle
Sudoku* GenerateSudoku(int difficulty) {
    Sudoku* s = NewEmptySudoku();
    if (s == NULL) return NULL;
    
    // First, fill a complete valid sudoku
    srand(time(NULL));
    
    // Fill the diagonal 3x3 boxes (they are independent)
    for (int box = 0; box < SIZE; box += BOX_SIZE) {
        int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        // Shuffle numbers randomly
        for (int i = 0; i < 9; i++) {
            int j = rand() % 9;
            int temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
        }
        
        // Fill current 3x3 box
        int index = 0;
        for (int i = box; i < box + BOX_SIZE; i++) {
            for (int j = box; j < box + BOX_SIZE; j++) {
                s->grid[i][j] = numbers[index++];
            }
        }
    }
    
    // Use backtracking to solve the rest
    if (!SolveSudoku(s)) {
        free(s);
        return NULL;
    }
    
    // Backup the complete sudoku as initial state
    memcpy(s->initial, s->grid, sizeof(s->grid));
    
    // Remove numbers based on difficulty
    int cells_to_remove;
    switch (difficulty) {
        case 1: cells_to_remove = 30; break; // Easy
        case 2: cells_to_remove = 40; break; // Medium
        case 3: cells_to_remove = 50; break; // Hard
        default: cells_to_remove = 40;
    }
    
    RemoveNumbers(s, cells_to_remove);
    
    return s;
}

// Set number at specified position
int Set(Sudoku* s, int row, int col, int value) {
    if (s == NULL || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return -1; // Invalid parameters
    }
    
    if (s->fixed[row][col]) {
        return -2; // Cannot modify initial numbers
    }
    
    if (value < 1 || value > 9) {
        return -3; // Number must be between 1-9
    }
    
    if (!IsValidMove(s, row, col, value)) {
        return -4; // Invalid move (violates sudoku rules)
    }
    
    // If there was a number before, remove it first
    if (s->grid[row][col] != 0) {
        s->empty_cells++;
    }
    
    s->grid[row][col] = value;
    s->empty_cells--;
    
    return 0; // Success
}

// Remove number from specified position
int Remove(Sudoku* s, int row, int col) {
    if (s == NULL || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return -1; // Invalid parameters
    }
    
    if (s->fixed[row][col]) {
        return -2; // Cannot remove initial numbers
    }
    
    if (s->grid[row][col] == 0) {
        return 0; // Already empty, no action needed
    }
    
    s->grid[row][col] = 0;
    s->empty_cells++;
    
    return 0; // Success
}

// Judge if number at specified position is correct
int Judge(Sudoku* s, int row, int col) {
    if (s == NULL || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return -1; // Invalid parameters
    }
    
    if (s->grid[row][col] == 0) {
        return 0; // Empty cell, cannot judge
    }
    
    // Check if current number matches the final answer
    if (s->grid[row][col] == s->initial[row][col]) {
        return 1; // Correct
    } else {
        return 0; // Incorrect
    }
}

// Check if a move is valid
bool IsValidMove(Sudoku* s, int row, int col, int value) {
    // Check row
    for (int j = 0; j < SIZE; j++) {
        if (j != col && s->grid[row][j] == value) {
            return false;
        }
    }
    
    // Check column
    for (int i = 0; i < SIZE; i++) {
        if (i != row && s->grid[i][col] == value) {
            return false;
        }
    }
    
    // Check 3x3 box
    int box_row = (row / BOX_SIZE) * BOX_SIZE;
    int box_col = (col / BOX_SIZE) * BOX_SIZE;
    
    for (int i = box_row; i < box_row + BOX_SIZE; i++) {
        for (int j = box_col; j < box_col + BOX_SIZE; j++) {
            if (i != row && j != col && s->grid[i][j] == value) {
                return false;
            }
        }
    }
    
    return true;
}

// Check if sudoku is solved
bool IsSolved(Sudoku* s) {
    if (s == NULL) return false;
    
    // Check if there are still empty cells
    if (s->empty_cells > 0) {
        return false;
    }
    
    // Check if all numbers follow the rules
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!IsValidMove(s, i, j, s->grid[i][j])) {
                return false;
            }
        }
    }
    
    return true;
}

// Reset to initial state
void Reset(Sudoku* s) {
    if (s == NULL) return;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            s->grid[i][j] = s->initial[i][j];
        }
    }
    
    // Recalculate empty cells count
    s->empty_cells = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s->grid[i][j] == 0) {
                s->empty_cells++;
            }
        }
    }
}

// Print sudoku grid
void PrintSudoku(Sudoku* s) {
    if (s == NULL) return;
    
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        if (i % BOX_SIZE == 0 && i != 0) {
            printf("------+-------+------\n");
        }
        
        for (int j = 0; j < SIZE; j++) {
            if (j % BOX_SIZE == 0 && j != 0) {
                printf("| ");
            }
            
            if (s->grid[i][j] == 0) {
                printf(". ");
            } else {
                if (s->fixed[i][j]) {
                    printf("\033[1m%d\033[0m ", s->grid[i][j]); // Bold for initial numbers
                } else {
                    printf("%d ", s->grid[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Solve sudoku using backtracking
bool SolveSudoku(Sudoku* s) {
    pos position;
    
    // If no empty cells, it's solved
    if (!FindEmptyCell(s, &position)) {
        return true;
    }
    
    int row = position.row;
    int col = position.col;
    
    // Try all possible numbers
    for (int num = 1; num <= 9; num++) {
        if (IsSafe(s, row, col, num)) {
            // Try placing the number
            s->grid[row][col] = num;
            
            // Recursively solve the rest
            if (SolveSudoku(s)) {
                return true;
            }
            
            // If failed, backtrack
            s->grid[row][col] = 0;
        }
    }
    
    return false; // Trigger backtracking
}

// Find an empty cell
bool FindEmptyCell(Sudoku* s, pos* position) {
    for (position->row = 0; position->row < SIZE; position->row++) {
        for (position->col = 0; position->col < SIZE; position->col++) {
            if (s->grid[position->row][position->col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Check if a number can be safely placed
bool IsSafe(Sudoku* s, int row, int col, int num) {
    // Check row
    for (int j = 0; j < SIZE; j++) {
        if (s->grid[row][j] == num) {
            return false;
        }
    }
    
    // Check column
    for (int i = 0; i < SIZE; i++) {
        if (s->grid[i][col] == num) {
            return false;
        }
    }
    
    // Check 3x3 box
    int box_row = (row / BOX_SIZE) * BOX_SIZE;
    int box_col = (col / BOX_SIZE) * BOX_SIZE;
    
    for (int i = box_row; i < box_row + BOX_SIZE; i++) {
        for (int j = box_col; j < box_col + BOX_SIZE; j++) {
            if (s->grid[i][j] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Remove numbers to create a puzzle
void RemoveNumbers(Sudoku* s, int cells_to_remove) {
    int removed = 0;
    
    while (removed < cells_to_remove) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        
        // If this position has a number, remove it
        if (s->grid[row][col] != 0) {
            int backup = s->grid[row][col];
            s->grid[row][col] = 0;
            
            // Mark as fixed position (initial number)
            s->fixed[row][col] = true;
            
            removed++;
        }
    }
    
    // Update empty cells count
    s->empty_cells = cells_to_remove;
}

// Simple command-line interface
void ShowMenu() {
    printf("\n=== Sudoku Game ===\n");
    printf("1. New Game - Easy\n");
    printf("2. New Game - Medium\n");
    printf("3. New Game - Hard\n");
    printf("4. Set Number (format: row col number)\n");
    printf("5. Remove Number (format: row col)\n");
    printf("6. Check if number is correct (format: row col)\n");
    printf("7. Reset Game\n");
    printf("8. Check if completed\n");
    printf("9. Show Sudoku\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main() {
    Sudoku* sudoku = NULL;
    int choice;
    int row, col, value;
    
    srand(time(NULL));
    
    printf("Welcome to Sudoku!\n");
    
    while (1) {
        ShowMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
            case 2:
            case 3:
                if (sudoku != NULL) {
                    free(sudoku);
                }
                sudoku = GenerateSudoku(choice);
                if (sudoku != NULL) {
                    printf("New game generated!\n");
                    PrintSudoku(sudoku);
                } else {
                    printf("Failed to generate sudoku!\n");
                }
                break;
                
            case 4:
                if (sudoku == NULL) {
                    printf("Please start a new game first!\n");
                    break;
                }
                printf("Enter row, column and number (0-8, 0-8, 1-9): ");
                scanf("%d %d %d", &row, &col, &value);
                int result = Set(sudoku, row, col, value);
                if (result == 0) {
                    printf("Number set successfully!\n");
                    PrintSudoku(sudoku);
                } else {
                    printf("Set failed: ");
                    switch (result) {
                        case -1: printf("Invalid parameters\n"); break;
                        case -2: printf("Cannot modify initial numbers\n"); break;
                        case -3: printf("Number must be between 1-9\n"); break;
                        case -4: printf("Violates sudoku rules\n"); break;
                    }
                }
                break;
                
            case 5:
                if (sudoku == NULL) {
                    printf("Please start a new game first!\n");
                    break;
                }
                printf("Enter row and column to remove number (0-8, 0-8): ");
                scanf("%d %d", &row, &col);
                result = Remove(sudoku, row, col);
                if (result == 0) {
                    printf("Number removed successfully!\n");
                    PrintSudoku(sudoku);
                } else {
                    printf("Remove failed: ");
                    switch (result) {
                        case -1: printf("Invalid parameters\n"); break;
                        case -2: printf("Cannot remove initial numbers\n"); break;
                    }
                }
                break;
                
            case 6:
                if (sudoku == NULL) {
                    printf("Please start a new game first!\n");
                    break;
                }
                printf("Enter row and column to check (0-8, 0-8): ");
                scanf("%d %d", &row, &col);
                result = Judge(sudoku, row, col);
                if (result == 1) {
                    printf("This number is correct!\n");
                } else if (result == 0) {
                    printf("This number is incorrect or the position is empty!\n");
                } else {
                    printf("Check failed: Invalid parameters\n");
                }
                break;
                
            case 7:
                if (sudoku == NULL) {
                    printf("Please start a new game first!\n");
                    break;
                }
                Reset(sudoku);
                printf("Game reset!\n");
                PrintSudoku(sudoku);
                break;
                
            case 8:
                if (sudoku == NULL) {
                    printf("Please start a new game first!\n");
                    break;
                }
                if (IsSolved(sudoku)) {
                    printf("Congratulations! Sudoku completed!\n");
                } else {
                    printf("Sudoku not yet completed, keep trying!\n");
                    printf("Remaining empty cells: %d\n", sudoku->empty_cells);
                }
                break;
                
            case 9:
                if (sudoku == NULL) {
                    printf("Please start a new game first!\n");
                    break;
                }
                PrintSudoku(sudoku);
                break;
                
            case 0:
                if (sudoku != NULL) {
                    free(sudoku);
                }
                printf("Thank you for playing! Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice, please try again!\n");
        }
    }
    
    return 0;
}