
#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
 
using namespace std;
 
// N - размер поля по умолчанию (оно квадратное); M - число мин на поле
#define N 10
#define M 10
 
// поле, и массив логических значений, обозначающий те поля, что открыты
int matrix[N][N];
bool open[N][N];
 
// проверяет ячейку на мину выход за пределы возвращает false
bool mine(int i, int j){
    if((i>=0) && (i<N)){
        if((j>=0) && (j<N)){
            if(matrix[i][j]==-1) return true;
        }
    }
    return false;
}
 
// проверяет ячейку на пустоту (true), выход за пределы массива возвращает false
bool empty(int i, int j){
    if((i>=0) && (i<N)){
        if((j>=0) && (j<N)){
            if(matrix[i][j]==0) 
				return true;
        }
    }
    return false;
}
 
// рекурсивная функция, которая открывает поля в точке попадания
void clean(int i,int j){
    // проверим на выход за пределы массива
    if((i>=0) && (i<N)){
        if((j>=0) && (j<N)){
            // проверим, не было ли открыто поле раньше
            if(!open[i][j]){
                // откроем
                open[i][j]=true;
                // если поле пустое (=0), просто пооткрываем всех его соседей
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
                // если не пустое (!=0) открываем только пустых (=0) соседей
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
 
// рисует "мину" - звездочку красного цвета
void coutmine(HANDLE hConsole){
    SetConsoleTextAttribute(hConsole, 12);  // red text
    cout<<"* ";
    SetConsoleTextAttribute(hConsole, 7);   // white text
}
 
// рисует минное поле с учетом открытых и закрытых полей
// и вспомогательные оси
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
 
// функция завершает игру, выведя одну из двух надписей "Gameover!" или "Congratulations!"
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
 
// в случае проигрыша эта функция откроет все мины
void openmines(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(matrix[i][j]==-1) open[i][j]=true;
        }
    }
}
 
// проверяет, все ли поле открыто, кроме мин
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
    // хэндл экна необходим для рисования цветного текста
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // инициализация
    setlocale(0, "rus");
    srand((int)time(NULL));
    
    // все чистим
    for(int c=0;c<100;c++){ matrix[c/10][c%10]=0; open[c/10][c%10]=false; }
    // заполняем массив поля минами
    for(int c=0;c<M;c++){
        do{
            i=rand()%N; j=rand()%N;
        }while(matrix[i][j]!=0);
        matrix[i][j]=-1;
    }
    // заполняем массив поля цифрами
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
 
    // главный игровой цикл
    while(true){
        // чистим экран от старого рисунка
        system("cls");
        // рисуем поле
        draw_matrix(hConsole);
        cout<<"\n";
        // запрашиваем координаты удара
        cout<<"Введите координаты удара (Пример:C3): ";
        cin>>s;
        // переводим координаты в цифровой вид
        if((s[0]>=65) && (s[0]<=74)) 
			j=s[0]-65;        // буква в промежутке от A до J
        else if((s[0]>=97) && (s[0]<=106)) 
			j=s[0]-97;  // буква в промежутке от a до j
        else continue;                              // если введены неверные значения, возврат в начало цикла
        if((s[1]>=48)&&(s[1]<=57)) 
			i=s[1]-48;
        else continue;
        // далее проверяем все восемь окрестных полей на пустые клетки
        // и если надо показываем некий кусок поля
        clean(i,j);
 
        if(mine(i,j)){ 
			openmines(); 
			fin(hConsole,true); 
			break; 
		}  // программа покидает цикл в случае проигрыша
        if(checkwin()){ 
			fin(hConsole, false); 
			break; 
		}                 // или победы
    }
 
    return 0;
}