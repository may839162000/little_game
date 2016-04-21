#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
/* 音效記得要加入這個 */
#include "audio.h"
/* 另外還有底下的設定 */
/* For sound effect: In [Project Options]->[Parameters]->[Linker] add the parameter -lwinmm */


#include "console_draw3.h"
#include "kb_input2.h"
#include "font.h"
#include "image.h"
#include "framework.h"


#include "console_draw3.h"  /* 在 DOS command window 畫圖 */

#define width 448
#define height 136
#define OFFSET_X  0
#define OFFSET_Y 0
#define REFRESH_DURATION 3
/*
putASCII2()  最後兩個參數分別是字元前景和背景的顏色
可以參考下面的顏色值對照表來設定你想要的顏色
   0: 黑     1: 暗藍   2: 暗綠   3: 暗青
   4: 暗紅   5: 暗紫   6: 暗黃   7: 淺灰
   8: 暗灰   9: 亮藍  10: 亮綠  11: 亮青
  12: 亮紅  13: 亮紫  14: 亮黃  15: 白
*/



#define NUM_KEYS 7
#define REFRESH_RATE 10





void setMainmenu(Menu *m);
typedef struct _image {
    int row;
    int col;
    char *pixel;
    int *color;

} Image;
typedef struct enemy_{
    int col;
    int row;
    int active;
    Image *sta[1];
}Enemy;
Enemy enemy[100];

typedef struct role_{
    int col;
    int row;
    int active;
    Image *sta[1];
}Role;
Role role;

int IsEnding;
typedef struct gun_{
    int col;
    int row;
    int active;
    Image *sta[1];
}Gun;
Gun gun[1000];





/*****************************/

typedef struct _menu0 {
    int x;
    int y;
    Image *menu0[2];
    int m;
} Menu0;

typedef struct _ani {
    int x;
    int y;
    Image *ani[7];
    int m;
} Ani;


typedef struct _endmenu {
    int x;
    int y;
    int ed;
    Image *pic[2];
} Endmenu;


/***************/



void show_map(void);
void read_enemy(void);
void show_enemy();
void enemy_move(void);
void show_move(void);
void shoot(char);
char map[height][width];




Image * read_image(char *pixel_file, char *color_file);
char getpixel(Image *ip, int x, int y);
int getcolor(Image *ip, int x, int y);
int my_game(void);

int close=0;
int delay=0;

int dif=0;
int lau=0;
int hp=20;

    int ii,jj,kk;
    int score=0;
    char s[16]={0},c[15]="YOUR SCORE ";

