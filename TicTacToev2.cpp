

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

class Game {
public:
    int ifWin = 0;
    int x, y;
    int symbol_place =  0;
    int symbol_choice;
    int taken_place = 0;
    string symbol, enemy_symbol, winner;
    string board[5][5] = { {"-", " - ", " - "," - ","-"},               //tablica do gry
    {"|", " _ ", " _ "," _ ","|"},
    {"|", " _ ", " _ "," _ ","|"},
    {"|", " _ ", " _ "," _ ","|"},
    {"-", " - ", " - "," - ","-"},
    };
    int getXcords() {                          //gettery, settery dla zmiennych klasy
        return x;
    }
    int getYcords() {
        return y;
    }
    void setXcords(int x) {
        this->x = x;
    }
    void setYcords(int y) {
        this->y = y;
    }
    int getTakenPlace() {
        return taken_place;
    }
    string getWinner() {
        return winner;
    }
    void setWinner(string winner) {
        this->winner = winner;
    }
    void setTakenPlace(int taken_place) {
        this->taken_place = taken_place;
    }
    string getBoard() {
         return board[x][y];
    }
    void setBoard(string board[5][5]) {
        this->board[x][y] = board[x][y];
    }
    string getSymbol() {
        return symbol;
    }
    void setSymbol(string symbol) {
        this->symbol = symbol;
    }
    string getEnemySymbol() {
        return enemy_symbol;
    }
    void setEnemySymbol(string enemy_symbol) {
        this->enemy_symbol = enemy_symbol;
    }
    int getIfWin() {
        return ifWin;
    }
    void setIfWin(int ifWin) {
        this->ifWin = ifWin;
    }
    string createBoard() {                                     //funkcja tworzaca tablice
        for (int x = 0; x <= 4; x++) {
            cout << endl;
            for (int y = 0; y <= 4; y++) {
                cout << board[x][y];
         }
      }
        cout << endl;
        return board[x][y];
    }
    string clearBoard() {
        for (int x = 1; x <= 3; x++) {
            cout << endl;
            for (int y = 1; y <= 3; y++) {
                board[x][y] = " _ ";
            }
        }
        return board[x][y];
    }
    string chooseSymbol() {
        while (true) {
            system("cls");                       //funkcja pozwalajaca na wybor znaku, ktorym bedzie gral gracz.
            cout << "Prosze wybrac symbol!" << endl;
            cout << "1. X" << endl;
            cout << "2. O" << endl;
            if (!(cin >> symbol_choice) || (symbol_choice <=0) || (symbol_choice>=3)) {                                //obsluga bledu, w wypadku nienapotkanego problemu.
                cin.clear();
                cin.ignore();
                cout << "Przy wyborze opcji, wystapil blad, prosze nacisnac jakikolwiek przycisk, i wybrac opcje ponownie." << endl;
                getchar(); getchar();
                system("cls");
                continue;
            }
            break;
        }
        switch (symbol_choice) {
        case 1:
            symbol = " X ";
            setSymbol(symbol);
            enemy_symbol = " O ";
            setEnemySymbol(enemy_symbol);
            break;
        case 2:
            symbol = " O ";
            setSymbol(symbol);
            enemy_symbol = " X ";
            setEnemySymbol(enemy_symbol);
            break;
        }
        return getSymbol();
    }
    string setSignOnBoard() {
            while (true) {                   //Funkcja pozwalajaca na zapisanie znaku na planszy.
                cout << "Prosze podac wspolrzedne, gdzie polozyc znak od 1-3, w rzedzie, oraz w kolumnie." << endl;
                cout << "Przykladowe wspolrzedne: 2 2" << endl;
                if (!(cin >> x >> y) && ((x <= 0 || x>4)) || (y<=0 || y>4)) {
                    system("cls");                            //obsluga bledu, w wypadku nienapotkanego problemu.
                    cin.clear();
                    cin.ignore();
                    cout << "Przy wyborze opcji, wystapil blad, prosze nacisnac jakikolwiek przycisk, i wybrac opcje ponownie." << endl;
                    getchar(); 
                    system("cls");
                    continue;
                }
                setXcords(x);
                setYcords(y);
                if ((board[getXcords()][getYcords()] == getSymbol()) || (board[getXcords()][getYcords()] == getEnemySymbol())) {
                    system("cls");
                    cout << "Dane miejsce jest juz zajete, prosze wybrac dane ponownie!" << endl;
                    cout << "Prosze nacisnac jakikolwiek przycisk..." << endl;
                    getchar(); getchar();
                    continue;
                }
                break;
            }
        board[getXcords()][getYcords()] = getSymbol();
        checkIfWin();
        checkIfDraw();
        if (getIfWin() >= 1) {
            system("cls");
            return getSymbol();
        }
        return getSymbol();
    }
    string setEnemySignOnBoard() {
        srand(time(NULL));
        while (true) {
            x = rand() % 3 + 1;
            y = rand() % 3 + 1;
            setXcords(x);
            setYcords(y);
            if ((board[getXcords()][getYcords()] == getEnemySymbol()) || (board[getXcords()][getYcords()] == getSymbol())) {
                continue;
            }
            else {
                break;
            }
        }
        board[getXcords()][getYcords()] = getEnemySymbol();
        checkIfWin();
        checkIfDraw();
        if (getIfWin() >= 1) {
            system("cls");
            return getEnemySymbol();
        }
        return getEnemySymbol();
    } 

