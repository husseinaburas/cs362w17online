/*  by looking the testme() function
    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
For certain value c get to next state and when state = 9 and  string = "reset\0" print error and exit
in inputChar()
I create an array of char c[] = { '[', '(', '{', ' ', 'a', 'x', '}', ')', ']' };
use rand() to set random get in next state

in inputString()
I create an array char c[] = {'r','a' ,'n' ,'d' ,'o' ,'m','t','e','s','t'};
which contains 'reset' so we can possibly generate expect string to print error and exit program*/
