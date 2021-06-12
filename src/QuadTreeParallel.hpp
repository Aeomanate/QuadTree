//
// Created by Aeomanate on 12.06.2021.
//

#ifndef QUADTREE_QUADTREEPARALLEL_HPP
#define QUADTREE_QUADTREEPARALLEL_HPP

#include <algorithm>
#include "QuadTreeBase.hpp"

template<typename T, typename Real = float>
class QuadTreeParallel: public QuadTreeBase<T, Real> {
  private:
    using typename QuadTreeBase<T, Real>::Node;
    using typename QuadTreeBase<T, Real>::Quadrants;
    using QuadTreeBase<T, Real>::MAX_VALUES_SIZE;
    using QuadTreeBase<T, Real>::MAX_DEPTH;
    using QuadTreeBase<T, Real>::NEITHER_ONE_QUADRANT;
    using QuadTreeBase<T, Real>::NORTH_WEST;
    using QuadTreeBase<T, Real>::NORTH_EAST;
    using QuadTreeBase<T, Real>::SOUTH_WEST;
    using QuadTreeBase<T, Real>::SOUTH_EAST;
  
  public:
    explicit QuadTreeParallel(
        Box<Real> const& box,
    std::function<Box<Real>(T const&)> get_box,
    std::function<bool(T const&, T const&)> equal = std::equal_to<T>())
    : m_box(box)
    , m_root(new Node())
    , m_get_box(get_box)
    , m_equal(equal)
    { }
    
    void add(T const& value) {
        add(m_root, 0, m_box, value);
    }
    
    void remove(T const& value) {
        std::unique_ptr<Node> null = nullptr;
        remove(m_root, null, m_box, value);
    }
  
  private:
    bool isLeaf(std::unique_ptr<Node> const& node) const {
        return node->children[0] == nullptr;
    }
    
    Box<Real> getQuadrantByIndex(Box<Real> const& box, int i) const {
        auto origin = box.getTopLeft();
        auto childSize = box.getSize() / static_cast<Real>(2);
        
        switch (i) {
            case NORTH_WEST: return { origin, childSize };
            case NORTH_EAST: return { origin + Vector2<Real>(childSize.x, 0), childSize };
            case SOUTH_WEST: return { origin + Vector2<Real>(0, childSize.y), childSize };
            case SOUTH_EAST: return { origin + childSize, childSize };
            
            case NEITHER_ONE_QUADRANT:
                assert(false && "Invalid child index");
                return Box<Real>();
            
            default:
                assert(false && "Unexpected child index, logic error");
                return Box<Real>();
        }
    }
    
    Quadrants getQuadrantIndex(Box<Real> const& nodeBox,
                               Box<Real> const& valueBox) const {
        auto center = nodeBox.getCenter();
        auto top = valueBox.top;
        auto bottom = valueBox.getBottom();
        auto right = valueBox.getRight();
        auto left = valueBox.left;
        
        bool is_west = right < center.x;
        bool is_east = left >= center.x;
        bool is_north = bottom < center.y;
        bool is_south = top >= center.y;
        
        if(is_west) {
            if(is_north) return NORTH_WEST;
            else if(is_south) return SOUTH_WEST;
            else return NEITHER_ONE_QUADRANT;
        }
        
        else if(is_east) {
            if(is_north) return NORTH_EAST;
            else if(is_south) return SOUTH_EAST;
            else return NEITHER_ONE_QUADRANT;
        }
        
        else return NEITHER_ONE_QUADRANT;
    }
    
    void add(std::unique_ptr<Node>& node, std::size_t depth,
             Box<Real> const& box, T const& value) {
        assert(node != nullptr);
        assert(box.contains(m_get_box(value)));
        if (isLeaf(node)) {
            if(depth >= MAX_DEPTH || node->values.size() < MAX_VALUES_SIZE) {
                // Insert the value in this node if possible
                node->values.push_back(value);
            } else {
                // Otherwise, we split and we try again
                split(node, box);
                add(node, depth, box, value);
            }
        } else {
            Quadrants i = getQuadrantIndex(box, m_get_box(value));
            if(i != Quadrants::NEITHER_ONE_QUADRANT) {
                // Add the value in a child if the value is entirely contained in it
                auto& child = node->children[static_cast<std::size_t>(i)];
                add(child, depth + 1, getQuadrantByIndex(box, i), value);
            } else {
                // Otherwise, we add the value in the current node
                node->values.push_back(value);
            }
        }
    }
    
