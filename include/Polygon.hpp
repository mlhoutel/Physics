#ifndef Polygon_HPP
#define Polygon_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../include/Corpse.hpp"
#include "../include/Circle.hpp"

namespace phy {

const static int ID_POLYGON = 3;

class Polygon : public Corpse
{
private:
	int points_number;
	std::vector<std::shared_ptr<sf::Vector2f>> points;

public:
	Polygon(float x = 0.0f, float y = 0.0f, float size = 1.0f, float mass = 1.0f, float damping = 1.0f, float speed_x = 0.0f, float speed_y = 0.0f, bool fixed = false, bool etherial = false, sf::Color color = sf::Color::White);
	virtual ~Polygon();

	const int get_class();

	void Step();
	void Stop();
	void Move(float x, float y);
	void Move(sf::Vector2f move);
	bool inBounds(float x1, float x2, float y1, float y2);
	bool Pointed(float x, float y);

	void Collision(std::shared_ptr<Corpse> a);

	std::vector<std::shared_ptr<sf::Vector2f>> get_points();
	void set_points(std::vector<std::shared_ptr<sf::Vector2f>> points);

	void add_point(int i);
	void remove_point(int i);

	void compute_center(); // position = average of all points

	vtr::Rectangle get_corpse_bounds();
};

}

#endif