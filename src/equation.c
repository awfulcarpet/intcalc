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

			head = append(head, TOKEN_NUMBER, val);
			continue;
		}

		if (is_operator(*c)) {
			head = append(head, TOKEN_OPERATOR, *c);
			c++;
			continue;
		}

		if (*c == '(' || *c == ')') {
			head = append(head, TOKEN_PAREN, *c);
			c++;
			continue;
		}

		if (*c == 'x') {
			head = append(head, TOKEN_VARIABLE, *c);
			c++;
			continue;
		}

		/* todo free head */
		return NULL;
	}

	return head;
}

double
calculate(struct Token *tokens, int x)
{
	return 0.0;
}

void
print_tokens(struct Token *tokens)
{
	while (tokens != NULL) {
		switch (tokens->type) {
			case TOKEN_NUMBER:   printf("number   %d\n", tokens->val); break;
			case TOKEN_OPERATOR: printf("operator %c\n", tokens->val); break;
			case TOKEN_VARIABLE: printf("variable %c\n", tokens->val); break;
			case TOKEN_PAREN:    printf("paren    %c\n", tokens->val); break;
		}
		tokens = tokens->next;
	}
}

struct term *
push_term(struct term *head, float c, float power)
{
	struct term *new_term = NULL;
	new_term = calloc(1, sizeof(struct term));
	new_term->c = c;
	new_term->power = power;
	new_term->next = NULL;

	if (head == NULL) {
		head = new_term;
		return head;
	}

	struct term *cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = new_term;

	return head;
}

int
parse_term(char *term, float *c, float *power) {
	char *start = term;
	while (*term != '\0' && *term != 'x') term++;

	char *buf[255] = {0};
	strncpy((char *)buf, start, term - start);
	*c = atof((char *)buf);
	if (*c == 0 && term - start == 0 && start[0] == 'x') {
		*c = 1;
	}

	if (*c == 0) {
		return 1;
	}
	if (*term == '\0') {
		return 0;
	}
	term++;
	start = term;
	while (*term != '\0') term++;
	if (start - term == 0) {
		*power = 1;
		return 0;
	}


	memset(buf, 0, 255);
	strncpy((char *)buf, start, term - start);
	*power = atof((char *)buf);
	if (*power == 0 && start[0] != '0') {
		return 1;
	}

	return 0;
}

struct term *
parse_equation(char *equation)
{
	int start = 0;
	int end = 0;
	struct term *terms = NULL;

	if (equation[0] == '\0') {
		return NULL;
	}

	char buf[255] = {0};
	float c = 1;
	float power = 0;

	int x = start;
	while (1) {
		// TODO: handle whitespace
		if (equation[end] == '+' || equation[end] == '\0') {
			strncpy(buf, equation, end);
			if (parse_term(buf, &c, &power)) {
				/* free_terms(terms); */
				/* return NULL; */
				goto cleanup;
			}
			/* printf("%d %f %f\n\n", equation, c, power); */

			terms = push_term(terms, c, power);


cleanup:
			if (equation[end] == '\0')
				break;

			memset(buf, 0, 255);
			equation = equation + end + 1;
			end = 0;
			c = 0;
			power = 0;
		}
		end++;
	}
	return terms;
}

float
get_value(struct term *equation, float x) {
	float y = 0.0;
	while (equation != NULL) {
		y += equation->c * powf(x, equation->power);
		equation = equation->next;
	}
	return y;
}

void
print_terms(struct term *head)
{
	while (head != NULL) {
		printf("%fx^%f\n", head->c, head->power);
		head = head->next;
	}
}

void
free_terms(struct term *head)
{
	if (head == NULL)
		return;

	struct term *cur = head;
	struct term *next = NULL;
	do {
		next = cur->next;
		free(cur);
		cur = next;
	} while (cur != NULL);
}
