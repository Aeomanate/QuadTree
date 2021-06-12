//
// Created by Aeomanate on 01.06.2021.
//

#ifndef QUADTREE_VECTOR_HPP
#define QUADTREE_VECTOR_HPP


template<typename T>
class Vector2 {
  public:
    T x, y;
    
    explicit Vector2<T>(T X = T(), T Y = T())
    : x(X)
    , y(Y)
    { }
    
    Vector2<T>& operator+=(Vector2<T> const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector2<T>& operator/=(T t) {
        x /= t;
        y /= t;
        return *this;
    }
};

template<typename T>
Vector2<T> operator+(Vector2<T> lhs, Vector2<T> const& rhs) {
    lhs += rhs;
    return lhs;
}

template<typename T>
Vector2<T> operator/(Vector2<T> vec, T t) {
    vec /= t;
    return vec;
}


#endif // QUADTREE_VECTOR_HPP
