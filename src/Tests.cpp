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

void QuadTree_CreateTest() {
    QuadTree<void*, float> tree(Box<float>{});
    (void)tree;
    std::cout << "QuadTree creatable...\n";
}

void Box_GetQuadrantIndexTest() {
    using Quadrants = typename Box<float>::Quadrants;
    Box<float> parent_box(100, 100, 100, 100);
    
    std::function<void()> tests[] = {
      [&] {
          Box<float> target_box(1, 1, 10, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NORTH_WEST);
      },
      
      [&] {
          Box<float> target_box(99, 99, 1, 1);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NORTH_WEST);
      },

      [&] {
          Box<float> target_box(50, 50, 100, 100);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },
      
      [&] {
          Box<float> target_box(100, 100, 100, 100);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },
      
      [&] {
          Box<float> target_box(150, 100, 10, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NORTH_EAST);
      },
      
      [&] {
          Box<float> target_box(150, 100, 51, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NORTH_EAST);
      },
      
      [&] {
          Box<float> target_box(100, 100, 100, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },
      
      [&] {
          Box<float> target_box(100, 150, 10, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::SOUTH_WEST);
      },
      
      [&] {
          Box<float> target_box(100, 150, 10, 51);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::SOUTH_WEST);
      },

      [&] {
          Box<float> target_box(100, 150, 51, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },

      [&] {
          Box<float> target_box(100, 150, 50, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::NEITHER_ONE_QUADRANT);
      },

      [&] {
          Box<float> target_box(150, 150, 10, 10);
          Quadrants quadrant = parent_box.quadrantIndex(target_box);
          assert(quadrant == Quadrants::SOUTH_EAST);
      },
    };
    
    for(auto const& test: tests) test();
    std::cout << "QuadTree indexes of quadrants compute correctly...\n";
}

void Box_GetQuadrantByIndexTest() {
    using Quadrants = typename Box<float>::Quadrants;
    Box<float> parent_box(100, 100, 100, 100);
    
    std::function<void()> tests[] = {
        [&] {
            auto box = parent_box.quadrantByIndex(Quadrants::NORTH_WEST);
            assert(abs(box.top - 100) < 1e-5);
            assert(abs(box.getBottom() - 150) < 1e-5);
            assert(abs(box.left - 100) < 1e-5);
            assert(abs(box.getRight() - 150) < 1e-5);
        },

        [&] {
            auto box = parent_box.quadrantByIndex(Quadrants::NORTH_EAST);
            assert(abs(box.top - 100) < 1e-5);
            assert(abs(box.getBottom() - 150) < 1e-5);
            assert(abs(box.left - 150) < 1e-5);
            assert(abs(box.getRight() - 200) < 1e-5);
        },

        [&] {
            auto box = parent_box.quadrantByIndex(Quadrants::SOUTH_WEST);
            assert(abs(box.top - 150) < 1e-5);
            assert(abs(box.getBottom() - 200) < 1e-5);
            assert(abs(box.left - 100) < 1e-5);
            assert(abs(box.getRight() - 150) < 1e-5);
        },

        [&] {
            auto box = parent_box.quadrantByIndex(Quadrants::SOUTH_EAST);
            assert(abs(box.top - 150) < 1e-5);
            assert(abs(box.getBottom() - 200) < 1e-5);
            assert(abs(box.left - 150) < 1e-5);
            assert(abs(box.getRight() - 200) < 1e-5);
        },
    
    };
    
    for(auto const& test: tests) test();
    std::cout << "QuadTree quadrants boxes compute correctly...\n";
}

void QuadTree_AddValuesTest() {
    using QT = QuadTree<Box<float>, float>;
    QT quadtree(Box<float>(0, 0, 100, 100));
    
    using ViB = ValueInBox<Box<float>, float>;
    class TreeObj: public ViB, public ClonableDerived<TreeObj, ViB> {
      public:
        explicit TreeObj(Box box): value(box) { }
        Box getBox() const override { return value; }
        Box& getValue() override { return value; }
        
      private:
        Box value;
    };
    
    std::vector<std::shared_ptr<TreeObj>> values = {
        // For 4 quadrants
        std::make_shared<TreeObj>(Box<float>(10, 10, 10, 10)),
        std::make_shared<TreeObj>(Box<float>(60, 10, 10, 10)),
        std::make_shared<TreeObj>(Box<float>(10, 60, 10, 10)),
        std::make_shared<TreeObj>(Box<float>(60, 60, 10, 10)),
    };
    
    for(int i = 0; i != 4; ++i) {
        for(auto const& value: values) {
            quadtree.add(value);
        }
    }
    
    assert(quadtree.m_root_node->isLeaf());
    assert(quadtree.m_root_node->m_values.size() == decltype(quadtree)::NodeType::getMaxValuesSize());
    
    for(auto const& value: values) {
        // Add one object to all child nodes
        quadtree.add(value);
    }
    
    assert(!quadtree.m_root_node->isLeaf());
    assert(quadtree.m_root_node->m_values.empty());
    for(auto const& child: quadtree.m_root_node->m_children) {
        assert(child->m_values.size() == 5);
    }
    
    // Add unbounded value
    quadtree.add(std::make_shared<TreeObj>(Box<float>(10, 10, 60, 10)));
    quadtree.add(std::make_shared<TreeObj>(Box<float>(10, 10, 10, 60)));
    quadtree.add(std::make_shared<TreeObj>(Box<float>(10, 10, 60, 60)));
    assert(quadtree.m_root_node->m_values.size() == 3);
    
    for(int i = 0; i != 16; ++i) {
        quadtree.add(std::make_shared<TreeObj>(Box<float>(10, 10, 60, 60)));
    }
    assert(quadtree.m_root_node->m_values.size() == 19);
    
    std::cout << "QuadTree add values work normal...\n";
}

