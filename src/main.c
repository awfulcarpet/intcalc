#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "inputbox.h"

int
main(void)
{
	InitWindow(500, 500, "intcalc");
	SetTargetFPS(60);

	struct TextInput equation = {
		(Rectangle){0, 0, 300, 50},
		{0},
		false
	};

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		focus_unfocus_inputbox(&equation);


		draw_inputbox(&equation);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
