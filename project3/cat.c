/*
cat.exe
Ali Akdemir
Fatih Yılmaz
Sencer Karapıçak
This program has the same functionality with cat command which is a command in UNIX platforms
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void catRead(int argc, char *argv[]);
void catWrite(int argc, char *argv[], int index);
void catAppend(int argc, char *argv[], int index);
void catReadN(int argc, char *argv[]);
void catWriteN(int argc,char *argv[], int index);
void catAppendN(int argc,char *argv[], int index);
void catReadB(int argc, char *argv[]);
void catWriteB(int argc,char *argv[],int index);
void catAppendB(int argc,char *argv[],int index);
void catReadS(int argc,char **argv);
void catWriteS(int argc,char *argv[],int index);
void catAppendS(int argc,char *argv[],int index);
void catReadT(int argc,char **argv);
void explanation();
void longestpalindrome(char *argv[]);
int palindrome(char *s);
void catDelete(int argc, char *argv[], int index);

int main (int argc, char *argv[])
{
   int index = 1;/*index holds index of > or >> characters*/
   int greaterSign = 0;/*greaterSign is to check whether user typed a redirection char*/
   for (int i=1; i<argc; i++)
   {
      /*If user wants to write on file below code is executed*/
      if (!strcmp(argv[i], "-w"))
      {
         greaterSign = 1;
         index = i;
         break;
      }
      /*If user wants to append on file below code is executed*/
      else if (!strcmp(argv[i],"-a"))
      {
         greaterSign = 2;
         index = i;
         break;
      }
      /*If user wants to read file below code is executed.*/
      else
      {
         greaterSign = 0;
      }
   }
   /*If user types '-n' as second argument below code is executed*/
   if(!strcmp(argv[1],"-n"))
   {  /*If user wants to read file below block is executed*/
      if (greaterSign==0)
      {
         catReadN(argc,argv);
      }
      /*If user wants to write on file below block is executed*/
      else if (greaterSign==1)
      {
         catWriteN(argc,argv,index);
      }
      /*If user wants to append on file below block is executed*/
      else if (greaterSign==2)
      {
         catAppendN(argc,argv,index);
      }
      else
      {
         fprintf(stderr,"Syntax Error.");
      }
   }
   /*If user types '-b' as second argument below code is executed*/
   else if (!strcmp(argv[1],"-b"))
   {
      /*If user wants to read file below block is executed*/
      if (greaterSign==0)
      {
         catReadB(argc,argv);
      }
      /*If user wants to write on file below block is executed*/
      else if (greaterSign==1)
      {
         catWriteB(argc,argv,index);
      }
      /*If user wants to append on file below block is executed*/
      else if (greaterSign==2)
      {
         catAppendB(argc,argv,index);
      }
      else
      {
         fprintf(stderr,"Syntax Error.");
      }
   }
   /*If user types '-s' as second argument below code is executed*/
   else if (!strcmp(argv[1],"-s"))
   {
      /*If user wants to read file below block is executed*/
       if (greaterSign==0)
      {
         catReadS(argc,argv);
      }
      /*If user wants to write on file below block is executed*/
      else if (greaterSign==1)
      {
         catWriteS(argc,argv,index);
      }
      /*If user wants to append on file below block is executed*/
      else if (greaterSign==2)
      {
         catAppendS(argc,argv,index);
      }
      else
      {
         fprintf(stderr,"Syntax Error.");
      }
   }
   /*If user types '-t' as second argument below code is executed*/
   /*'-t' option doesn't printf any blank line*/
   else if (!strcmp(argv[1],"-t"))
   {
      catReadT(argc,argv);
   }
   /*If user types '-d' as second argument below code is executed*/
   /*'-d' option deletes contents of the files*/
   else if (!strcmp(argv[1],"-d"))
   {
      catDelete(argc,argv,index);
   }
   /*If user types '-h' as second argument below code is executed*/
   else if (!strcmp(argv[1],"-h"))
   {
      explanation();
   }
   /*If user types '-p' a second argument below code is executed*/
   else if(!strcmp(argv[1],"-p"))
   {
	   longestpalindrome(argv);
   }
   /*If user types '-q' as second argument below code is executed*/
   else if (!strcmp(argv[1],"-q"))
   {
      exit(1);
   }
   /*If user doesn't type any options char below code is executed*/
   else
   {
      /*If user wants to read file below block is executed*/
      if (greaterSign==0)
      {
         catRead(argc,argv);
      }
      /*If user wants to write on file below block is executed*/
      else if (greaterSign==1)
      {
         catWrite(argc,argv,index);
      }
      /*If user wants to append on file below block is executed*/
      else if (greaterSign==2)
      {
         catAppend(argc,argv,index);
      }
   }
   return 0;
}
void catRead(int argc, char *argv[])
{
   for (int i=1; i<argc; i++)/*From second argument to last argument create a loop*/
      {
         FILE *f;
         f = fopen(argv[i], "r");/*open file*/
         while(1)
         {
            char c = fgetc(f);/*Get every character until the end of the file*/
            if (feof(f))
            {
               break;
            }
           putchar(c);/*Put characters to the screen*/
         }
         fclose(f);
      }
}

