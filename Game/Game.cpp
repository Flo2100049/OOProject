#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;
enum Direction  { STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4, UPLEFT = 5, UPRIGHT = 6, DOWNLEFT = 7, DOWNRIGHT = 8 };  //��� ��� ������ ������ ��� vampires ��� werewolfs.

char av, Day = 'M';            //Global ����������. -av ������� ��� ����� ��� ������� ��� -Day ������ ��� ���� � ��� �����.
int WIDTH, HEIGHT;             //Global ����������. -WIDTH ����� �� ������ ��� ����� ��� -HEIGHT ����� �� ���� ��� �����.
int  Alvamp, Alwere;           //Global ����������. -Alvamp ������� �� ������ ��� vampires ��� -Alwere ������� �� ������ ��� werewolfs.


void Pause() {                 //� ��������� Pause ��� �������� ���� �� �������� ����� �� �����.
	cout << "                         ##################################" << endl;
	cout << "                         ######       GAME PAUSE      #####" << endl;
	cout << "                         ##################################" << endl << endl << endl;
	cout << "-ALIVE WEREWOLFS: " << Alwere << endl;
	cout << "-ALIVE VAMPIRES: " << Alvamp << endl;
}
void checkTeam(char c) {                                              //��������� ��� �� �������� �� ������� ����� ����� ��� ��� ������.
	if (c != 'W' && c != 'w' && c != 'V' && c != 'v') {
		throw invalid_argument("Den dialekses kamia omada... \n");
	}
}
void checkMap(int HEIGHT, int WIDTH) {                                //��������� ��� �� �������� �� �������� ������ ���������� ��� ��� �����.
	if (HEIGHT <= 10) 
		if (WIDTH <= 8) 
		   throw invalid_argument("Mikres diastaseis pinaka... \n");

	if (HEIGHT >= 40 && WIDTH >= 100)
		throw invalid_argument("Megales diastaseis pinaka... \n");
}                          
class Original             //��������� ��� ��� ����� ����������� �� ����� �������.    
{
private:
	int x, y;              //������ ���� ���� �����
}; 

class OBSTACLES: private Original {          //����� ��� �� ������ ��� �� �������.
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

class Vampires : private Original            //����� ��� �� Vampires.
{
private:
	int x;
    int y;
	int ugeia = 3;
	int dinami = (rand() % 3 + 1);
	int amina = (rand() % 2 + 1);
	int iatriko = (rand() % 2);
	Direction drion;
public: 
	Vampires(int CordinareX, int CordinareY) { x = CordinareX; y = CordinareY; drion = STOP; }

	int GetX(Vampires* v) {return v->x;}
	int GetY(Vampires* v) {return v->y;}
	Direction GetDirection(Vampires* v) { return v->drion; }
	int GetYgeia(Vampires* v) {return v->ugeia;}
	int GetDinami(Vampires* v) {return v->dinami;}
	int GetAmina(Vampires* v) {return v->amina;}
	int GetIatriko(Vampires* v) {return v->iatriko;}
	
	void DamageAmina(Vampires* v, int i) {               //�� ���������� ��� ������ ������� ���� ��������� � �����.
		for (int k = 0; k <= i; k++)
			v->amina--;
	}
	void DamageUgeia(Vampires* v, int i) {               //�� ���������� ��� ������ ������� ��� ��� ������� ����� ��������� � �����.
		for (int k = 0; k <= i; k++)
			v->ugeia--;
	}
	void GiveIatriko(Vampires* v) {v->iatriko--;}        //���� ������� ������� ��������� ����� �������
	void TakeIatriko(Vampires* v) {v->ugeia++;}          //���� ��������� ��� ������� ��������� ������ �����.

	void Lose(Vampires* v) {                             //���� ����� ��������� � ������ ��� � ������������ ��� ��� �����.
		v->drion = STOP;
		v->x = 999;
		v->y = 999;
	}

	////////////////// ������������� /////////////////////
	void RandomDirection(Direction d, Vampires* V) {    // ���� ������� �� ��������� ����� ��� ���������� ��� ��� ������� ������������ ����
		V->drion = d;
	}
	void RandomDirection(Vampires* V) {                 // ������� ������ � ���������� ���.
		V->drion = (Direction)(rand() % 8 + 1);
	}
	//////////////////////////////////////////////////////