    int checkIfDraw() {
        for (int x = 1; x <= 3; x++) {
            for (int y = 1; y <= 3; y++) {
                if ((board[x][y] == getSymbol() || board[x][y] == getEnemySymbol())) {
                    taken_place++;
                    setTakenPlace(taken_place);
                    cout << taken_place << endl;
                } if (taken_place == 9) {
                    return taken_place;
                }
            }
        }
        taken_place = 0;
        return taken_place;
    }

    string checkIfWin() {                                          //funckja sprawdzajaca, czy gracz lub komputer wygrali runde poprzez sprawdzenie wszystkich mozliwosci wygranej.
        for (int i = 1; i <= 4; i++) {
            if (board[i][1] == getSymbol() && board[i][2] == getSymbol() && board[i][3] == getSymbol()) {
                createBoard();
                cout << "Wygral gracz o znaku : " << getSymbol() << endl;
                cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
                getchar(); getchar();
                ifWin++;
                setIfWin(ifWin);
                system("cls");
                setWinner(getSymbol());
                return getSymbol();
            }
        }
        for (int i = 1; i <= 4; i++) {
            if (board[i][1] == getEnemySymbol() && board[i][2] == getEnemySymbol() && board[i][3] == getEnemySymbol()) {
                createBoard();
                cout << "Wygral gracz o znaku : " << getEnemySymbol() << endl;
                cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
                getchar(); getchar();
                ifWin++;
                setIfWin(ifWin);
                system("cls");
                setWinner(getEnemySymbol());
                return getSymbol();
            }
        }

        for (int z = 1; z <= 4; z++) {
            if (board[1][z] == getSymbol() && board[2][z] == getSymbol() && board[3][z] == getSymbol()) {
                createBoard();
                cout << "Wygral gracz o znaku : " << getSymbol() << endl;
                cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
                getchar(); getchar();
                ifWin++;
                setIfWin(ifWin);
                system("cls");
                setWinner(getSymbol());
                return getSymbol();
            }
        }
        for (int z = 1; z <= 4; z++) {
            if (board[1][z] == getEnemySymbol() && board[2][z] == getEnemySymbol() && board[3][z] == getEnemySymbol()) {
                createBoard();
                cout << "Wygral gracz o znaku : " << getEnemySymbol() << endl;
                cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
                getchar(); getchar();
                ifWin++;
                setIfWin(ifWin);
                system("cls");
                setWinner(getEnemySymbol());
                return getEnemySymbol();
            }
        }
        if (board[1][1] == getSymbol() && board[2][2] == getSymbol() && board[3][3] == getSymbol()) {
            createBoard();
            cout << "Wygral gracz o znaku : " << getSymbol() << endl;
            cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
            getchar(); getchar();
            ifWin++;
            setIfWin(ifWin);
            system("cls");
            setWinner(getSymbol());
            return getEnemySymbol();
        }
        if (board[1][1] == getEnemySymbol() && board[2][2] == getEnemySymbol() && board[3][3] == getEnemySymbol()) {
            createBoard();
            cout << "Wygral gracz o znaku : " << getEnemySymbol() << endl;
            cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
            getchar(); getchar();
            ifWin++;
            setIfWin(ifWin);
            system("cls");
            setWinner(getEnemySymbol());
            return getEnemySymbol();
        }
        if (board[1][3] == getSymbol() && board[2][2] == getSymbol() && board[3][1] == getSymbol()) {
            createBoard();
            cout << "Wygral gracz o znaku : " << getSymbol() << endl;
            cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
            getchar(); getchar();
            ifWin++;
            setIfWin(ifWin);
            system("cls");
            setWinner(getSymbol());
            return getSymbol();
        }
        if (board[1][3] == getEnemySymbol() && board[2][2] == getEnemySymbol() && board[3][1] == getEnemySymbol()) {
            createBoard();
            cout << "Wygral gracz o znaku : " << getEnemySymbol() << endl;
            cout << "Prosze nacisnac jakikolwiek przycisk... " << endl;
            getchar(); getchar();
            ifWin++;
            setIfWin(ifWin);
            system("cls");
            setWinner(getEnemySymbol());
            return getEnemySymbol();
           
        }

        return getSymbol();
    }
};


