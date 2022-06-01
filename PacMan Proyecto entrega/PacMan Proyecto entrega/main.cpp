#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sstream>
#include <unistd.h>
#include <cstdio>


using namespace std;

#define ARRIBA     72    
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13


int backcolor=0;
int dir = 0;
int x=39,y=22;
int anteriorpx,anteriorpy;
char tecla;

//Variables
long int monedas = -5;
long int puntos = 0;
int vidas = 3;
long int mon=1;
int vid = 1;
int partidas;

void setCColor( int color){
        static HANDLE hConsole;

        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

        SetConsoleTextAttribute( hConsole, color | (backcolor * 0x10 + 0x100) );
}
int color[7] = {
      0x009,
      0x006,
      0x00C,
      0x002,
      0x00B,
      0x005,
      0x00F

     };
void gotoxy(int x, int y) {
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}


//Ocultar cursor
void OcultarCursor(){
    HANDLE hCon;//identificador
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);//declaracion de variable
    CONSOLE_CURSOR_INFO cci;//estructura que tiene dos atributos con los ques epuede controlar la apariencia del cursor
    cci.dwSize = 2;//Atributo de la estructura controla el tamaño del cursor
    cci.bVisible = FALSE;//para que el cursor se muestre en pantalla
    SetConsoleCursorInfo(hCon,&cci);//funcion dos parametros
 }
 
 
//Mapa
char mapa[50][100] = {
"                                                      ",
     "                  AXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXB",
     "                  Y_________________________________________Y",
     "                  Y_AXXXXXB_AXXXXXXXB_AXB_AXXXXXXXB_AXXXXXB_Y",
     "                  Y_Y     Y_Y       Y_Y Y_Y       Y_Y     Y_Y",
     "                  Y_DXXXXXC_DXXXXXXXC_DXC_DXXXXXXXC_DXXXXXC_Y",
     "                  Y________|_________|___|_________|________Y",
     "                  Y_AXXXXXB_AXB_AXXXXXXXXXXXXXB_AXB_AXXXXXB_Y",
     "                  Y_DXXXXXC_Y Y_DXXXXB   AXXXXC_Y Y_DXXXXXC_Y",
     "                  Y_________Y Y______Y   Y______Y Y_________Y",
     "                  DXXXXXXXB_Y DXXXXB_Y   Y_AXXXXC Y_AXXXXXXXC",
     "                  XXXXXXXXC_Y AXXXXC_DXXXC_DXXXXB Y_DXXXXXXXX",
     "                  ________|_Y Y_________________Y Y_|________",
     "                  XXXXXXXXB_DXC_AXXXXXX XXXXXXB_DXC_AXXXXXXXX",
     "                          Y_____Y      *      Y_____Y        ",
     "                  XXXXXXXXC_AXB_DXXXXXXXXXXXXXC_AXB_DXXXXXXXX",
     "                  ________|_Y Y_________________Y Y_|________",
     "                  XXXXXXXXB_Y Y_AXXXXXXXXXXXXXB_Y Y_AXXXXXXXX",
     "                  AXXXXXXXC_DXC_DXXXXB   AXXXXC_DXC_DXXXXXXXB",
     "                  Y________|_________Y   Y_________|________Y",
     "                  Y_AB_AXXB_AXXXXXXB_Y   Y_AXXXXXXB_AXB_AXB_Y",
     "                  Y_YY_Y  Y_DXXXXXXC_DXXXC_DXXXXXXC_Y Y_Y Y_Y",
     "                  Y_YY_Y  Y_________|_____|_________Y Y_Y Y_Y",
     "                  Y_YY_Y  Y_AXB_AXXXXXXXXXXXXXB_AXB_Y Y_Y Y_Y",
     "                  Y_DC_DXXC_Y Y_DXXXXXXXXXXXXXC_Y Y_DXC_DXC_Y",
     "                  Y_________Y Y_________________Y Y_________Y",
     "                  Y_AXXXXXXXC DXXXXB_AXXXB_AXXXXC DXXXXXXXB_Y",
     "                  Y_DXXXXXXXXXXXXXXC_DXXXC_DXXXXXXXXXXXXXXC_Y",
     "                  Y_________________|_____|_________________Y",
     "                  DXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXC",
};



