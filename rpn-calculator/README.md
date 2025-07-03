# RPN Calculator

A command-line calculator that evaluates mathematical expressions in Reverse Polish Notation (postfix notation) using a custom linked list stack.

## Overview

Reverse Polish Notation eliminates the need for parentheses by placing operators after their operands. For example, `3 4 +` equals `7`, and `3 4 + 2 *` equals `14`.

## Usage

```bash
gcc -o rpn-calc rpn-calculator.c
echo "3 4 +" | ./rpn-calc
# Output: 7.000000
```

## Features

- **Stack-based evaluation** using a custom linked list implementation
- **Supported operations**: addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`)
- **Dynamic memory management** with proper cleanup
- **Input validation** for numbers and operators
- **Error handling** for common edge cases

## Implementation Details

### Data Structure
```c
typedef struct Node {
    double data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;
```

### Algorithm
1. **Tokenize** input string using `strtok()`
2. **For each token**:
   - If number: push onto stack
   - If operator: pop two operands, compute result, push back
3. **Validate** final stack has exactly one value
4. **Clean up** all allocated memory

## Examples

```bash
# Basic arithmetic
echo "3 4 +" | ./rpn-calc          # 7.000000
echo "10 5 -" | ./rpn-calc         # 5.000000
echo "6 2 /" | ./rpn-calc          # 3.000000

# Complex expressions
echo "15 7 1 1 + - / 3 *" | ./rpn-calc  # 5.000000
# Equivalent to: ((15 / (7 - (1 + 1))) * 3)

# Floating point
echo "3.5 2.1 +" | ./rpn-calc      # 5.600000
```

## Error Handling

The calculator handles several error conditions:
- **Division by zero**: Prevents undefined behavior
- **Invalid operators**: Rejects unknown symbols
- **Insufficient operands**: Ensures stack has enough values
- **Invalid numbers**: Validates numeric input
- **Malformed expressions**: Checks final stack state
- **Memory allocation failures**: Graceful error handling

## Memory Management

- Each `push()` operation allocates memory for a new node
- Each `pop()` operation frees the removed node
- `destroy_stack()` ensures no memory leaks on program exit
- Error paths properly clean up allocated resources
