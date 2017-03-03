void primoVito(){
  if(US02.read()>30)while(x!=90){Moviment.Rotate(RL);direction=(direction+1)%4;}//destro
  else if(US03.read()<30)while(x!=90){Moviment.Rotate(!RL);direction=(direction-1)%4;}//sinistro
  float fine=US03.read()+30;
  Moviment.go(true);
  while(US03.read()<fine)int i=0;//controllo a destra e sinistra del calore,se trovato si deve girare in quella direzione e sbattersi fortemente sul muro.
  Moviment.stop();
  switch(direction){
    case(0):inizio[0]++;break;
    case(1):inizio[1]++;break;
    case(2):inizio[0]--;break;
    case(3):inizio[1]--;break;
  }
}

void setup() {}



void loop() {}