int main(void)
{



    Menu mainmenu;
    Audio audio[10];


    openAudioFile("ahhh.wav", &audio[0]);
	openAudioFile("bullet1.wav", &audio[2]);
	openAudioFile("bullet2.wav", &audio[3]);
	openAudioFile("doooi", &audio[4]);
    openAudioFile("lalala.wav", &audio[5]);
    openAudioFile("biu.wav", &audio[6]);









    int IsEnding = 0;
    int r;
    int tick=0;

    int k;
    char str[40] = {'\0'};

    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};

    int cur_tick, last_tick;





    /* 啟動鍵盤控制 整個程式中只要做一次就行了*/
    initializeKeyInput();
    cur_tick = last_tick = timer();

    /**setMainmenu(&mainmenu);**/


    saveScreen();


    /* 無窮迴圈  裡面包含了這個程式的主要工作
    而且每次迴圈會不斷把最新的畫面顯示到螢幕上
    像是播動畫一樣 每次迴圈更新一次畫面 */


    /******************************************************************************/

    int end=0,re=0,in=0;
    srand(time(NULL));


    Menu0 menu0;
    menu0.m=0;
    Endmenu endmenu;
    endmenu.ed=0;
    Ani ani;



    menu0.menu0[0]=read_image("menu0.pixel","menu0.color");
    menu0.menu0[1]=read_image("menu1.pixel","menu1.color");
    endmenu.pic[0]=read_image("ed0.pixel","ed0.color");
    endmenu.pic[1]=read_image("ed1.pixel","ed1.color");
    ani.ani[0]=read_image("a1.pixel","a1.color");
    ani.ani[1]=read_image("a2.pixel","a2.color");
    ani.ani[2]=read_image("a3.pixel","a3.color");
    ani.ani[3]=read_image("a4.pixel","a4.color");
    ani.ani[4]=read_image("a5.pixel","a5.color");
    ani.ani[5]=read_image("a6.pixel","a6.color");
    ani.ani[6]=read_image("a7.pixel","a7.color");

    menu0.x=1;
    menu0.y=1;



    /*menu*/
    while (close!=1){
     while (!IsEnding) {
        cur_tick=0;
        last_tick=0;




        cur_tick = timer(); /* 每個 tick 0.01 秒 */

        if (cur_tick-last_tick > REFRESH_RATE) {
            last_tick = cur_tick;
            tick++;


            clearScreen();

            if(tick<200) show_ani(&ani,0);
            if(tick<300 && tick>=200) {show_ani(&ani,1); playAudio(&audio[3]);}
            if(tick<300 && tick>=270) {pauseAudio(&audio[3]);}
            if(tick<500 && tick>=300) {show_ani(&ani,2);}
            if(tick<600 && tick>=500) {show_ani(&ani,3);}

            if(tick<620 && tick>=600) {show_ani(&ani,4);playAudio(&audio[6]);}
            if(tick<640 && tick>=620) {show_ani(&ani,5);}
            if(tick<660 && tick>=640) {show_ani(&ani,6);}
            if(tick<680 && tick>=660) {show_ani(&ani,4);}
            if(tick<700 && tick>=680) {show_ani(&ani,5);}
            if(tick<720 && tick>=700) {show_ani(&ani,6);}
            if(tick<740 && tick>=720) {show_ani(&ani,4);}
            if(tick<760 && tick>=740) {show_ani(&ani,5);}
            if(tick<780 && tick>=760) {show_ani(&ani,6);}
            if(tick<800 && tick>=780) {show_ani(&ani,4);}
            if(tick<820 && tick>=800) {show_ani(&ani,5);}
            if(tick<840 && tick>=820) {show_ani(&ani,6);}

            if(tick<1000 && tick>=860) {pauseAudio(&audio[6]);}


            if(tick>840){
                show_menu(&menu0);

            }
          /*  for(j=1;j<=100;j++){
                putString(1, j, logo, 15, 15);
            }*/

            drawCmdWindow();  /* update window immediately */



        }

if(tick>840){
        if (KEY_DOWN(VK_ESCAPE)) {
            close=1;
            end=1;
            in++;
            IsEnding = 1;
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);

        }
        if (KEY_DOWN(VK_RETURN)) {
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            in++;
            if(menu0.m%2==1) {end=1;close=1;}


            IsEnding = 1;
        }
        if (KEY_DOWN(VK_DOWN)) {
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            in++;
            move_menu(&menu0);
        }
        if (KEY_DOWN(VK_UP)) {
            in++;
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            move_menu(&menu0);
        }


        if(in==1){
            in=0;
            Sleep(150);
        }}


    }

    if(end==0) IsEnding=0;



    /*******************************************************************************/

    /*game*/
    while (!IsEnding) {

            openAudioFile("lalala.wav", &audio[5]);
            audio[5].loop = 1;

            /* 開始播放背景音樂  */
            playAudio(&audio[5]);




        /* 每經過 REFRESH_RATE 個 ticks 才會更新一次畫面 */
        cur_tick = timer(); /* 每個 tick 0.01 秒 */
        sprintf(str, "%10d", cur_tick/1000);

        if (cur_tick-last_tick > REFRESH_RATE) {




            last_tick = cur_tick;


           clearScreen();
           restoreScreen();




            drawCmdWindow();

        } /* end of if (cur_tick % REFRESH_RATE == 0 ... */

        for (k=0; k<NUM_KEYS; k++) {
            /* 按鍵從原本被按下的狀態 變成放開的狀態  這是為了處理按著不放的情況 */
            if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }

        /* 鍵盤控制 處理按著不放的狀況 */
        /**
        for (k=0; k<NUM_KEYS; k++) {

            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                        if (IsItemSelected(&mainmenu, 0)) {
                            PlaySound(TEXT("metalplate.wav"), NULL, SND_ASYNC|SND_FILENAME);



                    } else if (IsOnItem(&mainmenu, 1)) {
                        IsEnding = 1;
                    }
                    break;
                case VK_SPACE:

                    radioMenu(&mainmenu);
                    break;
                }

            }

        } **/



{
    int key_down[5] = {0};
    int key_val[5] = {VK_LEFT, VK_DOWN, VK_RIGHT,VK_UP,VK_ESCAPE};

    int m,n,o;
    clock_t startc;
    int game_tick = 0;
    int game_tick2 =0;
    int gametick3=0;
    startc = clock();
    role.col=OFFSET_X+(width/2);role.row=OFFSET_Y+54;
    while(!IsEnding)
    {
        show_move();
        show_map();
        drawCmdWindow();
        if ((double)(clock()-startc) > 0.005*CLOCKS_PER_SEC)
        {
            game_tick++;
            startc = clock();
            game_tick2++;
            gametick3++;
        }
        if (gametick3> 0.0001*REFRESH_DURATION){
                enemy_move();
            }
        if (game_tick > 0.00005*REFRESH_DURATION)
        {


            game_tick = 0;
            clearScreen();

            show_map();


            o=448*hp/20;

            for(m=1;m<=4;m++){
                for(n=1;n<=o;n++){
                    putASCII2(n,m,'M',12,12);
                }
            }


            if (game_tick2> 30*REFRESH_DURATION)
            {
                read_enemy();

                game_tick2=0;

            }


            show_enemy();
        }

    //if(waitForKeyDown(2))
        {

        for (k=0; k<5; k++) {
         /* 按鍵處在被按下的狀態  把這個事件記錄在 key_down[k] */
         if(KEY_DOWN(key_val[k]) && !key_down[k]) {
            key_down[k] = 1;

            switch(key_val[k])
            {
            case VK_UP:
                if(role.row>OFFSET_Y+1)role.row-=27;
                break;

            case VK_DOWN:
                if(role.row<OFFSET_Y+108)role.row+=27;
                break;

            case VK_RIGHT:
                shoot('l');
                PlaySound(TEXT("bullet2.wav"), NULL, SND_ASYNC|SND_FILENAME);
                break;

            case VK_LEFT:
                shoot('k');
                PlaySound(TEXT("bullet2.wav"), NULL, SND_ASYNC|SND_FILENAME);
                break;
            case VK_ESCAPE:
                close=1;
                end=1;
                IsEnding=1;
                break;
            }
        }
         if(KEY_UP(key_val[k]) && key_down[k]) {
            key_down[k] = 0;
         }
        }
        }

    if(hp<=0) {IsEnding=1; }

    }

    }




        openAudioFile("ahhh.wav", &audio[0]);
        playAudio(&audio[0]);

    jj=score;
    for(ii=0;ii<=10;ii++){
        s[ii]=c[ii];
    }
    for(ii=16;ii>=11;ii--){
        kk=jj%10;
        jj=jj/10;
        if(kk==0) s[ii]='0';
        if(kk==1) s[ii]='1';
        if(kk==2) s[ii]='2';
        if(kk==3) s[ii]='3';
        if(kk==4) s[ii]='4';
        if(kk==5) s[ii]='5';
        if(kk==6) s[ii]='6';
        if(kk==7) s[ii]='7';
        if(kk==8) s[ii]='8';
        if(kk==9) s[ii]='9';
    }

        IsEnding=1;



    } /* while (IsEnding) */

    /***************************************************************************************************/

    if(end==0) IsEnding=0;
    /*ed*/
    while (!IsEnding) {

        pauseAudio(&audio[5]);
        cur_tick = timer(); /* 每個 tick 0.01 秒 */

        if (cur_tick-last_tick > REFRESH_RATE) {
            last_tick = cur_tick;


            clearScreen();


            show_endmenu(&endmenu);
        setMainmenu(&mainmenu);
        showMenu(&mainmenu);


          /*  for(j=1;j<=100;j++){
                putString(1, j, logo, 15, 15);
            }*/

            drawCmdWindow();  /* update window immediately */



        }


        if (KEY_DOWN(VK_ESCAPE)) {
            in=1;
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            close=1;
            end=1;
            IsEnding = 1;
        }
        if (KEY_DOWN(VK_RETURN)) {
            in=1;
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            if(endmenu.ed%2==1){ end=1;close=1;}
            IsEnding = 1;
            re=1;
        }
        if (KEY_DOWN(VK_DOWN)) {
            in=1;
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            move_endmenu(&endmenu);
        }
        if (KEY_DOWN(VK_UP)) {
            in=1;
            openAudioFile("hit.wav", &audio[1]);
            playAudio(&audio[1]);
            move_endmenu(&endmenu);
        }

        if(in==1){
            in=0;
            Sleep(300);
        }




    }
    if(re==1) {
        IsEnding = 0;
        for(r=0;r<100;r++){
            if(enemy[r].active==1)enemy[r].active=0;
        }
        for(r=0;r<1000;r++){
            if(gun[r].active==1)gun[r].active=0;
        }
        hp=20;
        lau=0;
        dif=0;
        score=0;
    }
    }


