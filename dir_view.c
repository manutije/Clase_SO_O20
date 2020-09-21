#include <stdio.h>
#include <dirent.h>
#include <curses.h>

int leeChar() {
  int chars[5];
  int ch,i=0;
  nodelay(stdscr, TRUE);
  while((ch = getch()) == ERR); /* Espera activa */
  ungetch(ch);
  while((ch = getch()) != ERR) {
    chars[i++]=ch;
  }
  /* convierte a numero con todo lo leido */
  int res=0;
  for(int j=0;j<i;j++) {
    res <<=8;
    res |= chars[j];
  }
  return res;
}

int main()
{
    DIR *folder;
    struct dirent *entry;
    int files = 0;
    
    char *lista[] = {"Uno", "Dos", "Tres", "Cuatro" };
   int i = 0;
   int c;
   initscr();
   raw();
   noecho(); /* No muestres el caracter leido */
   cbreak(); /* Haz que los caracteres se le pasen al usuario */
   do {
      for (int j=0; j < 4; j++) {
         if (j == i) {
           attron(A_REVERSE);
         }
         mvprintw(5+j,5,lista[j]);
         attroff(A_REVERSE);
      }
      move(5+i,5);
      refresh();
      c = leeChar();
      switch(c) {
         case 0x1B5B41:
            i = (i>0) ? i - 1 : 3;
            break;
         case 0x1B5B42:
            i = (i<3) ? i + 1 : 0;
            break;
         default:
            // Nothing                                                                                                                                                                        
            break;
      }
      move(10,5);
      printw("Estoy en %d: Lei 0x%08x",i,c);
   } while (c != 0x1b);
   endwin();


    folder = opendir(".");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }

    while( (entry=readdir(folder)) )
    {
        files++;
        printf("File %3d: %s\n",
                files,
                entry->d_name
              );
    }

    closedir(folder);

    return(0);
}
