#define MAX_INPUT_TEXT_LEN 100

struct TextInput {
	Rectangle pos;
	char text[MAX_INPUT_TEXT_LEN + 1];
	bool editing;
};
void draw_inputbox(struct TextInput *text_input);