    void split(std::unique_ptr<Node>& node, Box<Real> const& box) {
        assert(node != nullptr);
        assert(isLeaf(node) && "Only leaves can be split");
        // Create children
        for (std::unique_ptr<Node>& child: node->children) {
            child.reset(new Node());
        }
        
        // Redirect values to children if it entire in children
        auto newThisValues = std::vector<T>();
        for (auto const& value: node->values) {
            Quadrants i = getQuadrantIndex(box, m_get_box(value));
            if(i != -1) {
                node->children[static_cast<std::size_t>(i)]->values.push_back(value);
            }
            else {
                newThisValues.push_back(value);
            }
        }
        node->values = std::move(newThisValues);
    }
    
    void remove(std::unique_ptr<Node>& node,
                std::unique_ptr<Node>& parent,
                Box<Real> const& box, T const& value) {
        assert(node != nullptr);
        assert(box.contains(m_get_box(value)));
        if (isLeaf(node)) {
            // Remove the value from node
            removeValue(node, value);
            // Try to merge the parent
            if (parent != nullptr) {
                tryMerge(parent);
            }
        }
        else {
            // Remove the value in a child
            // if the value is entirely contained in it
            auto i = getQuadrantIndex(box, m_get_box(value));
            if (i != -1) {
                auto& child = node->children[static_cast<std::size_t>(i)];
                remove(child, node, getQuadrantByIndex(box, i), value);
            }
            else {
                // Otherwise, we remove the value from the current node
                removeValue(node, value);
            }
        }
    }
    
    void removeValue(std::unique_ptr<Node>& node, const T& value) {
        // Find the value in node->values
        auto found = std::find_if(
            std::begin(node->values), std::end(node->values),
            [this, &value] (T const& rhs) { return m_equal(value, rhs); }
        );
        assert(found != std::end(node->values) &&
               "Trying to remove a value that is not present in the node");
        
        // Swap with the last element and pop back
        *found = std::move(node->values.back());
        node->values.pop_back();
    }
    
    void tryMerge(std::unique_ptr<Node> const& node) {
        assert(node != nullptr);
        assert(!isLeaf(node) && "Only interior nodes can be merged");
        auto count_child_values = node->values.size();
        for (const auto& child: node->children) {
            if (!isLeaf(child)) return;
            count_child_values += child->values.size();
        }
        if (count_child_values <= MAX_VALUES_SIZE) {
            node->values.reserve(count_child_values);
            // Merge the values of all the children
            for (auto const& child: node->children) {
                for (auto const& value: child->values) {
                    node->values.push_back(value);
                }
            }
            
            // Remove the children
            for (auto& child: node->children) {
                child.reset();
            }
        }
    }
    
    std::vector<T> query(const Box<Real>& box) const {
        auto values = std::vector<T>();
        query(m_root, m_box, box, values);
        return values;
    }
    
    void query(std::unique_ptr<Node> const& node,
               Box<Real> const& box, Box<Real> const& queryBox,
               std::vector<T>& values) const {
        assert(node != nullptr);
        assert(queryBox.intersects(box));
        for (const auto& value: node->values) {
            if(queryBox.intersects(m_get_box(value))) {
                values.push_back(value);
            }
        }
        
        if(!isLeaf(node)) {
            for (auto i = std::size_t(0); i != node->children.size(); ++i) {
                auto childBox = getQuadrantByIndex(box, static_cast<int>(i));
                if(queryBox.intersects(childBox)) {
                    query(node->children[i], childBox, queryBox, values);
                }
            }
        }
    }
  
  private:
    Box<Real> m_box;
    std::unique_ptr<Node> m_root;
    std::function<Box<Real>(T const&)> m_get_box;
    std::function<bool(T const&, T const&)> m_equal;
};


#endif // QUADTREE_QUADTREEPARALLEL_HPP
