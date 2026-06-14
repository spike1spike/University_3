#pragma once

#include "settings.h"

#include <cmath>

// Типы ячеек
enum CellType {
    EMPTY,
    OBSTACLE,
    START,
    END,
    QUEUE,
    VISITED,
    PATH,
};

// Структура для представления ячейки
struct Cell {
    int y, x;
    CellType type;
    int weight;
    int g, h; // Для алгоритма A*
    Cell* parent;

    Cell() : y(0), x(0), type(EMPTY), weight(1), g(0), h(0), parent(nullptr) {};
    Cell(int _y, int _x) : y(_y), x(_x), type(EMPTY), weight(1), g(0), h(0), parent(nullptr) {};
    Cell(int _y, int _x, int _weight) : y(_y), x(_x), type(EMPTY), weight(_weight), g(0), h(0), parent(nullptr) {};

    int f() const { return g + h; };

    // Перезагрузка оператора == для сравнения ячеек
    bool operator==(const Cell& other) const {
        return y == other.y && x == other.x;
    }
    // Перегрузка оператора > для алгоритма A*
    bool operator>(const Cell& other) const {
        return f() > other.f();
    }

    void set_type(CellType new_type) { type = new_type; };
    void set_weight(int new_weight) { weight = new_weight; };
    void set_h(int new_h) { h = new_h; };
    void set_parent(Cell* new_parent) {
        parent = new_parent;
        g = parent->get_g() + weight;
    }

    int get_y() const { return y; };
    int get_x() const { return x; };
    CellType get_type() const { return type; };
    int get_weight() const { return weight; };
    int get_g() const { return g; };
    Cell* get_parent() const { return parent; };
};

// Функция для вычисления эвристики (манхэттенское расстояние)
int manhattan_distance(const Cell& a, const Cell& b);

// Функция для проверки, находится ли ячейка в пределах сетки
bool isValid(int y, int x, int grid_size_y, int grid_size_x);