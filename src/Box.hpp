//
// Created by Aeomanate on 01.06.2021.
//

#ifndef QUADTREE_BOX_HPP
#define QUADTREE_BOX_HPP

#include <cassert>
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
};

#endif //QUADTREE_BOX_HPP
