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
	bool tab_next[4][2] = { false };
	bool tab_held[4][2] = { false };
	int tab_r[10][24] = { 255 };
	int tab_g[10][24] = { 255 };
	int tab_b[10][24] = { 255 };

	bool isleft = false;
	bool isup = true;
	bool isright = false;
	bool isdown = false;

	bool flag_drop = false;
	bool flag_force_clean = false;
	bool flag_force_new_figure = false;
	bool flag_over = false;
	bool flag_firstswap = true;

	bool flag_swapping = false;
	bool flag_holding = false;
	bool flag_holding_thisdrop = false;

	bool flag_override_once = false;

	bool flag_center_x = false;
	bool flag_center_y = false;

	bool flag_held_center_x = false;
	bool flag_held_center_y = false;

	int which_held = 0;

	string score_string = "0";
	string time_string = "0";

	bool pos_changed = false;

	int figure_id = 0;

	bool new_figure = true;

	int next_figure = 0;

	int fps_count = 0;
	double step_count = 0;
	double basespeed = 3;
	int speedpercent = 100;
	int speedpercent_color = 0;
	int l = 0;
	int k = 0;
	int score = 0;

	int time_s = 0;

	srand(time(NULL));

	int which = rand() % 7;

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

	int board_width = board.getSize().x;
	int board_height = board.getSize().y;

	int offset_x = res_width * 0.1;
	int offset_y = res_height * 0.025;

	RectangleShape block(Vector2f(board_width * 0.1 - 3, board_width * 0.1 - 3));
	block.setFillColor(Color::Green);
	block.setOutlineColor(Color::Black);
	block.setOutlineThickness(1);

	RectangleShape next_block(Vector2f(board_width * 0.1 - 3, board_width * 0.1 - 3));
	next_block.setFillColor(Color::White);
	next_block.setOutlineColor(Color::Black);
	next_block.setOutlineThickness(1);

	RectangleShape held_block(Vector2f(board_width * 0.1 - 3, board_width * 0.1 - 3));
	held_block.setFillColor(Color::Green);
	held_block.setOutlineColor(Color::Black);
	held_block.setOutlineThickness(1);

	RectangleShape next_board(Vector2f(block.getSize().x * 5, block.getSize().y * 3));
	next_board.setPosition(res_width - next_board.getSize().x - 100 - block.getSize().x * 0.5, res_height - next_board.getSize().y - res_height / 3 - block.getSize().y * 0.5);
	next_board.setOutlineColor(Color::White);
	next_board.setOutlineThickness(1);
	next_board.setFillColor(Color::Black);

	RectangleShape hold_board(Vector2f(block.getSize().x * 5, block.getSize().y * 3));
	hold_board.setPosition(res_width - hold_board.getSize().x - 100 - block.getSize().x * 0.5, res_height - hold_board.getSize().y - res_height / 3 * 1.5 - block.getSize().y * 0.5);
	hold_board.setOutlineColor(Color::White);
	hold_board.setOutlineThickness(1);
	hold_board.setFillColor(Color::Black);

	int next_offset_x = res_width - next_board.getSize().x - 100;
	int next_offset_y = res_height - next_board.getSize().y - res_height / 3;

	int held_offset_x = res_width - hold_board.getSize().x - 100;
	int held_offset_y = res_height - hold_board.getSize().y - res_height / 3 * 1.5;

	RectangleShape line(Vector2f(board.getSize().x, 2));
	line.setFillColor(Color::Red);
	line.setOutlineThickness(0);
	
	board.setPosition(res_width * 0.1, res_height * 0.025);
	board_visible.setPosition(res_width * 0.1 - 3, res_height * 0.025 - 2);

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

	Text next_txt;
	next_txt.setFont(gothic);
	next_txt.setString("Next");
	next_txt.setFillColor(Color::White);
	next_txt.setCharacterSize(20);
	next_txt.setPosition(next_board.getPosition().x, next_board.getPosition().y - 30);

	Text hold_txt;
	hold_txt.setFont(gothic);
	hold_txt.setString("Hold");
	hold_txt.setFillColor(Color::White);
	hold_txt.setCharacterSize(20);
	hold_txt.setPosition(hold_board.getPosition().x, hold_board.getPosition().y - 30);

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

	Text speed_txt;
	speed_txt.setFont(gothic);
	speed_txt.setFillColor(Color::White);
	speed_txt.setCharacterSize(20);
	speed_txt.setString("Speed - ");
	speed_txt.setPosition(res_width - speed_txt.getLocalBounds().width * 2, 15);

	Text speed_num_txt;
	speed_num_txt.setFont(gothic);
	speed_num_txt.setCharacterSize(20);
	speed_num_txt.setPosition(res_width - 80, 15);

	int next_box_1[2] = { 0 }, next_box_2[2] = { 0 }, next_box_3[2] = { 0 }, next_box_4[2] = { 0 };
	int held_box_1[2] = { 0 }, held_box_2[2] = { 0 }, held_box_3[2] = { 0 }, held_box_4[2] = { 0 };

	int active_box_1[5] = { 0 }, active_box_2[5] = { 0 }, active_box_3[5] = { 0 }, active_box_4[5] = { 0 };
	int active_box_1_left[2] = { 0 }, active_box_2_left[2] = { 0 }, active_box_3_left[2] = { 0 }, active_box_4_left[2] = { 0 };
	int active_box_1_right[2] = { 0 }, active_box_2_right[2] = { 0 }, active_box_3_right[2] = { 0 }, active_box_4_right[2] = { 0 };
	int active_box_1_down[2] = { 0 }, active_box_2_down[2] = { 0 }, active_box_3_down[2] = { 0 }, active_box_4_down[2] = { 0 };
	int active_box_1_up[2] = { 0 }, active_box_2_up[2] = { 0 }, active_box_3_up[2] = { 0 }, active_box_4_up[2] = { 0 };

	line.setPosition(offset_x, offset_y + 2 * block.getSize().y + 3);

	next_figure = rand() % 7;

	window.setActive(true);

	while (window.isOpen() == true)
	{
		window.clear(Color::Black);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				tab_next[i][j] = false;
				tab_held[i][j] = false;
			}
		}

		window.draw(board_visible);
		window.draw(line);
		window.draw(next_board);
		window.draw(hold_board);
	
		score_string = to_string(score);
		time_string = to_string(time_s);

		score_num_txt.setString(score_string);
		score_num_txt.setPosition(window.getSize().x - 70, window.getSize().y - 30);

		timer_num.setString(time_string);
		timer_num.setPosition(window.getSize().x - 70, window.getSize().y - 60);

		speedpercent = 100 * (3 + time_s * 0.02) / basespeed;

		speed_num_txt.setString(to_string(speedpercent) + "%");

		speedpercent_color = speedpercent / 1.5 - 75;

		if (speedpercent_color < 0)
		{
			speedpercent_color = 0;
		}

		speed_num_txt.setFillColor(Color(255, 255 - speedpercent_color, 255 - speedpercent_color, 255));

		window.draw(score_txt);
		window.draw(score_num_txt);
		window.draw(timer);
		window.draw(timer_num);
		window.draw(next_txt);
		window.draw(hold_txt);
		window.draw(speed_num_txt);
		window.draw(speed_txt);

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
						step_count = 100;
					}

					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						flag_drop = true;
					}

					if (Keyboard::isKeyPressed(Keyboard::F))
					{
						if (flag_holding_thisdrop == false)
						{
							if (flag_holding == false)
							{
								
								flag_holding = true;
								new_figure = true;
								flag_holding_thisdrop = true;
								flag_force_new_figure = false;

								which_held = which;

								switch (which_held)
								{
								case 0:
								{
									flag_held_center_x = false;
									flag_held_center_y = true;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 2;
									held_box_4[0] = 3;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 1;
									held_box_4[1] = 1;

									break;
								}

								case 1:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 0;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 0;
									held_box_2[1] = 1;
									held_box_3[1] = 1;
									held_box_4[1] = 1;

									break;
								}

								case 2:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 2;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 1;
									held_box_4[1] = 0;

									break;
								}

								case 3:
								{
									flag_held_center_x = false;
									flag_held_center_y = false;

									held_box_1[0] = 1;
									held_box_2[0] = 1;
									held_box_3[0] = 2;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 0;
									held_box_3[1] = 1;
									held_box_4[1] = 0;

									break;
								}

								case 4:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 0;
									held_box_4[1] = 0;

									break;
								}

								case 5:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 0;
									held_box_4[1] = 1;

									break;
								}

								case 6:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 0;
									held_box_2[1] = 0;
									held_box_3[1] = 1;
									held_box_4[1] = 1;

									break;
								}
								}

								tab[active_box_1[0]][active_box_1[1]] = false;
								tab[active_box_2[0]][active_box_2[1]] = false;
								tab[active_box_3[0]][active_box_3[1]] = false;
								tab[active_box_4[0]][active_box_4[1]] = false;

								tab_map[active_box_1[0]][active_box_1[1]] = false;
								tab_map[active_box_2[0]][active_box_2[1]] = false;
								tab_map[active_box_3[0]][active_box_3[1]] = false;
								tab_map[active_box_4[0]][active_box_4[1]] = false;

								flag_force_clean = true;
							}

							if (flag_holding == true)
							{
								new_figure = true;
								flag_swapping = true;
								flag_holding_thisdrop = true;

								int graph_which_held = which;

								switch (graph_which_held)
								{
								case 0:
								{
									flag_held_center_x = false;
									flag_held_center_y = true;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 2;
									held_box_4[0] = 3;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 1;
									held_box_4[1] = 1;

									break;
								}

								case 1:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 0;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 0;
									held_box_2[1] = 1;
									held_box_3[1] = 1;
									held_box_4[1] = 1;

									break;
								}

								case 2:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 2;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 1;
									held_box_4[1] = 0;

									break;
								}

								case 3:
								{
									flag_held_center_x = false;
									flag_held_center_y = false;

									held_box_1[0] = 1;
									held_box_2[0] = 1;
									held_box_3[0] = 2;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 0;
									held_box_3[1] = 1;
									held_box_4[1] = 0;

									break;
								}

								case 4:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 0;
									held_box_4[1] = 0;

									break;
								}

								case 5:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 1;
									held_box_2[1] = 1;
									held_box_3[1] = 0;
									held_box_4[1] = 1;

									break;
								}

								case 6:
								{
									flag_held_center_x = true;
									flag_held_center_y = false;

									held_box_1[0] = 0;
									held_box_2[0] = 1;
									held_box_3[0] = 1;
									held_box_4[0] = 2;

									held_box_1[1] = 0;
									held_box_2[1] = 0;
									held_box_3[1] = 1;
									held_box_4[1] = 1;

									break;
								}
								}

								tab[active_box_1[0]][active_box_1[1]] = false;
								tab[active_box_2[0]][active_box_2[1]] = false;
								tab[active_box_3[0]][active_box_3[1]] = false;
								tab[active_box_4[0]][active_box_4[1]] = false;

								tab_map[active_box_1[0]][active_box_1[1]] = false;
								tab_map[active_box_2[0]][active_box_2[1]] = false;
								tab_map[active_box_3[0]][active_box_3[1]] = false;
								tab_map[active_box_4[0]][active_box_4[1]] = false;

								flag_force_clean = true;
							}
						}
					}
				}

				break;
			}
			}
		}

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
			if (flag_force_new_figure == false)
			{
				if (flag_swapping == false)
				{
					which = next_figure;
					next_figure = rand() % 7;
				}

				if (flag_swapping == true)
				{
					int tmp_held;

					tmp_held = which_held;
					which_held = which;
					which = tmp_held;

					flag_swapping = false;
				}
			}

			if (flag_force_new_figure == true)
			{
				which = next_figure;
				next_figure = rand() % 7;

				flag_force_new_figure = false;
			}

			int rand_r = rand() % 255 + 150;
			int rand_g = rand() % 255 + 150;
			int rand_b = rand() % 255 + 150;

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

			switch (next_figure)
			{
			case 0:
			{
				flag_center_x = false;
				flag_center_y = true;

				next_box_1[0] = 0;
				next_box_2[0] = 1;
				next_box_3[0] = 2;
				next_box_4[0] = 3;

				next_box_1[1] = 1;
				next_box_2[1] = 1;
				next_box_3[1] = 1;
				next_box_4[1] = 1;

				break;
			}

			case 1:
			{
				flag_center_x = true;
				flag_center_y = false;

				next_box_1[0] = 0;
				next_box_2[0] = 0;
				next_box_3[0] = 1;
				next_box_4[0] = 2;

				next_box_1[1] = 0;
				next_box_2[1] = 1;
				next_box_3[1] = 1;
				next_box_4[1] = 1;

				break;
			}

			case 2:
			{
				flag_center_x = true;
				flag_center_y = false;

				next_box_1[0] = 0;
				next_box_2[0] = 1;
				next_box_3[0] = 2;
				next_box_4[0] = 2;

				next_box_1[1] = 1;
				next_box_2[1] = 1;
				next_box_3[1] = 1;
				next_box_4[1] = 0;

				break;
			}

			case 3:
			{
				flag_center_x = false;
				flag_center_y = false;

				next_box_1[0] = 1;
				next_box_2[0] = 1;
				next_box_3[0] = 2;
				next_box_4[0] = 2;

				next_box_1[1] = 1;
				next_box_2[1] = 0;
				next_box_3[1] = 1;
				next_box_4[1] = 0;

				break;
			}

			case 4:
			{
				flag_center_x = true;
				flag_center_y = false;

				next_box_1[0] = 0;
				next_box_2[0] = 1;
				next_box_3[0] = 1;
				next_box_4[0] = 2;

				next_box_1[1] = 1;
				next_box_2[1] = 1;
				next_box_3[1] = 0;
				next_box_4[1] = 0;

				break;
			}

			case 5:
			{
				flag_center_x = true;
				flag_center_y = false;

				next_box_1[0] = 0;
				next_box_2[0] = 1;
				next_box_3[0] = 1;
				next_box_4[0] = 2;

				next_box_1[1] = 1;
				next_box_2[1] = 1;
				next_box_3[1] = 0;
				next_box_4[1] = 1;

				break;
			}

			case 6:
			{
				flag_center_x = true;
				flag_center_y = false;

				next_box_1[0] = 0;
				next_box_2[0] = 1;
				next_box_3[0] = 1;
				next_box_4[0] = 2;

				next_box_1[1] = 0;
				next_box_2[1] = 0;
				next_box_3[1] = 1;
				next_box_4[1] = 1;

				break;
			}

			}

			figure_id = which;

			new_figure = false;
		}

		fps_count++;

		int current_figure = which;

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

		step_count = step_count + 3 + time_s * 0.02;

		if (flag_drop == true)
		{
			step_count = 100;
		}

		if (step_count >= 100)
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
			flag_holding_thisdrop = false;

			isup = true;
			isdown = false;
			isleft = false;
			isright = false;

			score += 10;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 24; j++)
				{
					if (j < 1)
					{
						if (tab[i][j] == true)
						{
							flag_over = true;
						}
					}
				}
			}	
		}

		if (flag_force_clean == false)
		{
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
		}

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

									tab_r[k][l + 1] = tab_r[k][l];
									tab_r[k][l] = 0;

									tab_g[k][l + 1] = tab_g[k][l];
									tab_g[k][l] = 0;

									tab_b[k][l + 1] = tab_b[k][l];
									tab_b[k][l] = 0;
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

		tab_next[next_box_1[0]][next_box_1[1]] = true;
		tab_next[next_box_2[0]][next_box_2[1]] = true;
		tab_next[next_box_3[0]][next_box_3[1]] = true;
		tab_next[next_box_4[0]][next_box_4[1]] = true;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (tab_next[i][j] == true)
				{
					if (flag_center_x == false)
					{
						if (flag_center_y == true)
						{
							next_block.setPosition(next_offset_x + i * (board_width * 0.1) - 5, next_offset_y + j * (board_width * 0.1) - next_block.getSize().y / 2);
						}
						else
						{
							next_block.setPosition(next_offset_x + i * (board_width * 0.1) - 5, next_offset_y + j * (board_width * 0.1));
						}
					}

					if (flag_center_x == true)
					{
						if (flag_center_y == true)
						{
							next_block.setPosition(next_offset_x + i * (board_width * 0.1) + next_block.getSize().x / 2 - 5, next_offset_y + j * (board_width * 0.1) - next_block.getSize().y / 2);
						}
						else
						{
							next_block.setPosition(next_offset_x + i * (board_width * 0.1) + next_block.getSize().x / 2 - 5, next_offset_y + j * (board_width * 0.1));
						}
					}

					window.draw(next_block);
				}
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				tab_held[i][j] = false;
			}
		}

		tab_held[held_box_1[0]][held_box_1[1]] = true;
		tab_held[held_box_2[0]][held_box_2[1]] = true;
		tab_held[held_box_3[0]][held_box_3[1]] = true;
		tab_held[held_box_4[0]][held_box_4[1]] = true;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (tab_held[i][j] == true)
				{
					if (flag_held_center_x == false)
					{
						if (flag_held_center_y == true)
						{
							held_block.setPosition(held_offset_x + i * (board_width * 0.1) - 5, held_offset_y + j * (board_width * 0.1) - next_block.getSize().y / 2);
						}
						else
						{
							held_block.setPosition(held_offset_x + i * (board_width * 0.1) - 5, held_offset_y + j * (board_width * 0.1));
						}
					}

					if (flag_held_center_x == true)
					{
						if (flag_held_center_y == true)
						{
							held_block.setPosition(held_offset_x + i * (board_width * 0.1) + held_block.getSize().x / 2 - 5, held_offset_y + j * (board_width * 0.1) - held_block.getSize().y / 2);
						}
						else
						{
							held_block.setPosition(held_offset_x + i * (board_width * 0.1) + held_block.getSize().x / 2 - 5, held_offset_y + j * (board_width * 0.1));
						}
					}

					if (flag_holding == true)
					{
						window.draw(held_block);
					}
				}
			}
		} 
		
		window.display();

		flag_force_clean = false;

	}

	return 0;
}