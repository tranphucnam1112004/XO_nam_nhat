#include<bits/stdc++.h>
#include<conio.h>
#include"windows.h"
using namespace std;
//--------các biến chính----------
int n=11, x=62, y=7, times, x_user=0, y_user=0, gameplay;
int x_start = x, y_start = y;
string player = "X";
string user_input[11][11];
bool gameover = false, enter = false;
map<string, int>mp = {{"X",0}, {"O",0}};

//----------------Khai báo nguyên hàm-----------------------------
//-----------Hàm phụ-------------------
int whereX();
int whereY();
void gotoXY(short x, short y);
void title();
void turn();

//-----------Hàm phụ để kiểm tra kết quả-------------
bool checkx(); //check cột
bool checky(); // check hàng
bool checkmaindia(); // check chéo chính
bool checkantidia(); // check chéo phụ
bool block();
//-----------Hàm chính----------------
void bot_turn();
void control();
void draw(string value); // vẽ bàn cờ với giá trị value vừa được nhập
void change(); // đổi người chơi
void start_value(); // khởi tạo giá trị ban đầu của bàn cờ
void check_ans(); // kiểm tra thắng thua
void bot_turn();
void gameplay1();
void gameplay2();

//------------main---------
int main (){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    while(true){
        system("cls");
        SetConsoleTextAttribute(posAt, 7);
        cout<<"----Menu---"<<endl;
        cout<<"1.Nguoi voi nguoi\n2.Nguoi voi may"<<endl;
        cout<<"Chon che do ban muon choi: ";
        do{
            cin>>gameplay;
            if(gameplay<1||gameplay>2){
                cout<<"Lua chon cua ban khong co, vui long chon lai: ";
            }
        }while(gameplay<1||gameplay>2);
        system("cls");
        switch(gameplay){
            case 1:{
                gameplay1();
            }break;
            case 2:{
                gameplay2();
            }break;
        }
    }
    return 0;
}

