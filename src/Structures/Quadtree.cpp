#include "../../include/Structures/QuadTree.hpp"

namespace gmt {

/* Vectors Operators: QuadTree=Copy */
QuadTree& QuadTree::operator=(const QuadTree& rhs) { return *this; }

/* Builder Constructor */
QuadTree::QuadTree(const BoundsI& bounds, const int& max_count, const int& max_depth) {
    this->bounds = bounds;
    this->max_count = max_count;
    this->max_depth = max_depth;

    this->root = std::make_unique<QuadNode>();

    std::cout << " bounds: " << gmt::to_string(this->bounds) << " max_count: " << gmt::to_string(this->max_count) << " max_depth: " << gmt::to_string(this->max_depth) << " root: " << gmt::to_string(this->root.get()) << std::endl;
}

QuadTree::QuadTree(const QuadTree& quadtree) {
    this->bounds = quadtree.bounds;
    this->max_count = quadtree.max_count;
    this->max_depth = quadtree.max_depth;

    this->root = std::make_unique<QuadNode>();
}

/* Default Destructor */
// QuadTree::~QuadTree() {}

void QuadTree::SplitNode(QuadNode* node, const BoundsI& bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }
    // if (!node->Leaf()) { throw std::invalid_argument(); }

    // Initialize the children nodes
    for (int i = 0; i < 4; i++) { node->childs[i] = std::make_unique<QuadNode>(); }

    // Assign the corpses to the childs
    std::vector<std::shared_ptr<phy::Corpse>> new_corpses = {};

    for (int i = 0; i < node->corpses.size(); i++) {
        BoundsI corpse_bounds;

        const std::shared_ptr<phy::Corpse> corpse = node->corpses.at(i);

        if (phy::Circle* circle = dynamic_cast<phy::Circle*>(corpse.get())) {
            corpse_bounds = circle->get_corpse_bounds();
        } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(corpse.get())) {
            corpse_bounds = polygon->get_corpse_bounds();
        }

        int index = Quadrant(bounds, corpse_bounds);

        if (index == -1) {
            new_corpses.push_back(corpse);
        } else {
            node->childs[index]->corpses.push_back(corpse);
        }
    }

    node->corpses = std::move(new_corpses);
}

BoundsI QuadTree::NodeBounds(const BoundsI& bounds, int index) const {
    UnitI midx = bounds.x1 + (bounds.x2 - bounds.x1) / UnitI(2);
    UnitI midy = bounds.y1 + (bounds.y2 - bounds.y1) / UnitI(2);
    switch (index) {
        case 0: return BoundsI(bounds.x1, bounds.y1, midx, midy);   // NW
        case 1: return BoundsI(midx, bounds.y1, bounds.x2, midy);   // NE
        case 2: return BoundsI(bounds.x1, midy, +midx, bounds.y2);  // SW
        case 3: return BoundsI(midx, midy, bounds.x2, bounds.y2);   // SE
    }
    throw std::out_of_range("Only 4 Sub-Nodes");
}

int QuadTree::Quadrant(const BoundsI& node_bounds, const BoundsI& corpse_bounds) const {
    UnitI midx = node_bounds.x1 + (node_bounds.x2 - node_bounds.x1) / UnitI(2);
    UnitI midy = node_bounds.y1 + (node_bounds.y2 - node_bounds.y1) / UnitI(2);

    // bool pos_top = corpse_bounds.y1 < midy && corpse_bounds.y2 < midy;
    // bool pos_bot = corpse_bounds.y1 >= midy;
    bool pos_left = corpse_bounds.x1 < midx && corpse_bounds.x2 < midx;
    bool pos_right = corpse_bounds.x1 >= midx;

    int index = -1;  // The corpse intersect with the node bounds

    if (corpse_bounds.y1 < midy && corpse_bounds.y2 < midy) {
        if (pos_left) {
            index = 0;
        } else if (pos_right) {
            index = 1;
        }
    } else if (corpse_bounds.y1 >= midy) {
        if (pos_left) {
            index = 2;
        } else if (pos_right) {
            index = 3;
        }
    }

    return index;
}

void QuadTree::AddCorpse(std::shared_ptr<phy::Corpse> corpse) {
    BoundsI corpse_bounds;

    if (phy::Circle* circle = dynamic_cast<phy::Circle*>(corpse.get())) {
        corpse_bounds = circle->get_corpse_bounds();
    } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(corpse.get())) {
        corpse_bounds = polygon->get_corpse_bounds();
    }

    Add(0, root.get(), bounds, corpse, corpse_bounds);
}

