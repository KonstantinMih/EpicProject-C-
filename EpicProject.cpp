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

	while (window.isOpen())
	{
		while (window.pollEvent(event))\
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{

				switch (event.key.code) {
				case(sf::Keyboard::Escape):
					window.close();
					break;
				case(sf::Keyboard::W):
					player.move_forward();
					break;
				case(sf::Keyboard::S):
					player.move_back();
					break;
				}

			}
		}

		for (size_t i = 0; i != window_x; ++i) {
			double phi = player.angle - player.fov / 2 + (i * player.fov) / window_x;

			for (double t = 0; t < 20; t += .05) {
				double cx = player.x + t * cos(player.angle);
				double cy = player.y + t * sin(player.angle);
				if (my_map(int(cx), int(cy)) != ' ') break;
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}