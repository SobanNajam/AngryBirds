/*soban najam 11-2051*/
#include <iostream>
#include <allegro.h>
#include <fstream>

#include<math.h>
#define pi 3.14159265358979323
using namespace std;

int counter = 0;

float VY(float,float);
float VX(float,float);
void input(float*,float*,float*,float*,BITMAP*,BITMAP*,BITMAP*,BITMAP*,ofstream&);
void output(int*,int*,int,int,BITMAP*);
bool collision(float,float,float,float,float,float,float,float);
bool mainmenu(BITMAP*,BITMAP*,int,int);
bool fnstncssl(BITMAP*,BITMAP*,int,int);


int main()
{
ofstream fout;
          fout.open("datalog.txt");
 //-------------------------------------
 //initialization   
 allegro_init();
 
 //install input devices
 install_keyboard();
 install_mouse();
 //setting up a window
 set_color_depth(32);
 set_gfx_mode(GFX_AUTODETECT_WINDOWED,1280,720,0,0); //by commenting "_WINDOWED" the entire screen can be accessed.
 
 //-------------------------------------
 // the code in between the dotted lines will always be used in game development.
 
 set_window_title("Angry Birds");
 
 int pa =1;
 //declaration
 float x=100,y=450,w=20,h=20;
 
 int so=0,jk=0;
 float l_f=6.5;
 float a = 70;
 int hit =0;
 float dt=0.1;
 float g=1.1;
 float vx,vy;
 int ok=0;

play:
if (pa=1){ 
 x=100,y=450,w=20,h=20;  
 a=70;
 dt=0.1;
 l_f=6.5;
 BITMAP *buffer=create_system_bitmap(1280,720);
 BITMAP* bird;
         bird = load_bitmap("simple.bmp",NULL);
 BITMAP* bg;
         bg = load_bitmap("b1.bmp",NULL);
 BITMAP* enemy;
         enemy = load_bitmap("sprites2.bmp",NULL);
 BITMAP* menu = load_bitmap("Main Menu.bmp",NULL); //--------
 BITMAP* point = load_bitmap("arrow.bmp",NULL);
  BITMAP* bap = load_bitmap("ss1.bmp",NULL);
 
 int xxx=430,yyy=180,game=0;
 
 
 game = mainmenu(menu,point,xxx,yyy);
        
  
       play3:
        if (game)
           {
           while ( !(key[KEY_ESC]) )
           {
             
            play2:
              if(counter==0 )
               {
               input(&x,&y,&a,&l_f,buffer,bird,bg,enemy,fout);
               vx= VX (a,l_f);
               vy = VY(a,l_f);
               counter=1;
               }
            
            blit(bg,buffer,0,0,0,0,1280,720);  
            masked_blit(bap,buffer,0,0,42,420,1280,720);
            masked_blit(bird,buffer,0,0,x,y,1280,720);
             if (hit ==1 )
              {
              int y3=180;
              pa=1;
              while(1){
              BITMAP* ta = load_bitmap("JEET.bmp",NULL);
              BITMAP* buffer3 = create_system_bitmap(1280,720);
              blit(buffer,buffer3,0,0,0,0,1280,720);
              masked_blit(ta,buffer3,0,0,0,0,1280,720);
              masked_blit(point,buffer3,0,0,10,y3,1280,720);
              blit(buffer3,screen,0,0,0,0,1280,720);
              
              if (key[KEY_DOWN])
              {y3 += 65;}
              if (key[KEY_UP])
              {y3 -= 65;}
              
              if (y3>310)y3=180;
              if (y3<180)y3=310;
              
              if (y3==180 && key[KEY_ENTER])
                 {
                  x=100,y=450,w=20,h=20;  
                  a=70;
                  dt=0.1;
                  l_f=6.5;
                  counter=0;
                  goto play2;
                  }
               
              if (y3==245 && key[KEY_ENTER])
                 {
                  counter=0;
                  
                  goto play;
                  }
              if (y3==310 && key[KEY_ENTER])
                 {
                  counter=0;
                  
                  game=0;
                  goto play3;
                  }rest(50);
              }
              }
            if (collision(x,y, x+30 , y+30 , 1000-10 , 580-10 , 1000+40 , 580+40 ) && hit==0 )
               {
                clear_bitmap(buffer);
                for (int k=0;k<9;k++)
                    {
                     blit(bg,buffer,0,0,0,0,1280,720);  
                     masked_blit(enemy,buffer,so,0,1000+jk,580,43,720);
                     masked_blit(bird,buffer,0,0,x,y,1280,720);
                     so+=43;
                     jk+=10;     
                     masked_blit(bap,buffer,0,0,42,420,1280,720);
                     blit(buffer,screen,0,0,0,0,1280,720);
                     rest(120);
                     clear_bitmap(buffer);
                    }hit=1;
                    
                     
               }
            if (hit != 1 && !(y > 580) )
               { 
               //main path start             
                x = x + vx*dt;
                y = y - (vy*dt) + (0.5*g*dt*dt);
                rest(25);
                dt+=0.36;
               //main path end
               }
            if (hit !=1)     
               masked_blit(enemy,buffer,0,0,1000,580,43,44);
      
        
           //BORDERS~~~
           if (x-38<0) x=38;
           if (x+38 > 1280) x=1280-38;
           if (y+10 > 600) y=600-10;            
           
           blit(buffer,screen,0,0,0,0,1280,720);
           if (hit!=1 &&  (y+10> 600 || y == 590))
              {
              int y3=180;
              pa=1;
              while(1){
              BITMAP* ta = load_bitmap("TRYAGAIN.bmp",NULL);
              BITMAP* buffer2 = create_system_bitmap(1280,720);
              blit(buffer,buffer2,0,0,0,0,1280,720);
              masked_blit(ta,buffer2,0,0,0,0,1280,720);
              masked_blit(point,buffer2,0,0,10,y3,1280,720);
              blit(buffer2,screen,0,0,0,0,1280,720);
              
              if (key[KEY_DOWN])
              {y3 += 65;}
              if (key[KEY_UP])
              {y3 -= 65;}
              
              if (y3>310)y3=180;
              if (y3<180)y3=310;
              
              if (y3==180 && key[KEY_ENTER])
                 {
                  x=100,y=450,w=20,h=20;  
                  a=70;
                  dt=0.1;
                  l_f=6.5;
                  counter=0;
                  goto play2;
                  }
               
              if (y3==245 && key[KEY_ENTER])
                 {
                  counter=0;
                  
                  goto play;
                  }
              if (y3==310 && key[KEY_ENTER])
                 {
                  counter=0;
                  
                  game=0;
                  goto play3;
                  }rest(50);
              }
              }
             
           
           
 
   
           rest(25); 

           }
 }
 
           
           destroy_bitmap(enemy);
           destroy_bitmap(bg);
           destroy_bitmap(bird);
           destroy_bitmap(buffer);
           destroy_bitmap(menu);
           destroy_bitmap(point);    

}}

