#pragma once

#include "settings.h"
#include "support.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>

class AStarVisualization {
private:
    void create_grid(const std::vector<std::vector<int>>* custom_grid = nullptr);
    template<typename Func>
    void place(Func place_func);
    bool try_place_obstacle_at_pos(int y, int x);
    bool try_place_start_at_pos(int y, int x);
    bool try_place_end_at_pos(int y, int x);
    void create_font();
    void create_weight_text();
    std::vector<std::pair<int, int>> find_path();
    void draw();

    sf::RenderWindow window;
    std::string mode;
    std::vector<std::vector<Cell>> grid;
    // --- Генератор случайных чисел
    std::mt19937 gen;
    std::uniform_int_distribution<size_t> cell_pos_dist;
    std::uniform_int_distribution<size_t> cell_weight_dist;
    // ---
    Cell* start_cell;
    Cell* end_cell;
    sf::Font font;
    std::vector<sf::Text> cell_weight_texts;
    bool path_calculated;
public:
    AStarVisualization(const std::string& _mode);
    AStarVisualization(const std::string& _mode, const std::vector<std::vector<int>>* custom_grid);
    void run();
};