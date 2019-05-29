#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>

#include<SFML/Main.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

using namespace std;
using namespace sf;

int main()
{
	bool tab[10][24] = { false };
	bool tab_map[10][24] = { false };
	int tab_r[10][24] = { 255 };
	int tab_g[10][24] = { 255 };
	int tab_b[10][24] = { 255 };

	bool isleft = false;
	bool isup = true;
	bool isright = false;
	bool isdown = false;

	bool flag_drop = false;

	bool flag_over = false;

	string score_string = "0";
	string time_string = "0";

	bool pos_changed = false;

	int figure_id = 0;

	bool new_figure = true;

	int fps_count = 0;
	int step_count = 0;
	int l = 0;
	int k = 0;
	int score = 0;

	int time_s = 0;

	srand(time(NULL));

	RenderWindow window(VideoMode::getDesktopMode(), "Tetris", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorGrabbed(true);

	int res_width = VideoMode::getDesktopMode().width;
	int res_height = VideoMode::getDesktopMode().height;

	RectangleShape board(Vector2f(res_height * 0.95 / 24 * 10, res_height * 0.95));

	RectangleShape board_visible(Vector2f(res_height * 0.95 / 24 * 10 + 1, res_height * 0.95 + 1));
	board_visible.setFillColor(Color::Black);
	board_visible.setOutlineThickness(4);
	board_visible.setOutlineColor(Color::White);

	RectangleShape line(Vector2f(board.getSize().x, 2));
	line.setFillColor(Color::Red);
	line.setOutlineThickness(0);
	
	board.setPosition(res_width * 0.1, res_height * 0.025);
	board_visible.setPosition(res_width * 0.1 - 3, res_height * 0.025 - 2);

	int board_width = board.getSize().x;
	int board_height = board.getSize().y;

	RectangleShape block(Vector2f(board_width * 0.1 - 3, board_width * 0.1 - 3));
	block.setFillColor(Color::Green);
	block.setOutlineColor(Color::Black);
	block.setOutlineThickness(1);

	int offset_x = res_width * 0.1;
	int offset_y = res_height * 0.025;

	Font gothic;
	gothic.loadFromFile("gothic.ttf");

	Text score_txt;
	score_txt.setFont(gothic);
	score_txt.setFillColor(Color::White);
	score_txt.setCharacterSize(20);
	score_txt.setString("Current score - ");
	score_txt.setPosition(window.getSize().x - score_txt.getLocalBounds().width * 1.5, window.getSize().y - score_txt.getLocalBounds().height * 2);
	
	Text score_num_txt;
	score_num_txt.setFont(gothic);
	score_num_txt.setFillColor(Color::White);
	score_num_txt.setCharacterSize(20);

	Text timer;
	timer.setFont(gothic);
	timer.setFillColor(Color::White);
	timer.setCharacterSize(20);
	timer.setString("Time - ");
	timer.setPosition(window.getSize().x - score_txt.getLocalBounds().width * 1.5 + (score_txt.getLocalBounds().width - timer.getLocalBounds().width), window.getSize().y - timer.getLocalBounds().height * 4);

	Text timer_num;
	timer_num.setFont(gothic);
	timer_num.setFillColor(Color::White);
	timer_num.setCharacterSize(20);

	int active_box_1[5], active_box_2[5], active_box_3[5], active_box_4[5];
	int active_box_1_left[2], active_box_2_left[2], active_box_3_left[2], active_box_4_left[2];
	int active_box_1_right[2], active_box_2_right[2], active_box_3_right[2], active_box_4_right[2];
	int active_box_1_down[2], active_box_2_down[2], active_box_3_down[2], active_box_4_down[2];
	int active_box_1_up[2], active_box_2_up[2], active_box_3_up[2], active_box_4_up[2];

	line.setPosition(offset_x, offset_y + 2 * block.getSize().y + 3);

	window.setActive(true);

	while (window.isOpen() == true)
	{

		window.clear(Color::Black);

		window.draw(board_visible);
		window.draw(line);
	
		score_string = to_string(score);
		time_string = to_string(time_s);

		score_num_txt.setString(score_string);
		score_num_txt.setPosition(window.getSize().x - 70, window.getSize().y - 30);

		timer_num.setString(time_string);
		timer_num.setPosition(window.getSize().x - 70, window.getSize().y - 60);

		window.draw(score_txt);
		window.draw(score_num_txt);
		window.draw(timer);
		window.draw(timer_num);

		if (flag_over == true)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 24; j++)
				{
					tab[i][j] = false;
					tab_map[i][j] = false;
					tab_r[i][j] = false;
					tab_g[i][j] = false;
					tab_b[i][j] = false;
					score = 0;
					new_figure = false;
					time_s = 0;
				}
			}
			
			flag_over = false;
		}

		if (new_figure == false)
		{
			tab[active_box_1[0]][active_box_1[1]] = false;
			tab[active_box_2[0]][active_box_2[1]] = false;
			tab[active_box_3[0]][active_box_3[1]] = false;
			tab[active_box_4[0]][active_box_4[1]] = false;
		}
		
		if (pos_changed == true)
		{

			while (active_box_1_up[0] < 0 || active_box_2_up[0] < 0 || active_box_3_up[0] < 0 || active_box_4_up[0] < 0)
			{
				active_box_1_up[0]++;
				active_box_2_up[0]++;
				active_box_3_up[0]++;
				active_box_4_up[0]++;
			}

			while (active_box_1_up[0] > 9 || active_box_2_up[0] > 9 || active_box_3_up[0] > 9 || active_box_4_up[0] > 9)
			{
				active_box_1_up[0]--;
				active_box_2_up[0]--;
				active_box_3_up[0]--;
				active_box_4_up[0]--;
			}

			while (active_box_1_down[0] < 0 || active_box_2_down[0] < 0 || active_box_3_down[0] < 0 || active_box_4_down[0] < 0)
			{
				active_box_1_down[0]++;
				active_box_2_down[0]++;
				active_box_3_down[0]++;
				active_box_4_down[0]++;
			}

			while (active_box_1_down[0] > 9 || active_box_2_down[0] > 9 || active_box_3_down[0] > 9 || active_box_4_down[0] > 9)
			{
				active_box_1_down[0]--;
				active_box_2_down[0]--;
				active_box_3_down[0]--;
				active_box_4_down[0]--;
			}

			while (active_box_1_left[0] < 0 || active_box_2_left[0] < 0 || active_box_3_left[0] < 0 || active_box_4_left[0] < 0)
			{
				active_box_1_left[0]++;
				active_box_2_left[0]++;
				active_box_3_left[0]++;
				active_box_4_left[0]++;
			}

			while (active_box_1_left[0] > 9 || active_box_2_left[0] > 9 || active_box_3_left[0] > 9 || active_box_4_left[0] > 9)
			{
				active_box_1_left[0]--;
				active_box_2_left[0]--;
				active_box_3_left[0]--;
				active_box_4_left[0]--;
			}

			while (active_box_1_right[0] < 0 || active_box_2_right[0] < 0 || active_box_3_right[0] < 0 || active_box_4_right[0] < 0)
			{
				active_box_1_right[0]++;
				active_box_2_right[0]++;
				active_box_3_right[0]++;
				active_box_4_right[0]++;
			}

			while (active_box_1_right[0] > 9 || active_box_2_right[0] > 9 || active_box_3_right[0] > 9 || active_box_4_right[0] > 9)
			{
				active_box_1_right[0]--;
				active_box_2_right[0]--;
				active_box_3_right[0]--;
				active_box_4_right[0]--;
			}

			pos_changed = false;
		}

		if (new_figure == true)
		{
			int which = rand() % 7;

			int rand_r = rand() % 255 + 100;
			int rand_g = rand() % 255 + 100;
			int rand_b = rand() % 255 + 100;

			active_box_1[2] = rand_r;
			active_box_1[3] = rand_g;
			active_box_1[4] = rand_b;

			active_box_2[2] = rand_r;
			active_box_2[3] = rand_g;
			active_box_2[4] = rand_b;

			active_box_3[2] = rand_r;
			active_box_3[3] = rand_g;
			active_box_3[4] = rand_b;

			active_box_4[2] = rand_r;
			active_box_4[3] = rand_g;
			active_box_4[4] = rand_b;

			switch (which)
			{
			case 0:
			{
				// ____

				active_box_1_up[0] = 3;
				active_box_1_up[1] = 0;
				active_box_2_up[0] = 4;
				active_box_2_up[1] = 0;
				active_box_3_up[0] = 5;
				active_box_3_up[1] = 0;
				active_box_4_up[0] = 6;
				active_box_4_up[1] = 0;

				active_box_1_down[0] = 3;
				active_box_1_down[1] = 0;
				active_box_2_down[0] = 4;
				active_box_2_down[1] = 0;
				active_box_3_down[0] = 5;
				active_box_3_down[1] = 0;
				active_box_4_down[0] = 6;
				active_box_4_down[1] = 0;

				active_box_1_left[0] = 4;
				active_box_1_left[1] = 0;
				active_box_2_left[0] = 4;
				active_box_2_left[1] = 1;
				active_box_3_left[0] = 4;
				active_box_3_left[1] = 2;
				active_box_4_left[0] = 4;
				active_box_4_left[1] = 3;

				active_box_1_right[0] = 4;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 4;
				active_box_2_right[1] = 1;
				active_box_3_right[0] = 4;
				active_box_3_right[1] = 2;
				active_box_4_right[0] = 4;
				active_box_4_right[1] = 3;

				break;
			}
			
			case 1:
			{
				// |__

				active_box_1_up[0] = 4;
				active_box_1_up[1] = 0;
				active_box_2_up[0] = 4;
				active_box_2_up[1] = 1;
				active_box_3_up[0] = 5;
				active_box_3_up[1] = 1;
				active_box_4_up[0] = 6;
				active_box_4_up[1] = 1;

				active_box_1_down[0] = 4;
				active_box_1_down[1] = 0;
				active_box_2_down[0] = 5;
				active_box_2_down[1] = 0;
				active_box_3_down[0] = 6;
				active_box_3_down[1] = 0;
				active_box_4_down[0] = 6;
				active_box_4_down[1] = 1;

				active_box_1_left[0] = 5;
				active_box_1_left[1] = 2;
				active_box_2_left[0] = 6;
				active_box_2_left[1] = 2;
				active_box_3_left[0] = 6;
				active_box_3_left[1] = 1;
				active_box_4_left[0] = 6;
				active_box_4_left[1] = 0;

				active_box_1_right[0] = 5;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 5;
				active_box_2_right[1] = 1;
				active_box_3_right[0] = 5;
				active_box_3_right[1] = 2;
				active_box_4_right[0] = 6;
				active_box_4_right[1] = 0;

				break;
			}

			case 2:
			{
				// __|

				active_box_1_up[0] = 4;
				active_box_1_up[1] = 1;
				active_box_2_up[0] = 5;
				active_box_2_up[1] = 1;
				active_box_3_up[0] = 6;
				active_box_3_up[1] = 1;
				active_box_4_up[0] = 6;
				active_box_4_up[1] = 0;

				active_box_1_down[0] = 4;
				active_box_1_down[1] = 0;
				active_box_2_down[0] = 4;
				active_box_2_down[1] = 1;
				active_box_3_down[0] = 5;
				active_box_3_down[1] = 0;
				active_box_4_down[0] = 6;
				active_box_4_down[1] = 0;

				active_box_1_left[0] = 5;
				active_box_1_left[1] = 0;
				active_box_2_left[0] = 6;
				active_box_2_left[1] = 0;
				active_box_3_left[0] = 6;
				active_box_3_left[1] = 1;
				active_box_4_left[0] = 6;
				active_box_4_left[1] = 2;

				active_box_1_right[0] = 5;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 5;
				active_box_2_right[1] = 1;
				active_box_3_right[0] = 5;
				active_box_3_right[1] = 2;
				active_box_4_right[0] = 6;
				active_box_4_right[1] = 2;

				break;
			}

			case 3:
			{
				// [ ]

				active_box_1_up[0] = 4;
				active_box_1_up[1] = 0;
				active_box_2_up[0] = 5;
				active_box_2_up[1] = 0;
				active_box_3_up[0] = 4;
				active_box_3_up[1] = 1;
				active_box_4_up[0] = 5;
				active_box_4_up[1] = 1;

				active_box_1_down[0] = 4;
				active_box_1_down[1] = 0;
				active_box_2_down[0] = 5;
				active_box_2_down[1] = 0;
				active_box_3_down[0] = 4;
				active_box_3_down[1] = 1;
				active_box_4_down[0] = 5;
				active_box_4_down[1] = 1;

				active_box_1_left[0] = 4;
				active_box_1_left[1] = 0;
				active_box_2_left[0] = 5;
				active_box_2_left[1] = 0;
				active_box_3_left[0] = 4;
				active_box_3_left[1] = 1;
				active_box_4_left[0] = 5;
				active_box_4_left[1] = 1;

				active_box_1_right[0] = 4;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 5;
				active_box_2_right[1] = 0;
				active_box_3_right[0] = 4;
				active_box_3_right[1] = 1;
				active_box_4_right[0] = 5;
				active_box_4_right[1] = 1;

				break;
			}

			case 4:
			{
				// S

				active_box_1_up[0] = 4;
				active_box_1_up[1] = 1;
				active_box_2_up[0] = 5;
				active_box_2_up[1] = 1;
				active_box_3_up[0] = 5;
				active_box_3_up[1] = 0;
				active_box_4_up[0] = 6;
				active_box_4_up[1] = 0;

				active_box_1_down[0] = 4;
				active_box_1_down[1] = 1;
				active_box_2_down[0] = 5;
				active_box_2_down[1] = 1;
				active_box_3_down[0] = 5;
				active_box_3_down[1] = 0;
				active_box_4_down[0] = 6;
				active_box_4_down[1] = 0;

				active_box_1_left[0] = 4;
				active_box_1_left[1] = 0;
				active_box_2_left[0] = 4;
				active_box_2_left[1] = 1;
				active_box_3_left[0] = 5;
				active_box_3_left[1] = 1;
				active_box_4_left[0] = 5;
				active_box_4_left[1] = 2;

				active_box_1_right[0] = 4;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 4;
				active_box_2_right[1] = 1;
				active_box_3_right[0] = 5;
				active_box_3_right[1] = 1;
				active_box_4_right[0] = 5;
				active_box_4_right[1] = 2;

				break;
			}

			case 5:
			{
				// _|_

				active_box_1_up[0] = 4;
				active_box_1_up[1] = 1;
				active_box_2_up[0] = 5;
				active_box_2_up[1] = 1;
				active_box_3_up[0] = 6;
				active_box_3_up[1] = 1;
				active_box_4_up[0] = 5;
				active_box_4_up[1] = 0;

				active_box_1_down[0] = 4;
				active_box_1_down[1] = 0;
				active_box_2_down[0] = 5;
				active_box_2_down[1] = 0;
				active_box_3_down[0] = 6;
				active_box_3_down[1] = 0;
				active_box_4_down[0] = 5;
				active_box_4_down[1] = 1;

				active_box_1_left[0] = 5;
				active_box_1_left[1] = 0;
				active_box_2_left[0] = 5;
				active_box_2_left[1] = 1;
				active_box_3_left[0] = 5;
				active_box_3_left[1] = 2;
				active_box_4_left[0] = 4;
				active_box_4_left[1] = 1;

				active_box_1_right[0] = 4;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 4;
				active_box_2_right[1] = 1;
				active_box_3_right[0] = 4;
				active_box_3_right[1] = 2;
				active_box_4_right[0] = 5;
				active_box_4_right[1] = 1;

				break;
			}

			case 6:
			{
				// Z

				active_box_1_up[0] = 4;
				active_box_1_up[1] = 0;
				active_box_2_up[0] = 5;
				active_box_2_up[1] = 0;
				active_box_3_up[0] = 5;
				active_box_3_up[1] = 1;
				active_box_4_up[0] = 6;
				active_box_4_up[1] = 1;

				active_box_1_down[0] = 4;
				active_box_1_down[1] = 0;
				active_box_2_down[0] = 5;
				active_box_2_down[1] = 0;
				active_box_3_down[0] = 5;
				active_box_3_down[1] = 1;
				active_box_4_down[0] = 6;
				active_box_4_down[1] = 1;

				active_box_1_left[0] = 5;
				active_box_1_left[1] = 0;
				active_box_2_left[0] = 5;
				active_box_2_left[1] = 1;
				active_box_3_left[0] = 4;
				active_box_3_left[1] = 1;
				active_box_4_left[0] = 4;
				active_box_4_left[1] = 2;

				active_box_1_right[0] = 5;
				active_box_1_right[1] = 0;
				active_box_2_right[0] = 5;
				active_box_2_right[1] = 1;
				active_box_3_right[0] = 4;
				active_box_3_right[1] = 1;
				active_box_4_right[0] = 4;
				active_box_4_right[1] = 2;

				break;
			}

			}

			figure_id = which;

			new_figure = false;
		}

		fps_count++;

		if (isleft == true)
		{
			if (
				tab_map[active_box_1_left[0]][active_box_1_left[1]] == false &&
				tab_map[active_box_2_left[0]][active_box_2_left[1]] == false &&
				tab_map[active_box_3_left[0]][active_box_3_left[1]] == false &&
				tab_map[active_box_4_left[0]][active_box_4_left[1]] == false
				)
			{
				active_box_1[0] = active_box_1_left[0];
				active_box_1[1] = active_box_1_left[1];
				active_box_2[0] = active_box_2_left[0];
				active_box_2[1] = active_box_2_left[1];
				active_box_3[0] = active_box_3_left[0];
				active_box_3[1] = active_box_3_left[1];
				active_box_4[0] = active_box_4_left[0];
				active_box_4[1] = active_box_4_left[1];
			}
		}

		if (isright == true)
		{
			if (
				tab_map[active_box_1_right[0]][active_box_1_right[1]] == false &&
				tab_map[active_box_2_right[0]][active_box_2_right[1]] == false &&
				tab_map[active_box_3_right[0]][active_box_3_right[1]] == false &&
				tab_map[active_box_4_right[0]][active_box_4_right[1]] == false
				)
			{
				active_box_1[0] = active_box_1_right[0];
				active_box_1[1] = active_box_1_right[1];
				active_box_2[0] = active_box_2_right[0];
				active_box_2[1] = active_box_2_right[1];
				active_box_3[0] = active_box_3_right[0];
				active_box_3[1] = active_box_3_right[1];
				active_box_4[0] = active_box_4_right[0];
				active_box_4[1] = active_box_4_right[1];
			}
		}

		if (isdown == true)
		{
			if (
				tab_map[active_box_1_down[0]][active_box_1_down[1]] == false &&
				tab_map[active_box_2_down[0]][active_box_2_down[1]] == false &&
				tab_map[active_box_3_down[0]][active_box_3_down[1]] == false &&
				tab_map[active_box_4_down[0]][active_box_4_down[1]] == false
				)
			{
				active_box_1[0] = active_box_1_down[0];
				active_box_1[1] = active_box_1_down[1];
				active_box_2[0] = active_box_2_down[0];
				active_box_2[1] = active_box_2_down[1];
				active_box_3[0] = active_box_3_down[0];
				active_box_3[1] = active_box_3_down[1];
				active_box_4[0] = active_box_4_down[0];
				active_box_4[1] = active_box_4_down[1];
			}
		}

		if (isup == true)
		{
			if (
				tab_map[active_box_1_up[0]][active_box_1_up[1]] == false &&
				tab_map[active_box_2_up[0]][active_box_2_up[1]] == false &&
				tab_map[active_box_3_up[0]][active_box_3_up[1]] == false &&
				tab_map[active_box_4_up[0]][active_box_4_up[1]] == false
				)
			{
				active_box_1[0] = active_box_1_up[0];
				active_box_1[1] = active_box_1_up[1];
				active_box_2[0] = active_box_2_up[0];
				active_box_2[1] = active_box_2_up[1];
				active_box_3[0] = active_box_3_up[0];
				active_box_3[1] = active_box_3_up[1];
				active_box_4[0] = active_box_4_up[0];
				active_box_4[1] = active_box_4_up[1];
			}
		}

		if (fps_count == 60)
		{
			fps_count = 0;
			time_s++;
		}

		step_count++;

		if (flag_drop == true)
		{
			step_count = 30;
		}

		if(step_count >= 30)
		{

			step_count = 0;

			tab[active_box_1[0]][active_box_1[1]] = false;
			tab[active_box_2[0]][active_box_2[1]] = false;
			tab[active_box_3[0]][active_box_3[1]] = false;
			tab[active_box_4[0]][active_box_4[1]] = false;

			tab_r[active_box_1[0]][active_box_1[1]] = 0;
			tab_r[active_box_2[0]][active_box_2[1]] = 0;
			tab_r[active_box_3[0]][active_box_3[1]] = 0;
			tab_r[active_box_4[0]][active_box_4[1]] = 0;

			tab_g[active_box_1[0]][active_box_1[1]] = 0;
			tab_g[active_box_2[0]][active_box_2[1]] = 0;
			tab_g[active_box_3[0]][active_box_3[1]] = 0;
			tab_g[active_box_4[0]][active_box_4[1]] = 0;

			tab_b[active_box_1[0]][active_box_1[1]] = 0;
			tab_b[active_box_2[0]][active_box_2[1]] = 0;
			tab_b[active_box_3[0]][active_box_3[1]] = 0;
			tab_b[active_box_4[0]][active_box_4[1]] = 0;

			if (active_box_1[1] != 23 && active_box_2[1] != 23 && active_box_3[1] != 23 && active_box_4[1] != 23)
			{
				active_box_1[1]++;
				active_box_2[1]++;
				active_box_3[1]++;
				active_box_4[1]++;

				active_box_1_up[1]++;
				active_box_2_up[1]++;
				active_box_3_up[1]++;
				active_box_4_up[1]++;

				active_box_1_down[1]++;
				active_box_2_down[1]++;
				active_box_3_down[1]++;
				active_box_4_down[1]++;

				active_box_1_left[1]++;
				active_box_2_left[1]++;
				active_box_3_left[1]++;
				active_box_4_left[1]++;

				active_box_1_right[1]++;
				active_box_2_right[1]++;
				active_box_3_right[1]++;
				active_box_4_right[1]++;
			}

			cout << active_box_1[1] << " " << active_box_1[0] << endl;

		}

		Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::KeyPressed:
				{
					
					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}

					if (flag_drop == false)
					{

						if (Keyboard::isKeyPressed(Keyboard::Q))
						{
							if (isup == true)
							{
								isup = false;
								isleft = true;
							}
							else

								if (isleft == true)
								{
									isleft = false;
									isdown = true;
								}
								else

									if (isdown == true)
									{
										isdown = false;
										isright = true;
									}
									else

										if (isright == true)
										{
											isright = false;
											isup = true;
										}

							pos_changed = true;

						}

						if (Keyboard::isKeyPressed(Keyboard::E))
						{

							if (isup == true)
							{
								isup = false;
								isright = true;
							}
							else

								if (isright == true)
								{
									isright = false;
									isdown = true;
								}
								else

									if (isdown == true)
									{
										isdown = false;
										isleft = true;
									}
									else

										if (isleft == true)
										{
											isleft = false;
											isup = true;
										}

							pos_changed = true;
						}

						if (Keyboard::isKeyPressed(Keyboard::A))
						{

							bool f_left = false;

							if (tab_map[active_box_1[0] - 1][active_box_1[1]] == true || tab_map[active_box_2[0] - 1][active_box_2[1]] == true || tab_map[active_box_3[0] - 1][active_box_3[1]] == true || tab_map[active_box_4[0] - 1][active_box_4[1]] == true)
							{
								f_left = true;
							}

							if ((active_box_1[0] != 0 && active_box_2[0] != 0 && active_box_3[0] != 0 && active_box_4[0] != 0) && f_left == false)
							{
								tab[active_box_1[0]][active_box_1[1]] = false;
								tab[active_box_2[0]][active_box_2[1]] = false;
								tab[active_box_3[0]][active_box_3[1]] = false;
								tab[active_box_4[0]][active_box_4[1]] = false;

								tab_r[active_box_1[0]][active_box_1[1]] = 0;
								tab_r[active_box_2[0]][active_box_2[1]] = 0;
								tab_r[active_box_3[0]][active_box_3[1]] = 0;
								tab_r[active_box_4[0]][active_box_4[1]] = 0;

								tab_g[active_box_1[0]][active_box_1[1]] = 0;
								tab_g[active_box_2[0]][active_box_2[1]] = 0;
								tab_g[active_box_3[0]][active_box_3[1]] = 0;
								tab_g[active_box_4[0]][active_box_4[1]] = 0;

								tab_b[active_box_1[0]][active_box_1[1]] = 0;
								tab_b[active_box_2[0]][active_box_2[1]] = 0;
								tab_b[active_box_3[0]][active_box_3[1]] = 0;
								tab_b[active_box_4[0]][active_box_4[1]] = 0;

								active_box_1[0]--;
								active_box_2[0]--;
								active_box_3[0]--;
								active_box_4[0]--;

								active_box_1_up[0]--;
								active_box_2_up[0]--;
								active_box_3_up[0]--;
								active_box_4_up[0]--;

								active_box_1_down[0]--;
								active_box_2_down[0]--;
								active_box_3_down[0]--;
								active_box_4_down[0]--;

								active_box_1_left[0]--;
								active_box_2_left[0]--;
								active_box_3_left[0]--;
								active_box_4_left[0]--;

								active_box_1_right[0]--;
								active_box_2_right[0]--;
								active_box_3_right[0]--;
								active_box_4_right[0]--;

							}
						}

						if (Keyboard::isKeyPressed(Keyboard::D))
						{
							bool f_right = false;

							if (tab_map[active_box_1[0] + 1][active_box_1[1]] == true || tab_map[active_box_2[0] + 1][active_box_2[1]] == true || tab_map[active_box_3[0] + 1][active_box_3[1]] == true || tab_map[active_box_4[0] + 1][active_box_4[1]] == true)
							{
								f_right = true;
							}

							if ((active_box_1[0] != 9 && active_box_2[0] != 9 && active_box_3[0] != 9 && active_box_4[0] != 9) && f_right == false)
							{

								tab[active_box_1[0]][active_box_1[1]] = false;
								tab[active_box_2[0]][active_box_2[1]] = false;
								tab[active_box_3[0]][active_box_3[1]] = false;
								tab[active_box_4[0]][active_box_4[1]] = false;

								tab_r[active_box_1[0]][active_box_1[1]] = 0;
								tab_r[active_box_2[0]][active_box_2[1]] = 0;
								tab_r[active_box_3[0]][active_box_3[1]] = 0;
								tab_r[active_box_4[0]][active_box_4[1]] = 0;

								tab_g[active_box_1[0]][active_box_1[1]] = 0;
								tab_g[active_box_2[0]][active_box_2[1]] = 0;
								tab_g[active_box_3[0]][active_box_3[1]] = 0;
								tab_g[active_box_4[0]][active_box_4[1]] = 0;

								tab_b[active_box_1[0]][active_box_1[1]] = 0;
								tab_b[active_box_2[0]][active_box_2[1]] = 0;
								tab_b[active_box_3[0]][active_box_3[1]] = 0;
								tab_b[active_box_4[0]][active_box_4[1]] = 0;

								active_box_1[0]++;
								active_box_2[0]++;
								active_box_3[0]++;
								active_box_4[0]++;

								active_box_1_up[0]++;
								active_box_2_up[0]++;
								active_box_3_up[0]++;
								active_box_4_up[0]++;

								active_box_1_down[0]++;
								active_box_2_down[0]++;
								active_box_3_down[0]++;
								active_box_4_down[0]++;

								active_box_1_left[0]++;
								active_box_2_left[0]++;
								active_box_3_left[0]++;
								active_box_4_left[0]++;

								active_box_1_right[0]++;
								active_box_2_right[0]++;
								active_box_3_right[0]++;
								active_box_4_right[0]++;
							}
						}

						if (Keyboard::isKeyPressed(Keyboard::S))
						{
							step_count = 30;
						}

						if (Keyboard::isKeyPressed(Keyboard::Space))
						{
							flag_drop = true;
						}

					}

					break;
				}
			}
		}

		bool f_below = false;

		if (tab_map[active_box_1[0]][active_box_1[1] + 1] == true || tab_map[active_box_2[0]][active_box_2[1] + 1] == true || tab_map[active_box_3[0]][active_box_3[1] + 1] == true || tab_map[active_box_4[0]][active_box_4[1] + 1] == true)
		{
			f_below = true;
		}

		bool f_ground = false;

		if (active_box_1[1] == 23 || active_box_2[1] == 23 || active_box_3[1] == 23 || active_box_4[1] == 23)
		{
			f_ground = true;
		}

		if (f_ground == true || f_below == true)
		{

			tab[active_box_1[0]][active_box_1[1]] = true;
			tab[active_box_2[0]][active_box_2[1]] = true;
			tab[active_box_3[0]][active_box_3[1]] = true;
			tab[active_box_4[0]][active_box_4[1]] = true;

			tab_map[active_box_1[0]][active_box_1[1]] = true;
			tab_map[active_box_2[0]][active_box_2[1]] = true;
			tab_map[active_box_3[0]][active_box_3[1]] = true;
			tab_map[active_box_4[0]][active_box_4[1]] = true;

			tab_r[active_box_1[0]][active_box_1[1]] = active_box_1[2];
			tab_r[active_box_2[0]][active_box_2[1]] = active_box_2[2];
			tab_r[active_box_3[0]][active_box_3[1]] = active_box_3[2];
			tab_r[active_box_4[0]][active_box_4[1]] = active_box_4[2];

			tab_g[active_box_1[0]][active_box_1[1]] = active_box_1[3];
			tab_g[active_box_2[0]][active_box_2[1]] = active_box_2[3];
			tab_g[active_box_3[0]][active_box_3[1]] = active_box_3[3];
			tab_g[active_box_4[0]][active_box_4[1]] = active_box_4[3];

			tab_b[active_box_1[0]][active_box_1[1]] = active_box_1[4];
			tab_b[active_box_2[0]][active_box_2[1]] = active_box_2[4];
			tab_b[active_box_3[0]][active_box_3[1]] = active_box_3[4];
			tab_b[active_box_4[0]][active_box_4[1]] = active_box_4[4];

			new_figure = true;
			flag_drop = false;

			isup = true;
			isdown = false;
			isleft = false;
			isright = false;

			score += 10;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 24; j++)
				{
					if (j < 2)
					{
						if (tab[i][j] == true)
						{
							flag_over = true;
						}
					}
				}
			}	
		}

		tab[active_box_1[0]][active_box_1[1]] = true;
		tab[active_box_2[0]][active_box_2[1]] = true;
		tab[active_box_3[0]][active_box_3[1]] = true;
		tab[active_box_4[0]][active_box_4[1]] = true;

		tab_r[active_box_1[0]][active_box_1[1]] = active_box_1[2];
		tab_r[active_box_2[0]][active_box_2[1]] = active_box_2[2];
		tab_r[active_box_3[0]][active_box_3[1]] = active_box_3[2];
		tab_r[active_box_4[0]][active_box_4[1]] = active_box_4[2];

		tab_g[active_box_1[0]][active_box_1[1]] = active_box_1[3];
		tab_g[active_box_2[0]][active_box_2[1]] = active_box_2[3];
		tab_g[active_box_3[0]][active_box_3[1]] = active_box_3[3];
		tab_g[active_box_4[0]][active_box_4[1]] = active_box_4[3];

		tab_b[active_box_1[0]][active_box_1[1]] = active_box_1[4];
		tab_b[active_box_2[0]][active_box_2[1]] = active_box_2[4];
		tab_b[active_box_3[0]][active_box_3[1]] = active_box_3[4];
		tab_b[active_box_4[0]][active_box_4[1]] = active_box_4[4];

		for (int j = 0; j < 24; j++)
		{
			int line = 0;

			for (int i = 0; i < 10; i++)
			{
				if (tab_map[i][j] == true)
				{
					line++;

					if (line == 10)
					{
						score += 100;

						for (int k = 0; k < 10; k++)
						{
							tab[k][j] = false;
							tab_map[k][j] = false;
						}

						for (int l = j; l > 0; l--)
						{
							for (int k = 0; k < 10; k++)
							{
								if (tab[k][l] == true)
								{
									tab[k][l + 1] = true;
									tab[k][l] = false;

									tab_map[k][l + 1] = true;
									tab_map[k][l] = false;
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				if (tab_map[i][j] == true || tab[i][j] == true)
				{
					block.setFillColor(Color(tab_r[i][j], tab_g[i][j], tab_b[i][j], 255));
					block.setPosition(offset_x + i * (board_width * 0.1), offset_y + j * (board_width * 0.1));
					window.draw(block);
				}
			}
		}

		window.display();

	}

	return 0;
}