void catWrite(int argc, char *argv[], int index)
{
    if (argc==3 && !strcmp(argv[1],"-w"))
    {/*If user types > character after cat.exe and adds one file name get characters from screen*/
      FILE *f = fopen(argv[2], "w");
      char c = fgetc(stdin);/*get character from stdin until user EOF*/
      while(c!=EOF)
      {
         fputc(c,f);/*puts typed char to file*/
         c = fgetc(stdin);
      }
      fclose(f);
    }
    /*If user types more than 3 chars executes below block*/
    else if (argc>3 && !strcmp(argv[index],"-w"))
    {
      for (int i=(index+1); i<argc; i++)/*Truncates files to zero which are typed before > argument*/
      {
         FILE *delete = fopen(argv[i], "w");
         fputs("\0", delete);
         fclose(delete);
      }
      for (int i=1; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*Appends contents of the files which are typed > char to files which typed after > char*/
            FILE *f2 = fopen(argv[i],"a+");
            char c = fgetc(f);
            while (c != EOF)
            {
               fputc(c,f2);
               c = fgetc(f);
            }
            fclose(f2);
         }
         fclose(f);
      }
    }
    else
    {
        fprintf(stderr,"Syntax error.");/*Otherwise prints error message*/
    }
}

void catAppend(int argc, char *argv[], int index)
{
   /*If user types > character after cat.exe and adds one file name get characters from screen*/
      if (argc==3 && !strcmp(argv[1],"-a"))
      {
         FILE *f = fopen(argv[2], "a");
         char c = fgetc(stdin);
         while(c!=EOF)
         {
            fputc(c,f);
            c = fgetc(stdin);
         }
         fclose(f);
      }
      else if (argc>3 && !strcmp(argv[index],"-a"))/*If user types more than 3 argument executes below block*/
      {
         for (int i=1; i<index; i++)/*Reads file which are typed before > char*/
         {
            FILE *f = fopen(argv[i],"r");
            for (int i=index+1;i<argc;i++)
            {
               /*Appends contents of the files which are typed > char to files which typed after > char*/
               FILE *f2 = fopen(argv[i],"a+");
               char c = fgetc(f);
               while (c != EOF)
               {
                  fputc(c,f2);
                  c = fgetc(f);
               }
               fclose(f2);
            }
            fclose(f);
         }
      }
      else
      {
         fprintf(stderr,"Syntax error.");/*Otherwise prints error message*/
      }
}

void catReadN(int argc, char *argv[])
{
   int line_number=1;
   for (int i=2; i<argc; i++)/*From second argument to last argument create a loop*/
   {
      FILE *f = fopen(argv[i], "r");/*open file*/;
      char c;
      printf("%5d  ",line_number);
      while((c = fgetc(f))!=EOF)
      {
         putchar(c);/*Put characters to the screen*/
         if (c == '\n')
         {
            printf("%5d  ",++line_number );
         }
      }
      printf("\n");
      line_number++;
      fclose(f);
   }
}

void catWriteN(int argc,char *argv[], int index)
{
   if (argc==4 && !strcmp(argv[2],"-w"))
   {
      FILE *f = fopen(argv[3],"w");
      int line_number=1;
      char c = fgetc(stdin);
      fprintf(f,"%5d ",line_number);
      while(c!=EOF)
      {
         fputc(c,f);
         if (c == '\n')
         {
            fprintf(f, "%5d ",++line_number );
         }

         c = fgetc(stdin);
      }
      line_number++;
      printf("\n");
      fclose(f);
   }
   else if (argc>4 && !strcmp(argv[index],"-w"))
   {
      /*TRUNCATES FILES TO ZERO WHICH ARE TYPED BEFORE > ARGUMENT*/
      for (int i=(index+1); i<argc; i++)
      {
         FILE *delete = fopen(argv[i], "w");
         fputs("\0", delete);
         fclose(delete);
      }

      /*READ EVERY FILE WHICH ARE WRITTEN AFTER > SIGN*/
      int line_number=1;
      for (int i=2; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*OPENING FILES TO APPEND*/
            FILE *f2 = fopen(argv[i],"a+");
            /*GETING CHAR BY CHAR FROM READING FILES*/
            char c;
            fprintf(f2,"%5d ",line_number);
            while ((c=fgetc(f)) != EOF)
            {
               fputc(c,f2);
               if (c == '\n')
               {
                  fprintf(f2, "%5d ",++line_number );
               }
            }
            fclose(f2);
         }

         line_number++;
         printf("\n");
         fclose(f);
      }
   }
   else
   {
      fprintf(stderr, "%s\n", "Syntax Error.");
   }
}


