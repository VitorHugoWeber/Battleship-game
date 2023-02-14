// Vitor Hugo Behlau Weber
// Battleship Game

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

void menu();

void clearScreen(){
    system("CLS");
}

void fillBoard(char board[10][10], char mask[10][10]){
    int line, column;
    for(line = 0; line < 10; line++){
        for(column = 0; column < 10; column++){
            board[line][column] = 'W';
            mask[line][column] = '*';
        }
    }
}

void printMap(){
    int counter;
    for(counter = 0; counter < 10; counter++){
        if(counter == 0){
            cout << "    ";
        }
        cout << counter << " ";
    }
    cout << "\n";

    for(counter = 0; counter < 10; counter++){
        if(counter == 0){
            cout << "    ";
        }
        cout << "| ";
    }
    cout << "\n";
}

void printBoard(char board[10][10], char mask[10][10], bool showAnswers){
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };
    int line, column;
    for(line = 0; line < 10; line++){
        cout << line << " -";
        for(column = 0; column < 10; column++){
            switch(mask[line][column]){
                case 'W':
                    cout << blue << " " << mask[line][column] << normal;
                    break;
                case 'S':
                    cout << green << " " << mask[line][column] << normal;
                    break;
                default:
                    cout << " " << mask[line][column];
                    break;
            }
        }
        cout << "\n";
    }

    if(showAnswers == true){
        for(line = 0; line < 10; line++){
            for(column = 0; column < 10; column++){
                cout << " " << board[line][column];
            }
            cout << "\n";
        }
    }
}

void placeShip(char board[10][10]){
    int amount = 5, placedAmount = 0;
    while(placedAmount < amount){
        int shipLine = rand() % 5;
        int shipColumn = rand() % 5;
        if(board[shipLine][shipColumn] == 'W'){
            board[shipLine][shipColumn] = 'S';
            placedAmount++;
        }
    }
}

void checkChoice(char board[10][10], int setLine, int setColumn, int *points, string *message){
    switch(board[setLine][setColumn]){
        case 'S':
            *points = *points + 1;
            *message = "Well done! You hit one ship!\n";
            break;
        case 'W':
            *message = "You hit the water, such a waste...\n";
    }
}

void game(string playerName){
    char board[10][10], mask[10][10];
    int line, column, setLine, setColumn, option;
    int points = 0, chances = 0, maximumChances = 15;
    string message;

    fillBoard(board, mask);
    placeShip(board);

    while(chances < maximumChances && points < 5){
        clearScreen();
        printMap();
        printBoard(board, mask, false);
        cout << "\nShips sank: " << points << " out of 5 to win the battle!\n";
        cout << "Remaining shots: " << maximumChances - chances << "\n";
        cout << message << "\n";

        setLine = -1;
        setColumn = -1;

        while((setLine < 0 || setColumn < 0) || (setLine > 9 || setColumn > 9)){
            cout << playerName << ", choose a line: ";
            cin >> setLine;
            cout << playerName << ", choose a column: ";
            cin >> setColumn;
        }
        checkChoice(board, setLine, setColumn, &points, &message);
        mask[setLine][setColumn] = board[setLine][setColumn];
        chances++;
    }

    if(points == 5){
        cout << "\nCongratulations! You won the Battleship War!\n\n";
        cout << "1 - Play again!\n";
        cout << "2 - Menu\n";
        cout << "3 - Exit\n\n";
        cin >> option;
        switch(option){
            case 1:
                game(playerName);
                break;
            case 2:
                menu();
                break;
            case 3:
                cout << "I hope you had a great time!\n";
                cout << "Goodbye!\n";
                break;
        }
    }
    else{
        cout << "\nGame Over! You lost!\n\n";
        cout << "1 - Play again!\n";
        cout << "2 - Menu\n";
        cout << "3 - Exit\n\n";
        cin >> option;
        switch(option){
            case 1:
                game(playerName);
                break;
            case 2:
                menu();
                break;
            case 3:
                cout << "I hope you had a great time!\n";
                cout << "Goodbye!\n";
                break;
            }
    }
}

void menu(){
    int option = 0;
    string playerName;

    while(option < 1 || option > 2){
        clearScreen();
        cout << "Welcome to the Battleship Game!\n";
        cout << "Type the number of the option that you want and click ENTER:\n\n";
        cout << "1 - Single Player\n";
        cout << "2 - Exit\n\n";
        cin >> option;

        switch(option){
            case 1:
                cout << "Game Started!\n";
                cout << "What is your name? ";
                cin >> playerName;
                game(playerName);
                break;
            case 2:
                cout << "I hope you had a great time!\n";
                cout << "Goodbye!\n";
                break;
        }
    }
}

int main(){
    srand((unsigned)time(NULL));
    menu();
    return 0;
}
