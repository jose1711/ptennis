#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "font.h"
// #include <iostream.h>

// 400 X 450


SDL_Surface *fondo;
SDL_Surface *implayer1;
SDL_Surface *implayer2;
SDL_Surface *mplayer;
SDL_Surface *isplayer1;
SDL_Surface *isplayer2;
SDL_Surface *splayer;
SDL_Surface *red;
SDL_Surface *screen;
SDL_Surface *pelota;
SDL_Surface *intro;
SDL_Surface *win;
SDL_Surface *lose;
SDL_Surface *tdem;

SDL_Event event;
int mpx, mpy, spx, spy = 50;
int sinitx, sinity = 50;
int px = 170;
int py = 345;
int salir =0;
int mxdir = 0;
int mydir = 0;
int pxdir = 0;
int pydir = 0;
int sxdir = 0;
int sydir = 0;
int pestado = 0; // estado de pelota
int bspeed = 6;
int bxspeed = 6;
int mpspeed = 6;
int spspeed = 6;
int set = 1;
int mispuntos = 0;
int suspuntos = 0;
int mset = 0;
int sset = 0;
bool powerup= false;
bool display = true;
bool ywin,ylose = false;
bool tintro = true;
SDLFont *font1;
char *stringa = "Set:";
char *stringb  = "Press 'H' for Help";
char *smispuntos = "--";
char *ssuspuntos = "--";
FILE *fkey;
bool demo = true;
char key[5];

//Mix_Chunk *music;
Mix_Chunk *poc;
Mix_Chunk *poc2;
Mix_Chunk *publico;
Mix_Chunk *boo;

//-----------------------------------------min and max
int min(int x, int y){
   if (x <= y){
    return x;
    }
    return y;
}
int max(int x, int y){
 if (x >= y){
 return x;
 }
 return y;
}
//------------------------------------------- random
int random(int num){
int LOW = 0; 
//cout << "entrada a random: " << num << endl;
//int ret = (int)(((long)rand()*num)/(long)(RAND_MAX+1));
int ret = rand() % (num - LOW + 1) + LOW;
//cout << "random: " << ret << endl;
return ret; 
}

