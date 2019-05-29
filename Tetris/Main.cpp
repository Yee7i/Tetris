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

	bool isleft = false;
	bool isup = true;
	bool isright = false;
	bool isdown = false;

	bool pos_changed = false;

	int figure_id = 0;

	bool new_figure = true;

	int fps_count = 0;
	int step_count = 0;
	int l = 0;
	int k = 0;

	int time_s = 0;

	srand(time(NULL));

	RenderWindow window(VideoMode::getDesktopMode(), "Tetris", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorGrabbed(true);

	int width = VideoMode::getDesktopMode().width;
	int height = VideoMode::getDesktopMode().height;

	RectangleShape board(Vector2f(height * 0.95 / 24 * 10, height * 0.95));

	RectangleShape board_visible(Vector2f(height * 0.95 / 24 * 10 + 1, height * 0.95 + 1));
	board_visible.setFillColor(Color::Black);
	board_visible.setOutlineThickness(4);
	board_visible.setOutlineColor(Color::White);

	board.setPosition(width * 0.1, height * 0.025);
	board_visible.setPosition(width * 0.1 - 3, height * 0.025 - 2);

	int board_width = board.getSize().x;
	int board_height = board.getSize().y;

	RectangleShape block(Vector2f(board_width * 0.1 - 3, board_width * 0.1 - 3));
	block.setFillColor(Color::Green);
	block.setOutlineColor(Color::Black);
	block.setOutlineThickness(1);

	int offset_x = width * 0.1;
	int offset_y = height * 0.025;

	Font gothic;
	gothic.loadFromFile("gothic.ttf");

	int active_box_1[2], active_box_2[2], active_box_3[2], active_box_4[2];
	int active_box_1_left[2], active_box_2_left[2], active_box_3_left[2], active_box_4_left[2];
	int active_box_1_right[2], active_box_2_right[2], active_box_3_right[2], active_box_4_right[2];
	int active_box_1_down[2], active_box_2_down[2], active_box_3_down[2], active_box_4_down[2];
	int active_box_1_up[2], active_box_2_up[2], active_box_3_up[2], active_box_4_up[2];

	window.setActive(true);

	while (window.isOpen() == true)
	{

		window.clear(Color::Black);

		window.draw(board_visible);

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

		if(step_count >= 30)
		{

			step_count = 0;

			tab[active_box_1[0]][active_box_1[1]] = false;
			tab[active_box_2[0]][active_box_2[1]] = false;
			tab[active_box_3[0]][active_box_3[1]] = false;
			tab[active_box_4[0]][active_box_4[1]] = false;

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

					if (Keyboard::isKeyPressed(Keyboard::Q))
					{
						if (isup == true)
						{
							isup = false;
							isleft = true;
						} else

						if (isleft == true)
						{
							isleft = false;
							isdown = true;
						} else

						if (isdown == true)
						{
							isdown = false;
							isright = true;
						} else

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
						} else

						if (isright == true)
						{
							isright = false;
							isdown = true;
						} else

						if (isdown == true)
						{
							isdown = false;
							isleft = true;
						} else

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

			new_figure = true;
			
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
									tab[k][l+1] = true;
									tab[k][l] = false;

									tab_map[k][l+1] = true;
									tab_map[k][l] = false;
								}
							}
						}
					}
				}
			}	
		} 

		tab[active_box_1[0]][active_box_1[1]] = true;
		tab[active_box_2[0]][active_box_2[1]] = true;
		tab[active_box_3[0]][active_box_3[1]] = true;
		tab[active_box_4[0]][active_box_4[1]] = true;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				if (tab[i][j] == true)
				{
					block.setPosition(offset_x + i * (board_width * 0.1), offset_y + j * (board_width * 0.1));
					window.draw(block);
				}
			}
		}

		window.display();

	}

	return 0;
}