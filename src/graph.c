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
	double stepsize_x = graph->pos.width / (graph->max_x - graph->min_x);
	double stepsize_y = graph->pos.height / (graph->max_y - graph->min_y);

	for (double i = graph->min_x; i < graph->max_x; i += graph->step) {
		double y = -get_value(equation, i); // pos is down on computer
		DrawPixel(graph->pos.x + graph->pos.width/2.0 + i * stepsize_x,
				graph->pos.y + graph->pos.height/2.0 + y * stepsize_y,
				BLUE);
	}
}

float
draw_and_calc_integral(struct graph *graph, struct term *equation, struct riemann *sum)
{
	if (equation == NULL) {
		return 0;
	}
	sum->sum = 0;
	// right riemann sum
	double width = (sum->b - sum->a) / sum->n;

	double stepsize_x = graph->pos.width / (graph->max_x - graph->min_x);
	double stepsize_y = graph->pos.height / (graph->max_y - graph->min_y);
	double x_axis_y = graph->pos.y + stepsize_y * (graph->max_y - graph->min_y) / 2;
	double y_axis_x = graph->pos.x + stepsize_x * (graph->max_x - graph->min_x) / 2;
	double max_pixel_width = (sum->b - sum->a) * stepsize_x;

	struct Color color = {
		255,
		0,
		0,
		1	
	};

	for (int i = 1; i <= sum->n; i++) {
		float y = get_value(equation, sum->a + width * i);
		sum->sum += y * width; 
		struct Color tint = {
			200,
			0,
			0,
			0.3 * 255
		};

		struct Rectangle rect = {
			y_axis_x + (sum->a + width * (i-1)) * stepsize_x,
			x_axis_y + -y * stepsize_y,
			width * stepsize_x,
			y * stepsize_y,
		};

		DrawRectangleRec(rect, tint);
	}

	return sum->sum;
}

void
graph_zoom(struct graph *graph)
{
	float zoom_diff = -GetMouseWheelMove();
	if (graph->max_x - zoom_diff <= graph->min_x + zoom_diff) {
		return;
	}
	if (graph->max_x - zoom_diff <= graph->min_x + zoom_diff) {
		return;
	}
	graph->max_x += -zoom_diff;
	graph->max_y += -zoom_diff;
	graph->min_x += zoom_diff;
	graph->min_y += zoom_diff;
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
