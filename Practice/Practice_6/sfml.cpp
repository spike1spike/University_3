#include "sfml.h"
#include "support.h"

AStarVisualization::AStarVisualization(const std::string& _mode, const std::vector<std::vector<int>>* custom_grid)
    : window(sf::VideoMode((*custom_grid)[0].size()* CELL_SIZE, custom_grid->size()* CELL_SIZE), "A*"),
    mode(_mode),
    grid(custom_grid->size(), std::vector<Cell>(custom_grid->size())),
    path_calculated(false) {

    create_grid(custom_grid);
}

AStarVisualization::AStarVisualization(const std::string& _mode)
    : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A*"),
    mode(_mode),
    grid(GRID_SIZE, std::vector<Cell>(GRID_SIZE)),
    gen(std::random_device()()),
    cell_pos_dist(0, GRID_SIZE - 1),
    cell_weight_dist(1, 99),
    path_calculated(false) {

    create_grid();
    if (mode == "random_weight") {
        create_font();
        create_weight_text();
    }
}

void AStarVisualization::run() {
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                // SPACE: Найти путь
                if (event.key.code == sf::Keyboard::Space) {
                    // Путь уже просчитан -> ничего не делать
                    if (path_calculated) { continue; };

                    std::vector<std::pair<int, int>> path = find_path();
                    if (path.empty()) {
                        std::cout << "Path not found" << std::endl;
                    }
                    else {
                        std::cout << "Path:" << std::endl;
                        for (auto cell : path) {
                            std::cout << "(" << cell.first << ";" << cell.second << ")" << std::endl;
                        }
                    }
                    std::cout << std::endl;
                    path_calculated = true;
                }

                // R: Сгенерировать новую карту, если режим - случайная генерация)
                if ((event.key.code == sf::Keyboard::R) && (mode != "custom")) {
                    create_grid();
                    if (mode == "random_weight") { create_weight_text(); };
                    path_calculated = false;
                }
            }
        }

        // Отрисовка программы
        window.clear();
        draw();
        window.display();
    }
}

void AStarVisualization::create_grid(const std::vector<std::vector<int>>* custom_grid) {
    if (mode == "custom") {
        for (int y = 0; y < custom_grid->size(); y++) {
            for (int x = 0; x < (*custom_grid)[0].size(); x++) {
                grid[y][x] = Cell(y, x);
                Cell& cell = grid[y][x];

                if ((*custom_grid)[y][x] == 1) {
                    cell.set_type(OBSTACLE);
                }
                else if ((*custom_grid)[y][x] == 2) {
                    cell.set_type(START);
                    start_cell = &cell;
                }
                else if ((*custom_grid)[y][x] == 3) {
                    cell.set_type(END);
                    end_cell = &cell;
                }
            }
        }
    }

    else if ((mode == "random") || (mode == "random_weight")) {
        // Создание массива сетки
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int x = 0; x < GRID_SIZE; x++) {
                if (mode == "random") {
                    grid[y][x] = Cell(y, x);
                }
                else if (mode == "random_weight") {
                    int weight = cell_weight_dist(gen);
                    grid[y][x] = Cell(y, x, weight);
                }
            }
        }

        // Генерация препятствий
        int obstacle_amount = GRID_SIZE * GRID_SIZE * 0.2;
        for (int i = 0; i < obstacle_amount; i++) {
            place([this](int y, int x) {return try_place_obstacle_at_pos(y, x); });
        }

        // Генерация начальной точки
        place([this](int y, int x) {return try_place_start_at_pos(y, x); });

        // Генерация конечной точки
        place([this](int y, int x) {return try_place_end_at_pos(y, x); });
    }
}

template<typename Func>
void AStarVisualization::place(Func place_func) {
    int y_pos = cell_pos_dist(gen);
    int x_pos = cell_pos_dist(gen);

    // --- Гарантированная случайная постановка чего-либо с первой сгенерированной позиции
    // Проход на строке y_pos по столбцам от x_pos до 0 (влево)
    for (int x = x_pos; x > -1; x--) {
        bool is_placed = place_func(y_pos, x);
        if (is_placed) { return; };
    }

    // Проход на строкам от (y_pos - 1) до 0, по столбцам от (GRID_SIZE - 1) до 0 (влево-вверх)
    for (int y = y_pos - 1; y > -1; y--) {
        for (int x = GRID_SIZE - 1; x > -1; x--) {
            bool is_placed = place_func(y, x);
            if (is_placed) { return; };
        }
    }

    // Проход на строке y_pos по столбцам от x_pos до (GRID_SIZE - 1) (вправо)
    for (int x = x_pos; x < GRID_SIZE; x++) {
        bool is_placed = place_func(y_pos, x);
        if (is_placed) { return; };
    }

    // Проход на строкам от (y_pos + 1) до (GRID_SIZE - 1), по столбцам от 0 до (GRID_SIZE - 1) (вправо-вниз)
    for (int y = y_pos + 1; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            bool is_placed = place_func(y, x);
            if (is_placed) { return; };
        }
    }
    // ---
}

bool AStarVisualization::try_place_obstacle_at_pos(int y, int x) {
    Cell& cell = grid[y][x];

    if (cell.get_type() != OBSTACLE) {
        cell.set_type(OBSTACLE);
        cell.set_weight(0);
        return true;
    }

    return false;
}

