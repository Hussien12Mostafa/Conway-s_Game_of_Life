#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> grid(10, vector<int>(10));
    grid[0][1] = 1;
    grid[1][2] = 1;
    grid[2][0] = 1;
    grid[2][1] = 1;
    grid[2][3] = 1;
    grid[2][4] = 1;
    grid[3][1] = 1;
    grid[3][4] = 1;
    grid[4][1] = 1;
    grid[4][2] = 1;
    grid[4][3] = 1;
    grid[4][4] = 1;

    int x_offset = 0;
    int y_offset = 0;

    while (true) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j]) {
                    cout << "X";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }

        x_offset++;
        y_offset++;

        vector<vector<int>> new_grid(grid.size(), vector<int>(grid[0].size()));

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j]) {
                    new_grid[(i + x_offset) % new_grid.size()][(j + y_offset) % new_grid[i].size()] = 1;
                }
            }
        }

        grid = new_grid;

        cout << endl << endl;
    }

    return 0;
}