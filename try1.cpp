#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>
using namespace std;
struct Point {
    int x, y;
};

int player;
const int SIZE = 8;
int order[8][8] = {
    9,2,8,6,6,8,2,9,
    2,1,3,4,4,3,1,2,
    8,3,7,5,5,7,3,8,
    6,4,5,0,0,5,4,6,
    6,4,5,0,0,5,4,6,
    8,3,7,5,5,7,3,8,
    2,1,3,4,4,3,1,2,
    9,2,8,6,6,8,2,9,
};
std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;
std::vector<Point> four;
std::map<int,Point> sfvp;
struct cmp1 {
    bool operator()(const Point& lhs, const Point& rhs) {
        return order[lhs.x][lhs.y] > order[rhs.x][rhs.y];
    }
};
set<Point, cmp1> next_valid_spots_set;


void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}
void usefour(std::ofstream& fout) {
    int n_valid_spotsnum = next_valid_spots.size();
    for (auto i = 0; i < n_valid_spotsnum;i++) {
        if ((next_valid_spots[i].x == 0 && next_valid_spots[i].y == 0)||(next_valid_spots[i].x == 0 && next_valid_spots[i].y == 7)|| (next_valid_spots[i].x == 7 && next_valid_spots[i].y == 0)|| (next_valid_spots[i].x == 7 && next_valid_spots[i].y == 7)) {

            Point p = next_valid_spots[i];
            // Remember to flush the output to ensure the last action is written to file.
            fout << p.x << " " << p.y << std::endl;
            break;
        }
    }
    fout.flush();
}
/*void orderofboard(std::ofstream& fout) {
    for (int i = 0; i < next_valid_spots.size(); i++) {
        if () {

            Point p = next_valid_spots[i];
            // Remember to flush the output to ensure the last action is written to file.
            fout << p.x << " " << p.y << std::endl;
            break;
        }
    }
    fout.flush();
}*/
void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({ x, y });
        next_valid_spots_set.insert({ x, y });
    }
}

void write_valid_spot(std::ofstream& fout) {
    int n_valid_spots = next_valid_spots.size();
    srand(time(NULL));
    // Choose random spot. (Not random uniform here)
    int index = (rand() % n_valid_spots);
    Point p = next_valid_spots[index];
    // Remember to flush the output to ensure the last action is written to file.
    fout << p.x << " " << p.y << std::endl;
    if (!next_valid_spots_set.empty()){
        auto firstp = next_valid_spots_set.begin();
        fout << (*firstp).x << " " << (*firstp).y << std::endl;
    }
    fout.flush();
}
void sfv() {

}
int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    usefour(fout);
    fin.close();
    fout.close();
    return 0;
}
