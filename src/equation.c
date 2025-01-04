#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "equation.h"

struct Token *
append(struct Token *head, enum TOKEN_TYPES type, int val)
{
	struct Token *new = calloc(1, sizeof(struct Token));
	new->type = type;
	new->val = val;
	new->next = NULL;

	if (head == NULL)
		return new;

	struct Token *token = head;
	while (token->next != NULL) token = token->next;

	token->next = new;

	return head;
}

int
is_operator(char c)
{
	return c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

int
op_to_tok(char c)
{
	switch (c) {
		case '+':
			return PLUS;
		case '-':
			return SUB;
		case '*':
			return MULT;
		case '/':
			return DIV;
		case '^':
			return POW;
		default:
			return -1;
	};
	return -1;
}

double
operate(enum OPERATORS op, double a, double b)
{
	switch (op) {
		case PLUS:
			return a + b;
		case SUB:
			return a - b;
		case MULT:
			return a * b;
		case DIV:
			return a / b;
		case POW:
			return pow(a, b);
	}
}

struct Token *
get_last(struct Token *head)
{
	if (head == NULL)
		return NULL;
	while (head->next != NULL) head = head->next;
	return head;
}

struct Token *
tokenize_equation(char *equation)
{
	struct Token *head = NULL;
	char *c = equation;

	while (*c != '\0') {
		while (*c == ' ') c++;

		if (isdigit(*c)) {
			int val = 0;
			do {
				val = val * 10 + (*c - '0');
			} while (isdigit(*++c));

			head = append(head, TOKEN_NUMBER, (double)val);
			continue;
		}

		if (is_operator(*c)) {
			head = append(head, TOKEN_OPERATOR, op_to_tok(*c));
			c++;
			continue;
		}

		if (*c == '(' || *c == ')') {
			head = append(head, TOKEN_PAREN, *c);
			c++;
			continue;
		}

		if (*c == 'x') {
			struct Token *last = get_last(head);
			if (last != NULL && get_last(head)->type == TOKEN_NUMBER)
				head = append(head, TOKEN_OPERATOR, op_to_tok('*'));

			head = append(head, TOKEN_VARIABLE, *c);
			c++;
			continue;
		}

		/* todo free head */
		free_tokens(head);
		return NULL;
	}

	return head;
}

double
calculate(struct Token *tokens, double x)
{
	struct Token * ostack[20] = {0};
	struct Token * hstack[20] = {0};
	int op = 0;
	int hp = 0;

	while (tokens != NULL) {
		if (tokens->type == TOKEN_NUMBER || tokens->type == TOKEN_VARIABLE)
			ostack[op++] = tokens;

		if (tokens->type == TOKEN_OPERATOR) {
			if (hp > 0) {
				if (hstack[hp - 1]->type == TOKEN_OPERATOR
						&& hstack[hp-1]->val > tokens->val)
				ostack[op++] = hstack[--hp];
			}
			hstack[hp++] = tokens;
		}

		tokens = tokens->next;
	}

	while (hp != 0) ostack[op++] = hstack[--hp];

	double sstack[20] = {0};
	int sp = 0;
	for (int i = 0; i < op; i++) {
		if (ostack[i]->type == TOKEN_OPERATOR) {
			if (sp < 2)
				return 0;
			double res = operate(ostack[i]->val, sstack[sp - 2], sstack[sp - 1]);

			sp -= 2;
			sstack[sp++] = res;
			continue;
		}
		if (ostack[i]->type == TOKEN_VARIABLE) {
			sstack[sp++] = x;
			continue;
		}
		sstack[sp++] = ostack[i]->val;
	}
	return sstack[0];
}

void
print_tokens(struct Token *tokens)
{
	while (tokens != NULL) {
		switch (tokens->type) {
			case TOKEN_NUMBER:   printf("number   %f\n", tokens->val); break;
			case TOKEN_OPERATOR: printf("operator %d\n", (int)tokens->val); break;
			case TOKEN_VARIABLE: printf("variable %c\n", (char)tokens->val); break;
			case TOKEN_PAREN:    printf("paren    %c\n", (char)tokens->val); break;
		}
		tokens = tokens->next;
	}
}

void
free_tokens(struct Token *tokens)
{
	if (tokens == NULL)
		return;

	struct Token *next = tokens->next;
	while (tokens != NULL) {
		next = tokens->next;
		free(tokens);
		tokens = next;
	}
}
