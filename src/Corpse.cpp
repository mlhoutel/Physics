#include "../include/Corpse.hpp"

namespace phy {

Corpse::Corpse(float x, float y, float mass, float damping, bool fixed, bool tied, bool etherial, sf::Color color) {
    static int global_corpse_id = 0;
    this->id = global_corpse_id++;

    this->fixed = fixed;
    this->tied = tied;
    this->etherial = etherial;
    this->removed = false;
    this->current_pos = sf::Vector2f(x, y);

    this->current_rotation = 0.0f;
    this->mass = mass;
    this->friction = 1.0f;

    this->color = color;
    set_damping(damping);
}

Corpse::~Corpse() = default;

int Corpse::get_id() const { return this->id; }
int Corpse::get_class() const { return ID_CORPSE; }

bool Corpse::get_fixed() const { return this->fixed; }
void Corpse::set_fixed(bool fixed) { this->fixed = fixed; }

bool Corpse::get_etherial() const { return this->etherial; }
void Corpse::set_etherial(bool etherial) { this->etherial = etherial; }

bool Corpse::get_tied() const { return this->tied; }
void Corpse::set_tied(bool tied) { this->tied = tied; }

bool Corpse::get_removed() const { return this->removed; }
void Corpse::Remove() { this->removed = true; }

void Corpse::Step() {}
void Corpse::Stop() {}
void Corpse::Move(float x, float y, bool relative) {}
void Corpse::Move(sf::Vector2f move, bool relative) {}
void Corpse::Collision(std::shared_ptr<Corpse> a) {}

void Corpse::CollisionResponse(phy::Corpse* corpse_a, phy::Corpse* corpse_b, const sf::Vector2f& vect_force) {
    float damping = (corpse_a->get_bounce() + corpse_b->get_bounce()) * 0.5f;  // Damping is evenly distributed among the corpses

    /*
        TEMP: TODO
        - recompute the damping with the proper forces applied
        - push the corpse out of the other shape with the normal vector and the force passed by parameter (vect_force)
            => BUT DON'T CHANCE THE VELOCITY (how to do? last pos?)
        - Then apply the vector (2m2v¯2 + (m1 −m2)v¯1)/(2m2v¯2 + (m1 −m2)v¯1)

    */
    // Test if the collision is asymetric (Fixed/Not Fixed) / or if the two corpses are Fixed
    if (corpse_a->get_fixed() || corpse_b->get_fixed()) {
        if (!corpse_a->get_fixed()) {
            // corpse_a is Not Fixed and corpse_b is Fixed:
            // sf::Vector2f temp_pos = corpse_a->get_last_pos();

            // corpse_a->set_last_pos(corpse_a->get_pos());
            corpse_a->Move(vect_force);
            // corpse_a->Move(ftn::Mirrored_Point(temp_pos - corpse_a->get_pos(), vect_force) * damping);

        } else if (!corpse_b->get_fixed()) {
            // corpse_a is Fixed and corpse_b is Not Fixed:
            // sf::Vector2f temp_pos = corpse_b->get_last_pos();

            // corpse_b->set_last_pos(corpse_b->get_pos());
            corpse_b->Move(-vect_force);
            // corpse_b->Move(ftn::Mirrored_Point(temp_pos - corpse_b->get_pos(), vect_force) * damping);
        } else {
            // Both corpse_a and corpse_b are Fixed:
            // corpse_a->Move(force*0.5f);
            // corpse_b->Move(-force*0.5f);
        }
    } else {
        // Both corpse_a and corpse_b are Not Fixed:
        float normal_mass = corpse_a->get_mass() + corpse_b->get_mass();
        float normal_mass_corpse_a = corpse_a->get_mass() / normal_mass;
        float normal_mass_corpse_b = corpse_b->get_mass() / normal_mass;

        // sf::Vector2f temp_pos_a = corpse_a->get_last_pos();
        // sf::Vector2f temp_pos_b = corpse_b->get_last_pos();

        // corpse_a->set_last_pos(corpse_a->get_pos());
        // corpse_b->set_last_pos(corpse_b->get_pos());

        corpse_a->Move(vect_force * normal_mass_corpse_b * 0.5f);
        corpse_b->Move(-vect_force * normal_mass_corpse_a * 0.5f);

        // corpse_a->Move(ftn::Mirrored_Point(temp_pos_a - corpse_a->get_pos(), vect_force) * damping);
        // corpse_b->Move(ftn::Mirrored_Point(temp_pos_b - corpse_b->get_pos(), vect_force) * damping);
    }
}

sf::Color Corpse::get_color() const { return this->color; }
void Corpse::set_color(sf::Color color) { this->color = color; }

sf::Vector2f Corpse::get_pos() const { return this->current_pos; }
float Corpse::get_pos_x() const { return this->current_pos.x; }
float Corpse::get_pos_y() const { return this->current_pos.y; }

void Corpse::set_pos(sf::Vector2f pos) { this->current_pos = pos; }
void Corpse::set_pos_x(float pos_x) { this->current_pos.x = pos_x; }
void Corpse::set_pos_y(float pos_y) { this->current_pos.y = pos_y; }

sf::Vector2f Corpse::get_last_pos() const { return this->last_pos; }
float Corpse::get_last_pos_x() const { return this->last_pos.x; }
float Corpse::get_last_pos_y() const { return this->last_pos.y; }

void Corpse::set_last_pos(sf::Vector2f pos) { this->last_pos = pos; }
void Corpse::set_last_pos_x(float pos_x) { this->last_pos.x = pos_x; }
void Corpse::set_last_pos_y(float pos_y) { this->last_pos.y = pos_y; }

sf::Vector2f Corpse::get_diff_pos() const { return (this->get_pos() - this->get_last_pos()); }
float Corpse::get_diff_pos_x() const { return (this->get_pos_x() - this->get_last_pos_x()); }
float Corpse::get_diff_pos_y() const { return (this->get_pos_y() - this->get_last_pos_y()); }

float Corpse::get_current_rotation() const { return this->current_rotation; }
void Corpse::set_current_rotation(float current_rotation) { this->current_rotation = current_rotation; }
float Corpse::get_last_rotation() const { return this->last_rotation; }
void Corpse::set_last_rotation(float last_rotation) { this->last_rotation = last_rotation; }
float Corpse::get_motor_rotation() const { return this->motor_rotation; }
void Corpse::set_motor_rotation(float motor_rotation) { this->motor_rotation = motor_rotation; }

void Corpse::set_damping(float damping) {
    if (damping < 0.1f) {
        this->damping = 0.1f;
    } else {
        this->damping = damping;
    }
}
float Corpse::get_bounce() const { return 1.0f / this->damping; }
float Corpse::get_mass() const { return this->mass; }

bool Corpse::Equals(const Corpse* other) {
    if (this->get_id() != other->get_id()) {
        return false;
    }
    if (this->get_class() != other->get_class()) {
        return false;
    }
    if (this->get_fixed() != other->get_fixed()) {
        return false;
    }
    if (this->get_etherial() != other->get_etherial()) {
        return false;
    }
    return true;
}

inline bool Corpse::operator==(const Corpse* other) { return this->Equals(other); }

}  // namespace phy