/*****************************************************************************************************/

    return 0;
}

void setMainmenu(Menu *m)
{
    int i;


    m->large_font = read_font("font.txt");
    m->x = 1;
    m->y = 3;
    m->fgcolor = 7;
    m->bgcolor = 15;
    m->num_options = 2;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;  /* 目前選擇的項目 */
    freopen("score.txt","w",stdout);
    printf("%d",score);

    freopen("score.txt","r",stdin);
    scanf("%d",&score);

    strcpy(m->text[0], s);
    strcpy(m->text[1],"");
    strcpy(m->alt_text[0], "");
    strcpy(m->alt_text[1], "");

}



int timer(void)
{
    return (clock()/(0.001*CLOCKS_PER_SEC));
}


/**void setMainmenu(Menu *m)
{
    int i;

    m->large_font = read_font("font.txt");
    m->x = 2;
    m->y = 2;
    m->fgcolor = 7;
    m->bgcolor = 15;
    m->num_options = 2;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;


    strcpy(m->text[0], "START");
    strcpy(m->text[1], "EXIT");
    strcpy(m->alt_text[0], "START *");
    strcpy(m->alt_text[1], "EXIT *");

} **/





/*--------------------------------------------------------------*/





void show_map(void)
{
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j <width; j++)
        {
            switch(map[i][j]) case'+': putASCII2(OFFSET_X+j , OFFSET_Y+i , map[i][j] , 3,0);

        }
    }
}