//Pintar mapa 
void pintar_mapa(){
     for(int i = 0 ; i < 78 ; i++){
         for(int j = 0 ; j < 30 ; j++){
               gotoxy(i,j);

               if(mapa[j][i] == 'X') {setCColor(color[5]);printf("%c",205);}
               if(mapa[j][i] == '_') {setCColor(color[1]); printf("%c",250);}
               else if(mapa[j][i] == 'Y') {setCColor(color[5]);printf("%c",186);}
               else if(mapa[j][i] == 'A') {setCColor(color[5]);printf("%c",201);}
               else if(mapa[j][i] == 'B') {setCColor(color[5]);printf("%c",187);}
               else if(mapa[j][i] == 'C') {setCColor(color[5]);printf("%c",188);}
               else if(mapa[j][i] == 'D') {setCColor(color[5]);printf("%c",200);}


         }
     }
}

//PacMan
void pacman(int x , int y){
     setCColor(color[1]);
     gotoxy(x,y); printf("%c",2);
}
void borrar_pacman(int x, int y){
     gotoxy(x,y); printf(" ");
     if(mapa[y][x] == '_'){ mapa[y][x] = ' '; monedas += 5; puntos += 1;}
}


//Guardado
void guardar() {
     ofstream archivo;
     string linea;
     int vecesg = 1;
       archivo.open("datos.txt",ios::out | ios::app);
      if(archivo.fail()){
         cout<<"No se pudo guardar la partida";
        exit(0);
      }
     archivo << vidas << endl;
     archivo << monedas <<endl;
     archivo.close();
     cout << "\n\n\t\t\tPartida guardada" << endl;
     fstream file0;
       file0.open("gdata.txt",ios::out | ios::app);
     file0 << vecesg << endl;
     if (file0.fail()){
	   getline(file0,linea); 
      vecesg+=1;
      ofstream file3;
      file3.open("guardardata2.txt",ios::out | ios::app);
      file3 <<vecesg<<endl;
      remove("gdata.txt");                
      rename ("gardardata2.txt", "gdata.txt");
     }
      exit(0);
 }
 
 
//Menu que permite al usuario guardar partida
void MenuGuardar(){

       int opcion;
    bool repetir = true;

    do
    {
        system("cls");

        // Texto del menú que se verá cada vez
     
        cout << "\n\n\t\t\tDesea Guardar Partida?" << endl;
        cout << "\t\t\t----------------" << endl;
        cout << "\n\t1. Si" << endl;
        cout << "\t2. No" << endl;
        
        
        
        cout << " "<< endl;
		cout << " "<< endl;
 
        
        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        int numero1, numero2;
        float resultado;
        switch (opcion)
        {
        case 1:
        		system("CLS");
             guardar();
        
            
            break;
             
        case 2: 
        cout << "\n\tGracias por Jugar :)"<< endl; 
            repetir = false;
            exit(0);
            break;
        }
    		
		
		 
    } while (repetir=false);
    


}


//Movimiento
void teclear(){
    if(kbhit()){
      tecla = getch();
      switch(tecla){
      case ARRIBA:
         dir = 0;
         break;

      case ABAJO:
         dir = 1;
         break;

      case DERECHA:
         dir = 2;
         break;

      case IZQUIERDA:
         dir = 3;
         break;
         
        case ESC:
        	system("cls");
        	MenuGuardar();
        	break;

      }

   }

}


//Fantasma
class fantasma{
      int fdir;
      int _x, _y;
      int col;
public:
      fantasma(int x , int y , int color);
      void dibujar_fantasma() const;
      void borrar_fantasma() const;
      void mover_fantasma();
      void choque_pacman();
};
fantasma::fantasma(int x , int y, int color){
      _x = x;
      _y = y;
      col = color;
      fdir = rand()%4;
}
void fantasma::dibujar_fantasma() const{

     setCColor(color[col]);
     gotoxy(_x,_y); printf("%c",6);
}
void fantasma::borrar_fantasma() const{

     gotoxy(_x,_y); printf(" ");
}
void fantasma::choque_pacman(){
     if(y == _y && x == _x || (fdir == 0 && dir == 1 || fdir == 1 && dir == 0
     ||fdir == 2 && dir == 3 || fdir == 3 && dir == 2 )&&(_y == anteriorpy && _x == anteriorpx)){


      x = 39;
      y = 22;
      dir = 4;
      vidas--;

     }


}
void fantasma::mover_fantasma(){
     borrar_fantasma();
     choque_pacman();
     int bolx=_x,boly=_y;

     if(mapa[_y][_x] == '|'){
             fdir = rand()%4;
     }
     if(mapa[_y][_x] == '*'){
             fdir = 0;
     }

     if(fdir == 2){
          if(mapa[_y][_x+1] != 'X' && mapa[_y][_x+1] != 'A' && mapa[_y][_x+1] != 'Y' &&
          mapa[_y][_x+1] != 'B' && mapa[_y][_x+1] != 'C' && mapa[_y][_x+1] != 'D')         _x++;
          else fdir = rand()%4;
     }
     if(fdir == 3){
          if(mapa[_y][_x-1] != 'X' && mapa[_y][_x-1] != 'A' && mapa[_y][_x-1] != 'Y' &&
          mapa[_y][_x-1] != 'B' && mapa[_y][_x-1] != 'C' && mapa[_y][_x-1] != 'D')          _x--;
          else fdir = rand()%4;
     }
     if(fdir == 0){
          if(mapa[_y-1][_x] != 'X' && mapa[_y-1][_x] != 'A' && mapa[_y-1][_x] != 'Y' &&
          mapa[_y-1][_x] != 'B' && mapa[_y-1][_x] != 'C' && mapa[_y-1][_x] != 'D')           _y--;
          else fdir = rand()%4;
     }
     if(fdir == 1){
          if(mapa[_y+1][_x] != 'X' && mapa[_y+1][_x] != 'A' && mapa[_y+1][_x] != 'Y' &&
      mapa[_y+1][_x] != 'B' && mapa[_y+1][_x] != 'C' && mapa[_y+1][_x] != 'D')                _y++;
          else fdir = rand()%4;
     }

     if(mapa[boly][bolx] == '_') {setCColor(color[1]); gotoxy(bolx,boly);printf("%c",250);}

     // rutina atajo
     if(_x <= 17) _x = 61;
        else if(_x >= 62) _x = 18;
     dibujar_fantasma();
}


