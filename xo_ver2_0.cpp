#include<bits/stdc++.h>
#include<conio.h>
#include"windows.h"
using namespace std;
//--------------variables---------
int console_width = 158, console_height = 39;
int line;
int n = 11;
int h_menu = 6, w_menu = 30;
int h_map = 23, w_map = 67;
int col_op1, col_op2;
int row_op1, row_op2;
int line_at;
int op_choose;
int xcur= console_width/2 - w_map/2 + 3, ycur= 11;
int save_xcur_start = xcur, save_ycur_start = ycur;
int input_x = 0, input_y = 0;
string value[11][11];
string player = "X";
string m = "Menu";
string op1 = "Nguoi voi nguoi";
string op2 = "Nguoi voi may";
string PAUSE = "Press any key to continue . . . ";
string quit = "Ban da dung tro choi!!!";
string tmp = "Nhan q de dung tro choi";
string tmp_menu = "Nhan m de quay ve menu";
string Xwin = "Tro choi da ket thuc!! Nguoi chien thang la X";
string Owin = "Tro choi da ket thuc!! Nguoi chien thang la O";
string str_x, str_y, str_main, str_anti;
string str_x1, str_y1, str_main1, str_anti1;
string str_x2, str_y2, str_main2, str_anti2;

bool op_enter = false;
bool input_enter = false;
bool check_first = false;
bool check_map = false;
bool gameover = false;

vector<pair<int,int>>Xpos;
vector<pair<int,int>>Opos;

char control = ' ';
char input_ctrl;

//---------set up value-------------
void setupvalue();

//--------------function----------
bool check_ans();
void change();
void title();
void menu();
void op_control();
void input_control();
void drawMap();
void gotoXY(short x, short y);
int whereX();
int whereY();
void makeString(int x, int y);
void bot_pos();
void bot_turn();

void play1();
void play2();


//-----------main---------------
int main (){
    while(control != 'q'){
        setupvalue();
        line = 3;
        system("cls");
        title();
        menu();
        while(!op_enter){
            op_control();
            if(control == 'q'){
                return 0;
            }
        }
        op_enter = false;
        control = 'a';
        input_ctrl = 'a';
        switch(op_choose){
            case 1:{
                xcur = save_xcur_start;
                ycur = save_ycur_start;
                input_x = 0, input_y = 0;
                play1();
                if(gameover){
                    op_choose = 0;
                    break;
                }
                if(input_ctrl == 'q'){
                    return 0;
                }
                else if(input_ctrl == 'm'){
                    op_choose = 0;
                    break;
                }
            }
            case 2:{
                xcur = save_xcur_start;
                ycur = save_ycur_start;
                input_x = 0, input_y = 0;
                play2();
                if(gameover){
                    op_choose = 0;
                    break;
                }
                if(input_ctrl == 'q'){
                    return 0;
                }
                else if(input_ctrl == 'm'){
                    op_choose = 0;
                    break;
                }
            }
        }
    }
    
    system("pause");
}

