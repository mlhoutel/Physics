#ifndef Functional_HPP
#define Functional_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

#define PI 3.141592654

namespace ftn {

struct Rectangle {
	sf::Vector2f pos;
	sf::Vector2f size;
};

struct Text {
	std::string str = "";
	float x = 0.0f;
	float y = 0.0f;
	float size = 18;
	bool fixed = false;
	sf::Color color = sf::Color::White;
};

float Dot(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b);
float Dot(float x1, float y1, float x2, float y2);

float Perp_Dot(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b);
float Perp_Dot(float x1, float y1, float x2, float y2);

float Length(const sf::Vector2f &vect);
float Length(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B);
float Length(float x, float y);
float Length(float x1, float y1, float x2, float y2);

float degree_to_radian(float degree);
float radian_to_degree(float radian);

sf::Vector2f Normalize(const sf::Vector2f &vect);
sf::Vector2f Norme(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B);
sf::Vector2f inverse_Norme(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B);

void Rotate(sf::Vector2f &vect, int angle);
void Scale(sf::Vector2f &vect, float scale);
bool Lines_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const sf::Vector2f &vect_D);

int line_orientation(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C);
bool on_segment(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C);
bool Segments_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const sf::Vector2f &vect_D);
bool Test_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const sf::Vector2f &vect_D);

sf::Vector2f Line_Projection(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b);
sf::Vector2f Segment_Projection(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b, const sf::Vector2f &vect_c);

sf::Vector2f Centroid(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges);
sf::Vector2f Points_Average(std::vector<sf::Vector2f> points);
std::pair<int, sf::Vector2f> Line_Circle_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const float &size);

std::pair<sf::Vector2f, sf::Vector2f> Closest_Edge(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> sides, sf::Vector2f point);

float digits_comma(float number, int digits);

float bearing(float x1, float y1, float x2, float y2);

bool rect_in_bounds(const ftn::Rectangle &object, const ftn::Rectangle &limits);
bool rect_out_bounds(const ftn::Rectangle &object, const ftn::Rectangle &limits);

template<class C>
std::shared_ptr<C> remove(int i, std::vector<std::shared_ptr<C>> &vect) {
	std::shared_ptr<C> corpse = vect.at(i);
	vect.erase(vect.begin()+i);
	return corpse;
}

template <typename T>
std::string to_string(T value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <typename T>
std::string to_string(std::vector<T> vector) {
	std::ostringstream oss;
	oss << "{";
	if (!vector.empty()) {
		std::copy(vector.begin(), vector.end()-1, std::ostream_iterator<T>(oss, ","));
    	oss << vector.back();
	}
    oss << "}";
	return oss.str();
}

template <typename T>
std::string to_string(sf::Vector2<T> vector) {
	std::ostringstream oss;
	oss << "{" << vector.x << ";" << vector.y << "}";
	return oss.str();
}

template <typename T>
bool decimal_equals(const T& a, const T& b, T epsilon = std::numeric_limits<T>::epsilon()) {
	return fabs(a - b) < epsilon;
}

}
#endif