#include "equation.h"
#include "riemann.h"

struct graph {
	Rectangle pos;
	float max_x;
	float min_x;
	float max_y;
	float min_y;
	float step;
};

void draw_graph_lines(struct graph *graph);
void draw_curve(struct graph *graph, struct term *equation);
float draw_and_calc_integral(struct graph *graph, struct term *equation, struct riemann *sum);
