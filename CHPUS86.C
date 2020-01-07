#include <alloc.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <bios.h>
#include <sys\stat.h>
#include <fcntl.h>
#include <dos.h>
#include "twindowl.h"
#include "keys.h"
#include "schpu.h"

WINDOW far *scr,far *help,far *proc, far *scrdir, far *scrlist;
WINDOW far *mosn, far *upprog, far *rabchpu;
int inte[] = {0,7,5};
int ra=0,  na=0, sh=0, lstr=0, scrd;
int port, nport, gdan, gport, prport;
long razch;

main()
{
  char c;
  int l,i,j,k,mo=0,m1,m2,m3,m4;
  int gd;
  char *menu[]={"êÄÅéíÄ ë óèì","éÅêÄÅéíäÄ ìè","äéçîàÉìêÄñàü","ÇõïéÑ",NULL};

  system("cls");
  mosn = establish_window(0,0,3,80);
  scr = establish_window(0,3,17,80);
  help = establish_window(0,23,3,80);
  proc = establish_window(0,20,3,80);
  scrdir = establish_window(35,3,17,45);
  scrlist = establish_window(0,12,8,80);
  if((mosn==0)||(scr==0)||(help==0)||(proc==0))
  {
    close_all();
    exit(1);
  }
  LoadConf();
  NPort();
  set_colors(help,NORMAL,MAGENTA,WHITE,BRIGHT);
  set_colors(scr,ALL,WHITE,BLUE,DIM);
  set_colors(scr,BORDER,BLACK,YELLOW,DIM);
  set_colors(scr,ACCENT,YELLOW,BLACK,DIM);
  set_colors(scr,NORMAL,WHITE,BLUE,DIM);
  set_border(scr,1);
  set_border(mosn,3);
  set_colors(mosn,ALL,BLACK,WHITE,DIM);
  set_colors(mosn,BORDER,BLUE,YELLOW,DIM);
  set_colors(mosn,ACCENT,WHITE,BLACK,DIM);
  set_colors(mosn,NORMAL,BLACK,WHITE,DIM);
  set_border(proc,2);
  set_colors(proc,ALL,YELLOW,WHITE,DIM);
  set_colors(proc,BORDER,BLACK,AQUA,DIM);
  set_colors(proc,ACCENT,BLACK,YELLOW+BLINK,BRIGHT);
  set_colors(proc,NORMAL,BLUE,WHITE,DIM);
  set_colors(scrdir,ALL,BLUE,WHITE,DIM);
  set_colors(scrdir,BORDER,BLACK,YELLOW,DIM);
  set_colors(scrdir,ACCENT,YELLOW,BLACK,DIM);
  set_colors(scrdir,NORMAL,BLUE,WHITE,DIM);
  set_border(scrdir,2);
  set_colors(scrlist,ALL,BLUE,WHITE,DIM);
  set_colors(scrlist,BORDER,WHITE,RED,DIM);
  set_colors(scrlist,ACCENT,YELLOW,BLACK,DIM);
  set_colors(scrlist,NORMAL,BLUE,WHITE,DIM);
  set_border(scrlist,1);
  wprintf(help,"    %c%c%c%c - ÇõÅéê,   %c%c%c - èéÑíÇÖêÜÑÖçàÖ,   ESC - ÇõïéÑ",24,25,26,27,17,196,217);

  display_window(scr);
  display_window(help);
  display_window(proc);
  set_cursor_type(-1);
  reverse_video(mosn);
  wprintf(mosn,"  %s  ",menu[0]);
  normal_video(mosn);
  wprintf(mosn,"   %s    %s    %s  ",menu[1],menu[2],menu[3]);
  wcursor(mosn,16,0);
  display_window(mosn);
  wcursor(scr,25,2);
  wprintf(scr," è‡Æ£‡†¨¨† ·¢Ôß® · ìóèì S8600 ");
  wcursor(scr,0,5);
  wprintf(scr,"     €        €€€€        €€€€        €      €€€€€€    €€€    €€€      € \n");
  wprintf(scr,"    €€€     €€    €€    €€    €€     €€€     €€   €€   €€ €  € €€     €€€ \n");
  wprintf(scr,"   €€ €€    €€    €€    €€          €€ €€    €€€€€€    €€  €€  €€    €€ €€ \n");
  wprintf(scr,"  €€   €€   €€    €€    €€         €€   €€   €€    €€  €€  €€  €€   €€   €€ \n");
  wprintf(scr," €€€€€€€€€  €€    €€    €€    €€  €€€€€€€€€  €€     €€ €€      €€  €€€€€€€€€ \n");
  wprintf(scr,"€€       €€   €€€€        €€€€   €€       €€ €€€€€€€€  €€      €€ €€       €€ \n");
 wcursor(scr,0,13);
  wprintf(scr,"  í¢•‡·™†Ô Æ°´. £. ä®¨‡Î                        éäÅ ‚•´•‰Æ≠ (8-236) 4-10-83 ");
    l = 0;scrd=0;
  while((c = getch()) != ESC)
  {
    switch(c)
    {
    case 32:
            if(scrd==1)
            {
            hide_window(scrdir);
            scrd=0;
            }
            else
            {
            display_window(scrdir);
            scrd=1;
            }
            break;
     case 77 :
               wcursor(mosn,(mosn->_cr - strlen(menu[mo])-4),0);
               wprintf(mosn,"  %s  ",menu[mo]);
               if((mo + 1) <= 3)
                 mo += 1;
               else
               {
                 mo = 0;
                 wcursor(mosn,0,0);
               }
               reverse_video(mosn);
               wprintf(mosn,"  %s  ",menu[mo]);
               normal_video(mosn);
               if((mo == 1) && (l == 1))
                 if((k = Upprog()) == -1)
                 {
                   wcursor(proc,0,0);
                   reverse_video(proc);
                   wprintf(proc,"                             ç• Â¢†‚†•‚ Ø†¨Ô‚®");
                   normal_video(proc);
                   getch();
                   clear_window(proc);
                 }
                 else if(k == ESC)
                   l = 0;
                 else
                   l = 1;
               if((mo == 0) && (l == 1))
                 if((k = Rabchpu()) == -1)
                 {
                   wcursor(proc,0,0);
                   reverse_video(proc);
                   wprintf(proc,"                             ç• Â¢†‚†•‚ Ø†¨Ô‚®");
                   normal_video(proc);
                   getch();
                   wcursor(proc,0,0);
                   wprintf(proc,"                                              ");
                 }
                 else if(k == ESC)
                   l = 0;
                 else
                   l = 1;
               break;
     case 75 : wcursor(mosn,(mosn->_cr - strlen(menu[mo])-4),0);
               wprintf(mosn,"  %s  ",menu[mo]);
               if((mo - 1) >= 0)
               {
                 mo -= 1;
                 wcursor(mosn,(mosn->_cr-strlen(menu[mo])-strlen(menu[mo+1])-8),0);
               }
               else
               {
                 mo = 3;
                 wcursor(mosn,(mosn->_cr + strlen(menu[1]) + strlen(menu[2]) + 8),0);
               }
               reverse_video(mosn);
               wprintf(mosn,"  %s  ",menu[mo]);
               normal_video(mosn);
               if((mo == 0) && (l == 1))
                 if((k = Rabchpu()) == -1)
                 {
                   wcursor(proc,0,0);
                   reverse_video(proc);
                   wprintf(proc,"                             ç• Â¢†‚†•‚ Ø†¨Ô‚®");
                   normal_video(proc);
                   getch();
                   wcursor(proc,0,0);
                   wprintf(proc,"                                              ");
                 }
                 else if(k == ESC)
                   l = 0;
                 else
                   l = 1;
               if((mo == 1) && (l == 1))
                 if((k = Upprog()) == -1)
                 {
                   wcursor(proc,0,0);
                   reverse_video(proc);
                   wprintf(proc,"                             ç• Â¢†‚†•‚ Ø†¨Ô‚®");
                   normal_video(proc);
                   getch();
                   wcursor(proc,0,0);
                   wprintf(proc,"                                              ");
                 }
                 else if(k == ESC)
                   l = 0;
                 else
                   l = 1;
               break;
     case 80 :
     case 13 : switch(mo)
               {
               case 0 : if((k = Rabchpu()) == -1)
                        {
                          wcursor(proc,0,0);
                          reverse_video(proc);
                          wprintf(proc,"                             ç• Â¢†‚†•‚ Ø†¨Ô‚®");
                          normal_video(proc);
                          getch();
                          wcursor(proc,0,0);
                          wprintf(proc,"                                              ");
                        }
                        else if(k == ESC)
                          l = 0;
                        else
                          l = 1;
                        break;
               case 1 : if((k = Upprog()) == -1)
                        {
                          wcursor(proc,0,0);
                          reverse_video(proc);
                          wprintf(proc,"                             ç• Â¢†‚†•‚ Ø†¨Ô‚®");
                          normal_video(proc);
                          getch();
                          wcursor(proc,0,0);
                          wprintf(proc,"                                              ");
                        }
                        else if(k == ESC)
                          l = 0;
                        else
                          l = 1;
                        break;
               case 2 :  Config();
                        break;
               case 3 : close_all();
                        SaveConf();
                        exit(1);
                        break;
               }
     default : break;
    }
    if((k == 75) || (k == 77))
      ungetch(k);
    k = 0;
  }
  close_all();
  SaveConf();
}


