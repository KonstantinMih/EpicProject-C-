#include <SFML/Graphics.hpp>
#include "EpicProject.h"

using namespace std;

int main()
{

	char proto_map[] = "0000222222220000"\
						"1              0"\
						"1      11111   0"\
						"1     0        0"\
						"0     0  1110000"\
						"0     3        0"\
						"0   10000      0"\
						"0   0   11100  0"\
						"0   0   0      0"\
						"0   0   1  00000"\
						"0       1      0"\
						"2       1      0"\
						"0       0      0"\
						"0 0000000      0"\
						"0              0"\
						"0002222222200000";

	Map my_map = Map(16, 16, &proto_map[0]);

	Player player = Player(3.456, 2.345, 1.523);

	size_t const window_x = 512;
	size_t const window_y = 512;

	sf::RenderWindow window(sf::VideoMode(window_x, window_y), "bruh");
	window.setFramerateLimit(60);

	sf::Event event;

	while (window.isOpen())  // Начало процессов
	{
		while (window.pollEvent(event))\
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)   // Кнопочки
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move_forward();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move_back();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.turn_left();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.turn_right();

		}

		window.clear(sf::Color::White);

		short previous_column = SHRT_MIN;

		// начало reycasting'а
		for (unsigned short i = 0; i != window_x; ++i) {    // for по i - номеру луча 
			double phi = player.angle - player.fov / 2 + (i * player.fov) / window_x;

			for (double r = 0; r < 20; r += .05) {  // for по t - расстаянию от игрока

				double wall_x = player.x + r * cos(phi);
				double wall_y = player.y + r * sin(phi);
				if (my_map(int(wall_x), int(wall_y)) != ' ') {
						
					double ray_direction = player.fov * (floor(0.5 * window_x) - i) / (window_x - 1);
					double ray_projection_pos = 0.5 * tan(ray_direction) / tan(0.5 * player.fov);

					short current_column = static_cast<short>(round(window_x * (0.5 - ray_projection_pos)));
					short next_column = window_x;

					if (i < window_x - 1) {
						double next_ray_direction = player.fov * (floor(0.5 * window_x) - 1 - i) / (window_x - 1);

						ray_projection_pos = 0.5 * tan(next_ray_direction) / tan(0.5 * player.fov);

						next_column = static_cast<short>(round(window_x * (0.5 - ray_projection_pos)));
					}

					if (previous_column < current_column) {
						double wall_height = round(window_y / (r * abs(cos(phi - player.angle))));

						sf::RectangleShape rectangle(sf::Vector2f(std::max(1, next_column - current_column), wall_height));
						rectangle.setPosition(current_column, window_y / 2 - wall_height / 2);
						rectangle.setFillColor(sf::Color::Blue);

						previous_column = current_column;

						window.draw(rectangle);
					}


				}
			}
		}

		window.display();
	}

	return 0;
}