bool AStarVisualization::try_place_start_at_pos(int y, int x) {
    Cell& cell = grid[y][x];

    if (cell.get_type() != OBSTACLE) {
        cell.set_type(START);
        cell.set_weight(0);
        start_cell = &cell;
        return true;
    }

    return false;
}

bool AStarVisualization::try_place_end_at_pos(int y, int x) {
    Cell& cell = grid[y][x];

    if ((cell.get_type() != OBSTACLE) && (cell.get_type() != START)) {
        cell.set_type(END);
        cell.set_weight(0);
        end_cell = &cell;
        return true;
    }

    return false;
}

void AStarVisualization::create_font() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "ERROR: COULD NOT IMPORT FONT" << std::endl;
        return;
    }
}

void AStarVisualization::create_weight_text() {
    cell_weight_texts.clear();

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            Cell& cell = grid[y][x];
            if ((cell.get_type() == OBSTACLE) || (cell.get_type() == START) || (cell.get_type() == END)) { continue; };
            int cell_weight = cell.get_weight();

            sf::Text weight_text;
            weight_text.setFont(font);
            weight_text.setCharacterSize(15);
            weight_text.setFillColor(sf::Color::Black);
            weight_text.setString(std::to_string(cell_weight));
            sf::FloatRect bounds = weight_text.getLocalBounds();
            weight_text.setOrigin(
                bounds.left + (bounds.width / 2.0f),
                bounds.top + (bounds.height / 2.0f)
            );
            double x_pos = (CELL_SIZE / 2.0f) + (x * CELL_SIZE);
            double y_pos = (CELL_SIZE / 2.0f) + (y * CELL_SIZE);
            weight_text.setPosition(x_pos, y_pos);

            cell_weight_texts.push_back(weight_text);
        }
    }
}

std::vector<std::pair<int, int>> AStarVisualization::find_path() {
    auto cmp = [](const Cell* a, const Cell* b) { return *a > *b; };
    std::priority_queue<Cell*, std::vector<Cell*>, decltype(cmp)> open_list;
    
    // Настройка ячейки начала
    start_cell->set_h(manhattan_distance(*start_cell, *end_cell));
    open_list.push(start_cell);

    while (!open_list.empty()) {
        Cell* current_cell = open_list.top();
        open_list.pop();

        if (*current_cell == *end_cell) {
            // Путь найден, реконструкция пути по указателям на родителей
            std::vector<std::pair<int, int>> path;
            Cell* cell = current_cell;
            while (cell) {
                path.emplace_back(cell->get_x(), cell->get_y());
                if ((cell->get_type() != START) && (cell->get_type() != END)) {
                    cell->set_type(PATH);
                }
                cell = cell->get_parent();
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (current_cell != start_cell) { current_cell->set_type(VISITED); };

        for (auto [dx, dy] : std::vector<std::pair<int, int>>{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} }) {
            int ny = current_cell->get_y() + dy;
            int nx = current_cell->get_x() + dx;

            if (!isValid(ny, nx, grid.size(), grid[0].size())) { continue; };

            Cell& neighbour_cell = grid[ny][nx];
            if (neighbour_cell.get_type() == EMPTY) {
                neighbour_cell.set_type(QUEUE);
                neighbour_cell.set_parent(current_cell);
                neighbour_cell.set_h(manhattan_distance(neighbour_cell, *end_cell));

                open_list.push(&neighbour_cell);
            }
            else if ((neighbour_cell.get_type() == QUEUE) && ((current_cell->get_g() + neighbour_cell.get_weight()) < neighbour_cell.get_g())) {
                neighbour_cell.set_parent(current_cell);

                open_list.push(&neighbour_cell);
            }
            else if (neighbour_cell.get_type() == END) {
                neighbour_cell.set_parent(current_cell);
                neighbour_cell.set_h(manhattan_distance(neighbour_cell, *end_cell));

                open_list.push(&neighbour_cell);
            }
        }
    }

    // Открытый список пуст -> пути к целевой клетке не существует
    return {};
}

void AStarVisualization::draw() {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            // Отрисовка клетки
            sf::RectangleShape cell_rect(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell_rect.setPosition(x * CELL_SIZE, y * CELL_SIZE);

            Cell& cell = grid[y][x];
            switch (cell.get_type()) {
            case EMPTY: cell_rect.setFillColor(sf::Color::White); break;
            case OBSTACLE: cell_rect.setFillColor(sf::Color::Black); break;
            case START: cell_rect.setFillColor(sf::Color(255, 165, 0)); break;
            case END: cell_rect.setFillColor(sf::Color::Cyan); break;
            case QUEUE: cell_rect.setFillColor(sf::Color::Green); break;
            case VISITED: cell_rect.setFillColor(sf::Color::Red); break;
            case PATH: cell_rect.setFillColor(sf::Color::Magenta); break;
            }

            window.draw(cell_rect);
        }
    }

    // Отрисовка веса клетки (в режиме "random_weight")
    if (mode == "random_weight") {
        for (sf::Text weight_text : cell_weight_texts) {
            window.draw(weight_text);
        }
    }
}