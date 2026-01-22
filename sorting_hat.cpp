#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <windows.h>   // For Sleep()
using namespace std;

#define MAX 20

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void enableANSI() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    mode |= 0x0004;    
    SetConsoleMode(h, mode);
}

class Queue {
    string arr[MAX];
    int front, rear;

public:
    Queue() { front = -1; rear = -1; }

    bool isFull() { return rear == MAX - 1; }
    bool isEmpty() { return (front == -1 || front > rear); }

    void enqueue(string name) {
        if (isFull()) {
            cout << "Queue is full! Cannot add more students.\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = name;
    }

    string dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return "";
        }
        return arr[front++];
    }
};

struct Question {
    string text;
    string options[4];
};

void hatThinkingAnimation(string student) {
    cout << "\nSorting Hat is placed on " << student << "'s head...\n";
    cout << "The hat is thinking";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        cout.flush();
        Sleep(600);
    }
    cout << "\nThe Hat awakens magically...\n";
    Sleep(1000);
    cout << "Magical energy fills the hall as the quiz begins! \n\n";
    Sleep(800);
}

void showHouseResult(string house) {
    cout << "\n--------------------------------------------\n";

    if (house == "Gryffindor") {
        cout << RED << BOLD;
        cout << "  " << house << "  \n";
        cout << "\"Their daring, nerve and chivalry set Gryffindors apart!\"\n";
    }
    else if (house == "Slytherin") {
        cout << GREEN << BOLD;
        cout << "  " << house << "  \n";
        cout << "\"Those cunning folk use any means to achieve their ends.\"\n";
    }
    else if (house == "Ravenclaw") {
        cout << BLUE << BOLD;
        cout << "  " << house << "  \n";
        cout << "\"Wit beyond measure is man's greatest treasure.\"\n";
    }
    else if (house == "Hufflepuff") {
        cout << YELLOW << BOLD;
        cout << "  " << house << "  \n";
        cout << "\"Those patient Hufflepuffs are true and unafraid of toil.\"\n";
    }

    cout << RESET;
    cout << "--------------------------------------------\n";
}

// Sorting Quiz
string sortingQuiz(string student, vector<Question> &questions) {
    int gryffindor = 0, slytherin = 0, ravenclaw = 0, hufflepuff = 0;

    hatThinkingAnimation(student);

    // Randomize questions
    vector<int> qIndex(questions.size());
    for (int i = 0; i < questions.size(); i++) qIndex[i] = i;

    shuffle(qIndex.begin(), qIndex.end(), mt19937(random_device{}()));

    for (int i = 0; i < 5; i++) {
        int qNum = qIndex[i];

        cout << MAGENTA << BOLD;
        cout << "Q" << i + 1 << ". " << questions[qNum].text << RESET << endl;

        for (int j = 0; j < 4; j++)
            cout << j + 1 << ". " << questions[qNum].options[j] << endl;

        int choice;
        while (true) {
            cout << CYAN << "Your choice: " << RESET;
            if (cin >> choice && choice >= 1 && choice <= 4) break;

            cout << RED << "Enter a valid number (1-4)!\n" << RESET;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1: gryffindor++; break;
            case 2: slytherin++; break;
            case 3: ravenclaw++; break;
            case 4: hufflepuff++; break;
        }

        cout << "--------------------------------------------\n";
    }

    cout << "\n The Sorting Hat is deciding your fate";
    for (int i = 0; i < 4; i++) {
        cout << ".";
        cout.flush();
        Sleep(500);
    }
    cout << "\n";
    Sleep(700);

    if (gryffindor >= slytherin && gryffindor >= ravenclaw && gryffindor >= hufflepuff)
        return "Gryffindor";
    else if (slytherin >= gryffindor && slytherin >= ravenclaw && slytherin >= hufflepuff)
        return "Slytherin";
    else if (ravenclaw >= gryffindor && ravenclaw >= slytherin && ravenclaw >= hufflepuff)
        return "Ravenclaw";
    else
        return "Hufflepuff";
}

int main() {
    enableANSI();
    srand(time(0));
    Queue q;

    cout << BOLD << "----------------------------------------------\n";
    cout << "   Welcome to the HOGWARTS SORTING CEREMONY \n";
    cout << "----------------------------------------------\n\n" << RESET;

    int n;
    cout << "Enter number of students: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string name;
        cout << "Enter name of student " << i + 1 << ": ";
        getline(cin, name);
        q.enqueue(name);
    }

    vector<Question> questions = {
        {"What quality do you value most?", {"Bravery", "Ambition", "Wisdom", "Loyalty"}},
        {"Choose your favorite magical creature:", {"Phoenix", "Basilisk", "Eagle", "Niffler"}},
        {"What would you do if you found a secret spellbook?", {"Use it for good", "Use it for power", "Study it deeply", "Keep it safe"}},
        {"Which subject do you prefer at Hogwarts?", {"Defense Against Dark Arts", "Potions", "Charms", "Herbology"}},
        {"How do you handle challenges?", {"Face them head-on", "Outsmart them", "Plan carefully", "Stay calm and kind"}},
        {"Choose your magical object:", {"Sword of Gryffindor", "Locket of Slytherin", "Diadem of Ravenclaw", "Cup of Hufflepuff"}},
        {"Which founder inspires you the most?", {"Godric Gryffindor", "Salazar Slytherin", "Rowena Ravenclaw", "Helga Hufflepuff"}},
        {"What’s your ideal weekend?", {"Adventure with friends", "Planning your future", "Reading books", "Helping others"}},
        {"Your friend is in trouble. You will:", {"Protect them immediately", "Use strategy", "Seek help", "Stay by their side"}},
        {"What would you rather be known for?", {"Courage", "Influence", "Knowledge", "Kindness"}}
    };

    cout << "\n The Sorting Ceremony will now begin! \n";
    Sleep(800);

    while (!q.isEmpty()) {
        string student = q.dequeue();
        string house = sortingQuiz(student, questions);
        cout << "\n " << student << " has been sorted into ";
        showHouseResult(house);
        Sleep(1000);
    }

    cout << "\n All students have been sorted! Welcome to Hogwarts!\n\n";
    return 0;
}