//----------function--------------
void setupvalue(){
    for(int i=0; i<11; i++){
        for(int j=0; j<11; j++){
            value[i][j] = " ";
        }
    }
}
void change(){
    if(player == "X") player="O";
    else player ="X";
}
void title(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(posAt, 2);
    string x = "_______ __ __ __ ____ ______ ______   ";
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<"_______ ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"__ ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"__ ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"__ ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"____ ";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"______ ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"______   "<<endl;
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<" _      ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"\\ \\  / /     ";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"/  __  \\      ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"\\  "<<endl;
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<"  _      ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"\\ \\/ /     ";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"|  /  \\  |      ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"\\ "<<endl;
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<"   _      ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"\\  /      ";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"|  |  |  |       ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"\\"<<endl;
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<"    _     ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"/  \\      ";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"|  |  |  |       ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"/ "<<endl;
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<"     _   ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"/ /\\ \\     ";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"|  \\__/  |      ";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"/  "<<endl;
    gotoXY(console_width/2 - (x.size())/2, line++);
    cout<<"      _ ";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"/_/";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"__";
    SetConsoleTextAttribute(posAt, 9);
    cout<<"\\_\\";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"_____";
    SetConsoleTextAttribute(posAt, 4);
    cout<<"\\______/";
    SetConsoleTextAttribute(posAt, 2);
    cout<<"______/   "<<endl;
    SetConsoleTextAttribute(posAt, 7);
    line += 2;
}
void menu(){
    xcur = save_xcur_start, ycur = save_ycur_start;
    input_x = 0, input_y = 0;
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    char c;
    for(int i=1; i<=h_menu; i++){
        gotoXY(console_width/2 - w_menu/2, line++);
        for(int j=1; j<=w_menu; j++){
            if(i==1){
                if(j==1){
                    c = 201;cout<<c;
                }else if(j==w_menu){
                    c = 187;cout<<c;
                }else{
                    c = 205;cout<<c;
                }
            }else if(i==3){
                if(j==1){
                    c = 204;cout<<c;
                }else if(j==w_menu){
                    c = 185;cout<<c;
                }else{
                    c = 205;cout<<c;
                }
            }else if(i==h_menu){
                if(j==1){
                    c = 200;cout<<c;
                }else if(j==w_menu){
                    c = 188;cout<<c;
                }else{
                    c = 205;cout<<c;
                }
            }else if(i==2){
                if(j==1 || j==w_menu){
                    c = 186;cout<<c;
                }else if(j==(w_menu/2 - (int)(m.size())/2)){
                    cout<<m;
                    j+=m.size()-1;
                    continue;
                }else{
                    c = ' ';cout<<c;
                }
            }else if(i==4){
                if(j==1 || j==w_menu){
                    c = 186;cout<<c;
                }else if(j==(w_menu/2 - (int)(op1.size())/2)){
                    row_op1 = whereY();
                    col_op1 = whereX();
                    line_at = row_op1;
                    cout<<op1;
                    j+=op1.size()-1;
                    continue;
                }else{
                    c = ' ';cout<<c;
                }
            }else if(i==5){
                if(j==1 || j==w_menu){
                    c = 186;cout<<c;
                }else if(j==(w_menu/2 - (int)(op2.size())/2)){
                    row_op2 = whereY();
                    col_op2 = whereX();
                    cout<<op2;
                    j+=op2.size()-1;
                    continue;
                }else{
                    c = ' ';cout<<c;
                }
            }
        }
    }
    gotoXY(console_width/2 - tmp.size()/2, line++);
    SetConsoleTextAttribute(posAt, 7);
    cout<<"Nhan ";
    SetConsoleTextAttribute(posAt, 6);
    cout<<"q";
    SetConsoleTextAttribute(posAt, 7);
    cout<<" de dung tro choi";
    gotoXY(console_width/2 - w_menu/2, line++);
    
}
void op_control(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoXY(console_width/2, line);
    int col_1_start = col_op1 - 3;
    int col_2_start = col_op2 - 3;
    int col_1_end = col_op1 + op1.size();
    int col_2_end = col_op2 + op2.size();

    if(!check_first){
        gotoXY(col_1_start, row_op1);
        SetConsoleTextAttribute(posAt, 2);
        cout<<">>>";
        gotoXY(col_1_end, row_op1);
        cout<<"<<<";
    }
    check_first = true;
    
    
    int check = 0;
    if(_kbhit()){
        check++;
        control = _getch();
        if(control == -32){
            control = _getch();
        }else if(control == 'q'){
            gotoXY(console_width/2 - quit.size()/2, line);
            SetConsoleTextAttribute(posAt, 6);
            cout<<quit;
            gotoXY(console_width/2, ++line);
            return;
        }
    }
    if(control == 13){
        if(line_at == row_op1){
            op_choose = 1;
        }else{
            op_choose = 2;
        }
        op_enter = true;
    }else if(control == 72){
        if(line_at-1 >= row_op1 && check == 1){
            gotoXY(col_2_start, row_op2);
            cout<<"   ";
            gotoXY(col_2_end, row_op2);
            cout<<"   ";

            line_at-=1;
            gotoXY(col_1_start, row_op1);
            SetConsoleTextAttribute(posAt, 2);
            cout<<">>>";
            gotoXY(col_1_end, row_op1);
            cout<<"<<<";
            gotoXY(console_width/2, line);
        }
    }else if(control == 80){
        if(line_at+1 <= row_op2 && check == 1){
            gotoXY(col_1_start, row_op1);
            cout<<"   ";
            gotoXY(col_1_end, row_op1);
            cout<<"   ";
            
            line_at+=1;
            gotoXY(col_2_start, row_op2);
            SetConsoleTextAttribute(posAt, 2);
            cout<<">>>";
            gotoXY(col_2_end, row_op2);
            cout<<"<<<";
            gotoXY(console_width/2, line);
        }
    }
}
void input_control(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!check_map){
        gotoXY(save_xcur_start, save_ycur_start);
    }
    check_map = true;
    int check = 0;
    if(_kbhit()){
        check++;
        input_ctrl = _getch();
        if(input_ctrl == -32){
            input_ctrl = _getch();
        }
        else if(input_ctrl == 'q'){
            gotoXY(console_width/2 - quit.size()/2, line);
            SetConsoleTextAttribute(posAt, 6);
            cout<<quit;
            gotoXY(console_width/2, ++line);
            return;
        }else if(input_ctrl == 'm'){
            return;
        }
    }

    if(input_ctrl == 13){
        if(value[input_y][input_x] == " "){
            value[input_y][input_x] = player;
            if(player == "X"){
                Xpos.push_back({input_x, input_y});
                SetConsoleTextAttribute(posAt, 4);
            }else{
                Opos.push_back({input_x, input_y});
                SetConsoleTextAttribute(posAt, 2);
            }
            cout<<player;
            input_enter = true;
        }
    }else if(input_ctrl == 72){
        if(input_y - 1 >= 0 && check == 1){
            ycur -= 2;
            input_y--;
            gotoXY(xcur, ycur);
        }
    }else if(input_ctrl == 80){
        if(input_y + 1 < 11 && check == 1){
            ycur += 2;
            input_y++;
            gotoXY(xcur, ycur);
        }
    }else if(input_ctrl == 75){
        if(input_x - 1 >= 0 && check == 1){
            xcur -= 6;
            input_x--;
            gotoXY(xcur, ycur);
        }
    }else if(input_ctrl == 77){
        if(input_x + 1 < 11 && check == 1){
            xcur += 6;
            input_x++;
            gotoXY(xcur, ycur);
        }
    }
}
void drawMap(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    char c;
    for(int i=1; i<=h_map; i++){
        gotoXY(console_width/2 - w_map/2, line++);
        for(int j=1; j<=w_map; j++){
            if(i==1){
                if(j==1){
                    c = 201;
                }else if(j==w_map){
                    c = 187;
                }else if(j%6==1){
                    c = 203;
                }else{
                    c = 205;
                }
            }else if(i==h_map){
                if(j==1){
                    c = 200;
                }else if(j==w_map){
                    c = 188;
                }else if(j%6==1){
                    c = 202;
                }else{
                    c = 205;
                }
            }else if(i%2==0){
                if(j%6==1){
                    c = 186;
                }else{
                    c = ' ';
                }
            }else{
                if(j==1){
                    c = 204;
                }else if(j==w_map){
                    c = 185;
                }else if(j%6==1){
                    c = 206;
                }else{
                    c = 205;
                }
            }
            cout<<c;
        }
    }
    gotoXY(console_width/2 - tmp.size()/2, line++);
    SetConsoleTextAttribute(posAt, 7);
    cout<<"Nhan ";
    SetConsoleTextAttribute(posAt, 6);
    cout<<"q";
    SetConsoleTextAttribute(posAt, 7);
    cout<<" de dung tro choi";
    gotoXY(console_width/2 - tmp_menu.size()/2, line++);
    SetConsoleTextAttribute(posAt, 7);
    cout<<"Nhan ";
    SetConsoleTextAttribute(posAt, 6);
    cout<<"m";
    SetConsoleTextAttribute(posAt, 7);
    cout<<" de quay ve menu";
    gotoXY(console_width/2 - w_map/2, line++);
}
void gotoXY(short x, short y){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos_cur = {x, y};
    SetConsoleCursorPosition(posAt, pos_cur);
}
int whereX(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
int whereY(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
void makeString(int x, int y){
    str_x1 = "", str_y1 = "", str_main1 = "", str_anti1 = "";
    str_x2 = "", str_y2 = "", str_main2 = "", str_anti2 = "";
    for(int k=0; k<5; k++){
        if(y+k < 11){
            str_x1 += value[y+k][x];
        }
        if(x+k < 11){
            str_y1 += value[y][x+k];
        }
        if(x+k < 11 && y+k < 11){
            str_main1 += value[y+k][x+k];
        }
        if(x-k >= 0 && y+k < 11){
            str_anti1 += value[y+k][x-k];
        }
    }
    for(int k=4; k>=1; k--){
        if(y-k >= 0){
            str_x2 += value[y-k][x];
        }
        if(x-k >= 0){
            str_y2 += value[y][x-k];
        }
        if(x-k >= 0 && y-k >= 0){
            str_main2 += value[y-k][x-k];
        }
        if(x+k < 11 && y-k >= 0){
            str_anti2 += value[y-k][x+k];
        }
    }
    str_x = str_x2 + str_x1;
    str_y = str_y2 + str_y1;
    str_main = str_main2 + str_main1;
    str_anti = str_anti2 + str_anti1;
}
void bot_pos(){
    int x, y;
    int tmpx, tmpy;
    int pos;
    for(auto it : Opos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("OOOO") != string::npos){
            pos = str_x.find("OOOO");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            if(tmpy - 1 >= 0 && value[tmpy - 1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy-1;
                return;
            }
            if(tmpy + 4 < n && value[tmpy + 4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy+4;
                return;
            }
        }
        if(str_y.find("OOOO") != string::npos){
            pos = str_y.find("OOOO");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            if(tmpx - 1 >= 0 && value[tmpy][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy;
                return;
            }
            if(tmpx + 4 < n && value[tmpy][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("OOOO") != string::npos){
            pos = str_main.find("OOOO");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            if(tmpx - 1 >= 0 && tmpy - 1 >= 0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx + 4 < n && tmpy+4 < n && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy+4;
                return;
            }
        }
        if(str_anti.find("OOOO") != string::npos){
            pos = str_anti.find("OOOO");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            if(tmpx + 1 < n && tmpy - 1 >= 0 && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx - 4 >= 0 && tmpy+4 < n && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx-4;
                input_y = tmpy+4;
                return;
            }
        }

        if(str_x.find("OOO O") != string::npos){
            pos = str_x.find("OOO O");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            input_x = tmpx;
            input_y = tmpy + 3;
            return;
        }
        if(str_y.find("OOO O") != string::npos){
            pos = str_y.find("OOO O");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            input_x = tmpx + 3;
            input_y = tmpy;
            return;
        }
        if(str_main.find("OOO O") != string::npos){
            pos = str_main.find("OOO O");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            input_x = tmpx + 3;
            input_y = tmpy + 3;
            return;
        }
        if(str_anti.find("OOO O") != string::npos){
            pos = str_anti.find("OOO O");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            input_x = tmpx - 3;
            input_y = tmpy + 3;
            return;
        }

        if(str_x.find("OO OO") != string::npos){
            pos = str_x.find("OO OO");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            input_x = tmpx;
            input_y = tmpy + 2;
            return;
        }
        if(str_y.find("OO OO") != string::npos){
            pos = str_y.find("OO OO");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            input_x = tmpx + 2;
            input_y = tmpy;
            return;
        }
        if(str_main.find("OO OO") != string::npos){
            pos = str_main.find("OO OO");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            input_x = tmpx + 2;
            input_y = tmpy + 2;
            return;
        }
        if(str_anti.find("OO OO") != string::npos){
            pos = str_anti.find("OO OO");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            input_x = tmpx - 2;
            input_y = tmpy + 2;
            return;
        }

        if(str_x.find("O OOO") != string::npos){
            pos = str_x.find("O OOO");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            input_x = tmpx;
            input_y = tmpy + 1;
            return;
        }
        if(str_y.find("O OOO") != string::npos){
            pos = str_y.find("O OOO");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            input_x = tmpx + 1;
            input_y = tmpy;
            return;
        }   
        if(str_main.find("O OOO") != string::npos){
            pos = str_main.find("O OOO");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            input_x = tmpx + 1;
            input_y = tmpy + 1;
            return;
        }
        if(str_anti.find("O OOO") != string::npos){
            pos = str_main.find("O OOO");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            input_x = tmpx - 1;
            input_y = tmpy + 1;
            return;
        }
    }
    for(auto it : Xpos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("XXXX") != string::npos){
            pos = str_x.find("XXXX");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            if(tmpy - 1 >= 0 && value[tmpy - 1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy-1;
                return;
            }
            if(tmpy + 4 < n && value[tmpy + 4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy+4;
                return;
            }
        }
        if(str_y.find("XXXX") != string::npos){
            pos = str_y.find("XXXX");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            if(tmpx - 1 >= 0 && value[tmpy][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy;
                return;
            }
            if(tmpx + 4 < n && value[tmpy][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("XXXX") != string::npos){
            pos = str_main.find("XXXX");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            if(tmpx - 1 >= 0 && tmpy - 1 >= 0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx + 4 < n && tmpy+4 < n && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy+4;
                return;
            }
        }
        if(str_anti.find("XXXX") != string::npos){
            pos = str_anti.find("XXXX");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            if(tmpx + 1 < n && tmpy - 1 >= 0 && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx - 4 >= 0 && tmpy+4 < n && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx-4;
                input_y = tmpy+4;
                return;
            }
        }

        if(str_x.find("XXX X") != string::npos){
            pos = str_x.find("XXX X");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            input_x = tmpx;
            input_y = tmpy + 3;
            return;
        }
        if(str_y.find("XXX X") != string::npos){
            pos = str_y.find("XXX X");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            input_x = tmpx + 3;
            input_y = tmpy;
            return;
        }
        if(str_main.find("XXX X") != string::npos){
            pos = str_main.find("XXX X");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            input_x = tmpx + 3;
            input_y = tmpy + 3;
            return;
        }
        if(str_anti.find("XXX X") != string::npos){
            pos = str_anti.find("XXX X");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            input_x = tmpx - 3;
            input_y = tmpy + 3;
            return;
        }

        if(str_x.find("XX XX") != string::npos){
            pos = str_x.find("XX XX");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            input_x = tmpx;
            input_y = tmpy + 2;
            return;
        }
        if(str_y.find("XX XX") != string::npos){
            pos = str_y.find("XX XX");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            input_x = tmpx + 2;
            input_y = tmpy;
            return;
        }
        if(str_main.find("XX XX") != string::npos){
            pos = str_main.find("XX XX");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            input_x = tmpx + 2;
            input_y = tmpy + 2;
            return;
        }
        if(str_anti.find("XX XX") != string::npos){
            pos = str_anti.find("XX XX");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            input_x = tmpx - 2;
            input_y = tmpy + 2;
            return;
        }

        if(str_x.find("X XXX") != string::npos){
            pos = str_x.find("X XXX");
            if(y<4){
                tmpy = 0;
            }else{
                tmpy = y - 4 + pos;
            }
            input_x = tmpx;
            input_y = tmpy + 1;
            return;
        }
        if(str_y.find("X XXX") != string::npos){
            pos = str_y.find("X XXX");
            if(x<4){
                tmpx = 0;
            }else{
                tmpx = x - 4 + pos;
            }
            input_x = tmpx + 1;
            input_y = tmpy;
            return;
        }   
        if(str_main.find("X XXX") != string::npos){
            pos = str_main.find("X XXX");
            int tmpmin = min(x, y);
            if(tmpmin >= 4){
                tmpx = x - 4 + pos;
                tmpy = y - 4 + pos;
            }else{
                tmpx = x - tmpmin + pos;
                tmpy = y - tmpmin + pos;
            }
            input_x = tmpx + 1;
            input_y = tmpy + 1;
            return;
        }
        if(str_anti.find("X XXX") != string::npos){
            pos = str_main.find("X XXX");
            int denta = 10 - tmpx;
            if(denta <= 4){
                tmpx = x - min(x, denta);
                tmpy = y + min(x, denta);
            }else{
                tmpx = x - min(x, 4);
                tmpy = y + min(x, 4);
            }
            input_x = tmpx - 1;
            input_y = tmpy + 1;
            return;
        }
    }
    for(auto it : Opos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("OOO") != string::npos){
            pos = str_x.find("OOO");
            tmpy = y - min(y, 4) + pos;
            if(tmpy - 2 >= 0 && value[tmpy - 2][tmpx] == " " && value[tmpy - 1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy + 4 < n && value[tmpy + 4][tmpx] == " " && value[tmpy + 3][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy + 3;
                return;
            }
            if(tmpy - 1 >= 0 && tmpy + 3 < n && value[tmpy - 1][tmpx] == " " && value[tmpy + 3][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
        }
        if(str_y.find("OOO") != string::npos){
            pos = str_y.find("OOO");
            tmpx = x - min(x, 4) + pos;
            if(tmpx - 2 >= 0 && value[tmpy][tmpx - 2] == " " && value[tmpy][tmpx - 1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx + 4 < n && value[tmpy][tmpx + 4] == " " && value[tmpy][tmpx + 3] == " "){
                input_x = tmpx + 3;
                input_y = tmpy;
                return;
            }
            if(tmpx - 1 >= 0 && tmpx + 3 < n && value[tmpy][tmpx - 1] == " " && value[tmpy][tmpx + 3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("OOO") != string::npos){
            pos = str_main.find("OOO");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpy-2>=0 && tmpx-2>=0 && value[tmpy-2][tmpx-2] == " " && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy+4<n && tmpx+4<n && value[tmpy+4][tmpx+4] == " " && value[tmpy+3][tmpx+3] == " "){
                input_x = tmpx + 3;
                input_y = tmpy + 3;
                return;
            }
            if(tmpy-1>=0 && tmpx-1>=0 && tmpy+3<n && tmpx+3<n && value[tmpy-1][tmpx-1] == " " && value[tmpy+3][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
        }
        if(str_anti.find("OOO") != string::npos){
            pos = str_anti.find("OOO");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpy-2>=0 && tmpx+2<n && value[tmpy-2][tmpx+2] == " " && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy+4<n && tmpx-4>=0 && value[tmpy+4][tmpx-4] == " " && value[tmpy+3][tmpx-3] == " "){
                input_x = tmpx - 3;
                input_y = tmpy + 3;
                return;
            }
            if(tmpy-1>=0 && tmpx+1<n && tmpy+3<n && tmpx-3>=0 && value[tmpy-1][tmpx+1] == " " && value[tmpy+3][tmpx-3] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
        } 
        
        if(str_x.find("OO O") != string::npos){
            pos = str_x.find("OO O");
            tmpy = y - min(y, 4) + pos;
            if(tmpy - 1 >= 0 && value[tmpy - 1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy-1;
                return;
            }
            if(tmpy + 4 < n && value[tmpy + 4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy+4;
                return;
            }
        }
        if(str_y.find("OO O") != string::npos){
            pos = str_y.find("OO O");
            tmpx = x - min(x, 4) + pos;
            if(tmpx - 1 >= 0 && value[tmpy][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy;
                return;
            }
            if(tmpx + 4 < n && value[tmpy][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("OO O") != string::npos){
            pos = str_main.find("OO O");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx - 1 >= 0 && tmpy - 1 >= 0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx + 4 < n && tmpy+4 < n && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy+4;
                return;
            }
        }
        if(str_anti.find("OO O") != string::npos){
            pos = str_anti.find("OO O");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx + 1 < n && tmpy - 1 >= 0 && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx - 4 >= 0 && tmpy+4 < n && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx-4;
                input_y = tmpy+4;
                return;
            }
        }
        
        if(str_x.find("O OO") != string::npos){
            pos = str_x.find("O OO");
            tmpy = y - min(y, 4) + pos;
            if(tmpy + 4 < n && value[tmpy + 4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy+4;
                return;
            }
            if(tmpy - 1 >= 0 && value[tmpy - 1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy-1;
                return;
            }
        }
        if(str_y.find("O OO") != string::npos){
            pos = str_y.find("O OO");
            tmpx = x - min(x, 4) + pos;
            if(tmpx + 4 < n && value[tmpy][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy;
                return;
            }
            if(tmpx - 1 >= 0 && value[tmpy][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("O OO") != string::npos){
            pos = str_main.find("O OO");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx + 4 < n && tmpy+4 < n && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx+4;
                input_y = tmpy+4;
                return;
            }
            if(tmpx - 1 >= 0 && tmpy - 1 >= 0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy-1;
                return;
            }
        }
        if(str_anti.find("O OO") != string::npos){
            pos = str_anti.find("O OO");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx - 4 >= 0 && tmpy+4 < n && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx-4;
                input_y = tmpy+4;
                return;
            }
            if(tmpx + 1 < n && tmpy - 1 >= 0 && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy-1;
                return;
            }
        }
        
    }
    for(auto it : Xpos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("XXX") != string::npos){
            pos = str_x.find("XXX");
            tmpy = y - min(y, 4) + pos;
            if(tmpy - 1 >= 0 && value[tmpy - 1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy + 3 < n && value[tmpy + 3][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy + 3;
                return;
            }
        }
        if(str_y.find("XXX") != string::npos){
            pos = str_y.find("XXX");
            tmpx = x - min(x, 4) + pos;
            if(tmpx - 1 >= 0 && value[tmpy][tmpx - 1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx + 3 < n && value[tmpy][tmpx + 3] == " "){
                input_x = tmpx + 3;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("XXX") != string::npos){
            pos = str_main.find("XXX");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpy-1>=0 && tmpx-1>=0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy+3<n && tmpx+3<n && value[tmpy+3][tmpx+3] == " "){
                input_x = tmpx + 3;
                input_y = tmpy + 3;
                return;
            }
        }
        if(str_anti.find("XXX") != string::npos){
            pos = str_anti.find("XXX");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpy-1>=0 && tmpx+1<n && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy+3<n && tmpx-3>=0 && value[tmpy+3][tmpx-3] == " "){
                input_x = tmpx - 3;
                input_y = tmpy + 3;
                return;
            }
        } 
        
        if(str_x.find("XX X") != string::npos){
            pos = str_x.find("XX X");
            tmpy = y - min(y, 4) + pos;
            input_x = tmpx;
            input_y = tmpy + 2;
            return;
        }
        if(str_y.find("XX X") != string::npos){
            pos = str_y.find("XX X");
            tmpx = x - min(x, 4) + pos;
            input_x = tmpx + 2;
            input_y = tmpy;
            return;
        }
        if(str_main.find("XX X") != string::npos){
            pos = str_main.find("XX X");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            input_x = tmpx + 2;
            input_y = tmpy + 2;
            return;
        }
        if(str_anti.find("XX X") != string::npos){
            pos = str_anti.find("XX X");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            input_x = tmpx - 2;
            input_y = tmpy + 2;
            return;
        }
        
        if(str_x.find("X XX") != string::npos){
            pos = str_x.find("X XX");
            tmpy = y - min(y, 4) + pos;
            input_x = tmpx;
            input_y = tmpy + 1;
            return;
        }
        if(str_y.find("X XX") != string::npos){
            pos = str_y.find("X XX");
            tmpx = x - min(x, 4) + pos;
            input_x = tmpx + 1;
            input_y = tmpy;
            return;
        }
        if(str_main.find("X XX") != string::npos){
            pos = str_main.find("X XX");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            input_x = tmpx + 1;
            input_y = tmpy + 1;
            return;
        }
        if(str_anti.find("X XX") != string::npos){
            pos = str_anti.find("X XX");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            input_x = tmpx - 1;
            input_y = tmpy + 1;
            return; 
        }
        
    }
    for(auto it : Opos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("OO") != string::npos){
            pos = str_x.find("OO");
            tmpy = y - min(y, 4) + pos;
            if(tmpy-3>=0 && value[tmpy-3][tmpx] == " " && value[tmpy-2][tmpx] == " " && value[tmpy-1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy-2>=0 && tmpy+2<n && value[tmpy-2][tmpx] == " " && value[tmpy-1][tmpx] == " " && value[tmpy+2][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy-1>=0 && tmpy+3<n  && value[tmpy-1][tmpx] == " " && value[tmpy+2][tmpx] == " " && value[tmpy+3][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy+4<n && value[tmpy+2][tmpx] == " " && value[tmpy+3][tmpx] == " " && value[tmpy+4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy + 2;
                return;
            }
        }
        if(str_y.find("OO") != string::npos){
            pos = str_y.find("OO");
            tmpx = x - min(x, 4) + pos;
            if(tmpx-3>=0 && value[tmpy][tmpx-3] == " " && value[tmpy][tmpx-2] == " " && value[tmpy][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx-2>=0 && tmpx+2<n && value[tmpy][tmpx-2] == " " && value[tmpy][tmpx-1] == " " && value[tmpy][tmpx+2] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx-1>=0 && tmpx+3<n  && value[tmpy][tmpx-1] == " " && value[tmpy][tmpx+2] == " " && value[tmpy][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx+4<n && value[tmpy][tmpx+2] == " " && value[tmpy][tmpx+3] == " " && value[tmpy][tmpx+4] == " "){
                input_x = tmpx + 2;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("OO") != string::npos){
            pos = str_main.find("OO");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx-3>=0 && tmpy-3>=0 && value[tmpy-1][tmpx-1] == " " && value[tmpy-2][tmpx-2] == " " && value[tmpy-3][tmpx-3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-2>=0 && tmpy-2>=0 && tmpx+2<n && tmpy+2<n && value[tmpy-1][tmpx-1] == " " && value[tmpy-2][tmpx-2] == " " && value[tmpy+2][tmpx+2] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-1>=0 && tmpy-1>=0 && tmpx+3<n && tmpy+3<n && value[tmpy-1][tmpx-1] == " " && value[tmpy+2][tmpx+2] == " " && value[tmpy+3][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+4<n && tmpy+4<n && value[tmpy+2][tmpx+2] == " " && value[tmpy+3][tmpx+3] == " " && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx + 2;
                input_y = tmpy + 2;
                return;
            }
        }
        if(str_anti.find("OO") != string::npos){
            pos = str_anti.find("OO");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx+3<n && tmpy-3>=0 && value[tmpy-1][tmpx+1] == " " && value[tmpy-2][tmpx+2] == " " && value[tmpy-3][tmpx+3] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+2<n && tmpy-2>=0 && tmpx-2>=0 && tmpy+2<n && value[tmpy-1][tmpx+1] == " " && value[tmpy-2][tmpx+2] == " " && value[tmpy+2][tmpx-2] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+1<n && tmpy-1>=0 && tmpx-3>=0 && tmpy+3<n && value[tmpy-1][tmpx+1] == " " && value[tmpy+2][tmpx-2] == " " && value[tmpy+3][tmpx-3] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-4>=0 && tmpy+4<n && value[tmpy+2][tmpx-2] == " " && value[tmpy+3][tmpx-3] == " " && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx - 2;
                input_y = tmpy + 2;
                return;
            }
        }
        
        if(str_x.find("O O") != string::npos){
            pos = str_x.find("O O");
            tmpy = y - min(y, 4) + pos;
            if(tmpy-2>=0 && value[tmpy-2][tmpx] == " " && value[tmpy-1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy-1>=0 && tmpy+3<n && value[tmpy-1][tmpx] == " " && value[tmpy+3][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy -1;
                return;
            }
            if(tmpy+4<n && value[tmpy+3][tmpx] == " " && value[tmpy+4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy + 3;
                return;
            }
        }
        if(str_y.find("O O") != string::npos){
            pos = str_y.find("O O");
            tmpx = x - min(x, 4) + pos;
            if(tmpx-2>=0 && value[tmpy][tmpx-2] == " " && value[tmpy][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx-1>=0 && tmpx+3<n && value[tmpy][tmpx-1] == " " && value[tmpy][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx+4<n && value[tmpy][tmpx+3] == " " && value[tmpy][tmpx+4] == " "){
                input_x = tmpx + 3;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("O O") != string::npos){
            pos = str_main.find("O O");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx-2>=0 && tmpy-2>=0 && value[tmpy-2][tmpx-2] == " " && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-1>=0 && tmpx+3<n && tmpy-1>=0 && tmpy+3<n && value[tmpy-1][tmpx-1] == " " && value[tmpy+3][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+4<n && tmpy+4<n && value[tmpy+3][tmpx+3] == " " && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx + 3;
                input_y = tmpy + 3;
                return;
            }
        }
        if(str_anti.find("O O") != string::npos){
            pos = str_anti.find("O O");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx+2<n && tmpy-2>=0 && value[tmpy-2][tmpx+2] == " " && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+1<n && tmpx-3>=0 && tmpy-1>=0 && tmpy+3<n && value[tmpy-1][tmpx+1] == " " && value[tmpy+3][tmpx-3] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-4>=0 && tmpy+4<n && value[tmpy+3][tmpx-3] == " " && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx - 3;
                input_y = tmpy + 3;
                return;
            }
        }
    }
    for(auto it : Xpos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("XX") != string::npos){
            pos = str_x.find("XX");
            tmpy = y - min(y, 4) + pos;
            if(tmpy-1>=0 && value[tmpy-1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy-1;
                return;
            }
            if(tmpy+2<n && value[tmpy+2][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy+2;
                return;
            }
        }
        if(str_y.find("XX") != string::npos){
            pos = str_y.find("XX");
            tmpx = x - min(x, 4) + pos;
            if(tmpx-1>=0 && value[tmpy][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy;
                return;
            }
            if(tmpx+2<n && value[tmpy][tmpx+2] == " "){
                input_x = tmpx+2;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("XX") != string::npos){
            pos = str_main.find("XX");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx-1>=0 && tmpy-1>=0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx+2<n && tmpy+2<n && value[tmpy+2][tmpx+2] == " "){
                input_x = tmpx+2;
                input_y = tmpy+2;
                return;
            }
        }
        if(str_anti.find("XX") != string::npos){
            pos = str_anti.find("XX");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx+1<n && tmpy-1>=0 && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx-2>=0 && tmpy+2<n && value[tmpy+2][tmpx-2] == " "){
                input_x = tmpx-2;
                input_y = tmpy+2;
                return;
            }
        }
        
        if(str_x.find("X X") != string::npos){
            pos = str_x.find("X X");
            tmpy = y - min(y, 4) + pos;
            input_x = tmpx;
            input_y = tmpy+1;
            return;
        }
        if(str_y.find("X X") != string::npos){
            pos = str_y.find("X X");
            tmpx = x - min(x, 4) + pos;
            input_x = tmpx+1;
            input_y = tmpy;
            return;
        }
        if(str_main.find("X X") != string::npos){
            pos = str_main.find("X X");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            input_x = tmpx+1;
            input_y = tmpy+1;
            return;
        }
        if(str_anti.find("X X") != string::npos){
            pos = str_anti.find("X X");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            input_x = tmpx-1;
            input_y = tmpy+1;
            return;
        }
    }
    for(auto it : Opos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("O") != string::npos){
            pos = str_x.find("O");
            tmpy = y - min(y, 4) + pos;
            if(tmpy-4>=0 && value[tmpy-4][tmpx] == " " && value[tmpy-3][tmpx] == " " && value[tmpy-2][tmpx] == " " && value[tmpy-1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy-3>=0 && tmpy+1<n && value[tmpy-3][tmpx] == " " && value[tmpy-2][tmpx] == " " && value[tmpy-1][tmpx] == " " && value[tmpy+1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy-2>=0 && tmpy+2<n && value[tmpy-2][tmpx] == " " && value[tmpy-1][tmpx] == " " && value[tmpy+1][tmpx] == " " && value[tmpy+2][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy-1>=0 && tmpy+3<n && value[tmpy-1][tmpx] == " " && value[tmpy+1][tmpx] == " " && value[tmpy+2][tmpx] == " " && value[tmpy+3][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy - 1;
                return;
            }
            if(tmpy+4<n && value[tmpy+3][tmpx] == " " && value[tmpy+2][tmpx] == " " && value[tmpy+1][tmpx] == " " && value[tmpy+4][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy + 1;
                return;
            }
        }
        if(str_y.find("O") != string::npos){
            pos = str_y.find("O");
            tmpx = x - min(x, 4) + pos;
            if(tmpx-4>=0 && value[tmpy][tmpx-4] == " " && value[tmpy][tmpx-3] == " " && value[tmpy][tmpx-2] == " " && value[tmpy][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx-3>=0 && tmpx+1<n && value[tmpy][tmpx-3] == " " && value[tmpy][tmpx-2] == " " && value[tmpy][tmpx-1] == " " && value[tmpy][tmpx+1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx-2>=0 && tmpx+2<n && value[tmpy][tmpx-2] == " " && value[tmpy][tmpx-1] == " " && value[tmpy][tmpx+1] == " " && value[tmpy][tmpx+2] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx-1>=0 && tmpx+3<n && value[tmpy][tmpx-1] == " " && value[tmpy][tmpx+1] == " " && value[tmpy][tmpx+2] == " " && value[tmpy][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy;
                return;
            }
            if(tmpx+4<n && value[tmpy][tmpx+3] == " " && value[tmpy][tmpx+2] == " " && value[tmpy][tmpx+1] == " " && value[tmpy][tmpx+4] == " "){
                input_x = tmpx + 1;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("O") != string::npos){
            pos = str_main.find("O");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx-4>=0 && tmpy-4>=0 && value[tmpy-4][tmpx-4] == " " && value[tmpy-3][tmpx-3] == " " && value[tmpy-2][tmpx-2] == " " && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-3>=0 && tmpx+1<n && tmpy-3>=0 && tmpy+1<n && value[tmpy-3][tmpx-3] == " " && value[tmpy-2][tmpx-2] == " " && value[tmpy-1][tmpx-1] == " " && value[tmpy+1][tmpx+1] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-2>=0 && tmpx+2<n && tmpy-2>=0 && tmpy+2<n && value[tmpy-2][tmpx-2] == " " && value[tmpy-1][tmpx-1] == " " && value[tmpy+1][tmpx+1] == " " && value[tmpy+2][tmpx+2] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-1>=0 && tmpx+3<n && tmpy-1>=0 && tmpy+3<n && value[tmpy-1][tmpx-1] == " " && value[tmpy+1][tmpx+1] == " " && value[tmpy+2][tmpx+2] == " " && value[tmpy+3][tmpx+3] == " "){
                input_x = tmpx - 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+4<n && tmpy+4<n && value[tmpy+3][tmpx+3] == " " && value[tmpy+2][tmpx+2] == " " && value[tmpy+1][tmpx+1] == " " && value[tmpy+4][tmpx+4] == " "){
                input_x = tmpx + 1;
                input_y = tmpy + 1;
                return;
            }
        }
        if(str_anti.find("O") != string::npos){
            pos = str_anti.find("O");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx+4<n && tmpy-4>=0 && value[tmpy-4][tmpx+4] == " " && value[tmpy-3][tmpx+3] == " " && value[tmpy-2][tmpx+2] == " " && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+3<n && tmpx-1>=0 && tmpy-3>=0 && tmpy+1<n && value[tmpy-3][tmpx+3] == " " && value[tmpy-2][tmpx+2] == " " && value[tmpy-1][tmpx+1] == " " && value[tmpy+1][tmpx-1] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+2<n && tmpx-2>=0 && tmpy-2>=0 && tmpy+2<n && value[tmpy-2][tmpx+2] == " " && value[tmpy-1][tmpx+1] == " " && value[tmpy+1][tmpx-1] == " " && value[tmpy+2][tmpx-2] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx+1<n && tmpx-3>=0 && tmpy-1>=0 && tmpy+3<n && value[tmpy-1][tmpx+1] == " " && value[tmpy+1][tmpx-1] == " " && value[tmpy+2][tmpx-2] == " " && value[tmpy+3][tmpx-3] == " "){
                input_x = tmpx + 1;
                input_y = tmpy - 1;
                return;
            }
            if(tmpx-4>=0 && tmpy+4<n && value[tmpy+3][tmpx-3] == " " && value[tmpy+2][tmpx-2] == " " && value[tmpy+1][tmpx-1] == " " && value[tmpy+4][tmpx-4] == " "){
                input_x = tmpx - 1;
                input_y = tmpy + 1;
                return;
            }
        }
    }
    for(auto it : Xpos){
        x = it.first;
        y = it.second;
        makeString(x, y);
        tmpx = x, tmpy = y;
        if(str_x.find("X") != string::npos){
            pos = str_x.find("X");
            tmpy = y - min(y, 4) + pos;
            if(tmpy-1>=0 && value[tmpy-1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy-1;
                return;
            }
            if(tmpy+1<n && value[tmpy+1][tmpx] == " "){
                input_x = tmpx;
                input_y = tmpy+1;
                return;
            }
        }
        if(str_y.find("X") != string::npos){
            pos = str_y.find("X");
            tmpx = x - min(x, 4) + pos;
            if(tmpx-1>=0 && value[tmpy][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy;
                return;
            }
            if(tmpx+1<n && value[tmpy][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy;
                return;
            }
        }
        if(str_main.find("X") != string::npos){
            pos = str_main.find("X");
            int tmpmin = min(4, min(x, y));
            tmpx = x - tmpmin + pos;
            tmpy = y - tmpmin + pos;
            if(tmpx-1>=0 && tmpy-1>=0 && value[tmpy-1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx+1<n && tmpy+1<n && value[tmpy+1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy+1;
                return;
            }
        }
        if(str_anti.find("X") != string::npos){
            pos = str_anti.find("X");
            int tmpmin = min(4, min(10 - x, y));
            tmpx = x + tmpmin - pos;
            tmpy = y - tmpmin + pos;
            if(tmpx+1<n && tmpy-1>=0 && value[tmpy-1][tmpx+1] == " "){
                input_x = tmpx+1;
                input_y = tmpy-1;
                return;
            }
            if(tmpx-1>=0 && tmpy+1<n && value[tmpy+1][tmpx-1] == " "){
                input_x = tmpx-1;
                input_y = tmpy+1;
                return;
            }
        }
    }
}
void bot_turn(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    change();
    bot_pos();
    value[input_y][input_x] = player;
    Opos.push_back({input_x, input_y});
    xcur = save_xcur_start + 6*input_x, ycur = save_ycur_start + 2*input_y;
    gotoXY(xcur, ycur);
    SetConsoleTextAttribute(posAt, 2);
    cout<<player;
    if(check_ans()){
        if(player == "X"){
            gotoXY(console_width/2 - Xwin.size()/2, line++);
            SetConsoleTextAttribute(posAt, 7);
            cout<<"Tro choi da ket thuc!! Nguoi chien thang la ";
            SetConsoleTextAttribute(posAt, 4);
            cout<<"X";
            gotoXY(console_width/2 - PAUSE.size()/2, line++);
            SetConsoleTextAttribute(posAt, 7);
            gameover = true;
            system("pause");
            return;
        }
        else{
            gotoXY(console_width/2 - Owin.size()/2, line++);
            SetConsoleTextAttribute(posAt, 7);
            cout<<"Tro choi da ket thuc!! Nguoi chien thang la ";
            SetConsoleTextAttribute(posAt, 2);
            cout<<"O";
            gotoXY(console_width/2 - PAUSE.size()/2, line++);
            SetConsoleTextAttribute(posAt, 7);
            gameover = true;
            system("pause");
            return;
        }
    }
}
bool check_ans(){
    int x, y;
    if(player == "X"){
        for(auto it : Xpos){
            x = it.first;
            y = it.second;
            str_x1 = "", str_y1 = "", str_main1 = "", str_anti1 = "";
            str_x2 = "", str_y2 = "", str_main2 = "", str_anti2 = "";
            for(int k=0; k<5; k++){
                if(y+k < 11){
                    str_x1 += value[y+k][x];
                }
                if(x+k < 11){
                    str_y1 += value[y][x+k];
                }
                if(x+k < 11 && y+k < 11){
                    str_main1 += value[y+k][x+k];
                }
                if(x-k >= 0 && y+k < 11){
                    str_anti1 += value[y+k][x-k];
                }
            }
            for(int k=4; k>=1; k--){
                if(y-k >= 0){
                    str_x2 += value[y-k][x];
                }
                if(x-k >= 0){
                    str_y2 += value[y][x-k];
                }
                if(x-k >= 0 && y-k >= 0){
                    str_main2 += value[y-k][x-k];
                }
                if(x+k < 11 && y-k >= 0){
                    str_anti2 += value[y-k][x+k];
                }
            }
            str_x = str_x2 + str_x1;
            str_y = str_y2 + str_y1;
            str_main = str_main2 + str_main1;
            str_anti = str_anti2 + str_anti1;
            if(str_x.find("XXXXX") != string::npos){
                return true;
            }
            if(str_y.find("XXXXX") != string::npos){
                return true;
            }
            if(str_main.find("XXXXX") != string::npos){
                return true;
            }
            if(str_anti.find("XXXXX") != string::npos){
                return true;
            }
        }
    }else{
        for(auto it : Opos){
            x = it.first;
            y = it.second;
            str_x1 = "", str_y1 = "", str_main1 = "", str_anti1 = "";
            str_x2 = "", str_y2 = "", str_main2 = "", str_anti2 = "";
            for(int k=0; k<5; k++){
                if(y+k < 11){
                    str_x1 += value[y+k][x];
                }
                if(x+k < 11){
                    str_y1 += value[y][x+k];
                }
                if(x+k < 11 && y+k < 11){
                    str_main1 += value[y+k][x+k];
                }
                if(x-k >= 0 && y+k < 11){
                    str_anti1 += value[y+k][x-k];
                }
            }
            for(int k=4; k>=1; k--){
                if(y-k >= 0){
                    str_x2 += value[y-k][x];
                }
                if(x-k >= 0){
                    str_y2 += value[y][x-k];
                }
                if(x-k >= 0 && y-k >= 0){
                    str_main2 += value[y-k][x-k];
                }
                if(x+k < 11 && y-k >= 0){
                    str_anti2 += value[y-k][x+k];
                }
            }
            str_x = str_x2 + str_x1;
            str_y = str_y2 + str_y1;
            str_main = str_main2 + str_main1;
            str_anti = str_anti2 + str_anti1;
            if(str_x.find("OOOOO") != string::npos){
                return true;
            }
            if(str_y.find("OOOOO") != string::npos){
                return true;
            }
            if(str_main.find("OOOOO") != string::npos){
                return true;
            }
            if(str_anti.find("OOOOO") != string::npos){
                return true;
            }
        }
    }
    return false;
}
void play1(){
    check_first = false;
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    player = "X";
    line = 1;
    title();
    drawMap();
    gameover = false;
    gotoXY(save_xcur_start, save_ycur_start);
    while(!gameover){
        while(!input_enter){
            input_control();
            if(input_ctrl == 'q'){
                return;
            }
            if(input_ctrl == 'm'){
                return;
            }
        }
        input_enter = false;
        if(check_ans()){
            if(player == "X"){
                gotoXY(console_width/2 - Xwin.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                cout<<"Tro choi da ket thuc!! Nguoi chien thang la ";
                SetConsoleTextAttribute(posAt, 4);
                cout<<"X";
                gotoXY(console_width/2 - PAUSE.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                gameover = true;
                system("pause");
                return;
            }
            else{
                gotoXY(console_width/2 - Owin.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                cout<<"Tro choi da ket thuc!! Nguoi chien thang la ";
                SetConsoleTextAttribute(posAt, 2);
                cout<<"O";
                gotoXY(console_width/2 - PAUSE.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                gameover = true;
                system("pause");
                return;
            }
        }
        change();
    }
    system("pause");
}
void play2(){
    check_first = false;
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    player = "X";
    line = 1;
    title();
    drawMap();
    gameover = false;
    gotoXY(save_xcur_start, save_ycur_start);
    while(!gameover){
        while(!input_enter){
            input_control();
            if(input_ctrl == 'q'){
                return;
            }
            if(input_ctrl == 'm'){
                return;
            }
        }
        input_enter = false;
        if(check_ans()){
            if(player == "X"){
                gotoXY(console_width/2 - Xwin.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                cout<<"Tro choi da ket thuc!! Nguoi chien thang la ";
                SetConsoleTextAttribute(posAt, 4);
                cout<<"X";
                gotoXY(console_width/2 - PAUSE.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                gameover = true;
                system("pause");
                return;
            }
            else{
                gotoXY(console_width/2 - Owin.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                cout<<"Tro choi da ket thuc!! Nguoi chien thang la ";
                SetConsoleTextAttribute(posAt, 2);
                cout<<"O";
                gotoXY(console_width/2 - PAUSE.size()/2, line++);
                SetConsoleTextAttribute(posAt, 7);
                gameover = true;
                system("pause");
                return;
            }
        }
        bot_turn();
        change();
    }
    system("pause");
}