void catAppendN(int argc,char *argv[], int index)
{
   if (argc==4 && !strcmp(argv[2],"-a"))
   {
      FILE *f = fopen(argv[3],"a");
      int line_number=1;
      char c = fgetc(stdin);
      fprintf(f,"%5d ",line_number);
      while(c!=EOF)
      {
         fputc(c,f);
         if (c == '\n')
         {
            fprintf(f, "%5d ",++line_number );
         }
         c = fgetc(stdin);
      }
      fclose(f);
   }
   else if (argc>4 && !strcmp(argv[index],"-a"))
   {
      /*READ EVERY FILE WHICH ARE WRITTEN AFTER > SIGN*/
      int line_number=1;
      for (int i=2; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*OPENING FILES TO APPEND*/
            FILE *f2 = fopen(argv[i],"a+");
            /*GETING CHAR BY CHAR FROM READING FILES*/
            char c;
            fprintf(f2,"%5d ",line_number);
            while ((c=fgetc(f)) != EOF)
            {
               fputc(c,f2);
               if (c == '\n')
               {
                  fprintf(f2, "%5d ",++line_number );
               }
            }
            fclose(f2);
         }
         line_number++;
         printf("\n");
         fclose(f);
      }
   }
   else
   {
      fprintf(stderr, "%s\n", "Syntax Error.");
   }
}

void catReadB(int argc, char *argv[])
{
   int line_number=1;
   for (int i=2; i<argc; i++)/*From second argument to last argument create a loop*/
   {
      FILE *f = fopen(argv[i], "r");/*open file*/;
      char s[1000];
      int k=0,l=0;
      while((s[l]=fgetc(f))!= EOF)
      {
         l++;
      }
      printf("%d  ",line_number);
      while(k<l)
      {
         fprintf(stdout, "%c",s[k]);

         if(s[k] == '\n' && s[k+1] != '\n')
         {
            fprintf(stdout,"%d: ",++line_number);
         }
         k++;
      }
      printf("\n");
      line_number++;
      fclose(f);
   }
}

void catWriteB(int argc,char *argv[],int index)
{

   if (argc==4 && !strcmp(argv[2],"-w"))
   {
      FILE *f = fopen(argv[3],"w");
      char s[1000];
      int line_number=1;
      int k=0,l=0;
      while((s[l]=fgetc(stdin))!= EOF)
      {
         l++;
      }
      fprintf(f,"%5d ",line_number);
      while(k<l)
      {
         fprintf(f, "%c",s[k]);

         if(s[k] == '\n' && s[k+1] != '\n')
         {
            fprintf(f,"%5d: ",++line_number);
         }
         k++;
      }
      printf("\n");
      line_number++;
      fclose(f);
   }
   else if (argc>4 && !strcmp(argv[index],"-w"))
   {
      /*TRUNCATES FILES TO ZERO WHICH ARE TYPED BEFORE > ARGUMENT*/
      for (int i=(index+1); i<argc; i++)
      {
         FILE *delete = fopen(argv[i], "w");
         fputs("\0", delete);
         fclose(delete);
      }

      /*READ EVERY FILE WHICH ARE WRITTEN AFTER > SIGN*/
      int line_number=1;
      for (int i=2; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*OPENING FILES TO APPEND*/
            FILE *f2 = fopen(argv[i],"a+");
            /*GETING CHAR BY CHAR FROM READING FILES*/
            char s[1000];
            int i=0,j=0;
            while((s[j]=fgetc(f))!= EOF)
            {
               j++;
            }
            fprintf(f2,"%d: ",line_number);
            while(i<j)
            {
               fprintf(f2, "%c",s[i]);

               if(s[i] == '\n' && s[i+1] != '\n')
               {
                 fprintf(f2,"%d: ",++line_number);
               }
               i++;
            }
            fclose(f2);
         }

         line_number++;
         printf("\n");
         fclose(f);
      }
   }
   else
   {
      fprintf(stderr, "%s\n", "Syntax Error.");
   }
}

