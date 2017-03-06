//Custom assert function that comes with a condition and a message

#define assertTrue(xy, MSG) do{if(!(xy)){ printf("%s\n",MSG);}}while(0)

