//
// Created by Aeomanate on 10.06.2021.
//

#ifndef QUADTREE_QUADTREEBASE_HPP
#define QUADTREE_QUADTREEBASE_HPP

#include <memory>
#include <vector>
#include "Box.hpp"

template <class BaseOfClonableType>
class ClonableBase {
  public:
    using Ptr = std::shared_ptr<BaseOfClonableType>;
    virtual Ptr clone() const = 0;
};


template <class Derived, class BaseOfClonableType>
class ClonableDerived: virtual public ClonableBase<BaseOfClonableType> {
  public:
    using typename ClonableBase<BaseOfClonableType>::Ptr;
    Ptr clone() const override {
        return std::make_shared<Derived>(static_cast<Derived const&>(*this));
    }
};

template <class ValueT, class BoxType = float>
struct ValueInBox: virtual public ClonableBase<ValueInBox<ValueT, BoxType>> {
    using Value = ValueInBox<ValueT, BoxType>;
    using Ptr = std::shared_ptr<Value>;
    using Box = Box<BoxType>;
    
    virtual ~ValueInBox() = default;
    
    virtual Box getBox() const = 0;
    
    virtual ValueT& getValue() = 0;
    
    ValueT const& getValue() const {
        return *const_cast<ValueT const*>(&const_cast<ValueInBox*>(this)->getValue());
    }
    
    bool operator==(ValueInBox const& other) const {
        return getValue() == other.getValue();
    }
};


template<class T, class Real>
class QuadTreeBase {
  public:
    using Value = typename ValueInBox<T, Real>::Value;
    using ValPtr = typename Value::Ptr;
    using Box = typename Value::Box;
    
    virtual void add(ValPtr const& value) = 0;
    
    virtual void remove(ValPtr const& value) = 0;
    
    virtual std::vector<ValPtr> query(Box const& box) = 0;
};

#endif //QUADTREE_QUADTREEBASE_HPP