	void RandomMovement(Vampires* V) {                  // ��������� �������
		int y = V->GetY(V);
		int x = V->GetX(V);
		if (y - 1 == 0 || y == 0)
		   V->y++;
		if (y == HEIGHT - 1 || y == HEIGHT) 
		   V->y--;
		if (x - 1 == 0 || x == 0)
		   V->x++;
		if (x == WIDTH - 1 || x == WIDTH || x == WIDTH + 1)
		   V->x--;
		 
		   switch (V->drion)
		   {
			  case UP:
				  if (y - 1 >= 0)
				   V->y--;
				  break;
			   case DOWN:
				   if (y < HEIGHT - 1)
				    V->y++;
				   break;
			   case LEFT:
				   if (x - 1 > 0)
				    V->x--;
				   break;
			   case RIGHT:
				   if (x < WIDTH - 2)
				    V->x++;
				   break;
			   case UPRIGHT:
				   if (y - 1 >= 0 && x < WIDTH - 2)
				    V->y--; V->x++;
				   break;
			   case UPLEFT:
				   if (y - 1 >= 0 && x - 1 > 0)
				    V->y--; V->x--;
				   break;
			   case DOWNRIGHT:
				   if (y < HEIGHT - 1 && x < WIDTH - 2)
				    V->y++; V->x++;
				   break;					   
			   case DOWNLEFT:
				   if (y < HEIGHT - 1 && x - 1 > 0)
				    V->y++; V->x--;
				   break;
		   }
	}
};

class Werewolfs : private Original
{
private:
	int x;
    int y;
	int ugeia = 3;
	int dinami = (rand() % 3 + 1);
	int amina =  (rand() % 2 + 1);
	int iatriko = (rand() % 2);
	Direction drion;
public:
	Werewolfs(int CordinareX, int CordinareY) { x = CordinareX; y = CordinareY; drion = STOP; }

	int GetX(Werewolfs* w) { return w->x; }
	int GetY(Werewolfs* w) { return w->y; }
	Direction GetDirection(Werewolfs* w) { return w->drion; }
	int GetYgeia(Werewolfs* w) { return w->ugeia; }
	int GetDinami(Werewolfs* w) { return w->dinami; }
	int GetAmina(Werewolfs* w) { return w->amina; }
	int GetIatriko(Werewolfs* w) { return w->iatriko; }

	void DamageAmina(Werewolfs* w, int i) { 
		for (int k = 0; k <= i; k++)
			w->amina--;
	}
	void DamageUgeia(Werewolfs* w, int i) { 
		for (int k = 0; k <= i; k++)
			w->amina--;
	}
	void GiveIatriko(Werewolfs* w) { w->iatriko--; }
	void TakeIatriko(Werewolfs* w) { w->ugeia++; }

	void Lose(Werewolfs* w) {
		w->drion = STOP;
		w->x = 999;
		w->y = 999;
	}

	/////////////// ������������� //////////////////////////
	void RandomDirection(Direction d, Werewolfs* W) {       
		W->drion = d;
		W->RandomMovement(W);
	}
	void RandomDirection(Werewolfs* W) {
		W->drion = (Direction)(rand() % 4 + 1);           //����� 4 ���� �� werewolfs ����� ������������� ������.
	}
	///////////////////////////////////////////////////////

	void RandomMovement(Werewolfs* W) {
		int y = W->GetY(W);
		int x = W->GetX(W);
		switch (W->drion)
		{
		case UP:
			if (y - 1 >= 0)
				W->y--;
		 break;
		case DOWN:
			if (y < HEIGHT - 1)
				W->y++;
		 break;
		case LEFT:
			if (x - 1 > 0)
				W->x--;
		 break;
		case RIGHT:
			if (x < WIDTH - 2)
				W->x++;
		 break;
		}
	}
};

class Avatar : private Original
{
private:
	char Team = av;     
	int x, y;
    int filtra = 1;
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

