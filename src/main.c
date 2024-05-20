#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "inputbox.h"
#include "equation.h"
#include "graph.h"

int
main(void)
{
	const int ScreenWidth = 1000;
	const int ScreenHeight = 400;
	InitWindow(ScreenWidth, ScreenHeight, "intcalc");
	SetTargetFPS(60);

	struct TextInput equation_box = {
		(Rectangle){0, 0, 300, 50},
		{0},
		false
	};
	
	struct graph graph = {
		(Rectangle){
			equation_box.pos.x + equation_box.pos.width,
			0,
			1000 - (equation_box.pos.x + equation_box.pos.width),
			400,
		},
		10,
		-10,
		10,
		-10,
		1
	};
	
	struct term *head = NULL;

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			focus_unfocus_inputbox(&equation_box);
			free_terms(head);
			head = parse_equation(equation_box.text);

			draw_inputbox(&equation_box);
			draw_graph_lines(&graph);
		EndDrawing();
	}

	CloseWindow();
	print_terms(head);
	return 0;
}
