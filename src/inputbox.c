#include "raygui.h"

#include "inputbox.h"

void
focus_unfocus_inputbox(struct TextInput *text_input)
{
	if (!IsMouseButtonPressed(0)) {
		return;
	}

	Vector2 mouse_pos = GetMousePosition();

	if (CheckCollisionPointRec(mouse_pos, text_input->pos)) {
		text_input->editing = true;
		return;
	} 

	text_input->editing = false;
}

void
draw_inputbox(struct TextInput *text_input)
{
	GuiTextBox(text_input->pos, text_input->text, MAX_INPUT_TEXT_LEN, text_input->editing);
}
