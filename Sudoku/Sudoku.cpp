#include<iostream>
#include <Windows.h>
#include <iomanip>
#include <algorithm>  
#include <ctime>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#define Size 9

enum KeyBoard {
    SPACE = 32,
    ENTER = 13,
    TAB = 9,
    ESC = 27,
    ARROWS = 224,
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    BACKSPACE = 8,
    S = 83,
    NUM0 = 48,
    NUM1,
    NUM2,
    NUM3,
    NUM4,
    NUM5,
    NUM6,
    NUM7,
    NUM8,
    NUM9
};

using std::cout;

class Sudoku {
private:
    int PlayingField[Size][Size];
    int ViewPlayingField[Size][Size];
    int PlayerValues[Size][Size];
public:
    Sudoku() {
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                ViewPlayingField[i][j] = 0;
                PlayerValues[i][j] = 0;
                PlayingField[i][j] = 0;
            }
        }
    }
    ~Sudoku() {
        // Вызвался деструктор
    }
    bool FillingRow(int row) {
        int NumbersForCheck[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, counter = 0;

        for (int col = 0, quantity = 0; col < Size; quantity++) {
            do {
                do {
                    PlayingField[row][col] = NumbersForCheck[rand() % Size];
                } while (!PlayingField[row][col]);
                counter++;
                if (counter > 15)
                    return false;
            } while (!CheckDirections(PlayingField[row][col], row, col, 1) || !CheckSquare(PlayingField[row][col], row, col, 1));
            counter = 0;
            for (int l = 0; l < Size; l++) {
                if (PlayingField[row][col] == NumbersForCheck[l]) {
                    NumbersForCheck[l] = 0;
                    col++;
                    break;
                }
            }
            if (quantity == 20) {
                return false;
            }
        }
        return true;
    }
    void Filling() {
        int repeats = 0;

        for (int row = 0; row < Size; row++) {
            while (true) {
                if (FillingRow(row))
                    break;
                else {
                    Clean(row);
                    repeats++;
                }
                if (repeats > 10) {
                    for (int l = 0; l < sqrt(Size) && row > 0; l++) {
                        Clean(row);
                        row--;
                    }
                    repeats = 0;
                }
            }
            repeats = 0;
        }
    }
    void ViewFieldFilling(int QuantityOpenCells) {
        int openRow, openCol;
        for (int i = 0; i < QuantityOpenCells; i++) {
            openRow = rand() % Size;
            openCol = rand() % Size;
            if (!ViewPlayingField[openRow][openCol])
                ViewPlayingField[openRow][openCol] = PlayingField[openRow][openCol];
            else
                i--;
        }
    }
    bool FindEmptyPlace(int& row, int& col) {
        for (row = 0; row < Size; row++)
            for (col = 0; col < Size; col++)
                if (ViewPlayingField[row][col] == 0)
                    return true;
        return false;
    }
    bool SolveSudoku() {
        int row, col;
        if (!FindEmptyPlace(row, col))
            return true;
        for (int num = 1; num <= Size; num++) {
            if (CheckDirections(num, row, col, 0) && CheckSquare(num, row, col, 0)) {
                ViewPlayingField[row][col] = num;
                if (SolveSudoku())
                    return true;
                ViewPlayingField[row][col] = 0;
            }
        }
        return false;
    }
    bool CheckPlayerValuesLocation() {
        for (int row = 0; row < Size; row++) {
            for (int col = 0; col < Size; col++) {
                if (PlayerValues[row][col])
                    if (!CheckDirections(PlayerValues[row][col], row, col, 0) || !CheckSquare(PlayerValues[row][col], row, col, 0))
                        return false;
            }
        }
        return true;
    }
    void CheckCorrectnessPlayerValues() {
        for (int row = 0; row < Size; row++) {
            for (int col = 0; col < Size; col++) {
                if (PlayingField[row][col] == PlayerValues[row][col])
                    ViewPlayingField[row][col] = PlayingField[row][col];
            }
        }
    }
    bool CheckResult() {
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                if (!ViewPlayingField[i][j])
                    if (PlayerValues[i][j] != PlayingField[i][j])
                        return false;
            }
        }
        return true;
    }
    bool CheckNulls() {
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                if (!ViewPlayingField[i][j])
                    return false;
            }
        }
        return true;
    }
    int CheckDirections(int check, int row, int col, bool selectionFields) {
        for (int i = 0; i < Size; i++) {
            if (selectionFields) {
                if (PlayingField[row][i] == PlayingField[row][col] && i != col)
                    return 0;
            }
            else {
                if (ViewPlayingField[row][i] == check && i != col)
                    return 0;
            }
            if (selectionFields) {
                if (PlayingField[i][col] == PlayingField[row][col] && i != row)
                    return 0;
            }
            else {
                if (ViewPlayingField[i][col] == check && i != row)
                    return 0;
            }
        }
        return 1;
    }
    int CheckSquare(int check, int row, int col, bool selectionFields) {

        int temp1 = row / 3 * 3, temp2 = col / 3 * 3;

        for (int i = temp1; i <= temp1 + 2; i++) {
            for (int j = temp2; j <= temp2 + 2; j++) {
                if (i == row && j == col)
                    continue;
                if (selectionFields) {
                    if (PlayingField[i][j] == check)
                        return 0;
                }
                else {
                    if (ViewPlayingField[i][j] == check)
                        return 0;
                }

            }
        }
        return 1;
    }
    void Clean(int vertCoordinates) {
        for (int col = 0; col < Size; col++) {
            PlayingField[vertCoordinates][col] = 0;
        }
    }
    void CleanALL() {
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                PlayingField[i][j] = 0;
                ViewPlayingField[i][j] = 0;
                PlayerValues[i][j] = 0;
            }
        }
    }
    void TransferOfValues(bool Selection) {
        for (int row = 0; row < Size; row++) {
            for (int col = 0; col < Size; col++) {
                if (!Selection)
                    ViewPlayingField[row][col] = PlayerValues[row][col];
                else
                    ViewPlayingField[row][col] = 0;
            }
        }
    }
    void Surrender() {
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                if (!ViewPlayingField[i][j])
                    PlayerValues[i][j] = PlayingField[i][j];
            }
        }
    }
    int Counter(int number) {
        int quantity = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                if (PlayerValues[i][j] == number || ViewPlayingField[i][j] == number)
                    quantity++;
            }
        }
        return quantity;
    }
    void SetPlayingField(int i, int j, int NewValue) {
        if (!ViewPlayingField[i][j])
            PlayerValues[i][j] = NewValue;
    }
    int GetPlayingField(int i, int j) {
        return ViewPlayingField[i][j];
    }
    int GetPlayerPlayingField(int i, int j) {
        return PlayerValues[i][j];
    }
};
class Choice {
private:
    int Condition;
    int MenuID;
    int GameCoordX, GameCoordY;
    Sudoku* sudoku;
    std::string ConditionReturn;
public:
    enum ChoiceButtons {
        START = 1,
        HELP,
        EXIT,
        CHOOSINGGAMEF,
        CHOOSINGGAMES,
        EASYLEVEL,
        MEDIUMLEVEL,
        HARDLEVEL,
        CENTRALELEMENT,
        HELPMENUCONDITION
    };
    enum ChoiceMenu {
        MAINMENU = 1,
        STARTMENU,
        HELPMENU,
        GAMEMENUF,
        LEVELSELECTION,
        GAMEMENUS
    };
    Choice() {
        Condition = 1;
        MenuID = 1;
        GameCoordX = 4;
        GameCoordY = 4;
        sudoku = NULL;
    }
    ~Choice() {
        // Вызвался деструктор
    }
    std::string PrintStartMainMenu() {
        if (Condition == START)
            return " > Начать игру < ";
        else
            return "   Начать игру   ";
    }
    std::string PrintHelpMainMenu() {
        if (Condition == HELP)
            return " > Помощь < ";
        else
            return "   Помощь   ";
    }
    std::string PrintExitMainMenu() {
        if (Condition == EXIT)
            return " > Выйти < ";
        else
            return "   Выйти   ";
    }
    std::string PrintUnravelGameMenu() {
        if (Condition == CHOOSINGGAMEF)
            return " > Разгадать судоку < ";
        else
            return "   Разгадать судоку   ";
    }
    std::string PrintGuessGameMenu() {
        if (Condition == CHOOSINGGAMES)
            return " > Загадать судоку < ";
        else
            return "   Загадать судоку   ";
    }
    std::string PrintUnravelGameMenuEasy() {
        if (Condition == EASYLEVEL)
            return " > Лёгкий уровень < ";
        else
            return "   Лёгкий уровень   ";
    }
    std::string PrintUnravelGameMenuMedium() {
        if (Condition == MEDIUMLEVEL)
            return " > Средний уровень < ";
        else
            return "   Средний уровень   ";
    }
    std::string PrintUnravelGameMenuHard() {
        if (Condition == HARDLEVEL)
            return " > Сложный уровень < ";
        else
            return "   Сложный уровень   ";
    }
    void ShowSudoku() {
        sudoku->Surrender();
    }
    void CheckCorrectnessValues() {
        sudoku->CheckCorrectnessPlayerValues();
    }
    void SolveCurrentSudoku() {
        if (MenuID == GAMEMENUS) {
            sudoku->TransferOfValues(0);
            if (sudoku->CheckPlayerValuesLocation())
                sudoku->SolveSudoku();
            else {
                sudoku->TransferOfValues(1);
            }
        }
    }
    void ChangeCondition(char newCondition) {
        if (MenuID == MAINMENU && START < Condition && newCondition == 'u') {
            Condition--;
        }
        else if (MenuID == MAINMENU && Condition < EXIT && newCondition == 'd') {
            Condition++;
        }
        else if (MenuID == STARTMENU && Condition < CHOOSINGGAMES && newCondition == 'd') {
            Condition++;
        }
        else if (MenuID == STARTMENU && CHOOSINGGAMEF < Condition && newCondition == 'u') {
            Condition--;
        }
        else if (MenuID == LEVELSELECTION && EASYLEVEL < Condition && newCondition == 'u') {
            Condition--;
        }
        else if (MenuID == LEVELSELECTION && Condition < HARDLEVEL && newCondition == 'd') {
            Condition++;
        }
        else if (MenuID == GAMEMENUF && GameCoordY > 0 && newCondition == 'u' || MenuID == GAMEMENUS && GameCoordY > 0 && newCondition == 'u') {
            GameCoordY--;
        }
        else if (MenuID == GAMEMENUF && 8 > GameCoordY && newCondition == 'd' || MenuID == GAMEMENUS && 8 > GameCoordY && newCondition == 'd') {
            GameCoordY++;
        }
        else if (MenuID == GAMEMENUF && 8 > GameCoordX && newCondition == 'r' || MenuID == GAMEMENUS && 8 > GameCoordX && newCondition == 'r') {
            GameCoordX++;
        }
        else if (MenuID == GAMEMENUF && GameCoordX > 0 && newCondition == 'l' || MenuID == GAMEMENUS && GameCoordX > 0 && newCondition == 'l') {
            GameCoordX--;
        }
    }
    void ChangeConditionValue(int newCondition) {
        if (newCondition == NUM1)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 1);
        else if (newCondition == NUM2)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 2);
        else if (newCondition == NUM3)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 3);
        else if (newCondition == NUM4)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 4);
        else if (newCondition == NUM5)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 5);
        else if (newCondition == NUM6)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 6);
        else if (newCondition == NUM7)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 7);
        else if (newCondition == NUM8)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 8);
        else if (newCondition == NUM9)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 9);
        else if (newCondition == NUM0)
            sudoku->SetPlayingField(GameCoordY, GameCoordX, 0);
    }
    void ChangeCurrentMenu() {
        if (Condition == START) {
            MenuID = STARTMENU;
            Condition = CHOOSINGGAMEF;
        }
        else if (Condition == CHOOSINGGAMEF) {
            MenuID = LEVELSELECTION;
            Condition = EASYLEVEL;
        }
        else if (Condition == CHOOSINGGAMES) {
            sudoku = new Sudoku;
            MenuID = GAMEMENUS;
            Condition = CENTRALELEMENT;
        }
        else if (Condition <= HARDLEVEL && Condition >= EASYLEVEL) {
            sudoku = new Sudoku;
            sudoku->Filling();
            switch (Condition) {
            case EASYLEVEL: sudoku->ViewFieldFilling(45); break;
            case MEDIUMLEVEL: sudoku->ViewFieldFilling(35); break;
            case HARDLEVEL: sudoku->ViewFieldFilling(25); break;
            }
            MenuID = GAMEMENUF;
            Condition = CENTRALELEMENT;
        }
        else if (Condition == HELP) {
            Condition = HELPMENUCONDITION;
            MenuID = HELPMENU;
        }
        else if (Condition == EXIT) {
            exit(0);
        }
    }
    void MenuReturn() {
        if (Condition <= EXIT)
            exit(0);
        else if (Condition >= CHOOSINGGAMEF && Condition <= CHOOSINGGAMES) {
            Condition = START;
            MenuID = MAINMENU;
        }
        else if (Condition == CENTRALELEMENT && MenuID == GAMEMENUF) {
            Condition = EASYLEVEL;
            MenuID = LEVELSELECTION;
            if (sudoku != NULL)
                sudoku->~Sudoku();
        }
        else if (Condition == CENTRALELEMENT && MenuID == GAMEMENUS) {
            Condition = CHOOSINGGAMEF;
            MenuID = STARTMENU;
            if (sudoku != NULL)
                sudoku->~Sudoku();
        }
        else if (EASYLEVEL <= Condition && Condition <= HARDLEVEL) {
            Condition = CHOOSINGGAMEF;
            MenuID = STARTMENU;
        }
        else if (Condition == HELPMENUCONDITION) {
            Condition = START;
            MenuID = MAINMENU;
        }
    }
    int GetMenuID() {
        return MenuID;
    }
    int GetCoordX() {
        return GameCoordX;
    }
    int GetCoordY() {
        return GameCoordY;
    }
    int GetCondition() {
        return Condition;
    }
    friend class Interface;
};
class Interface : public Choice {
private:
    enum Colors {
        LIGHTBLUE = 11,
        BLUE = 9,
        LIGHTYELLOW = 14,
        LIGHTRED = 12,
        LIGHTGRAY = 7,
        WHITE = 15,
        MAGENTA = 13
    };