void read_enemy(void)
{
    int i,j,k,m,n,stage=0;
    srand(time(NULL));
    j=(rand()*rand())%5;
    k=rand()%5;
    m=(rand()*rand()/7)%5;
    n=(rand()*rand()/13)%5;
    stage=dif/20;



    for(i=0;i<100;i++)
    {
        if(enemy[i].active==0)
        {
            if(rand()*rand()*rand()%3==0)enemy[i].col=OFFSET_X+1;
            else enemy[i].col=OFFSET_X+(width-2);

            enemy[i].row=OFFSET_Y+27*(j);
            enemy[i].active=1;
            break;
        }
    }

    if(j!=k && stage >= 1){
    for(i=0;i<100;i++)
    {
        if(enemy[i].active==0)
        {
            if(rand()*rand()%3==0)enemy[i].col=OFFSET_X+1;
            else enemy[i].col=OFFSET_X+(width-2);
            enemy[i].row=-OFFSET_Y+27*(k);
            enemy[i].active=1;
            break;
        }
    }
    }
    if(m!=k && m!=j && stage >= 3){
    for(i=0;i<100;i++)
    {
        if(enemy[i].active==0)
        {
            if((rand()*rand()/7)%3==0)enemy[i].col=OFFSET_X+1;
            else enemy[i].col=OFFSET_X+(width-2);
            enemy[i].row=-OFFSET_Y+27*(m);
            enemy[i].active=1;
            break;
        }
    }
    }
    if(n!=k && n!=j  && n!=m && stage >= 6){
    for(i=0;i<100;i++)
    {
        if(enemy[i].active==0)
        {
            if((rand()*rand()/13)%3==0)enemy[i].col=OFFSET_X+1;
            else enemy[i].col=OFFSET_X+(width-2);
            enemy[i].row=-OFFSET_Y+27*(n);
            enemy[i].active=1;
            break;
        }
    }
    }

}

void show_enemy()
{

    int i;
    for(i=0; i<100; i++)
    {
        if(enemy[i].active==1&&enemy[i].col<role.col){
            enemy[i].sta[0]=read_image("enemy1.pixel", "enemy1.color");
            show_image(enemy[i].sta[0], enemy[i].col, enemy[i].row);
        }
        else if(enemy[i].active==1&&enemy[i].col>role.col){
            enemy[i].sta[0]=read_image("enemy3.pixel", "enemy3.color");
            show_image(enemy[i].sta[0], enemy[i].col, enemy[i].row);
        }

    }

    for(i=0; i<1000; i++)
    {

        if(gun[i].active==1){
             gun[i].sta[0]=read_image("x.pixel", "x.color");
            show_image(gun[i].sta[0], gun[i].col, gun[i].row+5);

            /**show_image(ball.poke[0],gun[i].col,gun[i].row);**/
        }

    }

}
void show_move(void)
{

    if(delay==0){
    role.sta[0]=read_image("mainframe0.pixel", "mainframe0.color");
            show_image(role.sta[0], role.col-10, role.row);
    }
}