void catAppendB(int argc,char *argv[],int index)
{
   if (argc==4 && !strcmp(argv[2],"-a"))
   {
      FILE *f = fopen(argv[3],"a");
      char s[1000];
      int line_number=1;
      int k=0,l=0;
      while((s[l]=fgetc(stdin))!= EOF)
      {
         l++;
      }
      fprintf(f,"\n%d ",line_number);
      while(k<l)
      {
         fprintf(f, "%c",s[k]);

         if(s[k] == '\n' && s[k+1] != '\n')
         {
            fprintf(f,"%d: ",++line_number);
         }
         k++;
      }
      printf("\n");
      line_number++;
      fclose(f);
   }
   else if (argc>4 && !strcmp(argv[index],"-a"))
   {
      /*READ EVERY FILE WHICH ARE WRITTEN AFTER > SIGN*/
      int line_number=1;
      for (int i=2; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*OPENING FILES TO APPEND*/
            FILE *f2 = fopen(argv[i],"a+");
            /*GETING CHAR BY CHAR FROM READING FILES*/
            char s[1000];
            int i=0,j=0;
            while((s[j]=fgetc(f))!= EOF)
            {
               j++;
            }
            fprintf(f2,"%d: ",line_number);
            while(i<j)
            {
               fprintf(f2, "%c",s[i]);

               if(s[i] == '\n' && s[i+1] != '\n')
               {
                 fprintf(f2,"%d: ",++line_number);
               }
               i++;
            }
            fclose(f2);
         }

         line_number++;
         printf("\n");
         fclose(f);
      }
   }
   else
   {
      fprintf(stderr, "%s\n", "Syntax Error.");
   }
}
void catReadS(int argc,char **argv)
{

   for (int i=2; i<argc; i++)/*From second argument to last argument create a loop*/
   {
      FILE *f = fopen(argv[i], "r");/*open file*/;
      char s[1000];
      int i=0,j=0;

      while((s[j]=fgetc(f))!= EOF)
      {
         j++;
      }

      while(i<j)
      {
         if(s[i] == '\n' && s[i+1]=='\n' && s[i+2]=='\n')
         goto label;

         printf("%c",s[i]);

         label:i++;
      }
      printf("\n");

      fclose(f);
   }
}

void catWriteS(int argc,char *argv[],int index)
{

   if (argc==4 && !strcmp(argv[2],"-w"))
   {
      FILE *f = fopen(argv[3],"w");
      char s[1000];
      int i=0,j=0;

      while((s[j]=fgetc(stdin))!= EOF)
      {
         j++;
      }


      while(i<j)
      {
         if(s[i] == '\n' && s[i+1]=='\n' && s[i+2]=='\n')
         {
           goto label;
         }
           fprintf(f, "%c",s[i]);

          label:i++;
      }
      printf("\n");

      fclose(f);
   }
   else if (argc>4 && !strcmp(argv[index],"-w"))
   {
      /*TRUNCATES FILES TO ZERO WHICH ARE TYPED BEFORE > ARGUMENT*/
      for (int i=(index+1); i<argc; i++)
      {
         FILE *delete = fopen(argv[i], "w");
         fputs("\0", delete);
         fclose(delete);
      }

      /*READ EVERY FILE WHICH ARE WRITTEN AFTER > SIGN*/

      for (int i=2; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*OPENING FILES TO APPEND*/
            FILE *f2 = fopen(argv[i],"a+");
            /*GETING CHAR BY CHAR FROM READING FILES*/
            char s[1000];
            int i=0,j=0;

            while((s[j]=fgetc(f))!= EOF)
            {
               j++;
            }

            while(i<j)
            {
               if(s[i] == '\n' && s[i+1]=='\n' && s[i+2]=='\n')
               goto label2;

               fprintf(f2, "%c",s[i]);


               label2:i++;
            }
            fclose(f2);
         }


         printf("\n");
         fclose(f);
      }
   }
   else
   {
      fprintf(stderr, "%s\n", "Syntax Error.");
   }
}

