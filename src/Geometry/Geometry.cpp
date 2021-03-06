#include "../../include/Geometry/Geometry.hpp"
/*
Vector<T> Norme(const Vector<T> &v1, const Vector<T> &v2);
Vector<T> NormeInverse(const Vector<T> &v1, const Vector<T> &v2);
Vector<T> RotatePoint(const Vector<T> &v1, const Vector<T> &v2, float angle);
Vector<T> OnSegment(const Vector<T> &v1, const Vector<T> &v2, float angle);
Vector<T> SegmentsIntersect(const Vector<T> &v1, const Vector<T> &v2, float angle);
Vector<T> LinesIntersect(const Vector<T> &v1, const Vector<T> &v2, float angle);
Vector<T> LinesOrientation(const Vector<T> &v1, const Vector<T> &v2, float angle);

/* Dot product: [Ax Ay].[Bx By] = (Ax)(Bx)+(Ay)(By) = Amag*Bmag*cos(theta) */
// float gmt::Dot(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b) { return vect_a.x * vect_b.x + vect_a.y * vect_b.y; }
// float gmt::Dot(float x1, float y1, float x2, float y2) { return x1 * x2 + y1 * y2; }

/* Perp/Cross Dot product: [Ax Ay].[Bx By] = (Ax)(Bx)-(Ay)(By) = Amag*Bmag*sin(theta) */
/*float gmt::Cross(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b) { return vect_a.x * vect_b.y - vect_a.y * vect_b.x; }
float gmt::Cross(float x1, float y1, float x2, float y2) { return x1 * y2 - y1 * x2; }

sf::Vector2f gmt::Pow(const sf::Vector2f &vect, int power) {
    sf::Vector2f pow = vect;
    for (int i = 0; i < power - 1; i++) {
        pow.x = pow.x * pow.x;
        pow.y = pow.y * pow.y;
    }
    return vect;
}*/

/* Vector length: c^2=a^2+b^2 <=> c = sqrt(a*a+b*b) */
/*float gmt::Length(const sf::Vector2f &vect) { return std::sqrt(Dot(vect, vect)); }
float gmt::Length(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B) { return std::sqrt(Dot(vect_B - vect_A, vect_B - vect_A)); }
float gmt::Length(float x, float y) { return std::sqrt(Dot(x, y, x, y)); }
float gmt::Length(float x1, float y1, float x2, float y2) { return std::sqrt(Dot(x1 - x2, y1 - y2, x1 - x2, y1 - y2)); }
*/
/* Normalize vect = [Ax Ay].(1/size) = [Ax/size Ay/size] */
/*sf::Vector2f gmt::Normalize(const sf::Vector2f &vect) {
    sf::Vector2f temp_vect = {vect.x, vect.y};
    float length = gmt::Length(temp_vect);
    if (length != 0) { temp_vect /= length; }
    return temp_vect;
}*/
/* Return the Norme = [Ay - By, Bx - Ax] */
// sf::Vector2f gmt::Norme(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B) { return sf::Vector2f(vect_A.y - vect_B.y, vect_B.x - vect_A.x); }

/* Return the inverse Norme = [Ay - By, Bx - Ax] */
// sf::Vector2f gmt::inverse_Norme(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B) { return sf::Vector2f(vect_B.y - vect_A.y, vect_A.x - vect_B.x); }

/* Rotate the point A around the point B by the angle in degree */
/*sf::Vector2f gmt::Rotate_Point(sf::Vector2f pA, sf::Vector2f pB, float angle) {
    float theta = degree_to_radian(angle);
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);

    // translate point back to origin:
    sf::Vector2f rotated = pA - pB;
    rotated = {rotated.x * cos_theta - rotated.y * sin_theta, rotated.x * sin_theta - rotated.y * cos_theta};
    rotated += pB;
    return rotated;
}*/

/* Rotate vector: [Ax Ay].scale = [Ax*scale Ay*scale] */
/*void gmt::Rotate(sf::Vector2f &vect, int angle) {
    float theta = degree_to_radian(angle);
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    vect = sf::Vector2f(vect.x * cos_theta - vect.y * sin_theta, vect.x * sin_theta + vect.y * cos_theta);
}*/
/* Scale vector: [Ax Ay].scale = [Ax*scale Ay*scale] */
// void gmt::Scale(sf::Vector2f &vect, float scale) { vect = sf::Vector2f(vect.x * scale, vect.y * scale); }

