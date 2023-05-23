#include<bits/stdc++.h>
#include<conio.h>
#include"windows.h"
using namespace std;
//--------các biến chính----------
int n=11, x=62, y=7, times, x_user=0, y_user=0;
int x_start = x, y_start = y;
string player = "X";
string user_input[11][11];
bool gameover = false, enter = false;
map<string, int>mp = {{"X",0}, {"O",0}};


//----------------Khai báo nguyên hàm-----------------------------
//-----------Hàm phụ-------------------
int whereX();
int whereY();
void title();
void turn();

//-----------Hàm phụ để kiểm tra kết quả-------------
bool checkx(); //check cột
bool checky(); // check hàng
bool checkmaindia(); // check chéo chính
bool checkantidia(); // check chéo phụ

//-----------Hàm chính----------------
void control();
void draw(string value); // vẽ bàn cờ với giá trị value vừa được nhập
void change(); // đổi người chơi
void start_value(); // khởi tạo giá trị ban đầu của bàn cờ
void check_ans(); // kiểm tra thắng thua

//------------main---------
int main (){
    HANDLE posAt;
    posAt = GetStdHandle(STD_OUTPUT_HANDLE);
    
    int q;
    cout<<"Nhap vao so van ban muon choi: ";
    cin>>q;
    system("cls");
    cout<<endl;
    for(times = 1; times<=q; times++){
        player = "X";
        //cout<<"\n\n\n";
        if(times != 1){
            cout<<"\n\n";
        }else{
            cout<<"\n\n\n";
        }
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
        cout<<"\n\n";
    }
    int align = 72;
    string in_ans, out_ans;
    for(int k=1; k<=12; k++){
        char in_char = 175, out_char = 174;
        in_ans+=in_char;
        out_ans+=out_char;
    }
    cout<<setw(align)<<" ";
    cout<<in_ans<<" X   "<<mp["X"]<<":"<<mp["O"]<<"   O "<<out_ans<<endl;
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
void title(){
    int align = 72;
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
    cout<<setw(95)<<"Luot cua ";
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

//---------Hàm chính-------------------------------
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
