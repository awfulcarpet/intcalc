#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "inputbox.h"
#include "equation.h"
#include "riemann.h"
#include "graph.h"

int
main(void)
{
	const int ScreenWidth = 1000;
	const int ScreenHeight = 400;
	char *equation = "-x^3";
	struct Token *tokens = tokenize_equation(equation);
	printf("\n");
	print_tokens(tokens);
	printf("%f\n", calculate(tokens, 2));
	/*InitWindow(ScreenWidth, ScreenHeight, "intcalc");*/
	/*SetTargetFPS(60);*/
	/**/
	/*struct TextInput equation_box = {*/
	/*	(Rectangle){0, 0, 300, 50},*/
	/*	{0},*/
	/*	false*/
	/*};*/
	/**/
	/*struct TextInput a_box = {*/
	/*	(Rectangle){0, 50, 300, 50},*/
	/*	{[0] = '0', 0},*/
	/*	false*/
	/*};*/
	/*struct TextInput b_box = {*/
	/*	(Rectangle){0, 100, 300, 50},*/
	/*	{[0] = '0', 0},*/
	/*	false*/
	/*};*/
	/*struct TextInput n_box = {*/
	/*	(Rectangle){0, 150, 300, 50},*/
	/*	{'1', '0', '0', '0', '0', 0},*/
	/*	false*/
	/*};*/
	/**/
	/*struct TextInput area_box = {*/
	/*	(Rectangle){0, 200, 300, 50},*/
	/*	{'A', 'r', 'e', 'a', ':', ' ', 0},*/
	/*	false*/
	/*};*/
	/**/
	/*struct graph graph = {*/
	/*	(Rectangle){*/
	/*		equation_box.pos.x + equation_box.pos.width,*/
	/*		0,*/
	/*		1000 - (equation_box.pos.x + equation_box.pos.width),*/
	/*		400,*/
	/*	},*/
	/*	3,*/
	/*	-3,*/
	/*	3,*/
	/*	-3,*/
	/*	0.001*/
	/*};*/
	/**/
	/*struct riemann sum = {0};*/
	/*struct Token *tokens = NULL;*/
	/**/
	/*while (!WindowShouldClose()) {*/
	/*	BeginDrawing();*/
	/*		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));*/
	/*		free_tokens(tokens);*/
	/*		tokens = tokenize_equation(equation_box.text);*/
	/**/
	/*		sum.a = atof(a_box.text);*/
	/*		sum.b = atof(b_box.text);*/
	/*		sum.n = atof(n_box.text);*/
	/**/
	/*		graph_zoom(&graph);*/
	/**/
	/**/
	/*		draw_graph_lines(&graph);*/
	/*		draw_curve(&graph, tokens);*/
	/*		draw_and_calc_integral(&graph, tokens, &sum);*/
	/**/
	/*		draw_inputbox(&equation_box);*/
	/*		draw_inputbox(&a_box);*/
	/*		draw_inputbox(&b_box);*/
	/*		draw_inputbox(&n_box);*/
	/*		draw_inputbox(&area_box);*/
	/*		sprintf(area_box.text, "Area: %.4f", sum.sum);*/
	/*	EndDrawing();*/
	/*}*/
	/**/
	/*CloseWindow();*/
	/*return 0;*/
}