void LoadConf(void)
{
  FILE far *cnf;
  int h,i,j;
  if(access("schpu.cnf",0) == 0)
  {
    if((cnf = fopen("schpu.cnf","r")) == NULL)
      return;
    for(h = 0;h <= 2;h++)
    {
      if(fscanf(cnf,"%d",&inte[h]) == EOF)
        return;
    }
    fclose(cnf);
  }
}


void SaveConf(void)
{
  FILE far *cnf;
  int i,j,h;
  if((cnf = fopen("schpu.cnf","w")) != NULL)
  {
    fprintf(cnf,"%d %d %d ",inte[0],inte[1],inte[2]);
    fclose(cnf);
  }
}

void Config(void)
{
  WINDOW far *config;
  int in=0,end=0;
  char c;
  char far *menu3[] = {"èéêí             ",
                   "ëäéêéëíú èÖêÖÑÄóà",
                   "êÄáåÖê óÄëíà     ",
                   NULL};
  char far *menu3_a[][8] = {
                        {"ëéå1 ",
                         "ëéå2 ",
                         NULL,
                         NULL,
                         NULL,
                         NULL,
                         NULL,
                         NULL,
                         },
                        {"110    °Æ§ ",
                         "150    °Æ§ ",
                         "300    °Æ§ ",
                         "600    °Æ§ ",
                         "1200   °Æ§ ",
                         "2400   °Æ§ ",
                         "4800   °Æ§ ",
                         "9600   °Æ§ ",
                         },
                        {"2ä ",
                         "4ä ",
                         "8ä ",
                         "16ä",
                         "32ä",
                         "64ä",
                         NULL,
                         NULL,
                         },
                   NULL,};

  if((config = establish_window(34,3,6,36)) == 0)
    return (-1);
  set_border(config,2);
  set_colors(config,ALL,BLACK,AQUA,DIM);
  set_colors(config,BORDER,BLACK,MAGENTA,DIM);
  set_colors(config,ACCENT,YELLOW,BLACK,BRIGHT);
  set_colors(config,NORMAL,BLUE,WHITE,DIM);
  wcursor(help,0,0);
  wprintf(help,"   %c %c %c%c%c - ÇõÅéê, èêéÅÖã - àáåÖçÖçàÖ, ENTER - ÇõïéÑ         ",24,25,17,196,217);
  wcursor(config,0,0);
  reverse_video(config);
  wprintf(config,"  %s    %s  \n",menu3[0],menu3_a[0][inte[0]]);
  normal_video(config);
  wprintf(config,"  %s    %s  \n",menu3[1],menu3_a[1][inte[1]]);
  wprintf(config,"  %s    %s  \n",menu3[2],menu3_a[2][inte[2]]);
  display_window(config);

  while((c = getch()) != 13)
  {
    switch(c)
    {
/*    case 13 :*/
    case 80 : wcursor(config,0,in);
              wprintf(config,"  %s    %s  ",menu3[in],menu3_a[in][inte[in]]);
              if((in + 1) <= 2)
                in += 1;
              else
                in = 0;
              reverse_video(config);
              wcursor(config,0,in);
              wprintf(config,"  %s    %s  ",menu3[in],menu3_a[in][inte[in]]);
              normal_video(config);
              break;
    case 72 : wcursor(config,0,in);
              wprintf(config,"  %s    %s  ",menu3[in],menu3_a[in][inte[in]]);
              if((in - 1) >= 0)
                in -= 1;
              else
                in = 2;
              reverse_video(config);
              wcursor(config,0,in);
              wprintf(config,"  %s    %s  ",menu3[in],menu3_a[in][inte[in]]);
              normal_video(config);
              break;
    case 32 : switch(in)
              {
              case 0 : end = 1;break;
              case 1 : end = 7;break;
              case 2 : end = 5;break;
              }
              if((inte[in] + 1) <= end)
                inte[in] += 1;
              else
                inte[in] = 0;
              reverse_video(config);
              wcursor(config,21,in);
              wprintf(config,"  %s  ",menu3_a[in][inte[in]]);
              normal_video(config);
              break;
    default : break;
    }
  }
  delete_window(config);
  wcursor(help,0,0);
  wprintf(help,"    %c%c%c%c - ÇõÅéê,   %c%c%c - èéÑíÇÖêÜÑÖçàÖ,   ESC - ÇõïéÑ",24,25,26,27,17,196,217);
  NPort();
 return 1;
}


void NPort(void)
{
 int m;
 int nn[4];
  switch(inte[0])
  {
   case 0 : port=0;
            nport=0x3F8;
            prport=0x3F9;
            gdan=0x3FD;
            gport=0x3FA;
            break;
   case 1 : port=1;
            nport=0x2F8;
            prport=0x2F9;
            gdan=0x2FD;
            gport=0x2FA;
            break;
  }
  switch(inte[1])
  {
   case 0 : nn[0] = 0x00;break;
   case 1 : nn[0] = 0x20;break;
   case 2 : nn[0] = 0x40;break;
   case 3 : nn[0] = 0x60;break;
   case 4 : nn[0] = 0x80;break;
   case 5 : nn[0] = 0xA0;break;
   case 6 : nn[0] = 0xC0;break;
   case 7 : nn[0] = 0xE0;break;
  }
  switch(inte[2])
  {
   case 0 : razch = 2000;break;
   case 1 : razch = 3600;break;
   case 2 : razch = 7000;break;
   case 3 : razch = 14500;break;
   case 4 : razch = 29500;break;
   case 5 : razch = 58000;break;
  }
   nn[1] = 0x00;
   nn[2] = 0x00;
   nn[3] = 0x03;
  m = (nn[0] | nn[1] | nn[2] | nn[3]);
  bioscom(0,m,port);

}