int main()
{   
    string board[5][5] = { {"-", " - ", " - "," - ","-"},               //tablica do gry
    {"|", " _ ", " _ "," _ ","|"},
    {"|", " _ ", " _ "," _ ","|"},
    {"|", " _ ", " _ "," _ ","|"},
    {"-", " - ", " - "," - ","-"},
    };
        int lineNumber = 1;
        int gameNumber = 1;
        int choice2;
        string linia;
        fstream plik, plik2;                                      //obiekt pliku
        Game g;              //obiekt klasy
        int choice;
        while (true) {
            cout << "Witaj, prosze wybrac jedna z nastepujacych opcji." << endl;              //menu
            cout << "1. Nowa gra." << endl;
            cout << "2. Tabela wynikow." << endl;
            cout << "3. Wyjscie" << endl;
            if (!(cin >> choice) || (choice <= 0) || (choice >= 4)) {                                //obsluga bledu, w wypadku nienapotkanego problemu.
                cin.clear();
                cin.ignore();
                cout << "Przy wyborze opcji, wystapil blad, prosze nacisnac jakikolwiek przycisk, i wybrac opcje ponownie." << endl;
                getchar();
                system("cls");
                continue;
            }
            switch (choice) {
            case 1:
                g.chooseSymbol();
                while (true) {
                    system("cls");
                    cout << "WARTOSC IFWIN: " << g.getIfWin() << endl;

                    if (g.getIfWin() >= 1) {
                        system("cls");
                        break;
                    }
                    if (g.getTakenPlace() == 9) {
                        system("cls");
                        cout << "REMIS" << endl;
                        g.setWinner("REMIS");
                        g.createBoard();
                        break;
                    }
                    g.setSignOnBoard();
                    if (g.getIfWin() >= 1) {
                        system("cls");
                        break;
                    }
                    if (g.getTakenPlace() == 9) {
                        system("cls");
                        cout << "REMIS" << endl;
                        g.setWinner("REMIS");
                        g.createBoard();
                        break;
                    }
                    g.createBoard();
                    g.setEnemySignOnBoard();
                    if (g.getIfWin() >= 1) {
                        system("cls");
                        break;
                    }
                    if (g.getTakenPlace() == 9) {
                        system("cls");
                        cout << "REMIS" << endl;
                        g.createBoard();
                        g.setWinner("REMIS");
                        break;
                    }
                    cout << "Przeciwnik wykonal ruch!" << endl;
                    g.createBoard();
                    cout << "Prosze nacisnac jakikolwiek przycisk..." << endl;
                    getchar(); getchar();
                    system("cls");
                }
                g.setTakenPlace(0);
                g.setIfWin(0);
                cout << "Prosze nacisnac jakikolwiek przycisk..." << endl;
                getchar(); getchar();
                system("cls");
                plik.open("gry.txt", ios::out | ios::app);
                for (int x = 0; x <= 4; x++) {
                    plik << endl;
                    for (int y = 0; y <= 4; y++) {
                        g.setXcords(x);
                        g.setYcords(y);
                        board[x][y] = g.getBoard();
                        plik << board[x][y];
                    }
                }
                plik << endl;
                plik << "Znak gracza: " << g.getSymbol() << endl;
                plik << "Znak przeciwnika: " << g.getEnemySymbol() << endl;
                plik << "Zwyciezca: " << g.getWinner() << endl;
                plik.close();
                g.clearBoard();
                break;
            case 2:
                system("cls");
                plik2.open("gry.txt", ios::in); // opcja pokazujaca historie gier.
                while (!plik2.eof()) {
                    getline(plik2, linia);
                    cout << linia << endl;
                }
                plik2.close();
                cout << "Czy chcialbys usunac zawartosc pliku? " << endl;
                cout << "1. Tak" << endl;
                cout << "2. Nie" << endl;
                if (!((cin >> choice2)) || !(choice2 == 1 || choice2 == 2)) {                                //obsluga bledu, w wypadku nienapotkanego problemu.
                    cin.clear();
                    cin.ignore();
                    cout << "Przy wyborze opcji, wystapil blad, prosze nacisnac jakikolwiek przycisk, i wybrac opcje ponownie." << endl;
                    getchar();
                    system("cls");
                    continue;
                }
                switch (choice2) {
                case 1:
                    remove("gry.txt");
                    cout << "Zawartosc pliku zostala usunieta, prosze kliknac jakikolwiek przycisk, aby wrocic z powrotem do menu." << endl;
                    getchar(); getchar();
                    system("cls");
                    break;
                case 2:
                    break;
                }

                break;
            case 3:
                exit(0);
            }
        }
}






//TO DO: 
// MOZLIWOSC SORTOWANIA TABELI WYNIKOW W ZALENZNOSCI, OD CZASU GRY, NUMERU GRY ZAGRANEJ NA TYM URZADZENIU, ZNAKU, ORAZ ILOSCI ZAZNACZONYCH ZNAKOW PODCZAS GRY.
// USUN MOZLIWOSC WYPISYWANIA ZNAKOW BIALYCH PODCZAS POBIERANIA DANYCH OD UZYTKOWNIKA


