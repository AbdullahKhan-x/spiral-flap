#include "score.h"
#include <fstream>

int LoadHighScore() {
    int highScore = 0;
    std::ifstream file("highscore.dat");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}

void SaveHighScore(int newHighScore) {
    std::ofstream file("highscore.dat");
    if (file.is_open()) {
        file << newHighScore;
        file.close();
    }
}