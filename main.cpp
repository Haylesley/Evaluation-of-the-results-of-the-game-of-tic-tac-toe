#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Проверка на корректность символов на игровом поле
bool isValidChar(char c) {
    return c == 'X' || c == 'O' || c == '.';
}

// Функция для проверки победителя в строке
char checkLine(const string& line) {
    if (line[0] == line[1] && line[1] == line[2]) {
        return line[0]; // Возвращаем символ победителя
    }
    return '.'; // Никакого победителя
}

// Функция для получения победителя в столбце
char checkColumn(const vector<string>& board, int col) {
    return checkLine({board[0][col], board[1][col], board[2][col]});
}

// Функция для проверки диагоналей
char checkDiagonals(const vector<string>& board) {
    char diag1 = checkLine({board[0][0], board[1][1], board[2][2]});
    char diag2 = checkLine({board[0][2], board[1][1], board[2][0]});
    return diag1 != '.' ? diag1 : diag2; // Возвращаем победителя, если есть
}

// Основная функция для проверки состояния игры
string checkGameState(const vector<string>& board) {
    int countX = 0, countO = 0;
    char winnerX = '.', winnerO = '.';

    // Подсчет символов и проверка на корректность
    for (const auto& row : board) {
        for (char c : row) {
            if (!isValidChar(c)) {
                return "Incorrect";
            }
            if (c == 'X') countX++;
            if (c == 'O') countO++;
        }
    }

    // Проверка победителей
    for (const auto& row : board) {
        char result = checkLine(row);
        if (result == 'X') winnerX = 'X';
        if (result == 'O') winnerO = 'O';
    }

    // Проверка столбцов
    for (int i = 0; i < 3; ++i) {
        char result = checkColumn(board, i);
        if (result == 'X') winnerX = 'X';
        if (result == 'O') winnerO = 'O';
    }

    // Проверка диагоналей
    char diagonalWinner = checkDiagonals(board);
    if (diagonalWinner == 'X') winnerX = 'X';
    if (diagonalWinner == 'O') winnerO = 'O';

    // Проверка на некорректные состояния
    if ((winnerX == 'X' && winnerO == 'O') || (countO > countX) || (countX > countO + 1)) {
        return "Incorrect";
    }
    if (winnerX == 'X' && countX == countO) {
        return "Incorrect"; // Крестики выиграли, ноликов не должно быть столько же
    }
    if (winnerO == 'O' && countX > countO) {
        return "Incorrect"; // Нолики выиграли, крестиков не должно быть больше
    }

    // Результаты игры
    if (winnerX == 'X') return "Petya won";
    if (winnerO == 'O') return "Vanya won";
    if (countX + countO < 9) return "Nobody"; // Игра не завершена
    return "Nobody"; // Ничья
}

int main() {
    vector<string> board(3);
    // Ввод игрового поля
    for (int i = 0; i < 3; ++i) {
        cin >> board[i];
    }

    cout << checkGameState(board) << endl;

    return 0;
}
