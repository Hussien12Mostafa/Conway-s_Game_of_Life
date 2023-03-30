#include <SFML/Graphics.hpp>
#include <vector>
#include <numeric>
using namespace std;

const int BOARD_SIZE = 100;
const int CELL_SIZE = 5;

void draw_board(sf::RenderWindow& window, vector<vector<int>> board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
            if (board[i][j] == 1) {
                cell.setFillColor(sf::Color::White);
            } else {
                cell.setFillColor(sf::Color::Black);
            }
            window.draw(cell);
        }
    }
}

int count_neighbors(vector<vector<int>> board, int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i == row && j == col) {
                continue;
            }
            if (i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE) {
                continue;
            }
            if (board[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

vector<vector<int>> update_board(vector<vector<int>> board) {
    vector<vector<int>> new_board(BOARD_SIZE, vector<int>(BOARD_SIZE));
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int neighbors = count_neighbors(board, i, j);
            if (board[i][j] == 1 && neighbors < 2) {
                new_board[i][j] = 0;
            } else if (board[i][j] == 1 && neighbors > 3) {
                new_board[i][j] = 0;
            } else if (board[i][j] == 0 && neighbors == 3) {
                new_board[i][j] = 1;
            } else {
                new_board[i][j] = board[i][j];
            }
        }
    }
    return new_board;
}

void draw_histogram(sf::RenderWindow& window, vector<int> data) {
    int max_value = *max_element(data.begin(), data.end());
    sf::RectangleShape bar(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    bar.setFillColor(sf::Color::White);
    for (int i = 0; i < max_value; i++) {
        bar.setPosition(i * CELL_SIZE, window.getSize().y - ((i + 1) * CELL_SIZE));
        window.draw(bar);
    }
}

int main() {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE));
    // Set some cells to be alive
    board[50][50] = 1;
    board[50][51] = 1;
    board[50][52] = 1;

    sf::RenderWindow board_window(sf::VideoMode(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE), "Game of Life");
    sf::RenderWindow histogram_window(sf::VideoMode(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE), "Histogram");

    vector<int> live_counts;

    // Run the simulation indefinitely
    while (board_window.isOpen() && histogram_window.isOpen()) {
        sf::Event event;
        while (board_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                board_window.close();
                histogram_window.close();
            }
        }

        draw_board(board_window, board);

        // Count the number of live cells
        int live_count = accumulate(board.begin(), board.end(), 0,
                                     [](int sum, const vector<int>& row) { return sum + accumulate(row.begin(), row.end(), 0); });
        live_counts.push_back(live_count);

        histogram_window.clear(sf::Color::Black);
        draw_histogram(histogram_window, live_counts);

        // Update the board
        board = update_board(board);

        // Display the windows
        board_window.display();
        histogram_window.display();
    }
}

