#include "equation.h"

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
