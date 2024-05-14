#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_INPUT_TEXT_LEN 100

struct TextInput {
	Rectangle pos;
	char text[MAX_INPUT_TEXT_LEN + 1];
	bool editing;
};

void
focus_unfocus_textbox(struct TextInput *textInput)
{
	if (!IsMouseButtonPressed(0)) {
		return;
	}

	Vector2 mouse_pos = GetMousePosition();

	if (CheckCollisionPointRec(mouse_pos, textInput->pos)) {
		textInput->editing = true;
		return;
	} 

	textInput->editing = false;
}

int
main(void)
{
	InitWindow(500, 500, "intcalc");
	SetTargetFPS(60);

	struct TextInput equation = {
		(Rectangle){0, 0, 300, 50},
		{0},
		true
	};

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		focus_unfocus_textbox(&equation);


		GuiTextBox(equation.pos, equation.text, MAX_INPUT_TEXT_LEN, equation.editing);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
