#include "sudokuSolver.h"

int const N = 9;
int const n = 3; // root of N

void printBoard(vector<vector<int> > board){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
}

bool checkRow(vector<vector<int> > board){
    for(int i = 0; i < N; i++){
        // create array
        int arr[N] {};
        for(int j = 0; j<N; j++) arr[j] = board[i][j];

        //eval array
        sort(arr,arr+N);
        for(int j = 1; j < N; j++){
            if(arr[j] == 0) continue;
            if(arr[j] == arr[j-1]) return false;
        }
    } return true;
}

bool checkCol(vector<vector<int> > board){
    for(int i = 0; i < N; i++){
        // create array
        int arr[N] {};
        for(int j = 0; j<N; j++) arr[j] = board[j][i]; 

        //eval array
        sort(arr,arr+N);

        for(int j = 1; j < N; j++){
            if(arr[j] == 0) continue;
            if(arr[j] == arr[j-1]) return false;
        }
    } return true;
}

bool checkBox(vector<vector<int> > board){
    for(int i = 0; i < N; i++){
        int arr[N];
        for(int j = 0; j < N; j++) arr[j] = board[((i/n)*n) + (j/n)][((i % n) * n) + (j%n)];

        sort(arr,arr+N);
        for(int j = 1; j < N; j++){
            if(arr[j] == 0) continue;
            if(arr[j] == arr[j-1]) return false;
        }
    } return true;
}

bool checkBoard(vector<vector<int> > board){
    if(checkRow(board) && checkCol(board) && checkBox(board)) return true;
    else return false; 
}

int findNextSpace(vector<vector<int> > board){
    for(int i = 0; i < N*N; i++) {
        if(board[i/N][i%N] == 0) return i;
    } 
    return -1;
}

void insertBoard(vector<vector<int> > &board, int index, int value){
    board[index/N].at(index%N) = value;
}

bool canInsertBoard(vector<vector<int> > board, int nextAvailableSpace, int value ){
    insertBoard(board, nextAvailableSpace, value);
    if(checkBoard(board)) return true;
    else return false;
}


bool solveBoard(vector<vector<int> > &board){
    int nextAvailableSpace = findNextSpace(board);
    if(nextAvailableSpace == -1) return true;
    for(int i = 1; i <=N; i++){
        if(canInsertBoard(board,nextAvailableSpace,i)){ // checks to see if i will work in the space
            insertBoard(board,nextAvailableSpace,i); // if it worked than it will put it in the space
            if(solveBoard(board)) return true; // recursively calls to the next space and it will now be at the next open space since you just inserted
            else insertBoard(board, nextAvailableSpace, 0); // undoes the previous insert if it turns out down the line to be false, allows it to go to the next i
        }
    }return false;
}

int main(){

    vector<vector<int> > board(N);

    // input into board
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int input;
            cin >> input;
            if(input >= 0 && input<= N) board[i].push_back(input);
            else{
                cout << "Invalid Input";
                return -1;
            }
        }
    }
    cout << endl;
    cout << "PRE SOLVED BOARD: \n";
    printBoard(board);
    cout << "\n\n\n";
    if(solveBoard(board)){
        cout << "POST SOLVE: \n";
        printBoard(board);
    }
    else{
        cout << "Unsolvable!!";
    }
    
    
}

// 0  0  0  0  0  0  2  0  1
// 0  1  0  0  0  0  0  0  0  
// 0  4  5  0  0  0  0  0  0  
// 0  0  0  0  0  0  9  2  0  
// 0  3  2  9  0  0  0  0  0  
// 0  0  0  0  0  0  0  0  8  
// 0  0  0  0  0  0  1  1  0  
// 0  2  7  3  0  0  0  0  0  
// 4  0  0  0  0  0  0  0  6