	void Movement(char c) {            //��������� ������� ��� ����� ��� ������ �� ���� �� ������� ��� ������
		switch (c)
		{
		case 'p':           //�����
		case 'P':
			system("cls");
			Pause();
			system("pause");
			break;
		case 'w':
		case 'W':           //����
			if (y - 1 >= 0)
				y--;
			break;
		case 's':
		case 'S':           //����
			if (y < HEIGHT - 1)
				y++;
			break;
		case 'a':
		case 'A':          //��������
			if (x - 1 > 0)
				x--;
			break;
		case 'd':
		case 'D':          //�����
			if (x < WIDTH - 2)
				x++; 
			break;
		case 'h':
		case 'H':          //��� �� ������������� �� ������
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

class GAME                   //�������� ����� ��� ������� �� �����
{
private:
	bool playing = true;     //Bool ��������� �� �� �������� ����� �� ������� � �� ���� ���������
public:
	void Start() {           //�������� ����� �� �������� ��������
		cout << "                                    ###############################" << endl;
		cout << "                                    ##### WELCOME TO GAME!!! ######" << endl;
		cout << "                                    ###############################" << endl << endl;
//		Sleep(3000);    //Sleep for 3 sec
		system("cls");
		cout << "                                     CHOOSE YOUR AVATAR PLAYER..." << endl;
		cout << "                              PRESS V FOR VAMPIRES OR W FOR THE WEREWOLFS" << endl << endl;
		cin >> av;
		try
		{
			checkTeam(av);
		}
		catch (invalid_argument& inpt)          //������� ���������
		{
			system("cls");
			cerr << inpt.what() << endl;
			Sleep(3000);
			exit(0);
		}
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
	   try
	   {
		   checkMap(HEIGHT, WIDTH);
	   }
	   catch (invalid_argument& inpt)
	   {
		   system("cls");
		   cerr << inpt.what() << endl;
		   Sleep(3000);
		   exit(0);
	   }
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
	bool Collision(int x, int y, int x1, int y1) {     //��������� true �� ��� ������ ����� ��� ���� ������.
		if (x == y1 && y == x1)
			return true;
		else
			return false;
	}
	bool SeimioObstacle(vector<OBSTACLES> Obstacle, int i, int j) {  //�� ������ ��� ������� ��� ��� ������� ��������� true �� ����� ��� ������ ������.
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
	bool SeimioWerewolf(vector<Werewolfs*> werewolfs, int i, int j) {        //�� ������ ��� werewolfs  ��������� true �� ����� ��� ������ ������.
		bool k = false;
		for (Werewolfs* o : werewolfs) {
				if (i == o->GetX(o) && j == o->GetY(o)) {
					k = true;
					cout << "W";
					break;
				}
		}
		return k;
	}
	bool SeimioVampire(vector<Vampires*> vampires, int i, int j) {   // �� ������ ��� vampires ��������� true �� ����� ��� ������ ������.
		bool k = false;
		for (Vampires* o : vampires) {
				if (i == o->GetX(o) && j == o->GetY(o)) {
					k = true;
					cout << "v";
					break;
				}
		}
		return k;
	}

	void TeamWerewolfs(vector<Werewolfs*> werewolfs) {   //������� �� �� ������� ������� ������� �� ������� ��� ���� ������. 
		int x1; int y1;
		int x2; int y2;
		for (Werewolfs* o : werewolfs) {
			x1 = o->GetX(o);
			y1 = o->GetY(o);
			for (Werewolfs* w : werewolfs) {
				x2 = w->GetX(w);
				y2 = w->GetY(w);
				if (o != w){                                                 
					if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {            //������� ���� ��� �������� ���������� ��� 1.
						if (o->GetYgeia(o) < 3 && w->GetIatriko(w) > 0) {
							w->GiveIatriko(w);                               //��������� �� ������� ����� ��� �������.
							o->TakeIatriko(o);                                //��������� � ����� ����� ��� ���������.
						}

					}
			    }
		    }
		}
	}
	void TeamVampires(vector<Vampires*> vampires) {           //������� �� �� ������� ������� ������� �� ������� ��� ���� ������. 
		int x1; int y1;
		int x2; int y2;
		for (Vampires* o : vampires) {
			x1 = o->GetX(o);
			y1 = o->GetY(o);
			for (Vampires* w : vampires) {
				x2 = w->GetX(w);
				y2 = w->GetY(w);
				if (o != w) {                                                
					if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {            //������� ���� ��� �������� ���������� ��� 1.
						if (o->GetYgeia(o) < 5 && w->GetIatriko(w) > 0) {
							w->GiveIatriko(w);                               //��������� �� ������� ����� ��� �������.
							o->TakeIatriko(o);                               //��������� � ����� ����� ��� ���������.
						}

					}
				}
			}
		}
	}

	void wVSv(vector<Werewolfs*> werewolfs, vector<Vampires*> vampires) {    //��������� ��� ������� ��� ���������.
		int x1; int y1;
		int x2; int y2;
		int damage;
		for (Werewolfs* w : werewolfs) {
			if (w->GetX(w) != 999) {
				x1 = w->GetX(w);
				y1 = w->GetY(w);
				for (Vampires* v : vampires) {
					if (w->GetX(w) != 999) {
						x2 = v->GetX(v);
						y2 = v->GetY(v);
						if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
							if (w->GetDinami(w) > v->GetDinami(v)) {           //��������� ��� ���������� �� werewolf.
								if (v->GetAmina(v) > 0) {
									damage = v->GetAmina(v) - w->GetDinami(w); //�� damage ����� ������� ��� ����� ��� ���������� ��� ��� ������ ��� ������������
									if (damage >= 0)
										v->DamageAmina(v, w->GetDinami(w));    //����� ��� ������� ����� ��� ���������� ������� ��� �� ������.
									else
										v->DamageUgeia(v, abs(damage));        //��������� � ����� ��� ������ ������� ��� ����������� ������.
								}
								else {
									v->DamageUgeia(v, w->GetDinami(w));        //�� ��� ������� ����� ���� � ����� ��������� ������� ��� ��� ������ ��� �������.
								}          
								if (v->GetYgeia(v) <= 0) {                     //�� ���������� � ����� � ������� ������������.
								    v->Lose(v);
									Alvamp--;
								}
								else {                                         //���� ��� ������� �� � ������� ������� ���� �� ����������� �� �����.
									v->RandomDirection(v);
									v->RandomMovement(v);
								}
							}
							else if (v->GetDinami(v) > w->GetDinami(w)) {     //��������� ��� ���������� �� vampire.
								if (w->GetAmina(w) > 0) {
									damage = w->GetAmina(w) - v->GetDinami(v); //�o damage ����� ������� ��� ������ ��� ���������� ��� ��� ������ ����� ��� ����������.
									if (damage >= 0)
										w->DamageAmina(w, v->GetDinami(v));    //����� ��� ������� ����� ��� ���������� �������.
									else
										w->DamageUgeia(w, abs(damage));       //�������� ����� ��� ���������� �������.
								}
								else {
									w->DamageUgeia(w, v->GetDinami(v));       //�� ��� ������� ����� ����� ��������� � ����� ��� ��� ������ ���.
								}
								if (w->GetYgeia(w) <= 0) {                    //�� ���������� � ����� ���� � ������� ������������ ��� ��� �����.
									w->Lose(w);
									Alwere--;
								}
								else { 
									w->RandomDirection(w);                  //������ �� �������� ����� ���� � ������� ��������� �� �����.
									w->RandomMovement(w);
								}
							}
							else {                                             //���� ����� ���� ������ ������� ��� ���������.
								                                          //������ ��� � ��� ��� ��� ������ ���� ����� ������ �� ��� ����� ���� ��� ������ �����.
								if (w->GetAmina(w) > 0) {
									w->DamageAmina(w, 1);
								}
								else {
									w->DamageUgeia(w, 1);
								}
								  if (w->GetYgeia(w) <= 0) {
									w->Lose(w);
									Alwere--;
								  }
								if (v->GetAmina(v) > 0) {
									v->DamageAmina(v, 1);
								}
								else {
									v->DamageUgeia(v, 1);
								}
								  if (v->GetYgeia(v) <= 0) {
									v->Lose(v);
									Alwere--;
								  }
							}
						}
					}
				}
			}
		}
	}

	void draw()
	{
		int k = 0;                        //��������� ��� ���� ��� ������� ����������� ������� � ���� �� �����.
		Avatar Av(HEIGHT/2, WIDTH/2);
		FILTRA Filtro(rand() % HEIGHT + 1, rand() % WIDTH + 1, true);

		vector<OBSTACLES> Obstacles;     //Vector ��� ��  ������ � �� �������.
		for (int i = 0; i <= 1 + (HEIGHT + WIDTH)/20; i++) { 
			OBSTACLES obstacles(rand() % HEIGHT - 1 , rand() % WIDTH - 1 , rand() % HEIGHT - 1 , rand() % WIDTH - 1 ); 
			Obstacles.push_back(obstacles);
		}

		vector<Werewolfs*> werewolfs;  //Vector ��� werewolfs.
		vector<Vampires*> vampires;     //Vector ��� vampires.

		for (int i = 1; i <= (HEIGHT+WIDTH) / 15; i++) {
			Werewolfs* W = new Werewolfs(rand() % (WIDTH - 1) + 1, rand() % (HEIGHT - 1) + 1);			                                                                  
			werewolfs.push_back(W);
			Alwere = (HEIGHT + WIDTH) / 15;

			Vampires* V = new Vampires(rand() % (WIDTH - 1) + 1,  rand() % (HEIGHT - 1) + 1);		                                                                 
			vampires.push_back(V);
			Alvamp = (HEIGHT + WIDTH) / 15;
		}

		   while (playing) {
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
							Filtro.ChangeFltr(false);                     //Change ������ ����� ��� ������� ������ ���� �����
							Filtro.DestroyFiltro();
							Av.TakeFiltro();                              //��������� �� ������ ���� 1.
						}	
						else if (SeimioObstacle(Obstacles, i, j)) {     
							continue;
						}
						else if (!(SeimioObstacle(Obstacles, i, j)) && !(SeimioVampire(vampires, j, i)))
							if (SeimioWerewolf(werewolfs, j, i)) { 
							 continue;
						}
						else if (!(SeimioObstacle(Obstacles, i, j)) && !(SeimioWerewolf(werewolfs, j, i)))
							if (SeimioVampire(vampires, j, i)) {  
							 continue;
						}
						else {
							if (Day == 'M') {
								cout << '\xB2';   
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

				TeamWerewolfs(werewolfs);
				TeamVampires(vampires);
				wVSv(werewolfs, vampires);

				for (Werewolfs* o : werewolfs) {                             //������� ��� �������� ��� werewolfs.
					if (o->GetX(o) != 999) {
						o->RandomDirection(o);
						int x = o->GetX(o); int y = o->GetY(o); Direction d = o->GetDirection(o);
						if (y == HEIGHT - 1 || y == HEIGHT) {
							if (d == DOWN)
								o->RandomDirection(UP, o);
							else
								o->RandomMovement(o);
						}
						else {
							o->RandomMovement(o);
						}
					}
				}
				for (Vampires* o : vampires) {                         //������� ��� �������� ��� vampires.
					if (o->GetX(o) != 999) {
						o->RandomDirection(o);
						int x = o->GetX(o); int y = o->GetY(o); Direction d = o->GetDirection(o);
						if (x == WIDTH - 1 || x == WIDTH) {
							if (d == DOWN)
								o->RandomDirection(LEFT, o);
							else
								o->RandomMovement(o);
						}
						else {
							o->RandomMovement(o);
						}
					}
				}

				int prevFiltra = Av.GetFiltra();
				if (_kbhit()) {
					  Av.Movement(_getch());
				}
				int nextFiltra = Av.GetFiltra();
				if (prevFiltra - nextFiltra == 1) {    //�������� �� ��������������� ������
					if (Av.GetTeam() == 'W' || Av.GetTeam() == 'w') {
						for (Werewolfs* o : werewolfs) {
							o->TakeIatriko(o);                         //��������� ��� ����� ��� ������� ���� ��� ����� �������.
						}
					}
					else if (Av.GetTeam() == 'V' || Av.GetTeam() == 'v') {
						for (Vampires* o : vampires) {
							o->TakeIatriko(o);                         
						}
					}

				}

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

				if (Alvamp == 0) {
					playing = false;
					Sleep(2000);
					system("cls");
					if (Av.GetTeam() == 'W' || Av.GetTeam() == 'w') {
						cout << "                    ##########################################" << endl;
						cout << "                    ####        CONGRATULATIONS!          ####" << endl;
						cout << "                    ####       TEAM WEREWOLFS WON         ####" << endl;
						cout << "                    ##########################################" << endl;
						Sleep(3000);
						system("cls");
					}
					else {
						cout << "                    ##########################################" << endl;
						cout << "                    ####      :( YOUR TEAM LOSE!          ####" << endl;
						cout << "                    ####       TEAM WEREWOLFS WON         ####" << endl;
						cout << "                    ##########################################" << endl;
						Sleep(3000);
						system("cls");
					}
				}
				else if (Alwere == 0) {
					playing = false;
					Sleep(2000);
					system("cls");
					if (Av.GetTeam() == 'V' || Av.GetTeam() == 'V') {
						cout << "                    ##########################################" << endl;
						cout << "                    ####        CONGRATULATIONS!          ####" << endl;
						cout << "                    ####       TEAM VAMPIRES  WON         ####" << endl;
						cout << "                    ##########################################" << endl;
						Sleep(3000);
						system("cls");
					}
					else {
						cout << "                    ##########################################" << endl;
						cout << "                    ####     :( YOUR TEAM LOSE!           ####" << endl;
						cout << "                    ####       TEAM VAMPIRES WON          ####" << endl;
						cout << "                    ##########################################" << endl;
						Sleep(3000);
						system("cls");
					}
				}
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