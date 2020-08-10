#ifndef System_HPP
#define System_HPP

#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>

#include "../include/Corpse.hpp"
#include "../include/Circle.hpp"
#include "../include/Polygon.hpp"
#include "../include/Quadtree.hpp"
#include "../include/Functional.hpp"

namespace phy {

#define LS 100 // 2,998 * 10e+8
#define G 10 //6.7 * 10e-11

#define AROUND_QUADTREE 1000

class System
{
private:
	std::vector<Circle> circles;
	std::vector<Polygon> polygons;

	int corpses_size;
	int pairs_size;
	std::vector<std::shared_ptr<Corpse>> corpses;
	std::vector<std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>>> pairs;
	std::vector<std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>>> quad_pairs;

	Quadtree quadtree;

	float force_x;
	float force_y;
	bool gravity;

	int dt;

	ftn::Rectangle limits;

public:
	System(bool gravity = false, float force_x = 0.0f, float force_y = 0.0f, float limit_x = 4000.0f, float limit_y = 4000.0f); // System Constructor
	virtual ~System(); // System Destructor

	void Prepare();

	void Step();
	void CheckLimits();
	void CorpsesStep();
	void CorpseStop(int i);
	void PairsStep();

	void Collision(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b);
	void Forces(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b);

	void InitQuadtree();
	void StepQuadtree();
	std::shared_ptr<Quadtree> get_quadtree();

	int get_dt();
	void set_dt(int dt);
	void add_dt(int dt);

	float get_force_x();
	void set_force_x(float force_x);

	float get_force_y();
	void set_force_y(float force_y);

	bool get_gravity();
	void set_gravity(bool gravity);

	int get_corpses_size();
	int get_pairs_size();
	int get_quad_pairs_size();

	void addCorpse(Polygon a);
	void addCorpse(Circle a);

	void add_corpse(std::shared_ptr<Corpse> a);
	void add_pair(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b);

	ftn::Rectangle get_limits();

	std::vector<std::shared_ptr<Corpse>> get_corpses();
	std::shared_ptr<Corpse> get_corpse(int index);

	std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>> get_quad_pair(int index);

	std::vector<std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>>> get_pairs();
	std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>> get_pair(int index);
	std::shared_ptr<Corpse> get_pair_A(int index);
	std::shared_ptr<Corpse> get_pair_B(int index);
};

}

#endif