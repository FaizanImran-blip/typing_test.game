#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

class Game {
public:
    int ag;
    string nam;

    Game(int age, string name) : ag(age), nam(name) {}

    void showMenu() {
        cout << "\nYOUR NAME OR AGE HAS BEEN SELECTED\n";
        cout << "----------------------------------\n";
        cout << "Name: " << nam << "\n";
        cout << "Age: " << ag << "\n";
        cout << "TOTAL GAME LEVELS ARE: 10\n";
        cout << "Use UP/DOWN arrow keys, Enter to select mode\n\n";
    }

    void updateTimer(int remaining) {
        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        
        int min = remaining / 60;
        int sec = remaining % 60;
        cout << "⏱ [";
        if (min < 10) cout << "0";
        cout << min << ":";
        if (sec < 10) cout << "0";
        cout << sec << "]" << flush;
    }

    void startTypingChallenge(int selectedMode) {
        vector<string> EASY = {
            "Faizan is a very good software engineer.",
            "My name is Faizan. I am a software engineer.",
            "Never give up. Keep going."
        };
        vector<string> MEDIUM = {
            "Faizan investigates various tools based on project needs.",
            "I consistently deliver excellent work with passion.",
            "Never surrender. Resilience is the key to rising again."
        };
        vector<string> HARD = {
            "Faizan delves into multifaceted tools for complex projects.",
            "Dedicated software engineers strive for exceptional growth.",
            "Unwavering tenacity paves the path toward triumph."
        };

        vector<string> selectedList;
        if (selectedMode == 0) selectedList = EASY;
        else if (selectedMode == 1) selectedList = MEDIUM;
        else selectedList = HARD;

        int randomIndex = rand() % selectedList.size();
        string sentenceToType = selectedList[randomIndex];

        system("cls");
        cout << "⏱ [10:00]\n";  // Initial timer display
        cout << "\nType this sentence below before time runs out:\n";
        cout<<"COME ON "<<nam<<" you can do it"<<endl;
        cout << "\"" << sentenceToType << "\"\n\n";
        cout << "You typed: " << flush; // Prompt for user input

        string userInput = "";
        int timeLimit = 10;
        time_t startTime = time(0);
        COORD inputPos;
        inputPos.X = 11; // "You typed: " is 11 characters
        inputPos.Y = 5;  // Move to the line below the prompt

        while (true) {
            time_t now = time(0);
            int elapsed = now - startTime;
            int remaining = timeLimit - elapsed;

            if (remaining <= 0) {
                updateTimer(0);
                cout << "\n\n⛔ Time's up! You didn't finish in time.\n";
                cout << "SORRY "<<nam<<" Game Over!\n";
                return;
            }

            updateTimer(remaining);

            if (_kbhit()) {
                char ch = _getch();
                if (ch == 13) break; // Enter key to finish input
                else if (ch == 8 && !userInput.empty()) { // Backspace
                    userInput.pop_back();
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inputPos);
                    cout << userInput << " " << flush; // Clear last character
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inputPos);
                }
                else {
                    userInput += ch;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inputPos);
                    cout << userInput << flush;
                }
            }

            Sleep(100);
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 7}); // Move cursor down for result
        if (userInput == sentenceToType) {
            cout << "\nCorrect! You typed in time.\nYou Win!\n";
        } else {
            cout << "\nTyping incorrect!\nGame Over!\n";
        }
    }
};

int selectGameMode(const vector<string>& modes) {
    int selected = 0;
    while (true) {
        system("cls");
        cout << "Select Game Mode (Use UP/DOWN arrow keys, Press Enter to choose):\n\n";

        for (int i = 0; i < modes.size(); i++) {
            if (i == selected)
                cout << "-> " << modes[i] << "\n";
            else
                cout << "   " << modes[i] << "\n";
        }

        char key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == 72) {
                selected = (selected - 1 + modes.size()) % modes.size();
            } else if (key == 80) {
                selected = (selected + 1) % modes.size();
            }
        } else if (key == 13) {
            return selected;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int age;
    string name;

    cout << "ENTER YOUR NAME: ";
    getline(cin, name);

    cout << "ENTER YOUR AGE: ";
    cin >> age;

    Game g(age, name);
    g.showMenu();

    vector<string> modes = {"EASY", "MEDIUM", "HARD"};
    int selectedIndex = selectGameMode(modes);

    g.startTypingChallenge(selectedIndex);

    return 0;
}