/*int OUTPORT(char c)
{
  while (1)
  {
  while((((bioscom(3,0,0)) & 0x20) != 0))
  {
    if(kbhit() != 0)
      {
      if((getch()) == ESC)
        return -1;
      }
  }
   if(((bioscom(1,c,0) / 256) & 128) == 128)
   {
   error_message("ìëíêéâëíÇé çÖ ÉéíéÇé");
   delay(100);
   clear_message();
   flushall();
   if(kbhit() != 0)
    if((getch()) == ESC)
    return -1;
    }
      return 1;
 }
} */




int Rabchpu(void)
{
 int i;
 char c;
 char name[9] = "         ",nameu[5] = "     ", nname[9] = "         ", fname[9] = "         ";
 char rstr[5] = "     ",rfile[5] = "     ";
 char far *menu2[] = {"äÄíÄãéÉ       ","ÇõÇéÑ àá ìóèì  ","áÄÉêìáäÄ ìóèì  ","ìÑÄãÖçàÖ      ","èÖêÖàåÖçéÇÄçàÖ","ëéáÑÄçàÖ îÄâãÄ"};
 ra=0;
 if(rabchpu == 0)
 {
   if((rabchpu = establish_window(1,3,8,20)) == 0)
     return (-1);
   set_border(rabchpu,2);
   set_colors(rabchpu,ALL,BLACK,BLUE,BRIGHT);
   set_colors(rabchpu,BORDER,BLACK,GREEN,DIM);
   set_colors(rabchpu,ACCENT,WHITE,BLACK,DIM);
   set_colors(rabchpu,NORMAL,BLUE,WHITE,DIM);

   wprintf(rabchpu,"  %s  \n  %s  \n  %s  \n  %s  \n  %s",menu2[0],menu2[1],menu2[2],menu2[3],menu2[4]);
   wprintf(rabchpu,"  \n  %s",menu2[5]);
 }
 reverse_video(rabchpu);
 wcursor(rabchpu,0,ra);
 wprintf(rabchpu,"  %s  ",menu2[ra]);
 normal_video(rabchpu);
 display_window(rabchpu);
 while((c = getch()) != ESC)
 {
   switch(c)
   {
   case 0  : c = getch();
             switch(c)
             {
              case 60 : clear_window(scrlist);
                        wcursor(scrlist,0,0);
                        break;
              default : ungetch(c);
                        break;
             }
             break;
    case 32:
            if(scrd==1)
            {
            hide_window(scrdir);
            scrd=0;
            }
            else
            {
            display_window(scrdir);
            scrd=1;
            }
            break;
   case 77 :
   case 75 :
             wcursor(rabchpu,0,ra);
             wprintf(rabchpu,"  %s  ",menu2[ra]);
             hide_window(rabchpu);
             return c;
             /*break;*/
   case 80 : wcursor(rabchpu,0,ra);
             wprintf(rabchpu,"  %s  ",menu2[ra]);
             if((ra+1) <= 5)
               ra += 1;
             else
               ra = 0;
             reverse_video(rabchpu);
             wcursor(rabchpu,0,ra);
             wprintf(rabchpu,"  %s  ",menu2[ra]);
             normal_video(rabchpu);
             break;
   case 72 : wcursor(rabchpu,0,ra);
             wprintf(rabchpu,"  %s  ",menu2[ra]);
             if((ra-1) >= 0)
               ra -= 1;
             else
               ra = 5;
             reverse_video(rabchpu);
             wcursor(rabchpu,0,ra);
             wprintf(rabchpu,"  %s  ",menu2[ra]);
             normal_video(rabchpu);
             break;
   case 13 : switch(ra)
             {
              case 0 : clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô „·‚‡Æ©·‚¢†: ");
                       wgetstr(proc,nameu,4,17,1);
                       clear_window(proc);
                       clear_window(scrlist);
                       hide_window(rabchpu);
                       if(scrd==0)
                       display_window(scrdir);
                       DIR(nameu,1);
                       display_window(rabchpu);
                       break;
              case 1 : clear_window(scrlist);
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô ‰†©´†: ");
                       wgetstr(proc,name,8,12,1);
                       for(i = 0; i < 8; i++) {
                       if(name[i] == ' ') {
                       name[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô „·‚‡Æ©·‚¢†: ");
                       wgetstr(proc,nameu,4,17,1);
                       for(i = 0; i < 4; i++) {
                       if(nameu[i] == ' ') {
                       nameu[i] = '\0';
                       break;
                       }
                       }
                       hide_window(rabchpu);
                       INPUT(name,nameu,1);
                       display_window(rabchpu);
                       break;
              case 2 : clear_window(scrlist);
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô ‰†©´†: ");
                       wgetstr(proc,name,8,12,1);
                       for(i = 0; i < 8; i++) {
                       if(name[i] == ' ') {
                       name[i] = '\0';
                       break;
                       }
                       }
                       strcpy(fname,name);
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô „·‚‡Æ©·‚¢†: ");
                       wgetstr(proc,nameu,4,17,1);
                       for(i = 0; i < 4; i++) {
                       if(nameu[i] == ' ') {
                       nameu[i] = '\0';
                       break;
                       }
                       }
                       hide_window(rabchpu);
                       OUTPUT(name,nameu,fname,1);
                       delay(3000);
                       DIR(nameu,0);
                       display_window(rabchpu);
                       break;
              case 3 : clear_window(scrlist);
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô ‰†©´†: ");
                       wgetstr(proc,name,8,12,1);
                       for(i = 0; i < 8; i++) {
                       if(name[i] == ' ') {
                       name[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô „·‚‡Æ©·‚¢†: ");
                       wgetstr(proc,nameu,4,17,1);
                       for(i = 0; i < 4; i++) {
                       if(nameu[i] == ' ') {
                       nameu[i] = '\0';
                       break;
                       }
                       }
                       hide_window(rabchpu);
                       DELET(name,nameu,1);
                       delay(3000);
                       DIR(nameu,0);
                       display_window(rabchpu);
                       break;
              case 4 : clear_window(scrlist);
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô ‰†©´†: ");
                       wgetstr(proc,name,8,12,1);
                       for(i = 0; i < 8; i++) {
                       if(name[i] == ' ') {
                       name[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô ≠Æ¢Æ£Æ ‰†©´†: ");
                       wgetstr(proc,nname,8,19,1);
                       for(i = 0; i < 8; i++) {
                       if(name[i] == ' ') {
                       name[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô „·‚‡Æ©·‚¢†: ");
                       wgetstr(proc,nameu,4,17,1);
                       for(i = 0; i < 4; i++) {
                       if(nameu[i] == ' ') {
                       nameu[i] = '\0';
                       break;
                       }
                       }
                       hide_window(rabchpu);
                       REMOV(name,nameu,nname,1);
                       delay(3000);
                       DIR(nameu,0);
                       display_window(rabchpu);
                       break;
              case 5 : clear_window(scrlist);
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô ‰†©´†: ");
                       wgetstr(proc,name,8,12,1);
                       for(i = 0; i < 8; i++) {
                       if(name[i] == ' ') {
                       name[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"à¨Ô „·‚‡Æ©·‚¢†: ");
                       wgetstr(proc,nameu,4,17,1);
                       for(i = 0; i < 4; i++) {
                       if(nameu[i] == ' ') {
                       nameu[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"ê†ß¨•‡ ·‚‡Æ™®: ");
                       wgetstr(proc,rstr,4,15,1);
                       for(i = 0; i < 4; i++) {
                       if(rstr[i] == ' ') {
                       rstr[i] = '\0';
                       break;
                       }
                       }
                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"äÆ´®Á•·‚¢Æ ·‚‡Æ™: ");
                       wgetstr(proc,rfile,4,18,1);
                       for(i = 0; i < 4; i++) {
                       if(rfile[i] == ' ') {
                       rfile[i] = '\0';
                       break;
                       }
                       }
                       hide_window(rabchpu);
                       CREAT(name,nameu,rstr,rfile,1);
                       delay(3000);
                       DIR(nameu,0);
                       display_window(rabchpu);
                       break;
              default : break;
             }
             break;
   default : break;
   }
 }
   hide_window(rabchpu);
   hide_window(upprog);
   return c;
}

int Upprog(void)
{
 char far *menu1[] = {"èéÑÉéíéÇäÄ ìè","èéÑÉéíéÇäÄ ÇÇ","áÄÉêìáäÄ     ","èêéÑéãÜÖçàÖ  ",NULL};
 char c;
 if(upprog == 0)
 {
   if((upprog = establish_window(17,3,6,17)) == 0)
     return(-1);
   set_border(upprog,2);
   set_colors(upprog,ALL,BLACK,BLUE,BRIGHT);
   set_colors(upprog,BORDER,BLACK,GREEN,DIM);
   set_colors(upprog,ACCENT,WHITE,BLACK,DIM);
   set_colors(upprog,NORMAL,BLUE,WHITE,DIM);

   wprintf(upprog,"  %s  \n  %s  \n  %s  \n  %s",menu1[0],menu1[1],menu1[2],menu1[3]);
 }
 reverse_video(upprog);
 wcursor(upprog,0,na);
 wprintf(upprog,"  %s  ",menu1[na]);
 normal_video(upprog);
 display_window(upprog);
 while((c = getch()) != ESC)
 {
 switch(c)
 {
   case 0  : c = getch();
             switch(c)
             {
              case 60 : clear_window(scrlist);
                        wcursor(scrlist,0,0);
                        break;
              default : ungetch(c);
                        break;
             }
             break;
    case 32:
            if(scrd==1)
            {
            hide_window(scrdir);
            scrd=0;
            }
            else
            {
            display_window(scrdir);
            scrd=1;
            }
            break;
   case 77 :
   case 75 :
             wcursor(upprog,0,na);
             wprintf(upprog,"  %s  ",menu1[na]);
             hide_window(upprog);
             return c;
             /*break;*/
   case 80 : wcursor(upprog,0,na);
             wprintf(upprog,"  %s  ",menu1[na]);
             if((na+1) <= 3)
               na += 1;
             else
               na = 0;
             reverse_video(upprog);
             wcursor(upprog,0,na);
             wprintf(upprog,"  %s  ",menu1[na]);
             normal_video(upprog);
             break;
   case 72 : wcursor(upprog,0,na);
             wprintf(upprog,"  %s  ",menu1[na]);
             if((na-1) >= 0)
               na -= 1;
             else
               na = 3;
             reverse_video(upprog);
             wcursor(upprog,0,na);
             wprintf(upprog,"  %s  ",menu1[na]);
             normal_video(upprog);
             break;

 case 13 : switch(na)
             {
             case 0 :
                      hide_window(upprog);
                      Podup();
                      display_window(upprog);
                      break;
             case 1 :
                      hide_window(upprog);
                      Prodol();
                      display_window(upprog);
                      break;
             case 2 :
                      hide_window(upprog);
                      Podkach();
                      display_window(upprog);
                      break;
             case 3 :
                      hide_window(upprog);
                      Podcon();
                      display_window(upprog);
                      break;
             default : break;
             }
             break;
 default : break;
 }
 }
   hide_window(upprog);
   hide_window(rabchpu);
   return c;
}

void  DIR(char *nameu, int nw)
{
char com[14] = "DIR,/   ,/TY1";
char ch;
char str[128];
int i,r,j,n,strp;
char s=0;
com[5] = nameu[0];
com[6] = nameu[1];
com[7] = nameu[2];
n = 0;i = 0;strp = 0;
j = 0;
/*                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"%s ",com);*/
clear_window(scrdir);
wcursor(scrdir,0,0);
/*display_window(scrlist);
clear_window(scrlist);
wcursor(scrlist,0,0);*/
while(j < 13) {
 outp(nport,com[j++]);
 /*delay(200);*/
 do{}while((inp(gdan) & 0x20) == 0);
 }
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 0x1) == 0);
  ch = 0x7F & inp(nport);
    /*wputchar(scrlist,ch);*/
  if(s==27) break;
  } while(ch != ACK);
 do
 {
 if(s==27) break;
  do{} while((inp(gdan) & 0x1) == 0);
  ch = 0x7F & inp(nport);
  if(ch == DC2)
  {
   do
    {
 if(kbhit()) s=getch();
 if(s==27){ch=DC4; n=2;}
  do{} while((inp(gdan) & 0x1) == 0);
    ch = 0x7F & inp(nport);
    if(ch == '%')
    n++;
    if(n == 1 && ch != 0)
    {
     if((ch != CR) && (ch != '%') && (ch != DC4) && (ch != DC2))
      {
      str[i] = ch;
      i++;
      }
      if(ch == CR)
      {
  do{} while((inp(gdan) & 0x1) == 0);
      ch = inp(nport);
      str[i] ='\0';
      i = 0; strp = 1;
      }
     }
    } while(ch != DC4);
    }
   if(n == 1){
   for(j = 0; j < 10; j++){
  do{
   if(kbhit()) s=getch();
 if(s==27) break;
} while((inp(gdan) & 0x1) == 0);
    ch = 0x7F & inp(nport);
    }
    if(strp == 1)
    {
   strp = 0;
   outp(nport,DC3);
   do {}while ((inp(gdan) & 0x20) == 0);
   wprintf(scrdir,"%s\n",str);
   outp(nport,DC1);
   do {}while ((inp(gdan) & 0x20) == 0);
    }
   }
  } while(n != 2);
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
 if(s==27) break;
 }while(ch == 'F');
  if(nw==1)
  {
   text_message("äéåÄçÑÄ ÇõèéãçÖçÄ");
   delay(1000);
   clear_textmes();
   }
}

void INPUT(char *name, char *nameu, int nw)
{
char com[30] = "COP,";
char ustr[7] =",/TY1  ";
char s=0,ch;
char str[128];
int i,j,r,n,strp;
FILE *outfile;
strcat(com,name);
strcat(com,"/");
strcat(com,nameu);
strcat(com,ustr);
for(j=0;j<=29;j++)
{
if(com[j]==' ')
{
com[j]='\0';
break;
}
}
/*                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"%s ",com);*/
i = strlen(com);
if((outfile = fopen(name,"w")) == 0)
 {
 wcursor(proc,0,0);
 wprintf(proc,"   î†©´ ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
j = 0;
display_window(scrlist);
clear_window(scrlist);
wcursor(scrlist,0,0);
while(j < i) {
 outp(nport,com[j++]);
 do{}while((inp(gdan) & 0x20) == 0);
 }
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 n = 0;i = 0;strp = 0;
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch = 0x7F & inp(nport);
  if(s==27) break;
  } while(ch != ACK);
 do
 {
 if(s==27) break;
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch = 0x7F & inp(nport);
  if(s==27) break;
  if(ch == DC2)
  {
   do
    {
 if(s==27) break;
  do{} while((inp(gdan) & 1) == 0);
    ch = 0x7F & inp(nport);
    if(ch == '%')
    n++;
    if(n == 1 && ch != 0)
    {
     if((ch != CR) && (ch != '%') && (ch != DC4) && (ch != DC2))
      {
      str[i] = ch;
      i++;
      }
      if(ch == CR)
      {
  do{} while((inp(gdan) & 1) == 0);
      ch = 0x7F & inp(nport);
      str[i] ='\0';
      i = 0; strp = 1;
      }
     }
    } while(ch != DC4);
    }
   if(n == 1){
   for(j = 0; j < 10; j++){
  do{} while((inp(gdan) & 1) == 0);
    ch = 0x7F & inp(nport);
    }
    if(strp == 1)
    {
   outp(nport,DC3);
   do {}while ((inp(gdan) & 0x20) == 0);
   wprintf(scrlist,"%s\n",str);
   fprintf(outfile,"%s\n",str);
   strp = 0;
   outp(nport,DC1);
   do {}while ((inp(gdan) & 0x20) == 0);
    }
   }
  } while(n != 2);
if(nw==1)
{
   text_message("äéåÄçÑÄ ÇõèéãçÖçÄ");
   delay(1000);
   clear_textmes();
   }
   fclose(outfile);
   hide_window(scrlist);
}


void OUTPUT(char *name, char *nameu, char *fname, int nw)
{
char com[30] = "COP,/TY1,";
char ch, y[2] = "  ";
char str[12]="            ";
char strf[128];
int i,j,n,l,konec,kc;
char s=0;
FILE *infile;
strcat(com,fname);
strcat(com,"/");
strcat(com,nameu);
for(j=0;j<=29;j++)
{
if(com[j]==' ')
{
com[j]='\0';
break;
}
}
if((infile = fopen(name,"r")) == 0)
 {
wcursor(proc,0,0);
 wprintf(proc,"   î†©´ 3 ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
/*                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"%s ",com);*/
i = strlen(com);
n = 0;j = 0;
display_window(scrlist);
clear_window(scrlist);
wcursor(scrlist,0,0);
while(j < i) {
 outp(nport,com[j++]);
 /*delay(200);*/
 do{}while((inp(gdan) & 0x20) == 0);
 }
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 n = 0;i = 0;konec = 0;kc=0;
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 0x1) == 0);
  ch =0x7F & inp(nport);
  if(s==27) break;
  } while(ch != ACK);
  if(s!=27)
  {
  do{} while((inp(gdan) & 0x1) == 0);
  ch =0x7F & inp(nport);
  do{} while((inp(gdan) & 0x1) == 0);
  ch =0x7F & inp(nport);
  do{} while((inp(gdan) & 0x1) == 0);
  ch =0x7F & inp(nport);
  do{} while((inp(gdan) & 0x1) == 0);
  ch =0x7F & inp(nport);
  }
  do
  {
 if(s==27) break;
  if(kc==0)
  {
  do{} while((inp(gdan) & 0x1) == 0);
  ch =0x7F & inp(nport);
   }
   if(ch == DC1) {
   kc=0;
    if(n == 0){
     outp(nport,'%');
     do{} while((inp(gdan) & 0x20) == 0);
     n = 1;
     }
     else
     {
    do {
    if((fscanf(infile,"%c",&ch)) != EOF)
    {
     outp(nport,ch);
     do{} while((inp(gdan) & 0x20) == 0);
    if((scrlist ->_cr +1 ) < (scrlist ->_ww - 2))
    {
    wputchar(scrlist,ch);
     delay(30);
    }
    else
    {
    wputchar(scrlist,ch);
    delay(30);
    if((ch != CR) && (ch != LF))
    wputchar(scrlist,'\n');
    }
    }
    else {
    ch = LF;
    konec = 1;
    }
    } while(ch != LF);
    }
    }
    else
    {
    if(ch != DC3)
    {
  for(i=0; i<6; i++)
  {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
/*wprintf(scrlist,"%c",ch);*/
  }
/*wprintf(scrlist,"\n");*/
  j=0;
  for(i=0; i<=9; i++)
  {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  if(i > 4)
  {
  str[j]=ch;
  j=j+1;
  }
  }
/*wprintf(scrlist,"%s\n",str);*/
  if(strncmp(str,"2  04",5) == 0)
  {
if(nw == 1)
{
  clear_window(proc);
  wcursor(proc,1,0);
  wprintf(proc,"îÄâã ëìôÖëíÇìÖí, èÖêÖáÄèàëÄíú (Ñ/Y): ");
  wgetstr(proc,y,1,38,1);
 }
 else
 {
 y[0] = 'Y';
 delay(1000);
 }
 outp(nport,y[0]);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 }
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
 if(s==27) break;
 }while(ch != DC1);
 if(s==27) break;
 kc=1;
    }
    }
   }while(konec !=1);
   delay(3000);
    if(s!=27)
    {
    outp(nport,'%');
    do{}while((inp(gdan) & 0x20) == 0);
    do{}while((inp(gdan) & 1) == 0);
    ch =0x7F & inp(nport);
    }
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
 if(s==27) break;
 }while(ch == 'F');
if(nw==1)
   {
   text_message("äéåÄçÑÄ ÇõèéãçÖçÄ");
   delay(1000);
   clear_textmes();
   }
    fclose(infile);
    hide_window(scrlist);
}

void DELET(char *name, char *nameu, int nw)
{
char com[16] = "DEL,";
char s=0,ch,y[2]="  ";
char str[12];
int i,j,n;
strcat(com,name);
strcat(com,"/");
strcat(com,nameu);
for(j=0;j<=15;j++)
{
if(com[j]==' ')
{
com[j]='\0';
break;
}
}
/*                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"%s ",com);*/
i = strlen(com);
j = 0;
 wcursor(scrlist,0,0);
while(j < i) {
 outp(nport,com[j++]);
 do{}while((inp(gdan) & 0x20) == 0);
 }
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 n = 1;i = 0;
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch = 0x7F & inp(nport);
  if(s==27) break;
/*  wputchar(scrlist,ch);*/
  } while(ch != ACK);
 do
 {
  if(s==27) break;
  do{} while((inp(gdan) & 1) == 0);
  ch =0X7F & inp(nport);
      if(ch == LF)
      {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  j=0;
  for(i=0; i<=10; i++)
  {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  if(i>=6)
  {
  str[j]=ch;
  j=j+1;
  }
  }
/*wprintf(scrlist,"%s \n",str);*/
  if(strncmp(str,"2  02",5) == 0)
  {
if(nw == 1)
{
  clear_window(proc);
  wcursor(proc,1,0);
  wprintf(proc,"ìÑÄãàíú îÄâã (Y/N): ");
  wgetstr(proc,y,1,21,1);
  }
  else
  y[0]='Y';
  delay(1000);
 outp(nport,y[0]);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 }
      n = 0;
      }
 }while(n != 0);
if(nw==1)
{
   text_message("äéåÄçÑÄ ÇõèéãçÖçÄ");
   delay(1000);
   clear_textmes();
   }
}

void REMOV(char *name, char *nameu, char *nname, int nw)
{
char com[25] = "REN,";
char s=0,ch, str[8] = "        ";
int i,j,n;
strcat(com,name);
strcat(com,"/");
strcat(com,nameu);
strcat(com,",");
strcat(com,nname);
for(j=0;j<=24;j++)
{
if(com[j]==' ')
{
com[j]='\0';
break;
}
}
/*                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"%s ",com);*/
i = strlen(com);
j = 0;
 wcursor(scrlist,0,0);
while(j < i) {
 outp(nport,com[j++]);
 do{}while((inp(gdan) & 0x20) == 0);
 }
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 n = 1;i = 0;
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch = 0x7F & inp(nport);
  if(s==27) break;
  } while(ch != ACK);
 do
 {
  if(s==27) break;
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
      if(ch == LF)
      {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  j=0;
  for(i=0; i<=10; i++)
  {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  if(i>=6)
  {
  str[j]=ch;
  j=j+1;
  }
  }
/*wprintf(scrlist,"%s \n",str);*/
      n = 0;
      }
 }while(n != 0);
if(nw==1)
{
   text_message("äéåÄçÑÄ ÇõèéãçÖçÄ");
   delay(1000);
   clear_textmes();
   }
}

void CREAT(char *name, char *nameu, char *rstr, char *rfile, int nw)
{
char com[25] = "CRE,";
char s=0,ch, str[8] = "        ";
int i,j,n;
strcat(com,name);
strcat(com,"/");
strcat(com,nameu);
strcat(com,",");
strcat(com,rstr);
strcat(com,",");
strcat(com,rfile);
for(j=0;j<=24;j++)
{
if(com[j]==' ')
{
com[j]='\0';
break;
}
}
/*                       clear_window(proc);
                       wcursor(proc,1,0);
                       wprintf(proc,"%s ",com);*/
i = strlen(com);
j = 0;
 wcursor(scrlist,0,0);
while(j < i) {
 outp(nport,com[j++]);
 do{}while((inp(gdan) & 0x20) == 0);
 }
 outp(nport,CR);
 do{}while((inp(gdan) & 0x20) == 0);
 outp(nport,LF);
 do{}while((inp(gdan) & 0x20) == 0);
 n = 1;i = 0;
 do
 {
  do{
  if(kbhit()) s=getch();
  if(s==27) break;
} while((inp(gdan) & 1) == 0);
  ch = 0x7F & inp(nport);
  if(s==27) break;
  } while(ch != ACK);
 do
 {
  if(s==27) break;
  do{} while((inp(gdan) & 1) == 0);
  ch =0X7F & inp(nport);
      if(ch == LF)
      {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  j=0;
  for(i=0; i<=10; i++)
  {
  do{} while((inp(gdan) & 1) == 0);
  ch =0x7F & inp(nport);
  if(i>=6)
  {
  str[j]=ch;
  j=j+1;
  }
  }
/*wprintf(scrlist,"%s \n",str);*/
      n = 0;
      }
 }while(n != 0);
if(nw==1)
{
   text_message("äéåÄçÑÄ ÇõèéãçÖçÄ");
   delay(1000);
   clear_textmes();
   }
}


void Podup()
{
FILE *infile, *outfile, *noutfile;
char str[128];
char tstr[128], pstr[128];
char name[14]="              ", outname[5]="F";
char kordw[9]="         ";
char sh[3];
char xkoord[10], ykoord[10], zkoord[10],akoord[10],bkoord[10],gfun[4],nkadr[5],ffunk[5];
double fxkoord,fykoord,fzkoord,fakoord,fbkoord;
double tfxkoord,tfykoord,tfzkoord,tfakoord,tfbkoord;
double dxkoord,dykoord,dzkoord,dkordw;
int j,l,i,n,g01,iffunk;
long chz;
  wcursor(proc,1,0);
  wprintf(proc,"à¨Ô ‰†©´†: ");
  wgetstr(proc,name,12,12,1);
  for(i = 0; i < 13; i++) {
  if(name[i] == ' ') {
  name[i] = '\0';
  break;
  }
  }
  wcursor(proc,1,0);
  wprintf(proc,"Ç¢•§®‚• ß≠†Á•≠®• ™ÆÆ‡§®≠†‚Î W: ");
  wgetstr(proc,kordw,8,33,1);
  for(i = 0; i < 8; i++) {
  if(name[i] == ' ') {
  name[i] = '\0';
  break;
  }
  }
  dkordw=atof(kordw);
if((infile = fopen(name,"r+")) == 0)
 {
 wcursor(proc,1,0);
 wprintf(proc,"   î†©´ ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
 n=1;chz=0;
itoa(n,sh,10);
strcat(outname,sh);
  for(i = 0; i < 4; i++) {
  if(outname[i] == ' ') {
  name[i] = '\0';
  break;
  }
  }
if((outfile = fopen(outname,"w+")) == 0)
 {
 wcursor(proc,0,0);
 wprintf(proc,"   î†©´2 ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
if((noutfile = fopen("nacht","w+")) == 0)
 {
 wcursor(proc,0,0);
 wprintf(proc,"   î†©´ nacht ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
display_window(scrlist);
clear_window(scrlist);
wcursor(scrlist,0,0);
do
{
 for(i=0; i<128; i++)
 {
 str[i]=' ';
 }
fscanf(infile,"%s",str);
strcpy(tstr,str);
l=strlen(str);
tstr[l] = '\0';
 for(i=0; i<10; i++)
 {
 xkoord[i]=' ';
 ykoord[i]=' ';
 zkoord[i]=' ';
 akoord[i]=' ';
 bkoord[i]=' ';
 }
/*tfxkoord=0;tfykoord=0;tfzkoord=0;*/
i=0;j=0;
do
{
if(tstr[i] == 'G')
{
j=0;
do
{
gfun[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
gfun[j]='\0';
if((strcmp(gfun,"G1") == 0) || (strcmp(gfun,"G09") ==0) || (strcmp(gfun,"G9") ==0))
g01=1;
else
g01=0;
}
if(tstr[i] == 'X')
{
i=i+1;j=0;
do
{
xkoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
xkoord[j] = '\0';
tfxkoord=atof(xkoord);
}
if(tstr[i] == 'Y')
{
i=i+1;j=0;
do
{
ykoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
ykoord[j] = '\0';
tfykoord=atof(ykoord);
}
if(tstr[i] == 'Z')
{
i=i+1;j=0;
do
{
zkoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
zkoord[j] = '\0';
tfzkoord=atof(zkoord);
}
if(tstr[i] == 'A')
{
i=i+1;j=0;
do
{
akoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
akoord[j] = '\0';
tfakoord=atof(akoord);
}
if(tstr[i] == 'B')
{
i=i+1;j=0;
do
{
bkoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
bkoord[j] = '\0';
tfbkoord=atof(bkoord);
}
if(tstr[i] == 'F')
{
 for(j=0; j<5; j++)
 {
 ffunk[j]=' ';
 }
i=i+1;j=0;
do
{
ffunk[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
}
i=i+1;
/*wprintf(scrlist,"%d %d \n",i,l);*/
}while(i < l);
/*wprintf(scrlist,"X=%f Y=%f Z=%f \n",tfxkoord,tfykoord,tfzkoord);*/
chz=chz+l;
/*wprintf(scrlist,"%u \n",razch);*/
if(chz > razch)
{
l=strlen(str);
i=0;j=0;
 fxkoord=tfxkoord;fykoord=tfykoord;fzkoord=tfzkoord;
 fakoord=tfakoord;fbkoord=tfbkoord;
tfxkoord=0;tfykoord=0;tfzkoord=0;tfakoord=0;tfbkoord=0,iffunk=0;
do
{
if(tstr[i] == 'N')
{
i=i+1;j=0;
do
{
nkadr[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
nkadr[j] = '\0';
}
if(tstr[i] == 'G')
{
j=0;
do
{
gfun[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
gfun[j]='\0';
if((strcmp(gfun,"G1") == 0) || (strcmp(gfun,"G09") ==0) || (strcmp(gfun,"G9") ==0))
g01=1;
else
g01=0;
}
if(tstr[i] == 'X')
{
i=i+1;j=0;
do
{
xkoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
tfxkoord=atof(xkoord);
}
if(tstr[i] == 'Y')
{
i=i+1;j=0;
do
{
ykoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
tfykoord=atof(ykoord);
}
if(tstr[i] == 'Z')
{
i=i+1;j=0;
do
{
zkoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
tfzkoord=atof(zkoord);
}
if(tstr[i] == 'A')
{
i=i+1;j=0;
do
{
akoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
tfakoord=atof(akoord);
}
if(tstr[i] == 'B')
{
i=i+1;j=0;
do
{
bkoord[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
tfbkoord=atof(bkoord);
}
if(tstr[i] == 'F')
{
 for(j=0; j<5; j++)
 {
 ffunk[j]=' ';
 }
i=i+1;j=0;
do
{
ffunk[j]=tstr[i];
j=j+1;i=i+1;
if(tstr[i] == 13) break;
}while(tstr[i] < 0x3A);
iffunk=atoi(ffunk);
}
i=i+1;
/*wprintf(scrlist,"%d \n",i);*/
}while(i < l);
if(g01 ==1)
{
fprintf(outfile,"N%s",nkadr);
fprintf(outfile,"G9");
if(tfxkoord != 0)
{
fprintf(outfile,"X%.4f",tfxkoord);
}
if(tfykoord != 0)
{
fprintf(outfile,"Y%.4f",tfykoord);
}
if(tfzkoord != 0)
{
fprintf(outfile,"Z%.4f",tfzkoord);
}
if(tfakoord != 0)
{
fprintf(outfile,"A%.4f",tfakoord);
}
if(tfbkoord != 0)
{
fprintf(outfile,"B%.4f",tfbkoord);
}
if(iffunk != 0)
{
fprintf(outfile,"F%i",iffunk);
}
fprintf(outfile,"\n");
fprintf(outfile,"N1");
fprintf(outfile,"W%.3f\n",dkordw+1.0);
wprintf(scrlist,"TX=%f TY=%f TZ=%f \n",tfxkoord,tfykoord,tfzkoord);
 tfxkoord=fxkoord;tfykoord=fykoord;tfzkoord=fzkoord;
 tfakoord=fakoord;tfbkoord=fbkoord;
}
n=n+1;
chz=0;
fclose(outfile);
outname[1]='\0';
itoa(n,sh,10);
strcat(outname,sh);
if((outfile = fopen(outname,"w+")) == 0)
 {
 wcursor(proc,0,0);
 wprintf(proc,"   î†©´2 ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
if(g01 ==1)
{
fprintf(outfile,"N1");
fprintf(outfile,"W%.3f",dkordw);
fprintf(outfile,"\n");
wprintf(scrlist,"X=%f Y=%f Z=%f \n",fxkoord,fykoord,fzkoord);
}
fprintf(noutfile,"N%iX%.4fY%.4fZ%.4fA%.4fB%.4fF%s\n",n,fxkoord,fykoord,fzkoord,fakoord,fbkoord,ffunk);
 }
 if(!feof(infile))
 {
 strcpy(pstr,str);
 fprintf(outfile,"%s\n",str);
 }
}while (!feof(infile) );
fclose(outfile);
fclose(noutfile);
fclose(infile);
if((outfile = fopen("cikl","w+")) == 0)
 {
 wcursor(proc,0,0);
 wprintf(proc,"   î†©´ cikl ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
fprintf(outfile,"%d\n",n);
fclose(outfile);
if((outfile = fopen("ciklf","w+")) == 0)
 {
 wcursor(proc,0,0);
 wprintf(proc,"   î†©´ ciklf ≠• Æ‚™‡Î‚");
 reverse_video(proc);
 wprintf(proc,"ç†¶¨®‚• ESC");
 getch();
 normal_video(proc);
 clear_window(proc);
 return;
 }
fprintf(outfile,"1\n");
fclose(outfile);
    hide_window(scrlist);
}

void Podkach()
{
FILE *outfile, *infile;
char name[3]="F";
char s, ch, sh[5]="     ";
int n,ckf,nn,i;
DIR("MP0",0);
delay(5000);
OUTPUT("CIKL","MP0","CIKL",0);
delay(5000);
DIR("MP0",0);
delay(5000);
OUTPUT("F1","MP2","F",0);
delay(5000);
DIR("MP2",0);
if((infile=fopen("CIKL","r")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
fscanf(infile,"%s",sh);
fclose(infile);
ckf=atoi(sh);
for(i=0; i<4; i++)
{
sh[i]=' ';
}
if((outfile=fopen("CIKLF","w+")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ C ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
fprintf(outfile,"1\n",sh);
fclose(outfile);
delay(5000);
OUTPUT("CIKLF","MP0","CIKLF",0);
delay(5000);
DIR("MP0",0);
n=2;
wcursor(proc,1,0);
wprintf(proc,"èÆ§†©‚• ™Æ¨†≠§„ SPG,START/MP3 ® ™≠ÆØ™„ <èìëä>");
do
{
text_message("  é¶®§†≠®•  ");
do
{
do{
 if(kbhit()) s=getch();
 if(s==27) break;
}while((inp(gdan) & 0x1) == 0);
ch=0x7F & inp(nport);
 if(s==27) break;
}while(ch != '%');
 if(s==27) break;
delay(30000);
 nn=n;
 clear_textmes();
 text_message("   á†£‡„ß™†   ");
 name[1]='\0';
itoa(nn,sh,10);
strcat(name,sh);
clear_window(scrlist);
DIR("MP2",0);
delay(5000);
DELET("F","MP2",0);
delay(5000);
OUTPUT(name,"MP2","F",0);
delay(5000);
DIR("MP2",0);
delay(5000);
if((outfile=fopen("CIKLF","w+")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ C ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
fprintf(outfile,"%s\n",sh);
fclose(outfile);
OUTPUT("CIKLF","MP0","CIKLF",0);
delay(5000);
DIR("MP0",0);
n=n+1;
clear_textmes();
}while(n < ckf+1);
clear_textmes();
}

void Podcon()
{
FILE *outfile, *infile;
char name[3]="F";
char s, ch, sh[5]="     ";
int n,ckf,nn,i,ckfp,ckft,nach;
if((infile=fopen("CIKL","r")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
fscanf(infile,"%s",sh);
ckfp=atoi(sh);
fclose(infile);
for(i=0; i<4; i++)
{
sh[i]=' ';
}
if((infile=fopen("CIKLF","r+")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ C ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
fscanf(infile,"%s",sh);
fclose(infile);
ckft=atoi(sh);
for(i=0; i<4; i++)
{
sh[i]=' ';
}
ckf=ckfp;
n=ckft+1;nach=0;
do
{
text_message("   é¶®§†≠®•   ");
if(nach==1)
{
do
{
do{
 if(kbhit()) s=getch();
 if(s==27) break;
}while((inp(gdan) & 0x1) == 0);
ch=0x7F & inp(nport);
 if(s==27) break;
}while(ch != '%');
delay(30000);
}
 if(s==27) break;
 nn=n;
 clear_textmes();
 text_message("   á†£‡„ß™†   ");
 name[1]='\0';
itoa(nn,sh,10);
strcat(name,sh);
clear_window(scrlist);
DIR("MP2",0);
delay(5000);
DELET("F","MP2",0);
delay(5000);
OUTPUT(name,"MP2","F",0);
delay(5000);
DIR("MP2",0);
delay(5000);
if((outfile=fopen("CIKLF","w+")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ C ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
fprintf(outfile,"%s\n",sh);
fclose(outfile);
OUTPUT("CIKLF","MP0","CIKLF",0);
delay(5000);
DIR("MP0",0);
n=n+1;nach=1;
clear_textmes();
}while(n < ckf+1);
clear_textmes();
}

Prodol()
{
FILE *outfile, *infile;
char nchast[3]="   ";
char s[3]="   ", tochka[5]="     ";
char str[128];
char xkoord[10],ykoord[10],zkoord[10],akoord[10],bkoord[10],kordw[10]="          ";
char ffunk[5],gfun[3],nkadr[4];
double tfxkoord,tfykoord,tfzkoord,tfakoord,tfbkoord,wkoord;
int l,i,j,n,g01;
clear_window(proc);
  wcursor(proc,1,0);
  wprintf(proc,"Ç¢•§®‚• ≠Æ¨•‡ Á†·‚®: ");
  wgetstr(proc,nchast,2,21,1);
 for(i = 0; i < 2; i++) {
  if(nchast[i] == ' ') {
  nchast[i] = '\0';
  break;
  }
  }
  clear_window(proc);
  wcursor(proc,1,0);
  wprintf(proc,"ê†°Æ‚† Æ‚ 0 ·‚†≠™† Y/N: ");
  wgetstr(proc,s,2,24,1);
 for(i = 0; i < 2; i++) {
  if(s[i] == ' ') {
  s[i] = '\0';
  break;
  }
  }
  clear_window(proc);
  wcursor(proc,1,0);
  wprintf(proc,"Ç¢•§®‚• ØÆ§ÂÆ§ ØÆ ™ÆÆ‡§®≠†‚†¨ ¢ ‚ÆÁ™„: ");
  wgetstr(proc,tochka,4,39,1);
 for(i = 0; i < 4; i++) {
  if(tochka[i] == ' ') {
  tochka[i] = '\0';
  break;
  }
  }
  clear_window(proc);
  wcursor(proc,1,0);
  wprintf(proc,"Ç¢•§®‚• ß≠†Á•≠®• ™ÆÆ‡§®≠†‚Î W: ");
  wgetstr(proc,kordw,8,33,1);
 for(i = 0; i < 9; i++) {
  if(kordw[i] == ' ') {
  kordw[i] = '\0';
  break;
  }
  }
  clear_window(proc);
  wkoord=atof(kordw);
if((infile=fopen("f1","r")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ f1 ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
if((outfile=fopen("prodol","w")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ prodol ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
display_window(scrlist);
clear_window(scrlist);
wcursor(scrlist,0,0);
n=1;
fscanf(infile,"%s",str);
wprintf(scrlist,"%s\n",str);
fprintf(outfile,"%s\n",str);
/*if(strnicmp(str ,"(UOA,1)",4)!= 0)
{
 fscanf(infile,"%s",str);
 fprintf(outfile,"%s\n",str);
 }*/
 n=n+1;g01=0;
 if(s[0] == 'Y')
 {
 wprintf(scrlist,"N%iXY\n",n);
 fprintf(outfile,"N%iXY\n",n);
 }
 do
 {
 fscanf(infile,"%s",str);
 l=strlen(str);
 i=0;j=0;
 do
 {
if(str[i] == 'G')
{
j=0;
do
{
gfun[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
gfun[j]='\0';
if((strcmp(gfun,"G1") == 0) || (strcmp(gfun,"G01") ==0))
g01=1;
}
i=i+1;
}while(i < l);
if(g01 != 1)
{
wprintf(scrlist,"%s\n",str);
fprintf(outfile,"%s\n",str);
n=n+1;
}
}while(g01 != 1);
fclose(infile);
if((infile=fopen("nacht","r")) == 0)
{
wcursor(proc,0,0);
wprintf(proc,"î†©´ ≠• Æ‚™‡Î‚");
reverse_video(proc);
wprintf(proc,"ç†¶¨®‚• ESC");
getch();
normal_video(proc);
clear_window(proc);
return;
}
i=0;j=0;
do
{
i=0;j=0;
fscanf(infile,"%s",str);
if(str[i] == 'N')
{
i=i+1;j=0;
do
{
nkadr[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
nkadr[j] = '\0';
}
i=i+1;
}while(strcmp(nkadr,nchast) != 0);
l=strlen(str);
i=0;j=0;
do
{
if(str[i] == 'X')
{
i=i+1;j=0;
do
{
xkoord[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
tfxkoord=atof(xkoord);
}
if(str[i] == 'Y')
{
i=i+1;j=0;
do
{
ykoord[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
tfykoord=atof(ykoord);
}
if(str[i] == 'Z')
{
i=i+1;j=0;
do
{
zkoord[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
tfzkoord=atof(zkoord);
}
if(str[i] == 'A')
{
i=i+1;j=0;
do
{
akoord[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
tfakoord=atof(akoord);
}
if(str[i] == 'B')
{
i=i+1;j=0;
do
{
bkoord[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
tfbkoord=atof(bkoord);
}
if(str[i] == 'F')
{
i=i+1;j=0;
do
{
ffunk[j]=str[i];
j=j+1;i=i+1;
if(str[i] == 13) break;
}while(str[i] < 0x3A);
}
i=i+1;
/*wprintf(scrlist,"%d \n",i);*/
}while(i < l);
n=n+1;
fprintf(outfile,"N%iW%.4f\n",n,wkoord+1);
n=n+1;
if(strcmp(tochka,"XYZ") ==0)
fprintf(outfile,"N%iG28G1G9X%.4fY%.4fZ%.4fA%.4fB%.4fF%s\n",n,tfxkoord,tfykoord,tfzkoord,tfakoord,tfbkoord,ffunk);
if(strcmp(tochka,"XY") ==0)
{
fprintf(outfile,"N%iG28G1G9X%.4fY%.4fA%.4fB%.4fF%s\n",n,tfxkoord,tfykoord,tfakoord,tfbkoord,ffunk);
n=n+1;
fprintf(outfile,"N%iG9Z%.4f\n",n,tfzkoord);
}
if(strcmp(tochka,"XZ") ==0)
{
fprintf(outfile,"N%iG28G1G9X%.4fZ%.4fA%.4fB%.4fF%s\n",n,tfxkoord,tfzkoord,tfakoord,tfbkoord,ffunk);
n=n+1;
fprintf(outfile,"N%iG9Y%.4f\n",n,tfykoord);
}
if(strcmp(tochka,"YZ") ==0)
{
fprintf(outfile,"N%iG28G1G9Y%.4fZ%.4fA%.4fB%.4fF%s\n",n,tfykoord,tfzkoord,tfakoord,tfbkoord,ffunk);
n=n+1;
fprintf(outfile,"N%iG9X%.4f\n",n,tfxkoord);
}
fclose(infile);
fclose(outfile);
delay(20000);
hide_window(scrlist);

}