void catAppendS(int argc,char *argv[],int index)
{

   if (argc==4 && !strcmp(argv[2],"-a"))
   {
      FILE *f = fopen(argv[3],"a");

      char s[1000];
      int i=0,j=0;

      while((s[j]=fgetc(stdin))!= EOF)
      {
         j++;
      }

      while(i<j)
      {
         if(s[i] == '\n' && s[i+1]=='\n' && s[i+2]=='\n')
         goto label;

         fprintf(f, "%c",s[i]);

         label:i++;
      }
      printf("\n");
      fclose(f);
   }
   else if (argc>4 && !strcmp(argv[index],"-a"))
   {
      /*READ EVERY FILE WHICH ARE WRITTEN AFTER > SIGN*/

      for (int i=2; i<index; i++)
      {
         FILE *f = fopen(argv[i],"r");/*Reads file which are typed before > char*/
         for (int i=index+1;i<argc;i++)
         {
            /*OPENING FILES TO APPEND*/
            FILE *f2 = fopen(argv[i],"a+");
            /*GETING CHAR BY CHAR FROM READING FILES*/
            char s[1000];
            int i=0,j=0;

            while((s[j]=fgetc(f))!= EOF)
            {
               j++;
            }

            while(i<j)
            {
               if(s[i] == '\n' && s[i+1]=='\n' && s[i+2]=='\n')
               goto label2;

               fprintf(f2, "%c",s[i]);


               label2:i++;
            }
            fclose(f2);
         }
         printf("\n");
         fclose(f);
      }
   }
   else
   {
      fprintf(stderr, "%s\n", "Syntax Error.");
   }
}

void catReadT(int argc,char **argv)
{
   for (int i=2; i<argc; i++)/*From second argument to last argument create a loop*/
   {
      FILE *f = fopen(argv[i], "r");/*open file*/;
      char s[1000];
      int i=0,j=0;

      while((s[j]=fgetc(f))!= EOF)
      {
         j++;
      }

      while(i<j)
      {
         if(s[i] == '\n' && s[i+1]=='\n')
         goto label3;

         printf("%c",s[i]);

         label3:i++;
      }
      printf("\n");

      fclose(f);
   }
}

void explanation()
{
		fputs("\
		\n\
		Usage: cat [OPTION]... [FILE]...\n\
		Displays short description of cat and its use with a few examples.\n\
		-b, --number-nonblank    number nonempty output lines, overrides -n\n\
		-h, --shows examples       description of cat and its use with a few examples.\n\
		-n, --number             number all output lines\n\
		-s, --squeeze-blank      suppress repeated empty output lines\n\
		-q, --quit           stops the execution of the program\n\
		>,  --copies the content of the first txt file to the other file\n\
		>>, --appends content of the txt file to the next txt file\n\
		\n\
		======================================================================================\n\
		   Examples:\n\
		cat text1.txt > text2.txt\n\
		\n\
		this code copies the content of the text1.txtfile into text2.txt file.\n\
		\n\
		If there is something in text2.txt before copying process it is cleared.\n\
		======================================================================================\n\
		\n\
		cat text1.txt >> text2.txt  Appends the content of the text1.txt in text2.txt\n\
		\n\
		======================================================================================\n\
		  ",stdout);

}
/*Checks the given word for palindrome or not*/
int palindrome(char *s)
{
    int n = strlen(s);
    for (int i = 0, j = n-1; i <= j && s[i] != '\0'; i++, j--)
    {
        if (s[i] != s[j])
            return -1;
    }
    return 0;
}


/*divides the given string into words than checks one by one palindrome or not,further compares palindrome ones by their lenghts*/
void longestpalindrome(char *argv[])
{
	FILE *f4= fopen(argv[2], "r");
	char s[1000];
	int k=0;
	while((s[k]=fgetc(f4)) != EOF)
	{

		k++;
	}

	int lpallen=0;
	char *string,*lpal;

	string=strtok(s," ");//for dividing the string

	while(string != NULL)
	{
		if(!palindrome(string))//palindrome checking point
		{
			if(strlen(string)>lpallen)//lenght compare for palindrome ones
			{
		    lpal=string;
			lpallen=strlen(lpal);
		    }
		    else if(strlen(string)==lpallen)//if there is more than one equal longest palindrome
		    {
				printf("Error!There is more than one longest palindrome.\n");
				return ;
			}

		}
		string=strtok(NULL," ");//for dividing the string

	}

	printf("The longest palindrome is: %s \n",lpal);


}

void catDelete(int argc,char **argv, int index)
{
   for (int i=(index+1); i<argc; i++)/*Truncates files to zero which are typed before > argument*/
      {
         FILE *delete = fopen(argv[i], "w");
         fputs("\0", delete);
         fclose(delete);
      }
}
