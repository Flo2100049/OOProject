#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;
enum Direction  { STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4, UPLEFT = 5, UPRIGHT = 6, DOWNLEFT = 7, DOWNRIGHT = 8 }; //Gia thn tuxaia kinish ton vampire kai Lukantropon

char av, Day = 'M';              //Global metabliti pou deixni poia omada upostirizei o Avatar kai an einai prwh h nuxta
int WIDTH, HEIGHT;               //Global metablhtes gia ths diastashs tou xarth 
int  Alvamp, Alwere;

void Pause() {
	cout << "                         ##################################" << endl;
	cout << "                         ######       GAME PAUSE      #####" << endl;
	cout << "                         ##################################" << endl << endl << endl;
	cout << "-ALIVE WEREWOLFS: " << Alvamp << endl;
	cout << "-ALIVE VAMPIRES: " << Alwere << endl;
}

class Original        //Yperklash apo thn opoia klhronomountai oi klaseis Vampires kai Werewolfs
{
private:
	int x, y;   // Ta shmeia mesa ston xarth
}; 

class OBSTACLES: private Original {      //Klash gia ta dentra kai ta potamia
private:
	int DentroX = NULL;            
	int DentroY = NULL;
	int PotamiX = NULL;
	int PotamiY = NULL;
public:
	OBSTACLES(int x, int y, int z, int k) {
		DentroX = x;
		DentroY = y;
		PotamiX = z;
		PotamiY = k;
	}
	int GetDentroX() { return DentroX; }
	int GetDentroY() { return DentroY; }
	int GetPotamiX() { return PotamiX; }
	int GetPotamiY() { return PotamiX; }
};

class Vampires : private Original
{

private:
	int x;
    int y;
	int ugeia = (rand() % 3 + 1);
	int dinami = (rand() % 3 + 1);
	int amina = (rand() % 2 + 1);
	int iatriko = (rand() % 2);
	Direction drion;
public: 
	Vampires(int CordinareX, int CordinareY) { x = CordinareX; y = CordinareY; drion = STOP; }

	int GetX() {return x;}
	int GetY() {return y;}
	int GetYgeia() {return ugeia;}
	int GetDinami() {return dinami;}
	int GetAmina() {return amina;}
	int GetIatriko() {return iatriko;}

	void DamageUgeia() {ugeia--;}
	void DamageAmina() {amina--;}
	void GiveIatriko() {iatriko--;}
	void TakeIatriko() {ugeia++;}

	void Lose() {
		drion = STOP;
		x = NULL;
		y = NULL;
	}

	void ChangeDirection(Direction d) {
		drion = d;
	}
	void RandomDirection() {
		drion = (Direction)(rand() % 8 + 1);
	}
	void RandomMovement() {
		   switch (drion)
		   {
			  case UP:
				   y--;
				   break;
			   case DOWN:
				   y++;
				   break;
			   case LEFT:
				   x--;
				   break;
			   case RIGHT:
				   x++;
			   case UPRIGHT:
				   y--; x++;
				   break;
			   case UPLEFT:
				   y--; x--;
				   break;
			   case DOWNRIGHT:
				   y++; x++;
				   break;					   
			   case DOWNLEFT:
				   y++; x--;
				   break;
		   }
	}
};

class Werewolfs : private Original
{

private:
	int x;
    int y;
	int ugeia =  (rand() % 3 + 1);
	int dinami = (rand() % 3 + 1);
	int amina =  (rand() % 2 + 1);
	int iatriko = (rand() % 2);
	Direction drion;
public:
	Werewolfs(int CordinareX, int CordinareY) { x = CordinareX; y = CordinareY; drion = STOP; }

	int GetX() { return x; }
	int GetY() { return y; }
	int GetYgeia() { return ugeia; }
	int GetDinami() { return dinami; }
	int GetAmina() { return amina; }
	int GetIatriko() { return iatriko; }

	void DamageUgeia() { ugeia--; }
	void DamageAmina() { amina--; }
	void GiveIatriko() { iatriko--; }
	void TakeIatriko() { ugeia++; }

	void Lose() {
		drion = STOP;
		x = NULL;
		y = NULL;
	}

	void ChangeDirection(Direction d) {     //Allazoume thn kinish xeirokinita px gia na mhn phgainei panw se alla pragmata
		drion = d;
	}
	void RandomDirection() {
		drion = (Direction)(rand() % 4 + 1);  //Allazei tuxaia h kinisi
	}
	void RandomMovement() {
		switch (drion)
		{
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
		}
	}
};

