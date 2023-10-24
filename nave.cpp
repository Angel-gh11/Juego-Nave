#include<stdio.h>
#include<windows.h>
#include<conio.h> //identificador de las teclas
#include<stdlib.h>
#include<list>
using namespace std; 

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y){
	
	//hCon es una variable y HANDLE es el identificador
	HANDLE hCon; //es la ventana con la ique vamos a manipular(consola de aplicaciones)
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	// la estructura de llama COORD
	COORD dwPos; // sus valores son cordenadas x-y
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon,dwPos); //identificador handle y una estructura de datos
	
}

void OcultarCursor(){
	HANDLE hCon; 
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci; //controla la apariencia del cursor que se muestra en pantalla
	cci.dwSize= 1; //tamaño de grosor que va a tener el cursor
	cci.bVisible= FALSE; //controla la visibilidad del cursor
	SetConsoleCursorInfo(hCon,&cci);
}

void pintar_limites(){
	for (int i=2; i<98; i++){
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,33); printf("%c",205); //asignar las lineas hotizontales del recuadro
	}
	
	for (int i=4; i<33; i++){
		gotoxy(2,i); printf("%c",186); //asignar las lineas verticales del recuadro
		gotoxy(97,i); printf("%c",186);
	}
	
	gotoxy(2,3); printf("%c",201); // para agisnar las esquinas del recuadro 
	gotoxy(2,33);  printf("%c",200);
	gotoxy(97,3);  printf("%c",187);
	gotoxy(97,33);  printf("%c",188);
}

class NAVE{
	private: 
	 int x,y;
	 int corazones;
	 int vidas;
	public:
	 NAVE(int _x,int _y, int _corazones, int _vidas);
	 int X();
	 int Y();
	 int Vidas();
	 void Hp();
	 void pintar();
	 void borar();
	 void mover();
	 void pintar_corazones();
	 void muere();
};

NAVE::NAVE( int _x, int _y, int _corazones, int _vidas){
	x= _x;
	y= _y;
	corazones=_corazones;
	vidas=_vidas;
}

int NAVE::X(){ 
    return x;
}

int NAVE::Y(){
	return y;
}

int NAVE::Vidas(){
	return vidas;
}

void NAVE::Hp(){
	corazones --;
}

void NAVE::pintar(){
	gotoxy(x,y); printf("  %c",30);
	gotoxy(x,y+1); printf(" %c%c%c",40,219,41);
	gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);
}

void NAVE::borar(){
	gotoxy(x,y); printf("        ");
	gotoxy(x,y+1); printf("        ");
	gotoxy(x,y+2); printf("        ");
} 

void NAVE::mover(){
	// la funcion kbhit() detecta si se oprimio una tecla
	if(kbhit()){
		char tecla=getch(); // la funcion getch() guarda el valor de la tecla que se presiona
		borar();
		if(tecla== IZQUIERDA && x>3) x--;
		if(tecla== DERECHA && x+6<97) x++;
		if(tecla== ARRIBA && y>4) y--;
		if(tecla== ABAJO && y+3<33) y++;
		pintar();
		pintar_corazones();
			
	}
}

void NAVE::pintar_corazones(){
	
	gotoxy(60,2); printf("Vidas restantes %d",vidas);
	gotoxy(84,2); printf("HP");
	gotoxy(90,2); printf("      ");
	
	for(int j=0; j<corazones; j++){
		gotoxy(90+j,2); printf("%c",3);	
	}
}

void NAVE::muere(){
	if(corazones==0){
		borar();
		gotoxy(x,y);   printf("   **   ");
		gotoxy(x,y+1); printf("  ****  ");
		gotoxy(x,y+2); printf("   **   ");
		Sleep(220);
		
		borar();
		gotoxy(x,y);   printf(" * ** *");
		gotoxy(x,y+1); printf("  **** ");
		gotoxy(x,y+2); printf(" * ** *");
		Sleep(220);
		
		borar();
		gotoxy(x,y);   printf("* *** *");
		gotoxy(x,y+1); printf("  ***  ");
		gotoxy(x,y+2); printf("* *** *");
		Sleep(220);
		
		borar();
		vidas--;
		corazones=5;
		pintar_corazones();
		pintar();
		
	}
}