void QuadTree::Add(int depth, QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }
    if (node->Leaf()) {
        if (depth > max_depth) {
            node->corpses.push_back(corpse);  // Can't descend further more
        } else if (node->corpses.size() < max_count) {
            node->corpses.push_back(corpse);  // Still room in the node
        } else {
            SplitNode(node, node_bounds);
            Add(depth, node, node_bounds, corpse, corpse_bounds);
        }
    } else {
        int index = Quadrant(node_bounds, corpse_bounds);
        if (index == -1) {
            node->corpses.push_back(corpse);  // Can't fit the corpse in a sub node
        } else {
            Add(depth + 1, node->childs[index].get(), NodeBounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::Remove(QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }

    if (node->Leaf()) {
        SearchRemove(node, corpse);
    } else {
        int index = Quadrant(node_bounds, corpse_bounds);
        if (index == -1) {
            SearchRemove(node, corpse);
        } else {
            Remove(node->childs[index].get(), NodeBounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::SearchRemove(QuadNode* node, std::shared_ptr<phy::Corpse> corpse) {
    auto it = std::find_if(std::begin(node->corpses), std::end(node->corpses), [this, &corpse](const std::shared_ptr<phy::Corpse>& rhs) { return corpse == rhs; });

    if (it == std::end(node->corpses)) { throw std::out_of_range("Object don't exists in the Node"); }  // trying to repove an object that don't exist in the node

    *it = std::move(node->corpses.back());
    node->corpses.pop_back();
}

void QuadTree::CleanupNode(QuadNode* node) {
    if (!node->Leaf()) {
        int leaf_count = 0;
        for (int i = 0; i < 4; i++) {
            if (node->childs[i]->Leaf()) {
                leaf_count++;
            } else {
                CleanupNode(node->childs[i].get());
            }
        }

        if (leaf_count == 4) { node->childs = {nullptr, nullptr, nullptr, nullptr}; }
    }
}

void QuadTree::ClearNode(QuadNode* node) {
    node->corpses = {};
    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) {
            ClearNode(node->childs[i].get());
            node->childs[i] = nullptr;
        }
    }
}

void QuadTree::FindPairs(QuadNode* node, std::vector<std::pair<std::shared_ptr<phy::Corpse>, std::shared_ptr<phy::Corpse>>>& pairs) const {
    const int corpse_size = node->corpses.size();
    if (corpse_size > 1) {
        for (int a = 0; a < corpse_size; a++) {
            for (int b = a + 1; b < corpse_size; b++) { pairs.push_back({node->corpses.at(a), node->corpses.at(b)}); }
        }
    }

    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) {
            FindPairs(node->childs[i].get(), pairs);                   // Find pairs between the Child corpses
            ChildsPairs(node->corpses, node->childs[i].get(), pairs);  // Find pairs between the Child corpses and this node corpses
        }
    }
}

void QuadTree::FindBounds(QuadNode* node, const BoundsI& node_bounds, std::vector<BoundsI>& bounds) const {
    bounds.push_back(node_bounds);
    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) { FindBounds(node->childs[i].get(), NodeBounds(node_bounds, i), bounds); }
    }
}

void QuadTree::ChildsPairs(const std::vector<std::shared_ptr<phy::Corpse>>& corpses, QuadNode* node, std::vector<std::pair<std::shared_ptr<phy::Corpse>, std::shared_ptr<phy::Corpse>>>& pairs) const {
    const int parent_size = corpses.size();
    const int corpse_size = node->corpses.size();
    if (parent_size > 0 && corpse_size > 0) {
        for (int a = 0; a < parent_size; a++) {
            for (int b = 0; b < corpse_size; b++) { pairs.push_back({corpses.at(a), node->corpses.at(b)}); }
        }
    }
}
void QuadTree::UpdateCorpse(const int& index) {
    // TODO
}

void QuadTree::RemoveCorpse(std::shared_ptr<phy::Corpse> corpse) {
    // TODO
}

void QuadTree::Update() {
    // TODO
}

void QuadTree::Cleanup() { CleanupNode(root.get()); }

void QuadTree::Clear() { ClearNode(root.get()); }

std::vector<std::pair<std::shared_ptr<phy::Corpse>, std::shared_ptr<phy::Corpse>>> QuadTree::ComputePairs() const {
    std::vector<std::pair<std::shared_ptr<phy::Corpse>, std::shared_ptr<phy::Corpse>>> pairs = {};
    FindPairs(root.get(), pairs);
    return pairs;
}

std::vector<BoundsI> QuadTree::ComputeBounds() const {
    std::vector<BoundsI> bounds = {};
    FindBounds(root.get(), this->bounds, bounds);
    return bounds;
}

}  // namespace gmt