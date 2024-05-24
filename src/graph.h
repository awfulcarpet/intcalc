#include "equation.h"
#include "riemann.h"

struct graph {
	Rectangle pos;
	double max_x;
	double min_x;
	double max_y;
	double min_y;
	double step;
};

void draw_graph_lines(struct graph *graph);
void draw_curve(struct graph *graph, struct term *equation);
float draw_and_calc_integral(struct graph *graph, struct term *equation, struct riemann *sum);
void graph_zoom(struct graph *graph);