// -------------------------------- init images y audio
void init(){
setenv("SDL_DSP_NOSELECT", "1", 0);
SDL_Surface *temp1;
//mplayer
implayer1 = SDL_LoadBMP("data/mplayer1.bmp"); 
SDL_SetColorKey(implayer1, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(implayer1);
SDL_FreeSurface(implayer1);
implayer1 = temp1;


implayer2 = SDL_LoadBMP("data/mplayer2.bmp"); 
SDL_SetColorKey(implayer2, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(implayer2);
SDL_FreeSurface(implayer2);
implayer2 = temp1;

// splayer
//temp1 = SDL_LoadBMP("data/isplayer1.bmp"); 
isplayer1 = SDL_LoadBMP("data/splayer1.bmp"); 
SDL_SetColorKey(isplayer1, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(isplayer1);
SDL_FreeSurface(isplayer1);
isplayer1 = temp1;

//temp1 = SDL_LoadBMP("data/splayer2.bmp");
//isplayer2 = SDL_DisplayFormat(temp1);
isplayer2 = SDL_LoadBMP("data/splayer2.bmp"); 
SDL_SetColorKey(isplayer2, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(isplayer2);
SDL_FreeSurface(isplayer2);
isplayer2 = temp1;

//red
//temp1 = SDL_LoadBMP("data/red.bmp");
//red = SDL_DisplayFormat(temp1);
red = SDL_LoadBMP("data/red.bmp"); 
SDL_SetColorKey(red,(SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(red);
SDL_FreeSurface(red);
red = temp1;

//win
//temp1 = SDL_LoadBMP("data/win.bmp");
//win = SDL_DisplayFormat(temp1);
win = SDL_LoadBMP("data/win.bmp"); 
SDL_SetColorKey(win, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(win);
SDL_FreeSurface(win);
win = temp1;

//lose
//temp1 = SDL_LoadBMP("data/lose");
//lose = SDL_DisplayFormat(temp1);
lose = SDL_LoadBMP("data/lose.bmp"); 
SDL_SetColorKey(lose, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(lose);
SDL_FreeSurface(lose);
lose = temp1;

//pelota
//temp1 = SDL_LoadBMP("data/pelota.bmp");
//pelota = SDL_DisplayFormat(temp1);
pelota = SDL_LoadBMP("data/pelota.bmp"); 
SDL_SetColorKey(pelota, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(pelota);
SDL_FreeSurface(pelota);
pelota = temp1;

//intro
//temp1 = SDL_LoadBMP("data/intro");
//intro = SDL_DisplayFormat(temp1);
intro = SDL_LoadBMP("data/intro.bmp"); 
SDL_SetColorKey(intro, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(intro);
SDL_FreeSurface(intro);
intro = temp1;

//demo
//temp1 = SDL_LoadBMP("data/tdem");
//tdem = SDL_DisplayFormat(temp1);
tdem = SDL_LoadBMP("data/tdem.bmp"); 
SDL_SetColorKey(tdem, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(implayer1->format, 0, 255, 0));
temp1 = SDL_DisplayFormat(tdem);
SDL_FreeSurface(tdem);
tdem = temp1;

// fondo
//temp1 = SDL_LoadBMP("data/campo");
//fondo = SDL_DisplayFormat(temp1);
fondo = SDL_LoadBMP("data/campo.bmp"); 
temp1 = SDL_DisplayFormat(fondo);
SDL_FreeSurface(fondo);
fondo = temp1;
mplayer = implayer1;
splayer = isplayer1;
}

//------------------------------------------------
//----------------------------------- draw mplayer
void draw(){
   SDL_Rect dest;    //mplayer
   SDL_Rect sdest; //splayer;
   SDL_Rect destb; // red
   SDL_Rect destp;
   SDL_Rect desti; //intro
   SDL_Rect desty; //win/lose
   SDL_Rect destdem;
   SDL_Rect destdem2;
   
   destdem.x = fondo->w / 2 - tdem->w/2;
   destdem.y = fondo->h / 2 - tdem->h/2 - 170;
   
   destdem2.x = fondo->w / 2 - tdem->w/2;
   destdem2.y = fondo->h / 2 - tdem->h/2 + 170;
   
   desti.x = fondo->w / 2 - intro->w / 2;
   desti.y = fondo->h /2 - intro->h / 2;
   
   desty.x = fondo->w/2 - win->w / 2;
   desty.y = fondo->h /2 - win->h / 2;
   
   dest.x = mpx;
   dest.y = mpy;

   sdest.x = spx;
   sdest.y = spy;
   
   destb.x = 2;
   destb.y = fondo->h /2-35;
   destp.x = px;
   destp.y = py;
   SDL_BlitSurface(fondo, NULL, screen, 0);      //sinitx, sinity
   drawString(screen, font1, 35,5, "Set: %d scores: %d/%d", set, mset, sset);  // mispuntos arriba
   drawString(screen, font1, 350,5, "You: %d", mispuntos, 0,255,0);  // smispuntos
   drawString(screen, font1, 420,5, "Hi: %d", suspuntos, 0,255,0);  // ssuspuntos
   
   if(demo == true) {
   SDL_BlitSurface(tdem, NULL, screen, &destdem);
   SDL_BlitSurface(tdem, NULL, screen, &destdem2);
   }
   
   SDL_BlitSurface(red, NULL, screen, &destb);
   SDL_BlitSurface(mplayer, NULL, screen, &dest);
   SDL_BlitSurface(splayer, NULL, screen, &sdest);
   SDL_BlitSurface(pelota, NULL, screen, &destp);
   
   if(tintro) SDL_BlitSurface(intro, NULL, screen, &desti);
   if(ywin == true) SDL_BlitSurface(win, NULL, screen, &desty);
   if(ylose == true) SDL_BlitSurface(lose, NULL, screen, &desty);
   SDL_Flip(screen);
}


//---------------------------------------------------------------------------
//------------- funcion que retorna la distancia de la pelota a ambos players
double distancia(int x, int y, int x2, int y2){
      double distancia = sqrt(pow(x2-x, 2) + pow(y2 - y, 2));
      return distancia;
}

void punto_mio(){
Mix_PlayChannel(3, publico, 0);
py = 225;
px = 800;
//px = -800;
mplayer = implayer1;
splayer = isplayer1;
pestado = 0;  
if(!demo) mispuntos +=15;
//smispuntos =  "You: %d", mispuntos;  // mispuntos arriba
if(mispuntos == 45) {
mispuntos = 0;
suspuntos = 0;
set +=1;
mset +=1;
if(set > 6) {
if(mset >= sset){
set = 1;
mset = 0;
sset = 0;
printf("gano yo"); 
tintro = false; 
ylose = false; 
ywin = true;//gano yo
}
if(mset < sset) {
set = 1;
mset = 0;
sset = 0;
printf("gana el"); 
tintro = false; 
ywin = false; 
ylose = true;//gana el
}
}
}
}
void punto_suyo(){
Mix_PlayChannel(3, publico, 0);
py = 225;
px = 800;
//px = -800;
mplayer = implayer1;
splayer = isplayer1;
pestado = 0; 
if(!demo) suspuntos +=15;
if(suspuntos == 45){
mispuntos = 0;
suspuntos = 0;
set +=1;
sset +=1;
if(set > 6){
if(mset >= sset){
set = 1;
mset = 0;
sset = 0;
//printf("gano yo"); 
tintro = false; 
ylose = false; 
ywin = true;//gano yo
}
if(mset < sset) {
set = 1;
mset = 0;
sset = 0;
//printf("gana el"); 
tintro = false; 
ywin = false; 
ylose = true;//gana el
}
}
}
}

//-------------------------------------------------------
// -------------------------------------------- mcontrol:
void mcontrol(){
//cambios de sentido
if(mpx < 5) mxdir = 2;
if(mpx + mplayer-> w > fondo->w - 5) mxdir = 1;
if(mpy > fondo->h - 5) mydir = 1;
if(mpy < fondo->h/2 + 10) mydir = 2;


double mdist = distancia(px, py, mpx + mplayer->w /2, mpy + mplayer->h/2);
double sdist = distancia(px, py, spx + splayer->w /2, spy + splayer->h /2);

if(mdist < 50 && pestado == 2)Mix_PlayChannel(1, poc, 0);
if(sdist < 70 && pestado == 1)Mix_PlayChannel(2, poc2, 0);

if(mdist < 50 && pestado != 0) mplayer = implayer2;
if(mdist > 150 && pestado !=0) mplayer = implayer1;
if(sdist < 70 && pestado == 1) splayer = isplayer2;
if(sdist > 120 && pestado == 2) splayer = isplayer1;

if(sdist < 65 && pestado == 1){
powerup = false;
int x = random(3);
pxdir = x; //lanza la pelota de vuelta segun random(3)
pestado = 2;
}
if(mdist < 40 && pestado == 2) {
pxdir = mxdir;
mxdir = 0;
pestado = 1;
if(mydir == 1)powerup = true;
mydir = 0;
}
//-------------------------------- control splayer
if(pestado == 0 || pestado == 2) {  // volver al punto de partida
if(sinitx > spx)spx = min(spx + 5, sinitx);
if(sinitx < spx)spx = max(spx - 5, sinitx);
if(sinity > spy) spy = min(spy + 5, sinity);
if(sinity < spy) spy = max(spy - 5, sinity);
}
if(pestado == 1){   // si esta llegando del player hacia arriba
if(py < fondo->h/2 - 40) {  // si la pelota pasa de la red
if(px > spx){
sxdir = 2;
spx = min(spx + mpspeed + 5, px);
}
if(px < spx){
sxdir = 1;
spx = max(spx - mpspeed - 5, px);
}
if(py > spy) spy = min(spy + mpspeed + 2, py);
if(py < spy) spy = max(spy - mpspeed - 2, py);

}
}
//-------------------------------   control pelota
if(pestado == 0){  // pelota en la mano de mi jugador
px = mpx - 5;
py = mpy+ 10;
}
//puntuacion
if(py > fondo->h && pestado != 0) { //punto suyo
punto_suyo();

}
if(py < 0) {  //punto mio
 punto_mio();
}//fin punto mio

//---------------control pelota
if(pestado != 0){
if(px < 5) {
Mix_PlayChannel(2, boo, 0);
if(pestado == 1) punto_suyo(); //printf("la cago yo");
if(pestado == 2) punto_mio(); //printf("la caga el");
}
if(px > fondo->w - 5) {
Mix_PlayChannel(2, boo, 0);
if(pestado == 1) punto_suyo(); //printf("la cago yo");
if(pestado == 2) punto_mio(); //printf("la caga el");
}

if(pxdir ==1) px -= 2;
if(pxdir ==2) px += 2;
if((pestado == 1) && (!powerup)) py -= bspeed + 1;
if((pestado == 1) && (powerup)) py -= bspeed + 3; //powerup
if(pestado == 2) py += bspeed + 1;
}
// ----------------- control mi player en x
if(mxdir == 1) mpx -= mpspeed;
if(mxdir == 2)mpx +=mpspeed;

// ------------------ control en y
if(mydir == 1)mpy -=mpspeed;
if(mydir == 2) mpy +=mpspeed;

draw();
 
 }  // fin mcontrol



//-----------------------------------------------------------
// -------------------------------- main o la madre del cordero
int main(int argc, char *argv[]){

SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
atexit(SDL_Quit);     //402,452
screen = SDL_SetVideoMode(502,564, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

SDL_WM_SetCaption("ptennis 1.0 - deplastic.tk", NULL);
//SDL_WM_ToggleFullScreen(screen);
font1 = initFont("data/font1");
init();
px = mpx - 5;
py = mpy- 10;

mpx = fondo->w/2 - mplayer->w / 2;
mpy = fondo->h - 120;
spx = fondo->w/2 - splayer->w/2;
spy = 60;
sinitx = spx;
sinity = spy;

//music = Mix_LoadWAV("data/loop");
poc = Mix_LoadWAV("data/poc.wav");
poc2 = Mix_LoadWAV("data/poc2.wav");
publico = Mix_LoadWAV("data/aplauso.wav");
boo = Mix_LoadWAV("data/boo.wav");
//Mix_VolumeChunk(music,20);
//Mix_PlayChannel(-1, music, 100);

if((fkey = fopen("ptkey.dat", "r")) != NULL){
do{
fscanf(fkey, "%s", key);
//fgets(key, 5, fkey);
}while(feof(fkey)==0);
fclose(fkey);
//cout << key;
}

 //int n  = strcmp (key, "tencm" );
 if (strcmp (key,"tencm")==0) demo = false;
 if (strcmp (key,"tencm")!=0) demo = true;
 //if(n == 0) demo = false;  cout << "registered version";
// if(n != 0) demo = true;cout << "running in demo";

draw();

//-------------------------------------- game loop
while(SDL_PollEvent(&event)>= 0){
SDL_Delay(50);

//SDL_BlitSurface(fondo, NULL, screen, 0);
mcontrol(); // controla mplayer y luego splayer
/*
if(event.type == SDL_KEYUP){
if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT){
mxdir = 0;
}
if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN){
mydir = 0;
}
}
*/
 if(event.type == SDL_KEYDOWN){
 if(event.key.keysym.sym == SDLK_LEFT)mxdir =1; powerup = false;
 if(event.key.keysym.sym == SDLK_RIGHT)mxdir =2; powerup = false;
 if(event.key.keysym.sym == SDLK_UP)mydir =1; powerup = true;
 if(event.key.keysym.sym == SDLK_DOWN)mydir =2; powerup = false;
 
 if(event.key.keysym.sym == SDLK_1)mpspeed =5;bspeed = 5;bxspeed = 5;
 if(event.key.keysym.sym == SDLK_2)mpspeed =6; bspeed = 6;bxspeed = 6;
 if(event.key.keysym.sym == SDLK_3)mpspeed =7; bspeed = 7; bxspeed = 7;
 if(event.key.keysym.sym == SDLK_4)mpspeed =8;  bspeed = 8;bxspeed = 8;
 if(event.key.keysym.sym == SDLK_5)mpspeed =9; bspeed = 9; bxspeed = 9;
 
 if(event.key.keysym.sym == SDLK_ESCAPE){
 SDL_Quit();
 }
 if(event.key.keysym.sym == SDLK_SPACE){
 if(pestado == 0){
 //Mix_FreeChunk(music);
 Mix_PlayChannel(1, poc, 0);
 //powerup = true;
 tintro = false;
 ywin = false;
 ylose = false;
 mxdir = 0;
 mydir = 0;
 powerup = true;
 px += 50;
 if(px > fondo->w - 100) pxdir = 1;
 if(px < 100) pxdir = 2;
 pxdir = 0;
 //pxdir = mxdir;
 pestado = 1;
 }
 }
 
 }
if(event.type == SDL_MOUSEBUTTONDOWN){   // mousedown
//mpx -=5;
if(tintro) tintro = false;//Mix_FreeChunk(music);
if(ywin) ywin = false;
if(ylose)ylose = false;
draw();

}
if(event.type == SDL_MOUSEMOTION){    // mousemotion
}
if(event.type == SDL_QUIT){
break;
}
          
}


  return 0;
}
