#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>

int alive_neighbors(std::size_t x, std::size_t y,
                    std::vector<std::vector<int>> vGrid) {

  int width = vGrid.size() - 1;
  int height = vGrid[0].size() - 1;
  int sum = 0;
  // testing left cell
  if (y > 0 && vGrid[x][y - 1] == 1)
    sum++;
  // testing right cell
  if (y < height && vGrid[x][y + 1] == 1)
    sum++;
  // testing top cell
  if (x > 0 && vGrid[x - 1][y] == 1)
    sum++;
  // testing bottom cell
  if (x < width && vGrid[x + 1][y] == 1)
    sum++;

  if (y > 0 && x > 0 && vGrid[x - 1][y - 1] == 1)
    sum++;
  if (y > 0 && x < width && vGrid[x + 1][y - 1] == 1)
    sum++;
  if (y < height && x > 0 && vGrid[x - 1][y + 1] == 1)
    sum++;
  if (y < height && x < width && vGrid[x + 1][y + 1] == 1)
    sum++;

  return sum;
}

int life(std::size_t x, std::size_t y, std::vector<std::vector<int>> vGrid) {
  int sum = alive_neighbors(x, y, vGrid);

  // if alive and sum < 2 then die
  if (vGrid[x][y] == 1 && sum < 2)
    return 0;

  // if alive and sum is 2 or 3 then live
  if (vGrid[x][y] == 1 && (sum == 2 || sum == 3))
    return 1;

  // if alive and sum > 3 then die
  if (vGrid[x][y] == 1 && sum > 3)
    return 0;

  // if dead and sum = 3 then live
  if (vGrid[x][y] == 0 && sum == 3)
    return 1;

  return 0;
}

std::vector<std::vector<int>> new_grid(std::vector<std::vector<int>> grid) {
  std::vector<std::vector<int>> vTempGrid = grid;
  int x = grid.size();
  int y = grid[0].size();

  for (int r = 0; r < x; r++) {
    for (int c = 0; c < y; c++) {
      vTempGrid[r][c] = life(r, c, grid);
    }
  }

  return vTempGrid;
}

void print_generation(std::vector<std::vector<int>> vGrid) {
  std::string white_square = "⬜";
  std::string black_square = "⬛";
  int width = vGrid.size();
  int height = vGrid[0].size();

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int cur_cell = vGrid[x][y];
      if (cur_cell == 0) {
        std::cout << black_square;
      } else {
        std::cout << white_square;
      }
    }
    std::cout << std::endl;
  }
}

void generate_x(int generations, std::vector<std::vector<int>> vGrid) {
  std::vector<std::vector<int>> tGrid = vGrid;
  for (int g = 0; g < generations; g++) {
    std::system("clear");
    std::cout << "Generation " << (g + 1) << std::endl;
    print_generation(tGrid);
    tGrid = new_grid(tGrid);
    std::cout << std::endl;
    usleep(500 * 1000);
    // std::system("clear");
  }

  std::cout << "Generations Finished!" << std::endl;
}

int main() {

  std::vector<std::vector<int>> grid1 = {
      {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0},
      {0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
  };

  std::vector<std::vector<int>> beacon = {{1, 1, 0, 0, 0},
                                          {1, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 1},
                                          {0, 0, 0, 1, 1}};

  std::vector<std::vector<int>> glider = {{0, 0, 1, 0, 0},
                                          {1, 0, 1, 0, 0},
                                          {0, 1, 1, 0, 0},
                                          {0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0}};

  std::vector<std::vector<int>> pulsar = {
  {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0}
};


  generate_x(20, pulsar);

  return 1;
}