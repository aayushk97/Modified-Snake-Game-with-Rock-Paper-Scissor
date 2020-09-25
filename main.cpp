#include<windows.h>
#include <iostream>
#include <conio.h> //console input output for taking inputs from keyboard
#include <ctime>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
//Tail
int tailX[100], tailY[100];
int nTail; //Length of tail

void Setup(){
    gameOver = false;
    //Initially we want out snake to be at a pos in middle of map
    dir = STOP;
    x = width/2;
    y = height/2;
    //create a random no from 0 to width-1;
    fruitX = (rand() % (width-2)) + 1;
    fruitY = (rand() % (height-2)) + 1;

    //Initial Score
    score = 0;
}

void Draw(){
    //clear console window
    system("cls");
    //TOP wall
    for(int i = 0; i < width ; i++) cout <<"#";
    cout<<endl;

    for(int i = 1; i < height - 1; i++){
        for(int j = 0; j < width; j++){
            //set left and right boundary and play feild
            if(j == 0 || j == width - 1) cout<<"#";
            else if( i == y && j == x) cout<<"0"; //Head of Snake
            else if( i == fruitY && j == fruitX) cout<<"F";
            else{
                    bool print = false;
                    //Draw every Element of tail
                    for(int k = 0; k < nTail; k++){

                        if(tailX[k] == j && tailY[k] == i){
                            cout<<"o";
                            print = true;
                        }

                    }
                    if(!print) cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i = 0; i < width; i++) cout <<"#";
    cout<<endl;

    cout<<"Score: "<<score<<endl;
     cout<<fruitX<<fruitY;

}

void Input(){
    //_kbhit() returns a number if character in Keyboard is pressed
    //return 0 if nothing is pressed
    if(_kbhit()){
        //_getch() returns ascii value of key that was pressed
        switch(_getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic(){
    //Tail Logic
    int prevX =  tailX[0];
    int prevY =  tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    //for changing direction
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
        default:
            break;

    }
    //When we hit the wall
   // if(x > width || x < 0 || y > height || y < 0) gameOver = true;
    //If we want to go from right to left and bottom to top and vice versa and not stop game
    if(x >= width) x = 0;
    else if(x < 0) x = width - 1;
    if( y >= height) y = 0;
    else if( y < 0) y = height - 1;

    //Tail Hit Game Over
    for(int i = 0; i < nTail; i++){
            if(tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    //Eat The fruit and spawn it in again
    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % (width-2) + 1;
        fruitY = rand() % (height-2) + 1;
        nTail++;

    }
}

int rps(){

	system("cls");
	int rounds = 3;

    int player_score = 0, computer_score = 0;

	for(int round = 1; round <= rounds; round++){
		system("cls");
		int player_choice, computer_choice;
		cout<< "Round No:" << round <<"/"<<rounds << endl;
		cout<<"Your Score = " << player_score <<endl;
		cout<<"Computer Score =" << computer_score <<endl;
		cout<<" 1. Rock" << endl;
		cout<<" 2. Paper" << endl;
		cout<<" 3. Scissor" << endl;
		do{
			cout<<"Select your choice: ";
			cin >> player_choice;
		}while(player_choice > 3 && player_choice < 1);
		srand(time(0));
		computer_choice = (rand() % 3) + 1;

		if(player_choice == 1 && computer_choice == 3){
			cout<<"Player Win "<<endl;
			player_score++;
		}else if( player_choice == 2 && computer_choice == 1){
			cout<<"Player Win "<<endl;
			player_score++;
		}else if( player_choice == 3 && computer_choice == 2){
			cout<<"Player Win "<<endl;
			player_score++;
		}else if(player_choice == computer_choice){
			cout<<"Draw";
	 	}else{
			cout<<"Computer Win"<<endl;
			computer_score++;
		}
		cout<<"Press any key to continue..."<<endl;
		getch();
	}

	if(computer_score == player_score){
		cout<<"Game is Drawn";
		return 2;
	}else if( player_score > computer_score){
		cout<<"You won the game";
		return 1;
	}else{
		cout<<"Computer Won the Game";
		return 0;
	}
}


int main()
{
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(200);
        if(gameOver){
                system("cls");
                cout<<"Do you want to continue? Press x to exit."<<endl;
                cout<<"If you win in 2/3 rounds you get to keep your score else you start again"<<endl;
                char a;
                cin >> a;
                if( a != 'x'){

                int result = rps();
                if(result == 0) {
                    score = 0;
                    nTail = 0;
                    gameOver = false;

                }else if(result == 2){
                    score = 0;
                    nTail = 0;
                    gameOver = false;
                }else if(result == 1){
                    gameOver = false;
                    nTail = 0;
                }
            }

        }

    }

    return 0;
}