//Marcador 
void marcador(){


   gotoxy(5,4); printf("MONEDAS");
   gotoxy(5,6); printf("    ");
   setCColor(color[6]);
   gotoxy(5,6); printf("%ld",monedas);

   setCColor(color[1]);
   gotoxy(5,25); printf("VIDAS");
   for(int i = 0 ; i <= vidas ; i++){
       gotoxy(5,i+27);printf(" ");

   }
   for(int i = 0 ; i < vidas ; i++){
       gotoxy(5,i+27);printf("%c",2);

   }
   setCColor(color[2]);
   gotoxy(70,27);printf("%c",169);


}


//Funciones

void Iniciar();
void Cargar();
void leer();
void MenuGuardar();
void OcultarCursor();

//Menu que aparece al momento de que el usuario se queda sin vidas
void MenuMuerte(){

       int opcion;
    bool repetir = true;

    do
    {
        system("cls");

        // Texto del menú que se verá cada vez
     
        cout << "\n\n\t\t\tFin del Juego" << endl;
        cout << "\t\t\t----------------" << endl;
        cout << "\n\n\t\t\Desea continuar a cambio de sus monedas?" << endl;
        cout << "\n\t1. Si" << endl;
        cout << "\t2. No" << endl;
        
        
        
        cout << " "<< endl;
		cout << " "<< endl;
 
        
        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        int numero1, numero2;
        float resultado;
        switch (opcion)
        {
        case 1:
        		system("CLS");
            if (monedas < 100)  {
		         cout << "\n\tNo hay monedas suficientes"<< endl; 
		         system("pause");
        	}
        	else{
              vidas+=1;
              monedas -= 100;
              Iniciar();
            }
            break;
             
        case 2: 
         
            repetir = false;
            
            break;
        }
    		
		
		 
    } while (repetir=false);
    


}



		
//Ejecución del juego
void Iniciar()
{
   fantasma A(41,14,2);
   fantasma B(43,14,3);
   fantasma C(40,14,4);
   fantasma D(39,14,5);
   pintar_mapa();
  

   while(vidas > 0){
      marcador();
      borrar_pacman(x,y);
      anteriorpx = x; anteriorpy = y;
      teclear();
      if(dir == 0 && mapa[y-1][x] != 'X' && mapa[y-1][x] != 'A' && mapa[y-1][x] != 'Y' &&
      mapa[y-1][x] != 'B' && mapa[y-1][x] != 'C' && mapa[y-1][x] != 'D')                       y--;

      else if(dir == 1 && mapa[y+1][x] != 'X' && mapa[y+1][x] != 'A' && mapa[y+1][x] != 'Y' &&
      mapa[y+1][x] != 'B' && mapa[y+1][x] != 'C' && mapa[y+1][x] != 'D')                       y++;

      pacman(x,y);
      Sleep(55);
      borrar_pacman(x,y);

      B.choque_pacman();
      C.choque_pacman();
      D.choque_pacman();
      A.choque_pacman();

      anteriorpx = x; anteriorpy = y;
      teclear();

      if(dir == 2 && mapa[y][x+1] != 'X' && mapa[y][x+1] != 'A' && mapa[y][x+1] != 'Y' &&
      mapa[y][x+1] != 'B' && mapa[y][x+1] != 'C' && mapa[y][x+1] != 'D')                       x++;


      else if(dir == 3 && mapa[y][x-1] != 'X' && mapa[y][x-1] != 'A' && mapa[y][x-1] != 'Y' &&
      mapa[y][x-1] != 'B' && mapa[y][x-1] != 'C' && mapa[y][x-1] != 'D')                         x--;

      A.mover_fantasma();
      B.mover_fantasma();
      C.mover_fantasma();
      D.mover_fantasma();
      pacman(x,y);
      Sleep(55);

      if(x < 17) {
        borrar_pacman(x,y);
        x = 61;
      }
      else if(x > 62){
        borrar_pacman(x,y);
        x= 18;
      }
      if (puntos == 417) {
      	 system("cls");
      	 cout << "\n\tFelicidades, ganaste"<< endl;
      	 system("pause");
      	     return ;
	  }


   }



   for(int i = 0 ; i <= vidas ; i++){
       gotoxy(5,i+27);printf(" ");
     

   
   }
   
   
   MenuMuerte();
  
}

