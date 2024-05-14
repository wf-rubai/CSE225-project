#include <cstdlib>
#include <iostream>
#include "TruthTable/tableGenerator.cpp"

using namespace std;
void logo();
void loop();

int main(){
    // system("clear");
    // cin.get();
    loop();
}

void loop(){
    int n;
    do{
        system("clear");
        logo();
        cout << "What is your logic " << endl;
        cout << " 1. Solo truth-table" << endl;
        cout << " 2. Mega truth-table" << endl;
        cout << " 3. Solve my K-Map" << endl;
        cout << " 0. Quit" << endl;
        cout << endl << "Your wish? >> ";

        cin >> n;

        if(n==1){
            system("clear");
            logo();
            string str[1];
            cout << "Enter your equation: ";
            cin >> str[0];
            cout << endl << endl << "As you wish...";
            tableGenerator tg(str, 1);
        }else if(n==2){
            system("clear");
            logo();
            int nn=2;
            cout << "Enter nunber of equations: ";
            cin >> nn;
            string str[nn];
            for(int i=0; i<nn; i++){
                cout << "Enter equation no" << i+1 << ": ";
                cin >> str[i];
            }
            cout << endl << endl << "As you wish...";
            tableGenerator tg(str, nn);
        }else if(n==3){
            system("clear");
            logo();

        }
        cout << endl << endl << "Press \"Enter\" to bo back" << endl;
        cin.get( );
        cin.get( );
    }while(n != 0);
}

void logo(){
    cout << endl << endl;
    cout << "\t\t\t\t                                 ██┐" << endl;
    cout << "\t\t\t\t██┐                  ██┐         ██│" << endl;
    cout << "\t\t\t\t██│  ██████┐ ██████┐ └─┘ ██████┐ └─┘" << endl;
    cout << "\t\t\t\t██│  ██┌─██│ ██┌─██│ ██┐ ██┌───┘" << endl;
    cout << "\t\t\t\t███┐ ██████│ ██████│ ██│ ██████┐" << endl;
    cout << "\t\t\t\t└──┘ └─────┘ └───██│ └─┘  └────┘" << endl;
    cout << "\t\t\t\t             ██████│" << endl;
    cout << "\t\t\t\t             └─────┘" << endl;
    cout << endl << endl;
}