class Avatar : private Original
{
private:
	char Team = av;     
	int x, y;
    int filtra = 1;
	Direction drion;
public:
	Avatar(int xx, int yy)
	{
		x = yy;
		y = xx;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	int GetFiltra() { return filtra; };
	char GetTeam() { return av; }
	void GiveFiltro() {filtra--;}
	void TakeFiltro() {filtra++; }
    
	void Move(Direction direction) {
		drion = direction;
	}

	void Movement(char c) {
		switch (c)
		{
		case 'p':
		case 'P':      //Pause
			system("cls");
			Pause();
			system("pause");
			break;
		case 'w':
		case 'W':       //Panw
			if (y - 1 >= 0)
				y--;
			break;
		case 's':
		case 'S':       //Katw
			if (y < HEIGHT - 1)
				y++;
			break;
		case 'a':
		case 'A':       //Aristera
			if (x - 1 > 0)
				x--;
			break;
		case 'd':
		case 'D':       //Deksia
			if (x < WIDTH - 2)
				x++;
			break;
		case 'h':
		case 'H':

			if (filtra != 0) {
				if (av == 'V' || av == 'v') {
					if (Day == 'M') {
						filtra--;
					}
				}
				else {
					if (Day == 'N') {
						filtra--;
					}
				}
			}
			break;
		}
	}
};

class FILTRA : private Original
{
private:
	int x, y;
	bool fltr;                    // Alithis an uparxei filtro ston xarth alliws einai pseudhs
public:
	FILTRA(int i, int j, bool b) {
		x = i;
		y = j;
		fltr = b;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	bool GetFltr() { return fltr; }
	void ChangeFltr(bool b) { fltr = b;}

	void DestroyFiltro() {
		x = NULL;
		y = NULL;
	}
};

class GAME                 //Klash oi opoia th elenxei olo to paixnidi mas
{
private:
	bool playing = true;
	bool pause = false;
public:
	void Start() {
		cout << "                                    ###############################" << endl;
		cout << "                                    ##### WELCOME TO GAME!!! ######" << endl;
		cout << "                                    ###############################" << endl << endl;
//		Sleep(3000);    //Sleep for 3 sec
		system("cls");
		cout << "                                     CHOOSE YOUR AVATAR PLAYER..." << endl;
		cout << "                              PRESS V FOR VAMPIRES OR W FOR THE WEREWOLFS" << endl << endl;
		cin >> av;
   		system("cls");
		if (av =='w' || av == 'W')
			cout << "                                    COOL YOU ARE ON WEREWOLFS SIDE!" << endl;
		else
			cout << "                                    COOL YOU ARE ON VAMPIRES SIDE!" << endl;

//	   Sleep(3000);
       system("cls");
	   cout << "                                     GIVE THE HEIGHT OF THE MAP..." << endl;
	   cin >>  HEIGHT;
       cout << "                                     GIVE THE WIDTH OF THE MAP..." << endl;
	   cin >> WIDTH;
//	   Sleep(3000);
	   system("cls");
	   cout << "                                      COOL YOUR GAME IS READY!" << endl;
//	   Sleep(3000);
	   system("cls");
	   cout << "                                    U HAVE 1 FILTRO TO HELP YOUR TEAMMATES YGEIA" << endl;
	   cout << "                                                 MOVE UP -> W"<< endl;
	   cout << "                                   MOVE LEFT -> A             MOVE RIGHT -> D"<< endl;
	   cout << "                                                 MOVE DOWN -> S                              ";
//	   Sleep(5000);
	   system("cls");
	   cout << "                                                LETS PLAY!" << endl;
//	   Sleep(3000);
	   system("cls");
	}
	bool Collision(int x, int y, int x1, int y1) {     //Sunartisi pou gurnaei alithis an duo shmeia temnontai
		if (x == y1 && y == x1)
			return true;
		else
			return false;
	}
	bool SeimioObstacle(vector<OBSTACLES> Obstacle, int i, int j) {
		bool k = false;
		for (OBSTACLES o : Obstacle) {
			if (i == o.GetDentroX() && j == o.GetDentroY()) {
				k = true;
				cout << "\xD1";
			}
			else if (i == o.GetPotamiX() && j == o.GetPotamiY()) {
				k = true;
			    cout << "\xBA";
			}
		}
		return k;
	}

	bool SeimioWerewolf(vector<Werewolfs> werewolfs, int i, int j) {
		bool k = false;
		for (Werewolfs o : werewolfs) {
			if (i == o.GetX() && j == o.GetY()) {
				k = true;
				cout << "W";
				break;
			}
		}
		return k;
	}
	bool SeimioVampire(vector<Vampires> vampires, int i, int j) {
		bool k = false;
		for (Vampires o : vampires) {
			if (i == o.GetX() && j == o.GetY()) {
					k = true;
					cout << "v";
					break;
				}
			}
		return k;
	}

