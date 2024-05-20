#include <stdlib.h>
#include <ctype.h>
#include "equation.h"

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
	strncpy(buf, start, term - start);
	*c = atoi(buf);
	if (*c == 0 && term - start == 0) {
		*c = 1;
	}

	if (*c == 0 && buf[0] != '0' && start[0] != 'x' && term-start != 0) {
		return -1;
	}

	if (*term != 'x') {
		return 0;
	}

	term++;
	start = term;

	while (*term++ != '\0');

	memset(buf, 0, 255);
	strncpy(buf, start, term - start);
	*power = atoi(buf);
	if (*power == 0 && term-start != 0) {
		*power = 1;
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
				free_terms(terms);
				return NULL;
			}

			terms = push_term(terms, c, power);


			if (equation[end] == '\0')
				break;

			memset(buf, 0, 255);
			equation = equation + end + 1;
		}
		end++;
	}
	return terms;
}

void
print_terms(struct term *head)
{
	while (head != NULL) {
		printf("%f\n", head->c);
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
