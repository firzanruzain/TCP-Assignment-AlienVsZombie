#include <iostream>
using namespace std;

int main(){
    cout << "Do you wish to change game settings? (y/n)? => ";
        char option;
        cin >> option;

        if (option == 'y'){
            int rows,cols,zombies;
            cout << "\n\n";

            rowsEven:
                cout << "Board Rows    : ";
                cin >> rows;
                cout << endl;
                if (rows % 2 == 0){
                    cout << "Use odd number only!!!\n";
                    goto rowsEven;  
                }
}
}