//---------Hàm phụ------------
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO posAt;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &posAt))
		return posAt.dwCursorPosition.X;
	return -1;
}
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO posAt;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &posAt))
		return posAt.dwCursorPosition.Y;
	return -1;
}
void gotoXY(short x, short y){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos_cur = {x,y};
    SetConsoleCursorPosition(posAt, pos_cur);
}
void title(){
    int align = 74;
    string in_ans, out_ans;
    for(int k=1; k<=12; k++){
        char in_char = 175, out_char = 174;
        in_ans+=in_char;
        out_ans+=out_char;
    }
    cout<<setw(align)<<" ";
    cout<<"_______------- Round "<<times<<" -------_______"<<endl;
    cout<<setw(align)<<" ";
    cout<<in_ans<<" X   "<<mp["X"]<<":"<<mp["O"]<<"   O "<<out_ans<<endl;
}
void turn(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(posAt, 1);
    //gotoXY(0, 30);
    COORD curPos = { 0, 30 };
	SetConsoleCursorPosition(posAt, curPos);
    cout<<setw(97)<<"Luot cua ";
    if(player == "X"){
        SetConsoleTextAttribute(posAt, 4);
    }else{
        SetConsoleTextAttribute(posAt, 2);
    }
    cout<<player;
    SetConsoleTextAttribute(posAt, 7);
}
bool checkx(){
    string res = "";
    string ans= "";
    for(int k=1; k<=5; k++){
        ans+=player;
    }
    for(int i=0; i<n; i++){
        res+=user_input[i][x_user];
    }
    if(res.find(ans) != string::npos){
        return true;
    }else{
        return false;
    }
}
bool checky(){
    string res = "";
    string ans= "";
    for(int k=1; k<=5; k++){
        ans+=player;
    }
    for(int i=0; i<n; i++){
        res+=user_input[y_user][i];
    }
    if(res.find(ans) != string::npos){
        return true;
    }else{
        return false;
    }
}
bool checkmaindia(){
    int tmp = min(x_user,y_user);
    int start_x = x_user-tmp;
    int start_y = y_user-tmp;
    tmp = max(start_x, start_y);
    string res = "";
    string ans= "";
    for(int k=1; k<=5; k++){
        ans+=player;
    }
    int cnt = n - tmp;
    if(cnt < 5) return false;
    for(int i=1; i<=cnt; i++){
        res+=user_input[start_y][start_x];
        start_x++;
        start_y++;
    }
    if(res.find(ans) != string::npos){
        return true;
    }else{
        return false;
    }
}
bool checkantidia(){
    string res = "";
    string ans = "";
    for(int k=1; k<=5; k++){
        ans+=player;
    }
    map<int,int>antidia;
    for(int i=0; i<n; i++){
        antidia[i] = n-1-i;
    }
    int start_y, start_x, distance;
    if(y_user <= antidia[x_user]){
        distance = antidia[x_user] - y_user;
        start_y = 0;
        start_x = n - 1 - distance;
    }else{
        distance = y_user - antidia[x_user];
        start_x = n - 1;
        start_y = distance;
    }
    int cnt = n - distance;
    if(cnt < 5) return false;
    for(int i=1; i<=cnt; i++){
        res+=user_input[start_y][start_x];
        start_x--;
        start_y++;
    }
    if(res.find(ans) != string::npos){
        return true;
    }else{
        return false;
    }
}
bool block(){
    int x_input, y_input;
    int pos;
    string str_x, str_y, str_main, str_anti;
    string str_x2, str_y2, str_main2, str_anti2;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(user_input[i][j] != " "){
                str_x = "";
                str_y = "";
                str_main = "";
                str_anti = "";
                str_x2 = "";
                str_y2 = "";
                str_main2 = "";
                str_anti2 = "";
                x_input = j, y_input = i;
                for(int k=0 ;k<6; k++){
                    if(y_input+k < n){
                        str_x += user_input[y_input+k][x_input];
                    }
                    if(x_input+k < n){
                        str_y += user_input[y_input][x_input+k];
                    }
                    if(x_input+k < n && y_input+k<n){
                        str_main += user_input[y_input+k][x_input+k];
                    }
                    if(x_input-k >= 0 && y_input+k<n){
                        str_anti += user_input[y_input+k][x_input-k];
                    }
                    if(y_input-k >= 0){
                        str_x2 += user_input[y_input-k][x_input];
                    }
                    if(x_input-k >= 0){
                        str_y2 += user_input[y_input][x_input-k];
                    }
                    if(x_input-k >= 0 && y_input-k >= 0){
                        str_main2 += user_input[y_input-k][x_input-k];
                    }
                    if(x_input+k < n && y_input-k >= 0){
                        str_anti2 += user_input[y_input-k][x_input+k];
                    }
                }
                // tim "XXXX "
                if(str_x.find("XXXX ") != string::npos){
                    pos = str_x.find("XXXX ");
                    y_input += (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XXXX ") != string::npos){
                    pos = str_y.find("XXXX ");
                    x_input += (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XXXX ") != string::npos){
                    pos = str_main.find("XXXX ");
                    x_input += (pos + 4);
                    y_input += (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XXXX ") != string::npos){
                    pos = str_anti.find("XXXX ");
                    x_input -= (pos + 4);
                    y_input += (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XXXX ") != string::npos){
                    pos = str_x2.find("XXXX ");
                    y_input -= (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XXXX ") != string::npos){
                    pos = str_y2.find("XXXX ");
                    x_input -= (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XXXX ") != string::npos){
                    pos = str_main2.find("XXXX ");
                    x_input -= (pos + 4);
                    y_input -= (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XXXX ") != string::npos){
                    pos = str_anti2.find("XXXX ");
                    x_input += (pos + 4);
                    y_input -= (pos + 4);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim " XXXX"
                else if(str_x.find(" XXXX") != string::npos){
                    pos = str_x.find(" XXXX");
                    y_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find(" XXXX") != string::npos){
                    pos = str_y.find(" XXXX");
                    x_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find(" XXXX") != string::npos){
                    pos = str_main.find(" XXXX");
                    x_input += (pos);
                    y_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find(" XXXX") != string::npos){
                    pos = str_anti.find(" XXXX");
                    x_input -= (pos);
                    y_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find(" XXXX") != string::npos){
                    pos = str_x2.find(" XXXX");
                    y_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find(" XXXX") != string::npos){
                    pos = str_y2.find(" XXXX");
                    x_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find(" XXXX") != string::npos){
                    pos = str_main2.find(" XXXX");
                    x_input -= (pos);
                    y_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find(" XXXX") != string::npos){
                    pos = str_anti2.find(" XXXX");
                    x_input += (pos);
                    y_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "XXX X"
                else if(str_x.find("XXX X") != string::npos){
                    pos = str_x.find("XXX X");
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XXX X") != string::npos){
                    pos = str_y.find("XXX X");
                    x_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XXX X") != string::npos){
                    pos = str_main.find("XXX X");
                    x_input += (pos + 3);
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XXX X") != string::npos){
                    pos = str_anti.find("XXX X");
                    x_input -= (pos + 3);
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XXX X") != string::npos){
                    pos = str_x2.find("XXX X");
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XXX X") != string::npos){
                    pos = str_y2.find("XXX X");
                    x_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XXX X") != string::npos){
                    pos = str_main2.find("XXX X");
                    x_input -= (pos + 3);
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XXX X") != string::npos){
                    pos = str_anti2.find("XXX X");
                    x_input += (pos + 3);
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "XX XX"
                else if(str_x.find("XX XX") != string::npos){
                    pos = str_x.find("XX XX");
                    y_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XX XX") != string::npos){
                    pos = str_y.find("XX XX");
                    x_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XX XX") != string::npos){
                    pos = str_main.find("XX XX");
                    x_input += (pos + 2);
                    y_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XX XX") != string::npos){
                    pos = str_anti.find("XX XX");
                    x_input -= (pos + 2);
                    y_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XX XX") != string::npos){
                    pos = str_x2.find("XX XX");
                    y_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XX XX") != string::npos){
                    pos = str_y2.find("XX XX");
                    x_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XX XX") != string::npos){
                    pos = str_main2.find("XX XX");
                    x_input -= (pos + 2);
                    y_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XX XX") != string::npos){
                    pos = str_anti2.find("XX XX");
                    x_input += (pos + 2);
                    y_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "X XXX"
                else if(str_x.find("X XXX") != string::npos){
                    pos = str_x.find("X XXX");
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("X XXX") != string::npos){
                    pos = str_y.find("X XXX");
                    x_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("X XXX") != string::npos){
                    pos = str_main.find("X XXX");
                    x_input += (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("X XXX") != string::npos){
                    pos = str_anti.find("X XXX");
                    x_input -= (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("X XXX") != string::npos){
                    pos = str_x2.find("X XXX");
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("X XXX") != string::npos){
                    pos = str_y2.find("X XXX");
                    x_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("X XXX") != string::npos){
                    pos = str_main2.find("X XXX");
                    x_input -= (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("X XXX") != string::npos){
                    pos = str_anti2.find("X XXX");
                    x_input += (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "XXX  "
                else if(str_x.find("XXX  ") != string::npos){
                    pos = str_x.find("XXX  ");
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XXX  ") != string::npos){
                    pos = str_y.find("XXX  ");
                    x_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XXX  ") != string::npos){
                    pos = str_main.find("XXX  ");
                    x_input += (pos + 3);
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XXX  ") != string::npos){
                    pos = str_anti.find("XXX  ");
                    x_input -= (pos + 3);
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XXX  ") != string::npos){
                    pos = str_x2.find("XXX  ");
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XXX  ") != string::npos){
                    pos = str_y2.find("XXX  ");
                    x_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XXX  ") != string::npos){
                    pos = str_main2.find("XXX  ");
                    x_input -= (pos + 3);
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XXX  ") != string::npos){
                    pos = str_anti2.find("XXX  ");
                    x_input += (pos + 3);
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "  XXX"
                else if(str_x.find("  XXX") != string::npos){
                    pos = str_x.find("  XXX");
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("  XXX") != string::npos){
                    pos = str_y.find("  XXX");
                    x_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("  XXX") != string::npos){
                    pos = str_main.find("  XXX");
                    x_input += (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("  XXX") != string::npos){
                    pos = str_anti.find("  XXX");
                    x_input -= (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("  XXX") != string::npos){
                    pos = str_x2.find("  XXX");
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("  XXX") != string::npos){
                    pos = str_y2.find("  XXX");
                    x_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("  XXX") != string::npos){
                    pos = str_main2.find("  XXX");
                    x_input -= (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("  XXX") != string::npos){
                    pos = str_anti2.find("  XXX");
                    x_input += (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
            }
            else{
                str_x = "";
                str_y = "";
                str_main = "";
                str_anti = "";
                str_x2 = "";
                str_y2 = "";
                str_main2 = "";
                str_anti2 = "";
                x_input = j, y_input = i;
                for(int k=0 ;k<6; k++){
                    if(y_input+k < n){
                        str_x += user_input[y_input+k][x_input];
                    }
                    if(x_input+k < n){
                        str_y += user_input[y_input][x_input+k];
                    }
                    if(x_input+k < n && y_input+k<n){
                        str_main += user_input[y_input+k][x_input+k];
                    }
                    if(x_input-k >= 0 && y_input+k<n){
                        str_anti += user_input[y_input+k][x_input-k];
                    }
                    if(y_input-k >= 0){
                        str_x2 += user_input[y_input-k][x_input];
                    }
                    if(x_input-k >= 0){
                        str_y2 += user_input[y_input][x_input-k];
                    }
                    if(x_input-k >= 0 && y_input-k >= 0){
                        str_main2 += user_input[y_input-k][x_input-k];
                    }
                    if(x_input+k < n && y_input-k >= 0){
                        str_anti2 += user_input[y_input-k][x_input+k];
                    }
                }
                // tim "XXXX "
                if(str_x.find("XXXX ") != string::npos){
                    pos = str_x.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XXXX ") != string::npos){
                    pos = str_y.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XXXX ") != string::npos){
                    pos = str_main.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XXXX ") != string::npos){
                    pos = str_anti.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XXXX ") != string::npos){
                    pos = str_x2.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XXXX ") != string::npos){
                    pos = str_y2.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XXXX ") != string::npos){
                    pos = str_main2.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XXXX ") != string::npos){
                    pos = str_anti2.find("XXXX ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim " XXXX"
                else if(str_x.find(" XXXX") != string::npos){
                    pos = str_x.find(" XXXX");
                    y_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find(" XXXX") != string::npos){
                    pos = str_y.find(" XXXX");
                    x_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find(" XXXX") != string::npos){
                    pos = str_main.find(" XXXX");
                    x_input += (pos);
                    y_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find(" XXXX") != string::npos){
                    pos = str_anti.find(" XXXX");
                    x_input -= (pos);
                    y_input += (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find(" XXXX") != string::npos){
                    pos = str_x2.find(" XXXX");
                    y_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find(" XXXX") != string::npos){
                    pos = str_y2.find(" XXXX");
                    x_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find(" XXXX") != string::npos){
                    pos = str_main2.find(" XXXX");
                    x_input -= (pos);
                    y_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find(" XXXX") != string::npos){
                    pos = str_anti2.find(" XXXX");
                    x_input += (pos);
                    y_input -= (pos);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "XXX X"
                else if(str_x.find("XXX X") != string::npos){
                    pos = str_x.find("XXX X");
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XXX X") != string::npos){
                    pos = str_y.find("XXX X");
                    x_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XXX X") != string::npos){
                    pos = str_main.find("XXX X");
                    x_input += (pos + 3);
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XXX X") != string::npos){
                    pos = str_anti.find("XXX X");
                    x_input -= (pos + 3);
                    y_input += (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XXX X") != string::npos){
                    pos = str_x2.find("XXX X");
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XXX X") != string::npos){
                    pos = str_y2.find("XXX X");
                    x_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XXX X") != string::npos){
                    pos = str_main2.find("XXX X");
                    x_input -= (pos + 3);
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XXX X") != string::npos){
                    pos = str_anti2.find("XXX X");
                    x_input += (pos + 3);
                    y_input -= (pos + 3);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "XX XX"
                else if(str_x.find("XX XX") != string::npos){
                    pos = str_x.find("XX XX");
                    y_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XX XX") != string::npos){
                    pos = str_y.find("XX XX");
                    x_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XX XX") != string::npos){
                    pos = str_main.find("XX XX");
                    x_input += (pos + 2);
                    y_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XX XX") != string::npos){
                    pos = str_anti.find("XX XX");
                    x_input -= (pos + 2);
                    y_input += (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XX XX") != string::npos){
                    pos = str_x2.find("XX XX");
                    y_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XX XX") != string::npos){
                    pos = str_y2.find("XX XX");
                    x_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XX XX") != string::npos){
                    pos = str_main2.find("XX XX");
                    x_input -= (pos + 2);
                    y_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XX XX") != string::npos){
                    pos = str_anti2.find("XX XX");
                    x_input += (pos + 2);
                    y_input -= (pos + 2);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "X XXX"
                else if(str_x.find("X XXX") != string::npos){
                    pos = str_x.find("X XXX");
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("X XXX") != string::npos){
                    pos = str_y.find("X XXX");
                    x_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("X XXX") != string::npos){
                    pos = str_main.find("X XXX");
                    x_input += (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("X XXX") != string::npos){
                    pos = str_anti.find("X XXX");
                    x_input -= (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("X XXX") != string::npos){
                    pos = str_x2.find("X XXX");
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("X XXX") != string::npos){
                    pos = str_y2.find("X XXX");
                    x_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("X XXX") != string::npos){
                    pos = str_main2.find("X XXX");
                    x_input -= (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("X XXX") != string::npos){
                    pos = str_anti2.find("X XXX");
                    x_input += (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "XXX  "
                else if(str_x.find("XXX  ") != string::npos){
                    pos = str_x.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("XXX  ") != string::npos){
                    pos = str_y.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("XXX  ") != string::npos){
                    pos = str_main.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("XXX  ") != string::npos){
                    pos = str_anti.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("XXX  ") != string::npos){
                    pos = str_x2.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("XXX  ") != string::npos){
                    pos = str_y2.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("XXX  ") != string::npos){
                    pos = str_main2.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti2.find("XXX  ") != string::npos){
                    pos = str_anti2.find("XXX  ");
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                // tim "  XXX"
                else if(str_x.find("  XXX") != string::npos){
                    pos = str_x.find("  XXX");
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y.find("  XXX") != string::npos){
                    pos = str_y.find("  XXX");
                    x_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main.find("  XXX") != string::npos){
                    pos = str_main.find("  XXX");
                    x_input += (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("  XXX") != string::npos){
                    pos = str_anti.find("  XXX");
                    x_input -= (pos + 1);
                    y_input += (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_x2.find("  XXX") != string::npos){
                    pos = str_x2.find("  XXX");
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_y2.find("  XXX") != string::npos){
                    pos = str_y2.find("  XXX");
                    x_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_main2.find("  XXX") != string::npos){
                    pos = str_main2.find("  XXX");
                    x_input -= (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
                else if(str_anti.find("  XXX") != string::npos){
                    pos = str_anti2.find("  XXX");
                    x_input += (pos + 1);
                    y_input -= (pos + 1);
                    x_user = x_input;
                    y_user = y_input;
                    return true;
                }
            }
        }
    }
    return false;
}
bool add(){
    gotoXY(0,0);
    cout<<"HELLO";
    return true;
}
//---------Hàm chính-------------------------------
void bot_turn(){
    turn();
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(posAt, 2);
    change();
    if(block()){
        user_input[y_user][x_user] = player;
        x = 62+6*x_user;
        y = 7+2*y_user;
        gotoXY(x, y);
        cout<<player;
        return;
    }else{
        add();
    }
}
void control(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
	
    char arrow;
    int check_input = 0;
    x = whereX();
    y = whereY();
    if(_kbhit()){
        check_input++;
        arrow = _getch();
        if(arrow == -32){
            arrow = _getch();
        }
    }
    if(arrow == 13){
        if(user_input[y_user][x_user] == " "){
            user_input[y_user][x_user] = player;
            if(player == "X"){
                SetConsoleTextAttribute(posAt, 4);
            }else{
                SetConsoleTextAttribute(posAt, 2);
            }
            cout<<player;
            enter = true;
        }
    }else if(arrow == 75){
        if(x-6 >= x_start && check_input==1){
            x-=6;
            x_user-=1;
            //gotoXY(x, y);
            COORD curPos = { (short int)x, (short int)y };
	        SetConsoleCursorPosition(posAt, curPos);
        }
    }else if(arrow == 77){
        if(x+6 <= 122 && check_input==1){
            x+=6;
            x_user+=1;
            //gotoXY(x, y);
            COORD curPos = { (short int)x, (short int)y };
	        SetConsoleCursorPosition(posAt, curPos);
        }
    }else if(arrow == 72){
        if(y-2>=y_start && check_input==1){
            y-=2;
            y_user-=1;
            //gotoXY(x, y);
            COORD curPos = { (short int)x, (short int)y };
	        SetConsoleCursorPosition(posAt, curPos);
        }
    }else if(arrow == 80){
        if(y+2<=27 && check_input==1){
            y+=2;
            y_user+=1;
            //gotoXY(x, y);
            COORD curPos = { (short int)x, (short int)y };
	        SetConsoleCursorPosition(posAt, curPos);
        }
    }
}
void start_value(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            user_input[i][j] = " ";
        }
    }
}
void change(){
    if(player == "X") player="O";
    else player ="X";
}
void draw(string value){
    user_input[y_user][x_user] = value;

    int max_size = 2*n+1;
    int index_value = 0;
    int space = 5;
    int align = 58;
    for(int i=1; i<=max_size; i++){
        if(i%2==0){
            cout<<setw(align+1)<<" ";
        }
        for(int j=1; j<=max_size; j++){
            if(i==1){
                if(j==1){
                    char chr = 201;
                    cout<<setw(align+2)<<chr;
                }
                else if(j==max_size){
                    char chr = 187;
                    cout<<chr;
                }
                else if(j%2 != 0){
                    char chr = 203;
                    cout<<chr;
                } 
                else if (j%2 == 0){
                    char chr = 205;
                    for(int m=1; m<=space; m++){
                        cout<<chr;
                    }
                }
            }
            else if(i==max_size){
                if(j==1){
                    char chr = 200;
                    cout<<setw(align+2)<<chr;
                }
                else if(j==max_size){
                    char chr = 188;
                    cout<<chr;
                }
                else if(j%2 != 0){
                    char chr = 202;
                    cout<<chr;
                } else {
                    char chr = 205;
                    for(int m=1; m<=space; m++){
                        cout<<chr;
                    }
                }
            }
            else if(i%2==0){
                if(j%2 != 0){
                    char chr = 186;
                    cout<<chr;
                }else{
                    int tmp = (space+1)/2;
                    cout<<setw(tmp)<<user_input[index_value/n][index_value%n];
                    for(int m=1; m<=space-tmp; m++){
                        cout<<" ";
                    }
                    index_value++;
                }
            }
            else if(i%2!=0){
                if(j==1){
                    char chr = 204;
                    cout<<setw(align+2)<<chr;
                }else if(j==max_size){
                    char chr = 185;
                    cout<<chr;
                }else if(j%2 != 0){
                    char chr = 206;
                    cout<<chr;
                }else{
                    char chr = 205;
                    for(int m=1; m<=space; m++){
                        cout<<chr;
                    }
                }
            }
        }
        cout<<endl;
    }
}
void check_ans(){
    HANDLE change_color;
    change_color = GetStdHandle(STD_OUTPUT_HANDLE);
    bool check = false;
    if(checkx()){
        check = true;
    }
    if(checky()){
        check = true;
    }
    if(checkmaindia()){
        check = true;
    }
    if(checkantidia()){
        check = true;
    }

    if(check){
        mp[player]++;
        x = x_start, y = y_start;
        x_user = 0, y_user=0;
        gameover = true;
        system("cls");
        SetConsoleTextAttribute(change_color, 7);
    }
}
void gameplay1(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    player = "X";
    cout<<"\n\n\n\n";
    title();
    //----------khởi tạo các giá trị ban đầu của bàn cờ----------
    start_value();
    //----------Hiển thị bàn cờ trước khi bắt đầu----------------
    draw(" ");
    COORD curPos = { (short int)x, (short int)y };
    SetConsoleCursorPosition(posAt, curPos);
    gameover = false;
    //----------Bắt đầu chơi-----------------------
    int cnt_turn = 1;
    while(cnt_turn <= n*n && !gameover){
        turn();
        COORD curPos = { (short int)x, (short int)y };
        SetConsoleCursorPosition(posAt, curPos);
        cnt_turn ++;
        while(!enter){
            control();
        }
        enter = false;
        check_ans();
        change();
    }
}
void gameplay2(){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    player = "X";
    cout<<"\n\n\n\n";
    title();
    //----------khởi tạo các giá trị ban đầu của bàn cờ----------
    start_value();
    //----------Hiển thị bàn cờ trước khi bắt đầu----------------
    draw(" ");
    COORD curPos = { (short int)x, (short int)y };
    SetConsoleCursorPosition(posAt, curPos);
    gameover = false;
    int cnt_turn = 1;
    while(cnt_turn <= n*n && !gameover){
        turn();
        COORD curPos = { (short int)x, (short int)y };
        SetConsoleCursorPosition(posAt, curPos);
        cnt_turn ++;
        while(!enter){
            control();
        }
        enter = false;
        check_ans();
        bot_turn();
        change();
    }
}