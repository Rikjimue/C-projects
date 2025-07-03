#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  double data;
  struct Node *next;
} Node;

typedef struct {
  Node *top;
} Stack;

int is_operator(const char *token) {
  return (strlen(token) == 1 &&
         (token[0] == '+' || token[0] == '-' ||
          token[0] == '*' || token[0] == '/'));
}

void init_stack(Stack *s) {
  s->top = NULL;
}

int is_empty(Stack *s) {
  return s->top == NULL;
}

int push(Stack *s, const double num) {
  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Error: memory allocation failed!\n");
    return 1;
  }

  new_node->data = num;
  new_node->next = s->top;
  s->top = new_node;

  return 0;
}

double pop(Stack *s) {
  if (is_empty(s)) {
    printf("Error: buffer bnderflow!\n");
    exit(1);
  }

  Node *temp = s->top;
  double result = temp->data;
  s->top = s->top->next;

  free(temp);
  return result;
}

int len_stack(Stack *s) {
  int count = 0;
  Node *current = s->top;
  while (current != NULL) {
    current = current->next;
    count++;
  }
  return count;
}

void print_stack(Stack *s) {
  Node *current = s->top;
  printf("Stack: ");
  while (current != NULL) {
      printf("%lf -> ", current->data);
      current = current->next;
  }
  printf("\n");
}

void destroy_stack(Stack *s) {
  while (!is_empty(s)) {
    pop(s);
  }
}

int main() {
  Stack stack;
  init_stack(&stack);

  // Fill stack
  char buffer[1024];
  fgets(buffer, sizeof(buffer), stdin);
  char *token = strtok(buffer, " \t\n");

  while (token != NULL) {
    // Check for operator
    if (is_operator(token)) {
      if (len_stack(&stack) < 2) {
        printf("Error: invalid operands.\n");
        exit(1);
      }

      double operand1 = pop(&stack);
      double operand2 = pop(&stack);
      double result;

      switch (token[0]) {
        case '+':
          result = operand2 + operand1;
          break;
        case '-':
          result = operand2 - operand1;
          break;
        case '*':
          result = operand2 * operand1;
          break;
        case '/':
          if (operand2 == 0.0) {
            printf("Error: divison by 0!\n");
            exit(1);
          }
          result = operand2 / operand1;
          break;
        default:
          printf("Error: invalid operator!\n");
          exit(1);
      }

      push(&stack, result);

    // Check for number
    } else {
      double number;
      char *endptr;
      number = strtod(token, &endptr);

      if (*endptr != '\0') {
        printf("Error: '%s' is not a valid number!\n", token);
        exit(1);
      }
      push(&stack, number);
    }
    token = strtok(NULL, " \t\n");
  }
  if (len_stack(&stack) != 1) {
    printf("Error: invalid operands!\n");
    exit(1);
  }
  printf("%lf\n", stack.top->data);
  destroy_stack(&stack);
}

