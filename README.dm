# Task Manager

A simple command-line task management application written in C. This program allows users to create, edit, delete, and track tasks with priorities and completion status.

## Features

- **Task Management**
  - Add new tasks with title, description, and priority (1-10)
  - Delete existing tasks with confirmation
  - Edit task details (title, description, priority, status)
  - Mark tasks as completed

- **Task Organization**
  - View all tasks with detailed information
  - Sort tasks by:
    - Default (by ID)
    - Priority (highest first)
    - Completion status (incomplete first)
  - Prevent duplicate task titles

- **Data Persistence**
  - Automatic saving to file on exit
  - Manual save/load functionality
  - Tasks are stored in `tasks.txt` file
  - Preserves task ID sequence

## Installation & Compilation

### Prerequisites
- GCC compiler
- Standard C libraries

### Compilation
```bash
gcc -o task_manager task_manager.c
```

### Running
```bash
./task_manager
```

## Usage

### Main Menu Options
1. **Add Task** - Create a new task with title, description, and priority
2. **Remove Task** - Delete an existing task by ID
3. **Edit Task** - Modify task properties
4. **Mark as Completed** - Change task status to completed
5. **View All Tasks** - Display all tasks with sorting options
6. **Save Tasks** - Manually save tasks to file
7. **Load Tasks** - Manually load tasks from file
0. **Exit** - Quit the program (auto-saves)

### Task Properties
- **ID**: Auto-generated unique identifier
- **Title**: Task name (max 49 characters, unique)
- **Description**: Detailed task information (max 199 characters)
- **Priority**: Importance level from 1 (lowest) to 10 (highest)
- **Status**: Either "Completed" or "Not Completed"

## File Format

Tasks are saved in `tasks.txt` with the following format:
- First line: Next available task ID
- Subsequent lines: Task data separated by pipe (`|`) characters:
  ```
  id|title|description|priority|completed
  ```

## Data Structure

```c
typedef struct {
    int id;
    char title[50];
    char description[200];
    int priority;          // 1-10 scale
    int completed;         // 0 = not completed, 1 = completed
} Task;
```

## Constants

- `MAX_TASKS`: 100 (maximum number of tasks)
- `TITLE_LENGTH`: 50 characters
- `DESC_LENGTH`: 200 characters
- `FILENAME`: "tasks.txt"

## Error Handling

The program includes various error checks:
- Input validation for priority (1-10 range)
- Empty title prevention
- Duplicate title detection (case-insensitive)
- Array bounds checking
- File I/O error handling
- Invalid ID handling

## Sorting Algorithms

- **Priority Sort**: Uses `qsort()` with `compare_by_priority()` function
- **Status Sort**: Uses `qsort()` with `compare_by_status()` function
- **Default**: Maintains insertion order (by ID)

## Limitations

- Maximum of 100 tasks
- Task titles must be unique
- Text fields have fixed maximum lengths
- Data is stored in plain text format
- No search functionality included

## Future Enhancements

Potential improvements:
- Task categories/tags
- Due dates and reminders
- Advanced search/filtering
- Undo/redo functionality
- Export to other formats (CSV, JSON)
- Color-coded display
- Task statistics and reports
