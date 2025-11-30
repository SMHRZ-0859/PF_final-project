#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

//COLOR FUNCTION
void setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//CLOCK 
void digital_clock() {
    setColor(11);
    printf("Press Ctrl+C to stop the clock.\n");
    setColor(7);

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        printf("\rCurrent Time: %02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
        fflush(stdout);
        Sleep(1000);
    }
}

void alarm() {
    int hour, min;

    setColor(11);
    printf("Set Alarm Time (24h format)\n");
    setColor(7);

    printf("Hour: ");
    scanf("%d", &hour);
    printf("Minute: ");
    scanf("%d", &min);

    printf("Alarm set for %02d:%02d\n", hour, min);

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        if (t->tm_hour == hour && t->tm_min == min) {
            setColor(12);
            printf("\n⏰ Alarm ringing! Time is %02d:%02d\n", hour, min);
            setColor(7);
            break;
        }
        Sleep(30000);
    }
}

void stopwatch() {
    int seconds = 0;
    char input;

    setColor(11);
    printf("Stopwatch started. Press 'q' to stop.\n");
    setColor(7);

    while (1) {
        printf("\rElapsed Time: %02d:%02d", seconds / 60, seconds % 60);
        fflush(stdout);
        Sleep(1000);
        seconds++;

        if (_kbhit()) {
            input = _getch();
            if (input == 'q' || input == 'Q') break;
        }
    }
    printf("\nStopwatch stopped.\n");
}

void clockmenu() {
    int choice;
    while (1) {
        setColor(11);
        printf("\n--- Clock, Alarm, Stopwatch ---\n");
        setColor(7);

        printf("1. Digital Clock\n2. Alarm\n3. Stopwatch\n4. Back\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: digital_clock(); break;
            case 2: alarm(); break;
            case 3: stopwatch(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}

// To do list
#define FILE_NAME "todo.txt"

void showTasks() {
    FILE *file = fopen(FILE_NAME, "r");
    char task[200];
    int index = 1;

    setColor(10);
    printf("\n------ CURRENT TO-DO LIST ------\n");
    setColor(7);

    if (!file) {
        printf("(No tasks added yet!)\n");
        return;
    }

    while (fgets(task, sizeof(task), file)) {
        if (strlen(task) > 1)
            printf("%d. %s", index, task);
        index++;
    }

    if (index == 1)
        printf("(No tasks added yet!)\n");

    fclose(file);
}

void addTask() {
    FILE *file = fopen(FILE_NAME, "a");
    char task[200];

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    setColor(10);
    printf("\nEnter task to add: ");
    setColor(7);

    getchar();
    fgets(task, sizeof(task), stdin);

    if (task[strlen(task) - 1] != '\n')
        strcat(task, "\n");

    fputs(task, file);
    fclose(file);

    printf("Task added successfully!\n");
}

void removeTask() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }

    showTasks();

    int removeIndex, index = 1;
    char task[200];

    printf("\nEnter task number to remove: ");
    scanf("%d", &removeIndex);

    while (fgets(task, sizeof(task), file)) {
        if (index != removeIndex)
            fputs(task, temp);
        index++;
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    printf("Task removed successfully!\n");
}

void todoMenu() {
    int choice;

    while (1) {
        setColor(10);
        printf("\n------ TO-DO LIST ------\n");
        setColor(7);

        printf("1. Add Task\n");
        printf("2. Remove Task\n");
        printf("3. Print To-Do List\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: removeTask(); break;
            case 3: showTasks(); break;
            case 4: return;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

// chat bot
void chatbot() {
    char input[100];
    getchar();

    setColor(13);
    printf("\nSimple Chatbot (type 'bye' to quit)\n");
    setColor(7);

    while (1) {
        printf("You: ");
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "bye") == 0) {
            printf("Bot: Goodbye!\n");
            break;
        } else if (strcmp(input, "hello") == 0) {
            printf("Bot: Hello! How can I help you?\n");
        } else if (strcmp(input, "time") == 0) {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            printf("Bot: Current time is %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
        } else {
            printf("Bot: I didn't understand that.\n");
        }
    }
}

// tic tac toe
char board[3][3];

void initBoard() {
    char ch = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ch++;
}

void displayBoard() {
    system("cls");

    setColor(3);
    printf("\nTic-Tac-Toe Game\n\n");
    setColor(7);

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {
            char c = board[i][j];

            if (c == 'X') setColor(10);   
            else if (c == 'O') setColor(12); 
            else setColor(7); 

            printf(" %c ", c);
            setColor(7); 

            if (j < 2) printf("|");
        }

        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
}


char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==board[i][1] && board[i][1]==board[i][2]) return board[i][0];
        if (board[0][i]==board[1][i] && board[1][i]==board[2][i]) return board[0][i];
    }
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2]) return board[0][0];
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]) return board[0][2];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return ' ';

    return 'D';
}

void playTicTacToe() {
    int player = 1, choice;
    char mark;

    initBoard();

    while (1) {
        displayBoard();
        player = (player % 2) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("\nPlayer %d (%c), enter your move (1-9): ", player, mark);
        scanf("%d", &choice);

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Invalid or taken cell!\n");
            Sleep(1000);
            continue;
        }

        board[row][col] = mark;
        char result = checkWinner();

        if (result == 'X' || result == 'O') {
            displayBoard();
            setColor(12);
            printf("\nPlayer %d (%c) wins!\n", player, mark);
            setColor(7);
            break;
        }
        else if (result == 'D') {
            displayBoard();
            setColor(14);
            printf("\nIt's a draw!\n");
            setColor(7);
            break;
        }

        player++;
    }

    printf("\nPress Enter to return...");
    getchar(); getchar();
}

// ---------------- MAIN MENU ----------------
void showMenu() {
    setColor(14);
    printf("\n====================================\n");
    printf("      Welcome to My Utility App     \n");
    printf("====================================\n");
    setColor(7);

    printf("1. Clock (Time, Stopwatch, Alarm)\n");
    printf("2. To-Do List\n");
    printf("3. Chat Bot\n");
    printf("4. Tic-Tac-Toe Game\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: clockmenu(); break;
            case 2: todoMenu(); break;
            case 3: chatbot(); break;
            case 4: playTicTacToe(); break;
            case 5:
                printf("\nExiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
