#include <cstdlib>
#include <iostream>
#include "TruthTable/tableGenerator.cpp"
#include "kMap/mapGenerator.cpp"

using namespace std;
void logo();
void loop();

int main(){
    // loop();
    mapGenerator map("1,2,4,6,8,9,11,13,15");
}

void loop(){
    int n;
    do{
        system("clear");
        logo();
        cout << "What is your logic " << endl;
        cout << " 1. Solo Truth-Table" << endl;
        cout << " 2. Mega Truth-Table" << endl;
        cout << " 3. Fint My Logic" << endl;
        cout << " 4. Solve my Experession" << endl;
        cout << " 0. Quit" << endl;
        cout << endl << "Your wish? >> ";

        cin >> n;

        if(n==1){
            system("clear");
            logo();
            string str[1];
            cout << "Enter your equation: ";
            cin >> str[0];
            cout << endl << endl << "As you wish..." << endl << endl;
            tableGenerator tg(str, 1);
            cout << endl << endl << "Press \"Enter\" to bo back" << endl;
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
            cout << endl << endl << "As you wish..." << endl << endl;
            tableGenerator tg(str, nn);
            cout << endl << endl << "Press \"Enter\" to bo back" << endl;
        }else if(n==3){
            system("clear");
            logo();

            cout << endl << endl << "Press \"Enter\" to bo back" << endl;
        }else if(n==4){
            system("clear");
            logo();

            cout << endl << endl << "Press \"Enter\" to bo back" << endl;
        }
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
