#ifndef EQUATION_H
#define EQUATION_H
// queue
struct term {
	// currently only supports polynomials
	float c;
	float power;
	struct term *next;
};

// returns pointer to head
struct term * push_term(struct term *head, float c, float power); 

// returns pointer to a queue of terms
struct term * parse_equation(char *equation);

// frees queue of terms
void free_terms(struct term *head);

float get_value(struct term *equation, float x);
void print_terms(struct term *head);
#endif
