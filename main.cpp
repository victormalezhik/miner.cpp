
#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
 
using namespace std;
 
// N - ������ ���� �� ��������� (��� ����������); M - ����� ��� �� ����
#define N 10
#define M 10
 
// ����, � ������ ���������� ��������, ������������ �� ����, ��� �������
int matrix[N][N];
bool open[N][N];
 
// ��������� ������ �� ���� ����� �� ������� ���������� false
bool mine(int i, int j){
    if((i>=0) && (i<N)){
        if((j>=0) && (j<N)){
            if(matrix[i][j]==-1) return true;
        }
    }
    return false;
}
 
// ��������� ������ �� ������� (true), ����� �� ������� ������� ���������� false
bool empty(int i, int j){
    if((i>=0) && (i<N)){
        if((j>=0) && (j<N)){
            if(matrix[i][j]==0) 
				return true;
        }
    }
    return false;
}
 
// ����������� �������, ������� ��������� ���� � ����� ���������
void clean(int i,int j){
    // �������� �� ����� �� ������� �������
    if((i>=0) && (i<N)){
        if((j>=0) && (j<N)){
            // ��������, �� ���� �� ������� ���� ������
            if(!open[i][j]){
                // �������
                open[i][j]=true;
                // ���� ���� ������ (=0), ������ ����������� ���� ��� �������
                if(matrix[i][j]==0){
                    clean(i-1,j-1);
                    clean(i-1,j);
                    clean(i-1,j+1);
                    clean(i,j-1);
                    clean(i,j+1);
                    clean(i+1,j-1);
                    clean(i+1,j);
                    clean(i+1,j+1);
                }
                // ���� �� ������ (!=0) ��������� ������ ������ (=0) �������
                else{
                    if(empty(i-1,j-1)) 
						clean(i-1,j-1);
                    if(empty(i-1,j)) 
						clean(i-1,j);
                    if(empty(i-1,j+1)) 
						clean(i-1,j+1);
                    if(empty(i,j-1)) 
						clean(i,j-1);
                    if(empty(i,j+1)) 
						clean(i,j+1);
                    if(empty(i+1,j-1)) 
						clean(i+1,j-1);
                    if(empty(i+1,j)) 
						clean(i+1,j);
                    if(empty(i+1,j+1)) 
						clean(i+1,j+1);
                }
            }
        }
    }
}
 
// ������ "����" - ��������� �������� �����
void coutmine(HANDLE hConsole){
    SetConsoleTextAttribute(hConsole, 12);  // red text
    cout<<"* ";
    SetConsoleTextAttribute(hConsole, 7);   // white text
}
 
// ������ ������ ���� � ������ �������� � �������� �����
// � ��������������� ���
void draw_matrix(HANDLE hConsole){
    SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
    cout<<"  A B C D E F G H I J"<<endl;
    SetConsoleTextAttribute(hConsole, 7);  // white text
    for(int x=0;x<N;x++){
        SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
        cout<<x<<" ";
        SetConsoleTextAttribute(hConsole, 7);  // white text
        for(int y=0;y<N;y++){
            if(open[x][y]){
                SetConsoleTextAttribute(hConsole, 8);  // gray text
                if(matrix[x][y]==-1) coutmine(hConsole);
                else if(matrix[x][y]==0) cout<<". ";
                else cout<<matrix[x][y]<<" ";
                SetConsoleTextAttribute(hConsole, 7);  // white text
            }
            else{
                
                cout<<"# ";
                
            }
        }
        cout<<"\n";
    }
}
 
// ������� ��������� ����, ������ ���� �� ���� �������� "Gameover!" ��� "Congratulations!"
void fin(HANDLE hConsole, bool loser){
    COORD coord;
    coord.X = 33;
    coord.Y = 10;
    system("cls");
    draw_matrix(hConsole);
    SetConsoleCursorPosition(hConsole, coord);
    if(loser){
        SetConsoleTextAttribute(hConsole, 12);  // red text
        cout<<"G A M E O V E R";
        SetConsoleTextAttribute(hConsole, 7);  // white text
    }
    else{
        SetConsoleTextAttribute(hConsole, 10);  // red text
        cout<<"C O N G R A T U L A T I O N S";
        SetConsoleTextAttribute(hConsole, 7);  // white text
    }
    cout<<"\n\n\n\n";
    getch();
}
 
// � ������ ��������� ��� ������� ������� ��� ����
void openmines(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(matrix[i][j]==-1) open[i][j]=true;
        }
    }
}
 
// ���������, ��� �� ���� �������, ����� ���
bool checkwin(){
    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++){
            if((matrix[x][y]!=-1) && (!open[x][y])) return false;
        }
    }
    return true;
}
 
 
int main(int argc,char argv[])
{
    int i,j,k=0;
    char s[3];
    // ����� ���� ��������� ��� ��������� �������� ������
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �������������
    setlocale(0, "rus");
    srand((int)time(NULL));
    
    // ��� ������
    for(int c=0;c<100;c++){ matrix[c/10][c%10]=0; open[c/10][c%10]=false; }
    // ��������� ������ ���� ������
    for(int c=0;c<M;c++){
        do{
            i=rand()%N; j=rand()%N;
        }while(matrix[i][j]!=0);
        matrix[i][j]=-1;
    }
    // ��������� ������ ���� �������
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(matrix[i][j]!=-1){
                k=0;
                if(mine(i-1,j-1)) k++;
                if(mine(i-1,j)) k++;
                if(mine(i-1,j+1)) k++;
                if(mine(i,j-1)) k++;
                if(mine(i,j+1)) k++;
                if(mine(i+1,j-1)) k++;
                if(mine(i+1,j)) k++;
                if(mine(i+1,j+1)) k++;
                matrix[i][j]=k;
            }
        }
    }
 
    // ������� ������� ����
    while(true){
        // ������ ����� �� ������� �������
        system("cls");
        // ������ ����
        draw_matrix(hConsole);
        cout<<"\n";
        // ����������� ���������� �����
        cout<<"������� ���������� ����� (������:C3): ";
        cin>>s;
        // ��������� ���������� � �������� ���
        if((s[0]>=65) && (s[0]<=74)) 
			j=s[0]-65;        // ����� � ���������� �� A �� J
        else if((s[0]>=97) && (s[0]<=106)) 
			j=s[0]-97;  // ����� � ���������� �� a �� j
        else continue;                              // ���� ������� �������� ��������, ������� � ������ �����
        if((s[1]>=48)&&(s[1]<=57)) 
			i=s[1]-48;
        else continue;
        // ����� ��������� ��� ������ ��������� ����� �� ������ ������
        // � ���� ���� ���������� ����� ����� ����
        clean(i,j);
 
        if(mine(i,j)){ 
			openmines(); 
			fin(hConsole,true); 
			break; 
		}  // ��������� �������� ���� � ������ ���������
        if(checkwin()){ 
			fin(hConsole, false); 
			break; 
		}                 // ��� ������
    }
 
    return 0;
}