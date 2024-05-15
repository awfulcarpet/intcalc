#include <stdlib.h>
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

	while (head->next != NULL);
	head->next = new_term;

	return head;
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

	while (1) {
		if (equation[end] == '+' || equation[end] == '\0') {
			float c = 1;
			float power = 0;

			int x = start;
			char buf[6] = {0};
			while (equation[x++] != 'x' && x <= end);

			strncpy(buf, equation + start, x-1);
			c = atoi(buf);
			if (c == 0 && buf[0] != '0') {
				return NULL;
			}

			terms = push_term(terms, atoi(buf), 3);

			if (equation[end] == '\0')
				break;

			start = end + 1;
		}
		end++;
	}
	return terms;
}

void
free_terms(struct term *head)
{
	if (head == NULL)
		return;

	struct term *next = head->next;
	do {
		free(head);
		head = next;
		next = head->next;
	} while ((next != NULL));
}
