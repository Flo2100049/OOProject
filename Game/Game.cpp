#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;
enum Direction  { STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4, UPLEFT = 5, UPRIGHT = 6, DOWNLEFT = 7, DOWNRIGHT = 8 };  //Για την τυχαια κινιση των vampires και werewolfs.

char av, Day = 'M';            //Global metablhtes. -av deixnei thn omada tou paikth kai -Day δειχνει την mera kai thn nuxta.
int WIDTH, HEIGHT;             //Global metablhtes. -WIDTH einai to plato tou xarth kai -HEIGHT einai to upsos tou xarth.
int  Alvamp, Alwere;           //Global metablhtes. -Alvamp deixnei to plhthos twn vampires kai -ALwere deixnei to plhthos twn werewolfs.


void Pause() {                 //H sunarthsh Pause pou kaleitai otan to paixnidi einai se paush.
	cout << "                         ##################################" << endl;
	cout << "                         ######       GAME PAUSE      #####" << endl;
	cout << "                         ##################################" << endl << endl << endl;
	cout << "-ALIVE WEREWOLFS: " << Alwere << endl;
	cout << "-ALIVE VAMPIRES: " << Alvamp << endl;
}
void checkTeam(char c) {                                              //Sunarthsh gia na tsekarei an dinetai swsth omada gia ton paikth.
	if (c != 'W' && c != 'w' && c != 'V' && c != 'v') {
		throw invalid_argument("Den dialekses kamia omada... \n");
	}
}
void checkMap(int HEIGHT, int WIDTH) {                                //Sunarthsh gia na tsekarei an dinontai swstes diastaseis gia ton xarth.
	if (HEIGHT <= 10) 
		if (WIDTH <= 8) 
		   throw invalid_argument("Mikres diastaseis pinaka... \n");

	if (HEIGHT >= 40 && WIDTH >= 100)
		throw invalid_argument("Megales diastaseis pinaka... \n");
}                          
class Original             //Yperklash apo thn opoia klhronomoun oi alles klaseis.   
{
private:
	int x, y;              //Shmeia mesa ston xarth.
}; 

class OBSTACLES: private Original {          //Klash gia ta dentra kai ta potamia. 
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

class Vampires : private Original            //Klash gia ta Vampires. 
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
	
	void DamageAmina(Vampires* v, int i) {               //Se periptwsh pou dexthei epithesh tote meiwnetai h amuna. 
		for (int k = 0; k <= i; k++)
			v->amina--;
	}
	void DamageUgeia(Vampires* v, int i) {               //Se periptwsh pou dexthei apithesh kai den uparxei amuna meiwnetai h ugeia.
		for (int k = 0; k <= i; k++)
			v->ugeia--;
	}
	void GiveIatriko(Vampires* v) {v->iatriko--;}        //Otan boithaei kapoion sumpaikth dinei iatriko.
	void TakeIatriko(Vampires* v) {v->ugeia++;}          //Otan boithietai apo kapoion sumpaikth pernei ugeia.

	void Lose(Vampires* v) {                             //Otan xasei stamataei h kinish tou kai eksafanizetai apo ton xarth.
		v->drion = STOP;
		v->x = 999;
		v->y = 999;
	}

	////////////////// Πολυμορφισμος /////////////////////
	void RandomDirection(Direction d, Vampires* V) {    //otan theloume na allaksoume emeis thn kateuthinsh tou  gia kapoion sugkekrimeno logo.
		V->drion = d;
	}
	void RandomDirection(Vampires* V) {                 //Allazei tuxaia h kateuthinsh tou.
		V->drion = (Direction)(rand() % 8 + 1);
	}
	//////////////////////////////////////////////////////

	void RandomMovement(Vampires* V) {                  //Sunarthsh kinishs.
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
			w->ugeia--;
	}
	void GiveIatriko(Werewolfs* w) { w->iatriko--; }
	void TakeIatriko(Werewolfs* w) { w->ugeia++; }

	void Lose(Werewolfs* w) {
		w->drion = STOP;
		w->x = 999;
		w->y = 999;
	}