/* Search if the lines AB and CD intersect */
/*bool gmt::Lines_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const sf::Vector2f &vect_D) {
    float ABx = vect_A.x - vect_B.x;
    float ABy = vect_B.y - vect_A.y;
    float AB = ABy * vect_A.x + ABx * vect_A.y;

    float CDx = vect_C.x - vect_D.x;
    float CDy = vect_D.y - vect_C.y;
    float CD = CDy * vect_C.x + CDx * vect_C.y;

    float det = ABy * CDx - CDy * ABx;

    // Parallel Lines
    if (det == 0) { return false; }
    return true;
}
*/
/* Given the collinears points A,B and C, check if the point C lies on the line segment [AB] */
/*bool gmt::on_segment(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C) {
    if (vect_C.x > std::max(vect_A.x, vect_B.x)) { return false; }
    if (vect_C.x < std::min(vect_A.x, vect_B.x)) { return false; }
    if (vect_C.y > std::max(vect_A.y, vect_B.y)) { return false; }
    if (vect_C.y < std::min(vect_A.y, vect_B.y)) { return false; }

    return true;
}*/

/* Find the orientation of the ordered triplet (A, B, C) */
/*
    return 0 => A,B and C Colinear: [AB] // [BC]
    return 1 => Clockwise Orientation: [BA] => [AC] => [CB]
    return 2 => Counter Clockwise: [AB] => [BC] => [CA]
*/
// int gmt::line_orientation(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C) {
/*
    Using the segments slope:
    - if the two slopes are equals, the segments are colinears
    - if slope[AB] > slope[BC], the orientation is clockwise
    - if slope[AB] < slope[BC], the orientation is counter clockwise
*/
/*   int sigma = static_cast<int>((vect_B.y - vect_A.y) * (vect_C.x - vect_B.x) - (vect_B.x - vect_A.x) * (vect_C.y - vect_B.y));
   if (sigma == 0) { return 0; }
   if (sigma > 0) { return 1; }
   return 2;
}*/

/* Search if the segments AB and CD intersect */
/*bool gmt::Segments_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const sf::Vector2f &vect_D) {
    int orientationA = gmt::line_orientation(vect_A, vect_B, vect_C);
    int orientationB = gmt::line_orientation(vect_A, vect_B, vect_D);
    int orientationC = gmt::line_orientation(vect_C, vect_D, vect_A);
    int orientationD = gmt::line_orientation(vect_C, vect_D, vect_B);

    // General case
    if (orientationA != orientationB && orientationC != orientationD) { return true; }
    if (orientationA == 0 && gmt::on_segment(vect_A, vect_B, vect_C)) { return true; }
    if (orientationB == 0 && gmt::on_segment(vect_A, vect_B, vect_D)) { return true; }
    if (orientationC == 0 && gmt::on_segment(vect_C, vect_D, vect_A)) { return true; }
    if (orientationD == 0 && gmt::on_segment(vect_C, vect_D, vect_B)) { return true; }
    return false;
}*/

/* Project point A onto the line B */
/*sf::Vector2f gmt::Line_Projection(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b) {
    float dp = gmt::Dot(vect_a, vect_b);  // dot product of A and B
    float bd = gmt::Dot(vect_b, vect_b);  // length of B squared
    if (bd == 0) { return sf::Vector2f(); }
    return vect_b * (dp / bd);  // proj = [(dp/bd)*vect_b.x, (dp/bd)*vect_b.y]
}*/

/* Projected point C onto the line AB */
/*sf::Vector2f gmt::Segment_Projection(const sf::Vector2f &vect_a, const sf::Vector2f &vect_b, const sf::Vector2f &vect_c) {
    sf::Vector2f vect_ab = vect_b - vect_a;  // v2
    sf::Vector2f vect_ac = vect_c - vect_a;  // v1

    float dp = Dot(vect_ab, vect_ac);  // dot product of A and B
    float bd = Dot(vect_ab, vect_ab);  // length of B squared
    if (bd == 0) { return sf::Vector2f(); }
    return vect_a + (dp / bd) * vect_ab;  // proj = [(dp/bd)*vect_b.x, (dp/bd)*vect_b.y]
}*/

/* Test if the line segment [AB] intersect with the circle of center C and of radius size. Return true if collide and the collision point */
// std::pair<int, sf::Vector2f> gmt::Line_Circle_Intersect(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C, const float &size) {
// Check if one of the ends of the line segment (side) is inside the circle

