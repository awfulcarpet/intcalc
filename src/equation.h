#ifndef EQUATION_H
#define EQUATION_H

enum TOKEN_TYPES {
	TOKEN_NUMBER,
	TOKEN_OPERATOR,
	TOKEN_VARIABLE,
	TOKEN_PAREN,
};

struct Token {
	enum TOKEN_TYPES type;
	int val;

	struct Token *next;
};

struct Token *tokenize_equation(char *equation);
void print_tokens(struct Token *tokens);
double calculate(struct Token *tokens, int x);

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