    char delimiter = 151;

    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

public:
    Interface() {
        // Вызвался конструктор
    }
    ~Interface() {
        // Вызвался деструктор
    }
    void ChangeColorChoice() {
        SetConsoleTextAttribute(H, LIGHTYELLOW);
    }
    void ChangeColorRed() {
        SetConsoleTextAttribute(H, LIGHTRED);
    }
    void ChangeColorBlue() {
        SetConsoleTextAttribute(H, BLUE);
    }
    void ChangeColorLightBlue() {
        SetConsoleTextAttribute(H, LIGHTBLUE);
    }
    void ChangeColorMagenta() {
        SetConsoleTextAttribute(H, MAGENTA);
    }
    void ChangeColorStandart() {
        SetConsoleTextAttribute(H, LIGHTGRAY);
    }
    void ChangeColorStars() {
        SetConsoleTextAttribute(H, WHITE);
    }
    void PrintStars() {
        ChangeColorStars();
        for (int i = 0; i < 8; i++) {
            if (i % 2)
                cout << "\n\n";
            for (int j = 0; j < rand() % 180 + 5; j++) {
                cout << " ";
            }
            cout << "*";
        }
        ChangeColorStandart();
    }
    void PrintMainMenu() {
        PrintStars();
        cout << "\n\n" << std::setw(45) << PrintStartMainMenu() << std::endl << std::endl <<
            std::setw(42) << PrintHelpMainMenu() << std::endl << std::endl <<
            std::setw(41) << PrintExitMainMenu();

        PrintStars();
    }
    void PrintLevelSelectionMenu() {
        PrintStars();

        cout << "\n\n" << std::setw(45) << PrintUnravelGameMenuEasy() << std::endl << std::endl <<
            std::setw(46) << PrintUnravelGameMenuMedium() << std::endl << std::endl <<
            std::setw(46) << PrintUnravelGameMenuHard();

        PrintStars();
    }
    void ChangeCurrentMenu() {
        Choice::ChangeCurrentMenu();
    }
    void CheckCorrectness() {
        Choice::CheckCorrectnessValues();
    }
    void ChangeCurrentCondition(char newCondition) {
        Choice::ChangeCondition(newCondition);
    }
    void Return() {
        Choice::MenuReturn();
    }
    void PrintGameMenu() {
        PrintStars();

        cout << "\n\n" << std::setw(50) << PrintUnravelGameMenu() << std::endl << std::endl <<
            std::setw(49) << PrintGuessGameMenu() << std::endl << std::endl;

        PrintStars();
    }
    void Result() {
        cout <<
            "\n\t     ______     ______     __         __   __   ______     _____    \n" <<
            "\t    /\\  ___\\   /\\  __ \\   /\\ \\       /\\ \\ / /  /\\  ___\\   /\\  __-.  \n" <<
            "\t    \\ \\___  \\  \\ \\ \\/\\ \\  \\ \\ \\____  \\ \\ \\'/   \\ \\  __\\   \\ \\ \\/\\ \\ \n" <<
            "\t     \\/\\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\____- \n" <<
            "\t      \\/_____/   \\/_____/   \\/_____/   \\/_/      \\/_____/   \\/____/ \n\n";
    }
    void PrintGameInterface() {
        cout << "\t       _______. __    __   _______    ______    __  ___  __    __  \n" <<
            "\t      /       ||  |  |  | |       \\  /  __  \\  |  |/  / |  |  |  | \n" <<
            "\t     |   (----`|  |  |  | |  .--.  ||  |  |  | |  '  /  |  |  |  | \n" <<
            "\t      \\   \\    |  |  |  | |  |  |  ||  |  |  | |    <   |  |  |  | \n" <<
            "\t  .----)   |   |  `--'  | |  '--'  ||  `--'  | |  .  \\  |  `--'  | \n" <<
            "\t  |_______/     \\______/  |_______/  \\______/  |__|\\__\\  \\______/  \n\n";

        cout << "\t\t\t";
        for (int i = 0; i < 39; i++)
            cout << delimiter;

        cout << "\n\t\t\t| ";
        for (int i = 0; i < Size; i++) {
            if (i == 3 || i == 6) {
                cout << "\t\t\t";
                for (int i = 0; i < 39; i++)
                    cout << delimiter;
                cout << "\n\t\t\t| ";
            }
            else if (i != 0) {
                ChangeColorStars();
                for (int f = 0, star = rand() % 18 + 3; f < 15; f++) {
                    if (f == star)
                        cout << "*";
                    else
                        cout << " ";
                }
                ChangeColorStandart();
                cout << "\t\t|---+---+---++---+---+---++---+---+---|\n \t\t\t| ";
            }
            for (int j = 0; j < Size; j++) {
                if (i != Choice::GetCoordY() || j != Choice::GetCoordX())
                    if (Choice::sudoku->GetPlayingField(Choice::GetCoordY(), Choice::GetCoordX()) == Choice::sudoku->GetPlayingField(i, j) && Choice::sudoku->GetPlayingField(Choice::GetCoordY(), Choice::GetCoordX())) {
                        ChangeColorBlue();
                        cout << Choice::sudoku->GetPlayingField(i, j);
                    }
                    else if (Choice::sudoku->GetPlayerPlayingField(Choice::GetCoordY(), Choice::GetCoordX()) == Choice::sudoku->GetPlayerPlayingField(i, j) && Choice::sudoku->GetPlayerPlayingField(Choice::GetCoordY(), Choice::GetCoordX())) {
                        ChangeColorBlue();
                        cout << Choice::sudoku->GetPlayerPlayingField(i, j);
                    }
                    else if (Choice::sudoku->GetPlayingField(i, j) == Choice::sudoku->GetPlayerPlayingField(Choice::GetCoordY(), Choice::GetCoordX()) && Choice::sudoku->GetPlayingField(i, j)) {
                        ChangeColorBlue();
                        cout << Choice::sudoku->GetPlayingField(i, j);
                    }
                    else if (Choice::sudoku->GetPlayingField(i, j)) {
                        ChangeColorRed();
                        cout << Choice::sudoku->GetPlayingField(i, j);
                    }
                    else if (Choice::sudoku->GetPlayingField(Choice::GetCoordY(), Choice::GetCoordX()) == Choice::sudoku->GetPlayerPlayingField(i, j) && Choice::sudoku->GetPlayerPlayingField(i, j)) {
                        ChangeColorBlue();
                        cout << Choice::sudoku->GetPlayerPlayingField(i, j);
                    }
                    else if (Choice::sudoku->GetPlayerPlayingField(i, j)) {
                        ChangeColorLightBlue();
                        cout << Choice::sudoku->GetPlayerPlayingField(i, j);
                    }
                    else
                        cout << " ";
                else {
                    ChangeColorChoice();
                    if (Choice::sudoku->GetPlayingField(i, j))
                        cout << Choice::sudoku->GetPlayingField(i, j);
                    else if (Choice::sudoku->GetPlayerPlayingField(i, j))
                        cout << Choice::sudoku->GetPlayerPlayingField(i, j);
                    else
                        cout << "-";
                }
                ChangeColorStandart();

                if (j == 2 || j == 5)
                    cout << " || ";
                else if (j != Size - 1)
                    cout << " | ";
                else {
                    cout << " | ";
                    for (int f = 0, star = rand() % 20 + 3; f < 20; f++) {
                        if (f == star) {
                            ChangeColorStars();
                            cout << "*";
                            ChangeColorStandart();
                        }
                        else
                            cout << " ";
                    }
                }
            }
            cout << "\n";
        }
        cout << "\t\t\t";

        for (int i = 0; i < 39; i++)
            cout << delimiter;
    }
    void PrintGameInformation() {
        cout << "\n\n\t\t           ";
        for (int Number = 1; Number <= Size; Number += 2) {
            cout << Number << " - ";
            ChangeColorMagenta();
            cout << Choice::sudoku->Counter(Number) << "  ";
            ChangeColorStandart();
        }
        cout << "\n\n\t\t              ";
        for (int Number = 2; Number <= Size; Number += 2) {
            cout << Number << " - ";
            ChangeColorMagenta();
            cout << Choice::sudoku->Counter(Number) << "  ";
            ChangeColorStandart();
        }
        cout << "\n\n\n";
    }
    void PrintHelpMenu() {
        PrintStars();
        ChangeColorMagenta();
        cout << "\n\n\t" << "UP, DOWN, LEFT, RIGHT - Передвижение по полю (стрелки)\n";
        ChangeColorChoice();
        cout << "\t" << "1-9 - Числа (подсказки), 0 - Пустое поле\n";
        ChangeColorMagenta();
        cout << "\t" << "SPACE - Открывает всё поле в режиме разгадки и очищает поле в режиме загадок\n";
        ChangeColorChoice();
        cout << "\t" << "TAB - Проверка текущих выставленных (доступно только в режиме разгадки)\n";
        ChangeColorMagenta();
        cout << "\t" << "S - Решает заданное судоку (доступно только в режиме загадывания судоку)\n";
        ChangeColorChoice();
        cout << "\t" << "BACKSPACE - Возврат в прошлое меню или выход из игры\n";
        ChangeColorMagenta();
        cout << "\t" << "ESC - Принудительное завершение игры\n\n";
        ChangeColorStandart();
        PrintStars();
    }
    void Print() {
        if (Choice::GetMenuID() == Choice::START)
            PrintMainMenu();
        else if (Choice::GetMenuID() == Choice::HELPMENU) {
            PrintHelpMenu();
        }
        else if (Choice::GetMenuID() == Choice::GAMEMENUF) {
            PrintGameInterface();
            if (Choice::sudoku->CheckResult()) {
                Result();
                return void();
            }
            PrintGameInformation();
        }
        else if (Choice::GetMenuID() == Choice::GAMEMENUS) {
            PrintGameInterface();
            if (Choice::sudoku->CheckResult() && Choice::sudoku->CheckNulls()) {
                Result();
                return void();
            }
            PrintGameInformation();
        }
        else if (Choice::GetMenuID() == Choice::STARTMENU)
            PrintGameMenu();
        else if (Choice::GetMenuID() == Choice::LEVELSELECTION)
            PrintLevelSelectionMenu();
    }
};
int main() {
    system("mode 85, 33");
    srand(time(0));

    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);

    SetConsoleOutputCP(1251);
    static const TCHAR* myTitle = TEXT("Судоку");
    SetConsoleTitle(myTitle);

    Interface SudokuInterface;
    int Key;

    SudokuInterface.PrintMainMenu();

    while (true) {
        Key = _getch();
        if (Key == ESC) {
            cout << "ESC\n";
            exit(0);
        }
        else if (Key == LEFT) {
            SudokuInterface.ChangeCondition('l');
        }
        else if (Key == RIGHT) {
            SudokuInterface.ChangeCondition('r');
        }
        else if (Key == UP) {
            SudokuInterface.ChangeCondition('u');
        }
        else if (Key == DOWN) {
            SudokuInterface.ChangeCondition('d');
        }
        else if (Key == ENTER) {
            SudokuInterface.ChangeCurrentMenu();
        }
        else if (Key == BACKSPACE) {
            SudokuInterface.Return();
        }
        else if (Key >= NUM0 && Key <= NUM9) {
            SudokuInterface.ChangeConditionValue(Key);
        }
        else if (Key == SPACE) {
            SudokuInterface.ShowSudoku();
        }
        else if (Key == TAB) {
            SudokuInterface.CheckCorrectness();
        }
        else if (Key == S) {
            SudokuInterface.SolveCurrentSudoku();
        }
        system("cls");
        SudokuInterface.Print();
    }
    cout << "\n\n\n";

    system("pause");


    return 0;
}