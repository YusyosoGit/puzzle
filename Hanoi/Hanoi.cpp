/*
 * ハノイの塔
 * 実施プログラム
 * アルゴリズム入門 p67~
 */


#ifndef HANOI_H
#define HANOI_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>

#define NUM_PEGS    3
using namespace std;
typedef vector<string> peg;
peg HPeg[NUM_PEGS];
int PegHeight;

// プリント
void printPegs()
{
    static int nPhase;
    cout << "<" << nPhase++ << ">" << endl; 
    for (int i=0; i< NUM_PEGS; i++) {
        cout << "|";
        //auto it = HPeg[i].begin();
        int j= 1;
        for (; j<= HPeg[i].size(); j++) {
            cout << HPeg[i][j-1];
        }
        cout << "\x1b[0m";
        for (; j<= PegHeight; j++) {
            cout << "-";
        }
        cout << endl;
    }
}

// 円盤の移動
void moveDisk(int pgFrom, int pgTo) {
    HPeg[pgTo].push_back(HPeg[pgFrom].back());
    HPeg[pgFrom].pop_back();

    printPegs();
}


// タワーの移動
void moveTower(int height, int pgFrom, int pgTo)
{
    if (height == 1) {
        moveDisk(pgFrom, pgTo);
    }
    else {
        int pgRest= NUM_PEGS -pgFrom - pgTo;
        moveTower(height-1, pgFrom, pgRest);
        moveDisk(pgFrom, pgTo);
        moveTower(height-1, pgRest, pgTo);
    }
}

// メイン
int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "USAGE:" << argv[0] << " ＜円盤の数＞" << endl;
        return 1;
    }
    int nDisks;
    try {
        nDisks = std::stoi(argv[1]);
        if (nDisks < 1 || 15 < nDisks) {
            cout << "out of range." << endl;
            return 1;
        }
    }
    catch (std::invalid_argument) {
        cout << "not numeric." << endl;
        return 1;
    }

    // 初期化
    PegHeight = nDisks+2;
    for (int i=nDisks; i>=1; i--) {
        string s;
        switch (i % 4) {
        case 1:
            s += "\x1b[31;1m";
            break;
        case 2:
            s += "\x1b[36;1m";
            break;
        case 3:
            s += "\x1b[32;1m";
            break;
        case 0:
            s += "\x1b[33;1m";
        }
        s = s + char(i>=10? 'A'+i-10: '0'+i);
        HPeg[0].push_back(s);
//        HPeg[0].push_back(
//            i>=10? 'A'+i-10: '0'+i
//        );
    }
           
    // メイン処理
    printPegs();
    moveTower(nDisks, 0, 2);

    return 0;
}

#endif // HANOI_H
