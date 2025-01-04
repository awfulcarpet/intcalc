enum TOKEN_TYPES {
	TOKEN_NUMBER,
	TOKEN_OPERATOR,
	TOKEN_VARIABLE,
	TOKEN_PAREN,
};

enum OPERATORS {
	SUB = 1,
	PLUS = 2,
	MULT = 3,
	DIV = 4,
	POW = 5,
};

struct Token {
	enum TOKEN_TYPES type;
	double val;

	struct Token *next;
};

struct Token *tokenize_equation(char *equation);
void print_tokens(struct Token *tokens);
double calculate(struct Token *tokens, double x);
void free_tokens(struct Token *tokens);
