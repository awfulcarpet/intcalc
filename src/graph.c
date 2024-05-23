#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "equation.h"


void
draw_curve(struct graph *graph, struct term *equation)
{
	if (equation == NULL) {
		return;
	}
	int stepsize_x = graph->pos.width / (graph->max_x - graph->min_x);
	int stepsize_y = graph->pos.height / (graph->max_y - graph->min_y);

	for (float i = graph->min_x; i < graph->max_x; i += graph->step) {
		float y = -get_value(equation, i); // pos is down on computer
		DrawPixel(graph->pos.x + graph->pos.width/2.0 + i * stepsize_x,
				graph->pos.y + graph->pos.height/2.0 + y * stepsize_y,
				BLUE);
	}
}

void
draw_graph_lines(struct graph *graph)
{
	DrawRectangleRec(graph->pos, WHITE);
	float stepsize_x = graph->pos.width / (graph->max_x - graph->min_x);
	for (int i = 0; i < graph->max_x - graph->min_x; i++) {
		Vector2 start = {
			graph->pos.x + i * stepsize_x,
			graph->pos.y
		};
		Vector2 end = {
				graph->pos.x + i * stepsize_x, 
				graph->pos.y + graph->pos.height,
		};
		DrawLineEx(start, end, 1, GRAY);
		if (graph->min_x + i == 0) {
			DrawLineEx(start, end, 3, BLACK);
		}
	}

	float stepsize_y = graph->pos.height / (graph->max_y - graph->min_y);
	for (int i = 0; i < graph->max_y - graph->min_y; i++) {
		Vector2 start = {
			graph->pos.x,
			graph->pos.y + i * stepsize_y,
		};
		Vector2 end = {
			graph->pos.x + graph->pos.width,
			graph->pos.y + i * stepsize_y, 
		};

		DrawLineEx(start, end, 1, GRAY);
		if (graph->min_y + i == 0) {
			DrawLineEx(start, end, 3, BLACK);
		}
	}
}