class ASTEROIDES {
		private:
			int x,y;
		public:
		ASTEROIDES(int _x,int _y);	
		int X();
		int Y();
		void pintarAsteroides();
		void moverAsteroides();
		void chocaAsteroides(class NAVE &Nave);
		
};

ASTEROIDES::ASTEROIDES(int _x, int _y){
	x=_x;
	y=_y;
	
}

int ASTEROIDES::X(){
	return x;
}

int ASTEROIDES::Y(){
	return y;
}

void ASTEROIDES::pintarAsteroides(){
	gotoxy(x,y); printf("%c",225);
}

void ASTEROIDES::moverAsteroides(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y>32){
		x=rand() % 90 + 4; //la funcion rand() selecciona un numero cualquiera entre 0 y 90
		y=4;
	}
	pintarAsteroides();
}

void ASTEROIDES::chocaAsteroides(class NAVE &Nave){
	if(x>=Nave.X() && x<Nave.X()+6 && y>=Nave.Y() && y<=Nave.Y()+2){
		
	Nave.Hp();
	Nave.borar();
	Nave.pintar();
	Nave.pintar_corazones();
	
	x=rand() % 90 + 4; //la funcion rand() selecciona un numero cualquiera entre 0 y 90
	y=4;	
	}
}

class MUNICION{
	private:
		int x,y;
	public:
		MUNICION(int _x, int _y);
		int X();
		int Y();
		void mover();
		bool limite();
	 		
};

MUNICION::MUNICION(int _x, int _y){
	x=_x;
	y=_y;
}

int MUNICION::X(){
	return x;
}

int MUNICION::Y(){
	return y;
}

void MUNICION::mover(){
	gotoxy(x,y); printf(" ");
	if(y>4){
		y--;
	}
	gotoxy(x,y); printf("º");
}


bool MUNICION::limite(){
	if(y==4){
		return true;
	}else {
		return false;
	}
}

int main(){
	
	OcultarCursor();
	pintar_limites();
    NAVE nave(50,24,5,3);
	nave.pintar();
	nave.pintar_corazones();

	list<ASTEROIDES*> A;
	list<ASTEROIDES*>::iterator itA;
	
	for(int i=0; i<8; i++){
	A.push_back(new ASTEROIDES(rand() %90+3, rand() %5+4));	
	}
	
	list<MUNICION*> B;
	list<MUNICION*>::iterator it;
	
	int puntos=0;
	
	bool game_over = false;
	while(!game_over){
		
		gotoxy(4,2); printf("Puntaje %d", puntos);
		
		if(kbhit()){
			char tecla=getch();
			if(tecla=='q'){
				B.push_back(new MUNICION(nave.X()+2, nave.Y()-1)); //la funcion push_back() agrega una nueva municion a la lista 
			}
		}
		
		for (it=B.begin(); it!=B.end(); it++){
			(*it)->mover();
			if((*it)->limite()){
				gotoxy((*it)->X(),(*it)->Y());
				printf(" ");
				delete(*it);
				it=B.erase(it);
			}
		}
		
		for(itA=A.begin(); itA!=A.end(); itA++){
			(*itA)->moverAsteroides();
			(*itA)->chocaAsteroides(nave);
		}
		
		for(itA=A.begin(); itA!= A.end(); itA++){
			for(it=B.begin(); it!= B.end(); it++){
				if((*itA)->X() == (*it)->X() && ((*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() )){
				 
				 gotoxy((*it)->X(),(*it)->Y());
				 printf(" ");
				 delete(*it);
				 it=B.erase(it);
				 
				 A.push_back(new ASTEROIDES(rand() %90+3, 4));	
				 gotoxy((*itA)->X(),(*itA)->Y());
				 printf(" ");
				 delete(*itA);
				 itA=A.erase(itA);
				 
				 puntos=puntos+10;
				  
				}
			}
		}
		
		if(nave.Vidas()==0){
			game_over=true;
		}
		
		nave.muere();
		nave.mover();
		Sleep(30); //detiene lña ejecucuion del programa en este parametro por 30 ms
	}
	
	_getch();

	return 0;
}