void QuadTree_RemoveValuesTest() {
    using QT = QuadTree<Box<float>>;
    QT quadtree(Box<float>(0, 0, 100, 100));
    
    using ViB = ValueInBox<Box<float>>;
    class TreeObj: public ViB, public ClonableDerived<TreeObj, ViB> {
      public:
        explicit TreeObj(Box box): value(box) { }
        Box getBox() const override { return value; }
        Box& getValue() override { return value; }
      
      private:
        Box value;
    };
    
    std::vector<std::shared_ptr<TreeObj>> values = {
        std::make_shared<TreeObj>(Box<float>(10, 10, 10, 10)),
        std::make_shared<TreeObj>(Box<float>(60, 10, 10, 10)),
        std::make_shared<TreeObj>(Box<float>(10, 60, 10, 10)),
        std::make_shared<TreeObj>(Box<float>(60, 60, 10, 10)),
    };
    
    for(int i = 0; i != 4; ++i) {
        for(auto const& value: values) {
            quadtree.add(value);
        }
    }
    
    for(int i = 0; i != 4; ++i) {
        for(auto const& value: values) {
            quadtree.remove(value);
        }
    }
    
    assert(quadtree.m_root_node->m_values.empty());
    
    std::cout << "QuadTree values removed correctly...\n";
}

void QuadTree_MergeTest() {
    using QT = QuadTree<Box<float>>;
    QT quadtree(Box<float>(0, 0, 100, 100));
    
    using ViB = ValueInBox<Box<float>>;
    class TreeObj: public ViB, public ClonableDerived<TreeObj, ViB> {
      public:
        explicit TreeObj(Box box): value(box) { }
        Box getBox() const override { return value; }
        Box& getValue() override { return value; }
      
      private:
        Box value;
    };
    
    std::vector<std::shared_ptr<TreeObj>> values = {
        std::make_shared<TreeObj>(Box<float>{10, 10, 10, 10}),
        std::make_shared<TreeObj>(Box<float>{60, 10, 10, 10}),
        std::make_shared<TreeObj>(Box<float>{10, 60, 10, 10}),
        std::make_shared<TreeObj>(Box<float>{60, 60, 10, 10}),
    };
    
    for(int i = 0; i != 5; ++i) {
        for(auto const& value: values) {
            quadtree.add(value);
        }
    }
    
    assert(!quadtree.m_root_node->isLeaf());
    for(auto const& value: values) {
        quadtree.remove(value);
    }
    
    assert(quadtree.m_root_node->isLeaf());
    
    std::cout << "QuadTree merge test pass...\n";
}

void QuadTree_IntersectTest() {
    using QT = QuadTree<Box<float>>;
    QT quadtree(Box<float>(0, 0, 100, 100));
    
    using ViB = ValueInBox<Box<float>>;
    class TreeObj: public ViB, public ClonableDerived<TreeObj, ViB> {
      public:
        explicit TreeObj(Box box): value(box) { }
        Box getBox() const override { return value; }
        Box& getValue() override { return value; }
        
      private:
        Box value;
    };
    
    std::vector<std::shared_ptr<TreeObj>> values = {
        std::make_shared<TreeObj>(Box<float>{10, 10, 10, 10}),
        std::make_shared<TreeObj>(Box<float>{60, 10, 10, 10}),
        std::make_shared<TreeObj>(Box<float>{10, 60, 10, 10}),
        std::make_shared<TreeObj>(Box<float>{60, 60, 10, 10}),
    };
    
    for(auto const& value: values) {
        quadtree.add(value);
    }
    
    auto box = Box<float>(15, 15, 50, 1);
    auto intersected = quadtree.query(box);
    assert(*intersected[0] == *values[0]);
    assert(*intersected[1] == *values[1]);
    
    std::cout << "QuadTree intersect work correctly...\n";
}

void QuadTreeTests() {
    QuadTree_CreateTest();
    Box_GetQuadrantIndexTest ();
    Box_GetQuadrantByIndexTest ();
    QuadTree_AddValuesTest();
    QuadTree_RemoveValuesTest();
    QuadTree_MergeTest();
    QuadTree_IntersectTest();
}

void runTests() {
    #ifndef NDEBUG
    Box_ContainIntersectTest();
    
    QuadTreeTests();
    
    std::cout << "\n *** Parallel QuadTree test ***\n";
    
    std::cout << "All right\n";
    #endif
}
