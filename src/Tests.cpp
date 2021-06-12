// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 01.06.2021.
//

#include "Tests.hpp"

#include <iostream>
#include <functional>
#include "Box.hpp"

#define protected public
#include "QuadTreeBase.hpp"
#define private public
#include "QuadTree.hpp"
#include "QuadTreeParallel.hpp"
#undef private
#undef protected

void Box_ContainIntersectTest() {
    std::function<void()> boxTests[] = {
        // Contains
        [] {
            // a contains b
            Box<int> a(0, 0, 10, 10);
            Box<int> b(-1, -1, 11, 11);
            assert(a.contains(b) == false);
            assert(b.contains(a) == true);
            assert(a.intersects(b) == true);
            assert(b.intersects(a) == true);
        },
        
        [] {
            // a not intersects with b
            Box<int> a(0, 0, 10, 10);
            Box<int> b(100, 100, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // Intersects and contains each other
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, 0, 10, 10);
            assert(a.contains(b) == true);
            assert(b.contains(a) == true);
            assert(a.intersects(b) == true);
            assert(b.intersects(a) == true);
        },
        
        // Intersects
        
        [] {
            // a intersects b on the right side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(9, 0, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == true);
            assert(b.intersects(a) == true);
        },
        
        [] {
            // a intersects b on the left side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(-9, 0, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == true);
            assert(b.intersects(a) == true);
        },
        
        [] {
            // a intersects b on the top side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, -9, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == true);
            assert(b.intersects(a) == true);
        },
        
        [] {
            // a intersects b on the bottom side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, 9, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == true);
            assert(b.intersects(a) == true);
        },
        
        // Not intersects
        
        [] {
            // a NOT intersects b on the right side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(11, 0, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // a NOT intersects b on the left side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(-11, 0, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // a NOT intersects b on the top side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, -11, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // a NOT intersects b on the bottom side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, 11, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        // BORDERS Not intersects
        
        [] {
            // a NOT intersects b on the right side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(10, 0, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // a NOT intersects b on the left side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(-10, 0, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // a NOT intersects b on the top side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, -10, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        [] {
            // a NOT intersects b on the bottom side
            Box<int> a(0, 0, 10, 10);
            Box<int> b(0, 10, 10, 10);
            assert(a.contains(b) == false);
            assert(b.contains(a) == false);
            assert(a.intersects(b) == false);
            assert(b.intersects(a) == false);
        },
        
        // ---
        
        [] {
            std::cout << "Box work...\n";
        }
    };
    
    for(auto const& test: boxTests) test();
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_CreateTest() {
    using QT = CustomQuadTree<T, Real>;
    QT tree(Box<Real>{}, [] (void*){ return Box<int>(); });
    (void)tree;
    std::cout << "QuadTree creatable...\n";
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_GetQuadrantIndexTest() {
    using QT = CustomQuadTree<T, Real>;
    using Quadrants = typename QT::Quadrants;
    QT quadtree(Box<Real>(0, 0, 0, 0), [] (void*){ return Box<Real>(); });
    Box<Real> parent_box(100, 100, 100, 100);
    
    std::function<void()> tests[] = {
      [&] {
          Box<Real> target_box(1, 1, 10, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NORTH_WEST);
      },
      
      [&] {
          Box<Real> target_box(99, 99, 1, 1);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NORTH_WEST);
      },

      [&] {
          Box<Real> target_box(50, 50, 100, 100);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },
      
      [&] {
          Box<Real> target_box(100, 100, 100, 100);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },
      
      [&] {
          Box<Real> target_box(150, 100, 10, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NORTH_EAST);
      },
      
      [&] {
          Box<Real> target_box(150, 100, 51, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NORTH_EAST);
      },
      
      [&] {
          Box<Real> target_box(100, 100, 100, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },
      
      [&] {
          Box<Real> target_box(100, 150, 10, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::SOUTH_WEST);
      },
      
      [&] {
          Box<Real> target_box(100, 150, 10, 51);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::SOUTH_WEST);
      },

      [&] {
          Box<Real> target_box(100, 150, 51, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },

      [&] {
          Box<Real> target_box(100, 150, 50, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },

      [&] {
          Box<Real> target_box(150, 150, 10, 10);
          Quadrants quadrant = quadtree.getQuadrantIndex(parent_box, target_box);
          assert(quadrant == Quadrants::SOUTH_EAST);
      },
    };
    
    for(auto const& test: tests) test();
    std::cout << "QuadTree indexes of quadrants compute correctly...\n";
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_GetQuadrantByIndexTest() {
    using QT = CustomQuadTree<T, Real>;
    using Quadrants = typename QT::Quadrants;
    QT quadtree(Box<Real>(0, 0, 0, 0), [] (void*){ return Box<Real>(); });
    Box<Real> parent_box(100, 100, 100, 100);
    
    std::function<void()> tests[] = {
        [&] {
            auto box = quadtree.getQuadrantByIndex(parent_box, Quadrants::NORTH_WEST);
            assert(abs(box.top - 100) < 1e-5);
            assert(abs(box.getBottom() - 150) < 1e-5);
            assert(abs(box.left - 100) < 1e-5);
            assert(abs(box.getRight() - 150) < 1e-5);
        },

        [&] {
            auto box = quadtree.getQuadrantByIndex(parent_box, Quadrants::NORTH_EAST);
            assert(abs(box.top - 100) < 1e-5);
            assert(abs(box.getBottom() - 150) < 1e-5);
            assert(abs(box.left - 150) < 1e-5);
            assert(abs(box.getRight() - 200) < 1e-5);
        },

        [&] {
            auto box = quadtree.getQuadrantByIndex(parent_box, Quadrants::SOUTH_WEST);
            assert(abs(box.top - 150) < 1e-5);
            assert(abs(box.getBottom() - 200) < 1e-5);
            assert(abs(box.left - 100) < 1e-5);
            assert(abs(box.getRight() - 150) < 1e-5);
        },

        [&] {
            auto box = quadtree.getQuadrantByIndex(parent_box, Quadrants::SOUTH_EAST);
            assert(abs(box.top - 150) < 1e-5);
            assert(abs(box.getBottom() - 200) < 1e-5);
            assert(abs(box.left - 150) < 1e-5);
            assert(abs(box.getRight() - 200) < 1e-5);
        },
    
    };
    
    for(auto const& test: tests) test();
    std::cout << "QuadTree quadrants boxes compute correctly...\n";
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_AddValuesTest() {
    using QT = CustomQuadTree<T, Real>;
    QT quadtree(Box<Real>(0, 0, 100, 100), [] (Box<Real> const* ptr){
        return *ptr;
    });
    
    std::vector<Box<Real>> values = {
        Box<Real>{10, 10, 10, 10},
        Box<Real>{60, 10, 10, 10},
        Box<Real>{10, 60, 10, 10},
        Box<Real>{60, 60, 10, 10},
    };
    
    for(int i = 0; i != 4; ++i) {
        for(auto const& value: values) {
            quadtree.add(&value);
        }
    }
    
    assert(quadtree.isLeaf(quadtree.m_root));
    assert(quadtree.m_root->values.size() == quadtree.MAX_VALUES_SIZE);
    
    for(auto const& value: values) {
        // Add one object to all child nodes
        quadtree.add(&value);
    }
    
    assert(!quadtree.isLeaf(quadtree.m_root));
    assert(quadtree.m_root->values.empty());
    for(auto const& child: quadtree.m_root->children) {
        assert(child->values.size() == 5);
    }
    
    // Add unbounded value
    quadtree.add(new Box<Real>(10, 10, 60, 10));
    assert(quadtree.m_root->values.size() == 1);
    quadtree.add(new Box<Real>(10, 10, 10, 60));
    assert(quadtree.m_root->values.size() == 2);
    quadtree.add(new Box<Real>(10, 10, 60, 60));
    assert(quadtree.m_root->values.size() == 3);
    
    for(int i = 0; i != 16; ++i) {
        quadtree.add(new Box<Real>(10, 10, 60, 60));
    }
    assert(quadtree.m_root->values.size() == 19);
    
    std::cout << "QuadTree add values work normal...\n";
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_RemoveValuesTest() {
    using QT = CustomQuadTree<T, Real>;
    QT quadtree(Box<Real>(0, 0, 100, 100), [] (Box<Real> const* ptr) {
        return *ptr;
    });
    
    std::vector<Box<Real>> values = {
        Box<Real>{10, 10, 10, 10},
        Box<Real>{60, 10, 10, 10},
        Box<Real>{10, 60, 10, 10},
        Box<Real>{60, 60, 10, 10},
    };
    
    for(int i = 0; i != 4; ++i) {
        for(auto const& value: values) {
            quadtree.add(&value);
        }
    }
    
    for(int i = 0; i != 4; ++i) {
        for(auto const& value: values) {
            quadtree.remove(&value);
        }
    }
    
    assert(quadtree.m_root->values.empty());
    
    std::cout << "QuadTree values removed correctly...\n";
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_MergeTest() {
    using QT = CustomQuadTree<T, Real>;
    QT quadtree(Box<Real>(0, 0, 100, 100), [] (Box<Real> const* ptr){
        return *ptr;
    });
    
    std::vector<Box<Real>> values = {
        Box<Real>{10, 10, 10, 10},
        Box<Real>{60, 10, 10, 10},
        Box<Real>{10, 60, 10, 10},
        Box<Real>{60, 60, 10, 10},
    };
    
    for(int i = 0; i != 5; ++i) {
        for(auto const& value: values) {
            quadtree.add(&value);
        }
    }
    
    assert(!quadtree.isLeaf(quadtree.m_root));
    for(auto const& value: values) {
        quadtree.remove(&value);
    }
    
    assert(quadtree.isLeaf(quadtree.m_root));
    
    std::cout << "QuadTree merge test pass...\n";
}

template <template<class, class> class CustomQuadTree, class T, class Real>
void QuadTree_IntersectTest() {
    using QT = CustomQuadTree<T, Real>;
    QT quadtree(Box<Real>(0, 0, 100, 100), [] (Box<Real> const* ptr){
        return *ptr;
    });
    
    std::vector<Box<Real>> values = {
        Box<Real>{10, 10, 10, 10},
        Box<Real>{60, 10, 10, 10},
        Box<Real>{10, 60, 10, 10},
        Box<Real>{60, 60, 10, 10},
    };
    
    for(auto const& value: values) {
        quadtree.add(&value);
    }
    
    auto box = Box<Real>(15, 15, 50, 1);
    std::vector<Box<Real> const*> intersected = quadtree.query(box);
    assert(intersected[0] == &values[0]);
    assert(intersected[1] == &values[1]);
    
    std::cout << "QuadTree intersect work correctly...\n";
}

template <template <class, class> class CustomQuadTree>
void customQuadTreeTests() {
    QuadTree_CreateTest<CustomQuadTree, void*, int>();
    QuadTree_GetQuadrantIndexTest<CustomQuadTree, void*, float>();
    QuadTree_GetQuadrantByIndexTest<CustomQuadTree, void*, float>();
    QuadTree_AddValuesTest<CustomQuadTree, Box<float> const*, float>();
    QuadTree_RemoveValuesTest<CustomQuadTree, Box<float> const*, float>();
    QuadTree_MergeTest<CustomQuadTree, Box<float> const*, float>();
    QuadTree_IntersectTest<CustomQuadTree, Box<float> const*, float>();
}

void runTests() {
    #ifndef NDEBUG
    Box_ContainIntersectTest();
    
    customQuadTreeTests<QuadTree>();
    
    std::cout << "\n *** Parallel QuadTree test ***\n";
    customQuadTreeTests<QuadTreeParallel>();
    
    std::cout << "All right\n";
    #endif
}