void enemy_move(void)
{
    Audio audio[10];

    int i,j;
    for(i=0;i<100;i++){
        if(enemy[i].active==1){
            if(enemy[i].col<role.col )enemy[i].col++;
            else enemy[i].col--;
            if(enemy[i].col==role.col){hp=hp-5;   enemy[i].active=0; openAudioFile("laugh.wav", &audio[lau]);playAudio(&audio[lau]);lau++;}
        }
    }

    for(i=0; i<1000; i++)
    {
        if(gun[i].active==1){
            if(gun[i].col<role.col&&gun[i].col>=0) gun[i].col--;
            else if(gun[i].col>role.col&&gun[i].col<width) gun[i].col++;
            else if(gun[i].col=width-1||gun[i].col==0){gun[i].active=0;hp-=3; openAudioFile("laugh.wav", &audio[lau]);playAudio(&audio[lau]);lau++;}
        }

    }
    for(i=0; i<1000; i++){
        for(j=0; j<100; j++){
            if(gun[i].active==1&&enemy[j].active==1){
                    if(gun[i].row==enemy[j].row){
                if(gun[i].col==enemy[j].col||gun[i].col==(enemy[j].col)-1||gun[i].col==(enemy[j].col)+1){
                    gun[i].active=0;
                    enemy[j].active=0;
                    dif++;
                    score=score+dif*10;
                    PlaySound(TEXT("doooi.wav"), NULL, SND_ASYNC|SND_FILENAME);
                }}}}}

}


void shoot(char ch)
{
    int i;
    switch(ch)
    {
    case 'l':
        for(i=0;i<1000;i++){
            if(gun[i].active==0){
                gun[i].col=role.col+1;
                gun[i].row=role.row;
                gun[i].active=1;
                role.sta[0]=read_image("mainframe1.pixel", "mainframe1.color");
                show_image(role.sta[0], role.col, role.row);
                delay=1;
                break;
            }
        }

        break;
    case 'k':
        for(i=0;i<1000;i++){
        if(gun[i].active==0){
            gun[i].col=role.col-1;
            gun[i].row=role.row;
            gun[i].active=1;
            role.sta[0]=read_image("mainframe4.pixel", "mainframe4.color");
                show_image(role.sta[0], role.col, role.row);
                delay=1;
            break;
        }}
    }
}

char getpixel(Image *ip, int x, int y)
{
    return ip->pixel[y*ip->col + x];
}

int getcolor(Image *ip, int x, int y)
{
    return ip->color[y*ip->col + x];
}


void show_image(Image *ip, int offx, int offy)
{
    int x=0, y=0;
    char c;
    for (y=0; y<ip->row; y++) {
        for (x=0; x<ip->col; x++) {
            c = getpixel(ip, x, y);
            if (c!=' ')
            putASCII2( x + offx, y + offy, c, 0,getcolor(ip, x, y));
            }
    }
    if(delay==1)Sleep(100);delay=0;

}
Image * read_image(char *pixel_file, char *color_file)
{
    FILE *fid1, *fid2;
    int row, col, i, j;
    Image *p;

    fid1 = fopen(pixel_file, "r");
    fid2 = fopen(color_file, "r");
    if (fid1==NULL || fid2==NULL) {
        return NULL;
    } else {
        fscanf(fid1, "%d%d", &row, &col);
        fscanf(fid2, "%d%d", &row, &col); // supposedly, size should be the same
        p = (Image*) malloc(sizeof(Image));
        p->row = row;
        p->col = col;
        p->pixel = (char*) malloc(sizeof(char)*row*col);
        p->color = (int*) malloc(sizeof(int)*row*col);
        fscanf(fid1, "%*c");
        for (i=0; i<row; i++) {
            for (j=0; j<col; j++) {
                fscanf(fid1, "%c", & (p->pixel[i*col+j]));
                fscanf(fid2, "%1x", & (p->color[i*col+j]));
            }
            fscanf(fid1, "%*c");
            fscanf(fid2, "%*c");
        }
        fclose(fid1);
        fclose(fid2);
        return p;
    }
}

/***********************************************/
void show_menu(Menu0 *rp)
{
    show_image(rp->menu0[rp->m%2],0,0);


}
void show_endmenu(Endmenu *rp)
{
    show_image(rp->pic[rp->ed%2],0,0);

}

void show_ani(Ani *rp,int a)
{
    show_image(rp->ani[a],200,25);


}


/**
void show_ball(Ball *rp,int x,int y)
{
    rp->col=x;
    rp->row=y;
    show_image(rp->ball,rp->col,rp->row);
}
**/

void move_menu(Menu0 *rp)
{

    rp->m++;

}



void move_endmenu(Endmenu *rp)
{

    rp->ed++;

}
