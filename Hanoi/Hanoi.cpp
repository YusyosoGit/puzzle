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

#define NUM_PEGS    3
using namespace std;
typedef vector<char> peg;
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
        for (int j= 1; j<= PegHeight; j++) {
            if (j<= HPeg[i].size())
                cout << HPeg[i][j-1];
            else
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


// 移動ルール
void Hanoi(int nDisk, int pgFrom, int pgTo)
{
    if (nDisk == 1) {
        moveDisk(pgFrom, pgTo);
    }
    else {
        int pgRest= NUM_PEGS -pgFrom - pgTo;
        Hanoi(nDisk-1, pgFrom, pgRest);
        moveDisk(pgFrom, pgTo);
        Hanoi(nDisk-1, pgRest, pgTo);
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
        HPeg[0].push_back(
            i>=10? 'A'+i-10: '0'+i
        );
    }
           
    // メイン処理
    printPegs();
    Hanoi(nDisks, 0, 2);

    return 0;
}

#endif // HANOI_H