//Función que permite cargar la partida
    void leer()
{
	   int veces=0;
	   string linea;
	   string datos[2];
	   int c = 0;
	   ifstream archivo ;	   
	   archivo.open("datos.txt",ios::in);
	   if(archivo.fail()){
	      cout<<"No se pudo abrir el archivo";
	      exit(0);
        }	   
	   while (!archivo.eof()) {
	   getline(archivo,linea);
	   	datos[c]= linea;
	   	c++;
    } 
       archivo.close();
      
      string vidas1 = (datos[0]);
      string monedas1 = (datos[1]);
      istringstream(vidas1) >> vidas;
      istringstream(monedas1) >> monedas;
      
    fstream file1;
       file1.open("cdata.txt",ios::out | ios::app);
     file1 << veces << endl;
     if (file1.fail()){
	   getline(file1,linea); 
      veces+=1;
      ofstream file2;
      file2.open("cargardata2.txt",ios::out | ios::app);
      file2 <<veces<<endl;
      remove("cdata.txt");                
      rename ("cargardata2.txt", "cdata.txt");
     }
       Iniciar();	    
}


//Función que permite contabilizar cuantas veces se guardó y se cargó la partida
void GuardarYCargar(){
string linea;
            cout << "veces que se gaurdo la partida:"<<endl;
            ifstream file0 ;	   
	          file0.open("gdata.txt",ios::in);
	         if(file0.fail()){
	         cout<<"No se pudo abrir el archivo";
	         exit(0);
        }	   
        
	   while (!file0.eof()) {
	   getline(file0,linea);
	   cout << (file0,linea) <<endl;
		}

        cout <<"veces que se cargo la partida:"<<endl;
        ifstream file1 ;	   
	        file1.open("gdata.txt",ios::in);
	         if(file1.fail()){
	         cout<<"No se pudo abrir el archivo";
	         exit(0);
        }	   
        
	   while (!file1.eof()) {
	   getline(file1,linea);
	   cout<<(file1,linea)<<endl;
	}
}


// Menu De Inicio
int main()
{

    OcultarCursor();
    int opcion;
    bool repetir = true;

    do
    {
        system("cls");

        // Texto del menú que se verá cada vez
     
        cout << "\n\n\t\t\tMenu de Opciones" << endl;
        cout << "\t\t\t----------------" << endl;
        cout << "\n\t1. Nueva Partida" << endl;
        cout << "\t2. Cargar ultimo punto de control" << endl;
        cout << "\t3. Lista de partidas guardadas y cargadas" << endl;
        cout << "\t0. SALIR" << endl;
        
        cout << " "<< endl;
		cout << " "<< endl;
        
        cout << "\n\tInstructivo: ";
        cout << "\n\t|||Nueva partida le permite jugar por primera vez al juego|||";
        cout << "\n\t|||Carga la ultima partida|||";
		cout << "\n\t|||Le permite revisar una lista con todas las partidas guardadas|||"<< endl;
		cout << "\n\t|||Para guardar una partida presione ESC durante la partida|||"<< endl;
		        
        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        int numero1, numero2;
        float resultado;
        switch (opcion)
        {
        case 1:
        	
        	
        	system("CLS");
        	
        	
            Iniciar();
            system("CLS");
            leer();
            break;
            

        case 2:
         	
        system("CLS");	
         leer();
            
            break;

        case 3:
        	system("CLS");
        	GuardarYCargar();
            
            system ("pause");
            break;

        case 0:
            repetir = false;
            break;
        }
    		
		
		 
    } while (repetir=false);
    

	return 0 ;
}



