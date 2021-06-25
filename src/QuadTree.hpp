//
// Created by Aeomanate on 01.06.2021.
//

#ifndef QUADTREE_QUADTREE_HPP
#define QUADTREE_QUADTREE_HPP

#include <memory>
#include <type_traits>
#include <algorithm>
#include "QuadTreeBase.hpp"

template <class T, class Real>
class Node {
  public:
    using Ptr = std::unique_ptr<Node>;
    using ValPtr = std::shared_ptr<ValueInBox<T, Real>>;
    using Box = Box<Real>;
    using Quadrants = typename Box::Quadrants;
    
  public:
    bool isLeaf() const {
        return m_children[0] == nullptr;
    }
    
    static size_t getMaxDepth() {
        return 8;
    }
    
    static size_t getMaxValuesSize() {
        return 16;
    }
    
    void add(std::size_t depth, Box const& node_box, ValPtr const& value) {
        assert(node_box.contains(value->getBox()));
        if (isLeaf()) {
            if(depth >= getMaxDepth() || m_values.size() < getMaxValuesSize()) {
                // Insert the value in this node if possible
                push(value);
            } else {
                // Otherwise, we split and we try again
                split(node_box);
                add(depth, node_box, value);
            }
        } else {
            Quadrants i = node_box.quadrantIndex(value->getBox());
            if(i != Quadrants::NEITHER_ONE_QUADRANT) {
                // Add the value in a child if the value is entirely contained in it
                child(i)->add(depth + 1, node_box.quadrantByIndex(i), value);
            } else {
                // Otherwise, we add the value in the current node
                push(value);
            }
        }
    }
    
    void remove(Box const& node_box, ValPtr const& value, Node* parent = nullptr) {
        assert(node_box.contains(value->getBox()));
        if (isLeaf()) {
            remove(value);
            if (parent) parent->tryMerge();
        }
        else {
            Quadrants i = node_box.quadrantIndex(value->getBox());
            if (i != Quadrants::NEITHER_ONE_QUADRANT) {
                child(i)->remove(node_box.quadrantByIndex(i), value, this);
            }
            else {
                // Remove the value in a child
                // if the value is entirely contained in it
                remove(value);
            }
        }
    }
    
    void query(Box const& node_box, Box const& query_box,
               std::vector<ValPtr>& match_values) {
        assert(query_box.intersects(node_box));
        for (ValPtr& value: m_values) {
            if(query_box.intersects(value->getBox())) {
                match_values.push_back(value);
            }
        }
        
        if(!isLeaf()) {
            for (int i = 0; i != static_cast<int>(m_children.size()); ++i) {
                Box child_box = node_box.quadrantByIndex(i);
                if(query_box.intersects(child_box)) {
                    query(child_box, query_box, match_values);
                }
            }
        }
    }
  
  private:
    Ptr& child(int i) {
        return m_children[static_cast<std::size_t>(i)];
    }
    
    void push(ValPtr const& value) {
        m_values.push_back(value->clone());
    }
    
    void split(Box const& node_box) {
        assert(isLeaf() && "Only leaves can be split");
        // Create m_children
        for (Ptr& child: m_children) {
            child.reset(new Node());
        }
        
        // Redirect m_values to m_children if it entire in m_children
        std::vector<ValPtr> new_this_values;
        for (ValPtr& value: m_values) {
            Quadrants i = node_box.quadrantIndex(value->getBox());
            if(i != Quadrants::NEITHER_ONE_QUADRANT) {
                child(i)->m_values.push_back(std::move(value));
            }
            else {
                new_this_values.push_back(std::move(value));
            }
        }
        m_values = std::move(new_this_values);
    }
    
    void remove(ValPtr const& value) {
        auto found = std::find_if(
            m_values.begin(), m_values.end(),
            [this, &value] (ValPtr const& rhs) {
                return *value == *rhs;
            }
        );
        assert(found != m_values.end() &&
               "Trying to remove a value that is not present in the node");
        
        *found = std::move(m_values.back());
        m_values.pop_back();
    }
    
    void tryMerge() {
        assert(!isLeaf() && "Only interior nodes can be merged");
        size_t count_child_values = m_values.size();
        for (Ptr const& child: m_children) {
            if (!child->isLeaf()) return;
            count_child_values += child->m_values.size();
        }
        
        if (count_child_values <= getMaxValuesSize()) {
            m_values.reserve(count_child_values);
            for (Ptr& child: m_children) {
                for (ValPtr& value: child->m_values) {
                    m_values.push_back(std::move(value));
                }
            }
            
            for (Ptr& child: m_children) {
                child.reset();
            }
        }
    }
  
  private:
    std::array<std::unique_ptr<Node>, 4> m_children;
    std::vector<ValPtr> m_values = { };
};

template<class T, class Real = float>
class QuadTree: public QuadTreeBase<T, Real> {
  private:
    using NodeType = Node<T, Real>;
    using NodePtr = std::unique_ptr<NodeType>;
    using Box = typename QuadTreeBase<T, Real>::Box;
    using ValPtr = typename QuadTreeBase<T, Real>::ValPtr;
    using Quadrants = typename Box::Quadrants;
  
  public:
    explicit QuadTree(Box tree_box)
    : m_tree_box(tree_box)
    , m_root_node(new NodeType())
    { }
    
    void add(ValPtr const& value) override {
        m_root_node->add(0, m_tree_box, value);
    }
    
    void remove(ValPtr const& value) override {
        m_root_node->remove(m_tree_box, value);
    }
    
    std::vector<ValPtr> query(Box const& query_box) {
        std::vector<ValPtr> match_values;
        m_root_node->query(m_tree_box, query_box, match_values);
        return match_values;
    }
  
  private:
    Box m_tree_box;
    NodePtr m_root_node;
};

#endif //QUADTREE_QUADTREE_HPP
