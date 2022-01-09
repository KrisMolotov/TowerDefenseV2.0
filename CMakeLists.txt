cmake_minimum_required(VERSION 3.21)
project(TowerDefenseV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(TowerDefenseV2E Evil.h Evil.cpp TestEvil.cpp)
add_executable(TowerDefenseV2C TreeNode.h BinaryTree.h Map.h Castle.h Castle.cpp TestCastle.cpp)
add_executable(TowerDefenseV2W Wall.h Wall.cpp TestWall.cpp)
add_executable(TowerDefenseV2T Tower.h Tower.cpp TestTower.cpp)
add_executable(TowerDefenseV2L Evil.h Evil.cpp Lair.h Lair.cpp TestLair.cpp)
add_executable(TowerDefenseV2S Evil.h Evil.cpp Tower.h Tower.cpp Wall.h Wall.cpp Lair.h Lair.cpp
        Castle.h Castle.cpp Square.h Square.cpp TestSquare.cpp)
add_executable(TowerDefenseV2LS TreeNode.h BinaryTree.h Map.h Landscape.h Evil.h Evil.cpp Tower.h Tower.cpp Wall.h Wall.cpp Lair.h Lair.cpp
        Castle.h Castle.cpp Square.h Square.cpp Landscape.cpp TestLandscape.cpp)