END_OF_MAIN();


void input(float* x,float* y,float* angle,float* Launch_Force,BITMAP* buffer,BITMAP* bird2,BITMAP* bg,BITMAP* enemy,ofstream &fout)
{
     float xlast=*x;
     float ylast=*y;
     int x1=0,y1=0;
     BITMAP* bap = load_bitmap("ss1.bmp",NULL);
     
 while ( !key[KEY_SPACE] )
       {
        rest(25);
        blit(bg,buffer,0,0,0,0,1280,720); 
        masked_blit(bird2,buffer,0,0,*x,*y,1280,720);
        masked_blit(bap,buffer,x1,y1,42,420,1280,720);
        masked_blit(enemy,buffer,0,0,1000,580,43,44);
       
        
        if (key[KEY_LEFT])
           {*x = *x-1;  }              
        if (key[KEY_UP])
           {*y = *y-1;   }            
        if (key[KEY_DOWN])
           {*y = *y+1; }               
        if (key[KEY_RIGHT])
           {*x = *x+1; }
                   

           if (*x-18<0) *x=18;
           if (*y-18<0) *y=18;
           if (*x+18 > 1280) *x=1280-18;
           if (*y+18 > 600) *y=600-18;
       
           blit(buffer,screen,0,0,0,0,1280,720);
           clear_bitmap(buffer);
           //rest(25);
       }
       
       fout << "Value of xlast  " <<xlast  << endl;  
       fout << "Value of x  " <<*x  << endl;  
       fout << "Value of ylast  " <<ylast  << endl;  
       fout << "Value of y  " <<*y  << endl;  
       
       fout << "Value of lf  " <<*Launch_Force  << endl;  
       fout << "Value of angle  " <<*angle  << endl;  
       *Launch_Force = (xlast - *x) - ((xlast - *x)/1.16 );
       *angle = (*y - ylast) * 1.4;
       fout << "Value of new lf  " <<*Launch_Force  << endl;  
       fout << "Value of new angle  " <<*angle  << endl;  
       
}

