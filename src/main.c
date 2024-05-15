#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "inputbox.h"
#include "equation.h"

int
main(void)
{
	InitWindow(1000, 400, "intcalc");
	SetTargetFPS(60);

	struct TextInput equation_box = {
		(Rectangle){0, 0, 300, 50},
		{0},
		false
	};
	
	struct term *head = NULL;

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			focus_unfocus_inputbox(&equation_box);
			free_terms(head);
			head = parse_equation(equation_box.text);

			draw_inputbox(&equation_box);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
