//
// Created by Aeomanate on 10.06.2021.
//

#ifndef QUADTREE_QUADTREEBASE_HPP
#define QUADTREE_QUADTREEBASE_HPP

#include <memory>
#include <vector>
#include <functional>
#include "Box.hpp"
#include "Vector.hpp"

template<typename T, typename Real>
class QuadTreeBase {
  protected:
    struct Node {
        std::array<std::unique_ptr<Node>, 4> children;
        std::vector<T> values = { };
    };
    
    enum Quadrants {
        // 0 | 1
        // -----
        // 2 | 3
        // Not contained fully in any quadrant
        NEITHER_ONE_QUADRANT = -1,
        NORTH_WEST           = 0,
        NORTH_EAST           = 1,
        SOUTH_WEST           = 2,
        SOUTH_EAST           = 3
    };
  
  public:
    explicit QuadTreeBase(size_t max_values_size = 16, size_t max_depth = 8)
    : MAX_VALUES_SIZE(max_values_size)
    , MAX_DEPTH(max_depth)
    { }
    
    virtual void add(T const& value) = 0;
    
    virtual void remove(const T& value) = 0;
  
  protected:
    virtual bool isLeaf(std::unique_ptr<Node> const& node) const = 0;
    
    virtual Box<Real> getQuadrantByIndex(Box<Real> const& box, int i) const = 0;
    
    virtual Quadrants getQuadrantIndex(Box<Real> const& nodeBox,
                                       Box<Real> const& valueBox) const = 0;
    
    virtual void add(std::unique_ptr<Node>& node, std::size_t depth,
                      Box<Real> const& box, T const& value) = 0;
    
    virtual void split(std::unique_ptr<Node>& node, Box<Real> const& box) = 0;
    
    virtual void remove(std::unique_ptr<Node>& node,
                        std::unique_ptr<Node>& parent,
                        Box<Real> const& box, T const& value) = 0;
    
    virtual void removeValue(std::unique_ptr<Node>& node, const T& value) = 0;
    
    virtual void tryMerge(std::unique_ptr<Node> const& node) = 0;
    
    virtual std::vector<T> query(const Box<Real>& box) const = 0;
    
    virtual void query(std::unique_ptr<Node> const& node,
                       Box<Real> const& box, Box<Real> const& queryBox,
                       std::vector<T>& values) const = 0;
  
  protected:
    const std::size_t MAX_VALUES_SIZE = 16;
    const std::size_t MAX_DEPTH = 8;
};

#endif //QUADTREE_QUADTREEBASE_HPP