// if (gmt::Length(vect_A, vect_C) < size * EDGE_APPROXIMATION) { return {2, sf::Vector2f()}; }
// if (gmt::Length(vect_B, vect_C) < size * EDGE_APPROXIMATION) { return {3, sf::Vector2f()}; }

// Check if the closest point on the line is inside the circle
/*
float side_len = gmt::Length(vect_A, vect_B);
float dot = gmt::Dot(vect_C-vect_A, vect_B-vect_A) / (side_len*side_len);
sf::Vector2f closest = vect_A + dot * (vect_B-vect_A);
*/
/*
 sf::Vector2f closest = gmt::Segment_Projection(vect_A, vect_B, vect_C);

 if (!gmt::on_segment(vect_A, vect_B, closest)) { return {0, sf::Vector2f()}; }
 if (gmt::Length(closest, vect_C) <= size) { return {1, closest}; }

 return {0, sf::Vector2f()};
}*/
/*
gmt::BoundsI gmt::Reorder_Rectangle(gmt::BoundsI rectangle) {
    std::vector<sf::Vector2f> points = {rectangle.pos, rectangle.pos + rectangle.size};
    const auto min_max_x = std::minmax_element(points.begin(), points.end(), [](const sf::Vector2f &lhs, const sf::Vector2f &rhs) { return lhs.x < rhs.x; });
    const auto min_max_y = std::minmax_element(points.begin(), points.end(), [](const sf::Vector2f &lhs, const sf::Vector2f &rhs) { return lhs.y < rhs.y; });

    float min_x = (*min_max_x.first).x;
    float max_x = (*min_max_x.second).x;
    float min_y = (*min_max_y.first).y;
    float max_y = (*min_max_y.second).y;

    return {sf::Vector2f(min_x, min_y), sf::Vector2f(max_x - min_x, max_y - min_y)};
}*/

/* Angle from a line: atan2(y, x) = Arg(x+iy) rad <=> atan2(y, x)*(180/3.1415)= Arg(x+iy) deg */
// float gmt::bearing(float x1, float y1, float x2, float y2) { return atan2(y1 - y2, x1 - x2) * (180 / PI); }

/* Compute the angle formed by 3 points */
/*
float gmt::angle(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B, const sf::Vector2f &vect_C) {
    sf::Vector2f vect_AB = vect_B - vect_A;
    sf::Vector2f vect_CB = vect_B - vect_C;

    return atan2(Cross(vect_AB, vect_CB), Dot(vect_AB, vect_CB)) * (180 / PI);
}*/
/*
bool gmt::rect_in_bounds(const gmt::BoundsI &object, const gmt::BoundsI &limits) {
    // One point in bounds
    // p1 (x,y)
    if (object.pos.x > limits.pos.x && object.pos.x < limits.pos.x + limits.size.x && object.pos.y > limits.pos.y && object.pos.y < limits.pos.y + limits.size.y) { return true; }
    // p2 (x+w,y)
    if (object.pos.x + object.size.x > limits.pos.x && object.pos.x + object.size.x < limits.pos.x + limits.size.x && object.pos.y > limits.pos.y && object.pos.y < limits.pos.y + limits.size.y) { return true; }
    // p3 (x,y+h)
    if (object.pos.x > limits.pos.x && object.pos.x < limits.pos.x + limits.size.x && object.pos.y + object.size.y > limits.pos.y && object.pos.y + object.size.y < limits.pos.y + limits.size.y) { return true; }
    // p4 (x+w,y+h)
    if (object.pos.x + object.size.x > limits.pos.x && object.pos.x + object.size.x < limits.pos.x + limits.size.x && object.pos.y + object.size.y > limits.pos.y && object.pos.y + object.size.y < limits.pos.y + limits.size.y) { return true; }

    return false;
}*/
/*
bool gmt::rect_out_bounds(const gmt::BoundsI &object, const gmt::BoundsI &limits) {
    // One face out bounds
    // f1
    if (object.pos.x < limits.pos.x) { return true; }
    // f2
    if (object.pos.x + object.size.x > limits.pos.x + limits.size.x) { return true; }
    // f3
    if (object.pos.y < limits.pos.y) { return true; }
    // f4
    if (object.pos.y + object.size.y > limits.pos.y + limits.size.y) { return true; }

    return false;
}*/

/* Compute the mirrored point from A to the line B */
// sf::Vector2f gmt::Mirrored_Point(const sf::Vector2f &vect_A, const sf::Vector2f &vect_B) { return 2.0f * gmt::Line_Projection(vect_A, vect_B) - vect_A; }