	/////////////// Πολυμορφισμος //////////////////////////
	void RandomDirection(Direction d, Werewolfs* W) {       
		W->drion = d;
		W->RandomMovement(W);
	}
	void RandomDirection(Werewolfs* W) {
		W->drion = (Direction)(rand() % 4 + 1);           //Mexri 4 afou oi werewolfs exoun periorismenoi kinish.
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

	void Movement(char c) {            //Sunarthsh kinishs tou dikou mas paikth me bash ta koumpia pou patame.
		switch (c)
		{
		case 'p':           //Paush
		case 'P':
			system("cls");
			Pause();
			system("pause");
			break;
		case 'w':
		case 'W':           //Panw
			if (y - 1 >= 0)
				y--;
			break;
		case 's':
		case 'S':           //Katw
			if (y < HEIGHT - 1)
				y++;
			break;
		case 'a':
		case 'A':          //Aristera
			if (x - 1 > 0)
				x--;
			break;
		case 'd':
		case 'D':          //Deksia
			if (x < WIDTH - 2)
				x++; 
			break;
		case 'h':
		case 'H':          //Gia to filtro
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

class GAME                   //Kentrikh klash pou elenxei ta panta.
{
private:
	bool playing = true;     //Bool metablhth an to paixnidi einai se ekseliksh h an exei teleiwsei.
public:
	void Start() {           //Kaleitai molis to paixnidi ksekinaei. 
		cout << "                                    ###############################" << endl;
		cout << "                                    ##### WELCOME TO GAME!!! ######" << endl;
		cout << "                                    ###############################" << endl << endl;
		Sleep(3000);    //Sleep for 3 sec
		system("cls");
		cout << "                                     CHOOSE YOUR AVATAR PLAYER..." << endl;
		cout << "                              PRESS V FOR VAMPIRES OR W FOR THE WEREWOLFS" << endl << endl;
		cin >> av;
		try
		{
			checkTeam(av);
		}
		catch (invalid_argument& inpt)          //Ελενχος δεδομενων
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

	   Sleep(3000);
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
	   Sleep(3000);
	   system("cls");
	   cout << "                                      COOL YOUR GAME IS READY!" << endl;
	   Sleep(3000);
	   system("cls");
	   cout << "                                    U HAVE 1 FILTRO TO HELP YOUR TEAMMATES YGEIA" << endl;
	   cout << "                                                 MOVE UP -> W"<< endl;
	   cout << "                                   MOVE LEFT -> A             MOVE RIGHT -> D"<< endl;
	   cout << "                                                 MOVE DOWN -> S                              ";
	   Sleep(5000);
	   system("cls");
	   cout << "                                                LETS PLAY!" << endl;
	   Sleep(3000);
	   system("cls");
	}
	bool Collision(int x, int y, int x1, int y1) {     //Epistefei true an duo shmeia einai sto ido shmeio.
		if (x == y1 && y == x1)
			return true;
		else
			return false;
	}
	bool SeimioObstacle(vector<OBSTACLES> Obstacle, int i, int j) {  //Ta shmeia twn dentrwn kai twn potamwn epistefei true an einai ena tetoio shmeio.
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
	bool SeimioWerewolf(vector<Werewolfs*> werewolfs, int i, int j) {    //Ta shmeia werewolfs epistefei true an einai tetoio shmeio.
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
	bool SeimioVampire(vector<Vampires*> vampires, int i, int j) {   //Paromoia gia tous vampires kai edw.
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

	void TeamWerewolfs(vector<Werewolfs*> werewolfs) {   //Elenxei an tha uparksei boitheia anamesa se sumpaiktes. 
		int x1; int y1;
		int x2; int y2;
		for (Werewolfs* o : werewolfs) {
			x1 = o->GetX(o);
			y1 = o->GetY(o);
			for (Werewolfs* w : werewolfs) {
				x2 = w->GetX(w);
				y2 = w->GetY(w);
				if (o != w){                                                 
					if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {            //Apoluth timh ths diaforas miktoterou tou 1.
						if (o->GetYgeia(o) < 3 && w->GetIatriko(w) > 0) {
							w->GiveIatriko(w);                               //Meiwnetai toiatriko autou pou boithaei.
							o->TakeIatriko(o);                                //Auksanetai h ugeia autounou pou boithietai.
						}

					}
			    }
		    }
		}
	}
	void TeamVampires(vector<Vampires*> vampires) {           //Elenxei an tha uparksei boitheia anamesa se sumpaktes.
		int x1; int y1;
		int x2; int y2;
		for (Vampires* o : vampires) {
			x1 = o->GetX(o);
			y1 = o->GetY(o);
			for (Vampires* w : vampires) {
				x2 = w->GetX(w);
				y2 = w->GetY(w);
				if (o != w) {                                                
					if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {            
						if (o->GetYgeia(o) < 5 && w->GetIatriko(w) > 0) {
							w->GiveIatriko(w);                              
							o->TakeIatriko(o);                            
						}

					}
				}
			}
		}
	}

	void wVSv(vector<Werewolfs*> werewolfs, vector<Vampires*> vampires) {    //Sunarthsh pou elenxei ths epitheseis.
		int x1; int y1;
		int x2; int y2;
		int damage;
		for (Werewolfs* w : werewolfs) {
			if (w->GetX(w) != 999) {
				x1 = w->GetX(w);
				y1 = w->GetY(w);
				for (Vampires* v : vampires) {
					if (v->GetX(v) != 999) {
						x2 = v->GetX(v);
						y2 = v->GetY(v);
						if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
							if (w->GetDinami(w) > v->GetDinami(v)) {           //Periptwsh oti epitithetai werewolf.
								if (v->GetAmina(v) > 0) {
									damage = v->GetAmina(v) - w->GetDinami(w); //To damage einai analogo ths amunas tou amunomenou kai thn dunamh tou epitethinomenou.
									if (damage >= 0)
										v->DamageAmina(v, w->GetDinami(w));    //Pleon den uparxei amuna gia mellontikh epithesh.
									else
										v->DamageUgeia(v, abs(damage));        //Meiwnetai h ugeia oso prepei analoga thn upolhpomenh amuna.
								}
								else {
									v->DamageUgeia(v, w->GetDinami(w));        //An den uparxei amuna tote h ugeia meiwnetai akribws oso thn dunamh.							          
								}

								if (v->GetYgeia(v) <= 0) {                     //An mhdenistei h ugeia o paikths eksafanizetai.
									v->Lose(v);
									Alvamp--;
								}
								else {                                         //Meta apo epithesh an o paikths anteksei tha prospathisei na fugei.
									v->RandomDirection(v);
									v->RandomMovement(v);
								}
							}
							else if (v->GetDinami(v) > w->GetDinami(w)) {     //Periptwsh pou epitithetai to vampire ginontai ta idia pragmata.
								if (w->GetAmina(w) > 0) {
									damage = w->GetAmina(w) - v->GetDinami(v);
									if (damage >= 0)
										w->DamageAmina(w, v->GetDinami(v));
									else
										w->DamageUgeia(w, abs(damage));
								}
								else {
									w->DamageUgeia(w, v->GetDinami(v));
								}
								if (w->GetYgeia(w) <= 0) {
									w->Lose(w);
									Alwere--;
								}
								else {
									w->RandomDirection(w);
									w->RandomMovement(w);
								}
							}
							else {                                             //Otan exoun idia dunamh kanoume mia parallagh.
								                                 //Xanoun kai h duo apo mia monada th amunas alliws an den exoun apo mia monada apo thn ugeia.
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
									Alvamp--;
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
		int k = 0;                        //Metablith pou meta apo kapoies epanaleipseis-loop allazei thn nuxta se mera.
		Avatar Av(HEIGHT/2, WIDTH/2);
		FILTRA Filtro(rand() % HEIGHT + 1, rand() % WIDTH + 1, true);

		vector<OBSTACLES> Obstacles;     //Vector apo denta k potamia. 
		for (int i = 0; i <= 1 + (HEIGHT + WIDTH)/20; i++) { 
			OBSTACLES obstacles(rand() % HEIGHT - 1 , rand() % WIDTH - 1 , rand() % HEIGHT - 1 , rand() % WIDTH - 1 ); 
			Obstacles.push_back(obstacles);
		}

		vector<Werewolfs*> werewolfs;  //Vector apo werewolfs.
		vector<Vampires*> vampires;     //Vector apo vampires.

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
							Filtro.ChangeFltr(false);                     //Change φιλτρο pleon den uparxei filtro ston xarth.
							Filtro.DestroyFiltro();
							Av.TakeFiltro();                              //Auksanoume filtro kata 1.        
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

				for (Werewolfs* o : werewolfs) {                             //Allazei ths kiniseis twn werewolfs.
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
				for (Vampires* o : vampires) {                         //Allazei ths kiniseis twn vampires. 
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
				if (prevFiltra - nextFiltra == 1) {    //Blepoume an xrhsimopoihthike filtro. 
					if (Av.GetTeam() == 'W' || Av.GetTeam() == 'w') {
						for (Werewolfs* o : werewolfs) {
							o->TakeIatriko(o);                         //Auksanoume thn ugeia twn paiktwn meta apo xrhsh filtrou. 
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

				
				for (Vampires* o : vampires) {
					cout << "Vampires: ";
					cout << "UGEIA: " << o->GetYgeia(o);
					cout << " AMINA: " << o->GetAmina(o);
					cout << " IATRIKO: " << o->GetIatriko(o);
					cout << " DIANAMI: " << o->GetDinami(o) << endl;
				}
				
				for (Werewolfs* o : werewolfs) {
					cout << "Werewolfs: ";
					cout << "UGEIA: " << o->GetYgeia(o);
					cout << " AMINA: " << o->GetAmina(o);
					cout << " IATRIKO: " << o->GetIatriko(o);
					cout << " DIANAMI: " << o->GetDinami(o) << endl;
				}


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