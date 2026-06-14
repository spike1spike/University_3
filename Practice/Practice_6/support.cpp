#include "support.h"

// Функция для вычисления эвристики (манхэттенское расстояние)
int manhattan_distance(const Cell& a, const Cell& b) {
    return std::abs(a.get_x() - b.get_x()) + std::abs(a.get_y() - b.get_y());
}

// Функция для проверки, находится ли ячейка в пределах сетки
bool isValid(int y, int x, int grid_size_y, int grid_size_x) {
    return ((0 <= y) && (y <= (grid_size_y - 1))) && ((0 <= x) && (x <= (grid_size_x - 1)));
}