float VY(float angle,float force)
{
  
 float jx;
 float soban;
 
       jx = ((angle*pi)/180);
       
       soban = (jx - ((jx*jx*jx)/6));
       
       return force * soban;
       
}

float VX(float angle,float force)
{
 float jx;
 float soban;
 
       jx = ((angle*pi)/180);
       
       soban = (1 - ((jx*jx)/2)+((jx*jx*jx)/24));
       
       return (force * soban);}

bool collision(float bx,float by,float bw,float bh,float px,float py,float pw,float ph)
{
        return ( bx >= px-43 && by >= py-44 && bx < px+43 && by < py+44 );
 
}


bool mainmenu(BITMAP* menu,BITMAP* point,int xxx,int yyy)
{
   BITMAP *buffer=create_system_bitmap(1280,720);
   while (!(key[KEY_ESC]))
         {
         rest(75);                 
         blit(menu,buffer,0,0,0,0,1280,720); 
         
         if (key[KEY_UP])
            {
            yyy -=85;
            if (yyy < 180) yyy=350;
            }
         else if (key[KEY_DOWN])
            {
            yyy += 85;
            if (yyy > 350) yyy=180;
            }
            
         masked_blit(point,buffer,0,0,xxx,yyy,1280,720);
         blit(buffer,screen,0,0,0,0,1280,720);
          
          readkey();      
          if (yyy == 180 && key[KEY_ENTER])
             {
             clear_bitmap(buffer);
             return true;
              }
          else if (yyy == 265 && key[KEY_ENTER])
                  {return fnstncssl(menu,point,320,650);}
          else if (yyy == 350 && key[KEY_ENTER])
                  {return false;}   
          
         

}
}

bool fnstncssl(BITMAP* menu,BITMAP* point,int xxx,int yyy)
{
 BITMAP* buffer = create_system_bitmap(1280,720);
 BITMAP* in =  load_bitmap("instructions.bmp",NULL);  
   
   while(1)
   {
    rest(150);
    blit(in,buffer,0,0,0,0,1280,720);
    masked_blit(point,buffer,0,0,xxx,yyy,1280,720);
    blit(buffer,screen,0,0,0,0,1280,720);
    readkey();
    
    if (key[KEY_RIGHT])
       xxx += 430;    
    if (key[KEY_LEFT])
       xxx -= 430;
    
    if (xxx > 750)xxx=320;
    if (xxx < 320)xxx=750;
    
    if (xxx== 320 && key[KEY_ENTER] )
       {
        destroy_bitmap(buffer);
        destroy_bitmap(in);
        return mainmenu(menu,point,430,180);
       }
    if (xxx== 750 && key[KEY_ENTER] )
       {return true;}
   
   
   clear(buffer);
   }      
}

