//
// Created by Aeomanate on 01.06.2021.
//

#ifndef QUADTREE_BOX_HPP
#define QUADTREE_BOX_HPP

#include <cassert>
#include <memory>
#include <cstring>
#include "Vector.hpp"

template<typename T>
class Box {
  public:
    T left;
    T top;
    T width; // Must be positive
    T height; // Must be positive
    
    explicit Box(T Left = 0, T Top = 0, T Width = 0, T Height = 0)
    : left(Left)
    , top(Top)
    , width(Width)
    , height(Height)
    { }
    
    Box(Vector2<T> const& position, Vector2<T> const& size)
    : left(position.x)
    , top(position.y)
    , width(size.x)
    , height(size.y)
    { }
    
    T getRight() const {
        return left + width;
    }
    
    T getBottom() const {
        return top + height;
    }
    
    Vector2<T> getTopLeft() const {
        return Vector2<T>(left, top);
    }
    
    Vector2<T> getCenter() const {
        return Vector2<T>(left + width / 2, top + height / 2);
    }
    
    Vector2<T> getSize() const {
        return Vector2<T>(width, height);
    }
    
    bool contains(const Box<T>& box) const {
        return left <= box.left && box.getRight() <= getRight() &&
               top <= box.top && box.getBottom() <= getBottom();
    }
    
    bool intersects(const Box<T>& box) const {
        bool outside =
            left >= box.getRight() || getRight() <= box.left ||
            top >= box.getBottom() || getBottom() <= box.top;
        return !outside;
    }
    
    bool operator==(Box<T> const& other) const {
        return memcmp(this, &other, sizeof(Box<T>)) == 0;
    }
    
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
    
    Box quadrantByIndex(int i) const {
        auto origin = getTopLeft();
        auto childSize = getSize() / static_cast<T>(2);
        
        switch (i) {
            case NORTH_WEST: return { origin, childSize };
            case NORTH_EAST: return { origin + Vector2<T>(childSize.x, 0), childSize };
            case SOUTH_WEST: return { origin + Vector2<T>(0, childSize.y), childSize };
            case SOUTH_EAST: return { origin + childSize, childSize };
            
            case NEITHER_ONE_QUADRANT:
                assert(false && "Invalid child index");
                return Box();
            
            default:
                assert(false && "Unexpected child index, logic error");
                return Box();
        }
    }
    
    Quadrants quadrantIndex(Box const& someBox) const {
        auto center = getCenter();
        auto stop = someBox.top;
        auto sbottom = someBox.getBottom();
        auto sright = someBox.getRight();
        auto sleft = someBox.left;
        
        bool is_west = sright < center.x;
        bool is_east = sleft >= center.x;
        bool is_north = sbottom < center.y;
        bool is_south = stop >= center.y;
        
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
    
};

#endif //QUADTREE_BOX_HPP