	void draw()
	{
		int k = 0;
		Avatar Av(HEIGHT/2, WIDTH/2);
		FILTRA Filtro(rand() % HEIGHT + 1, rand() % WIDTH + 1, true);

		vector<OBSTACLES> Obstacles;
		for (int i = 0; i <= 1 + (HEIGHT + WIDTH)/20; i++) { 
			OBSTACLES obstacles(rand() % HEIGHT - 1 , rand() % WIDTH - 1 , rand() % HEIGHT - 1 , rand() % WIDTH - 1 ); 
			Obstacles.push_back(obstacles);
		}

		vector<Werewolfs> werewolfs;
		vector<Vampires> vampires;
		for (int i = 1; i <= (HEIGHT+WIDTH) / 15; i++) {
			Werewolfs W(rand() % HEIGHT, rand() % WIDTH);
			werewolfs.push_back(W);
			Alwere = (HEIGHT + WIDTH) / 15;
			Vampires V(rand() % HEIGHT, rand() % WIDTH);
			vampires.push_back(V);
			Alvamp = (HEIGHT + WIDTH) / 15;
		}

		   while (playing && !pause) {
				k++;
				for (int i = 0; i < WIDTH; i++)
					cout << '\xDB';
				cout << endl;
				for (int i = 0; i < HEIGHT; i++) {
					for (int j = 0; j < WIDTH; j++) {
						if (j == 0) {
							cout << '\xDB';
						}
						else if (j == WIDTH - 1) {
							cout << '\xDB' << endl;
						}
						else if (i == Av.GetY() && j == Av.GetX()) {
							cout << Av.GetTeam();
						}
						else if (i == Filtro.GetX() && j == Filtro.GetY() && Filtro.GetFltr() == true) {
							cout << '!';
						}
						else if (Collision(Av.GetX(), Av.GetY(), Filtro.GetX(), Filtro.GetY())) {
							Filtro.ChangeFltr(false);       //Change filtro pleon to filtro dn uparxei ston xarth
							Filtro.DestroyFiltro();
							Av.TakeFiltro();                //Auksanoume to filtro kata 1		
						}
						else if (SeimioObstacle(Obstacles, i, j)) {  //Mpainei mesa mono an sto seimio i,j uparxei dentro h potami
							continue;
						}
						else if (SeimioWerewolf(werewolfs, i, j)) {
							continue;
						}
						else if (SeimioVampire(vampires, i, j)) {
							continue;
						}
						else {
							if (Day == 'M') {
								cout << '\xB2';   //Mera \xB2 nuxta \xB0
								if (k == 50) {
									k = 0;
									Day = 'N';
								}
							}
							else if (Day == 'N') {
								cout << '\xB0';
								if (k == 50) {
									k = 0;
									Day = 'M';
								}
							}
						}

					}
				}
				for (int i = 0; i < WIDTH; i++)
					cout << '\xDB';
				cout << endl;

				for (Werewolfs o : werewolfs) {
					o.RandomDirection();
					o.RandomMovement();
				}
				for (Werewolfs o : werewolfs) {
					o.RandomDirection();
					o.RandomMovement();
				}

		           if(_kbhit())
					  Av.Movement(_getch());
				cout << endl << endl;

				if (Av.GetTeam() == 'W' || Av.GetTeam() == 'w') {
					if (Day == 'M')
						cout << "IS MORNING U CAN'T USE THE FILTRO WAIT FOR THE NIGHT" << endl << endl;
					else
						cout << "IS NIGHT U CAN USE THE FILTRO" << endl << endl;
				}

				if (Av.GetTeam() == 'V' || Av.GetTeam() == 'v') {
					if (Day == 'N')
						cout << "IS NIGHT U CAN'T USE THE FILTRO WAIT FOR THE NIGHT" << endl << endl;
					else
						cout << "IS MORNING U CAN USE THE FILTRO" << endl << endl;
				}

				if (Av.GetFiltra() != 0)
					cout << "PRESS (H) TO USE THE FILTRA " << "(!)" << endl;
				cout << "FILTRA TO USE: " << Av.GetFiltra() << endl << endl;
				cout << "PRESS (P) TO PAUSE THA GAME " << endl;

				Sleep(60);
				system("cls");
           }
    }
};    

int main() {
	GAME Game;
	Game.Start();
	Game.draw();
	
	return 0;
}