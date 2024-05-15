#include <raylib.h>
#include "graph.h"

void
draw_graph_lines(struct graph *graph)
{
	DrawRectangleRec(graph->pos, WHITE);

	int steps_x = (float)(graph->max_x - graph->min_x) / graph->step;
	int stepsize_x = graph->pos.width / steps_x;

	for (int i = 0; i < steps_x; i++) {
		DrawLine(graph->pos.x + i * stepsize_x, graph->pos.y,
				graph->pos.x + i * stepsize_x, 
				graph->pos.y + graph->pos.height,
				BLACK);
	}

	int steps_y = (float)(graph->max_y - graph->min_y) / graph->step;
	int stepsize_y = graph->pos.height / steps_y;

	for (int i = 0; i < steps_y; i++) {
		DrawLine(graph->pos.x, graph->pos.y + i * stepsize_y,
				graph->pos.x + graph->pos.width,
				graph->pos.y + i * stepsize_y,
				BLACK);
	}
}
