#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   DIV,
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{
    if (op[1] != '\0')
	       IssueBadOperationError();
	   
    switch (*op)
    {	 
	case '+':
	 return ADD;
	case 'x':
	 return MULT;
	case '-':
	 return SUBTRACT;
	case '/':
	 return DIV;
	default:
	 return UNSUPPORTED;
}
}

double StringToDouble(char *str)
{
	double answer = 0.0;
	int i = 0;
	int decimal = 0;
	int is_neg = 0;
	int places = 0;
	int sub_num = 0;
	if(str[0] == '-')
	{
		i ++;
		is_neg = 1;
	}

   while (str[i] != '\0') /*loop through all characters in string*/
   {	   if(str[i]=='-')
	   {
	   IssueBadNumberError();
	   }

	   if (str[i] == '.')
	   {
		decimal++;
		places = 0;
		i++;

	   }

	   places++;
	   sub_num = str[i] - '0';

	   if(sub_num > 9)
	   {
	   	IssueBadNumberError();
	   }

	 i++;
	answer= (answer+sub_num)*10; 
   	}
   if (decimal > 1 || is_neg > 1)
   { 
	   IssueBadNumberError();
   }

  if(decimal == 1)
  {
   for(int j = 0; j < places; j++)
   {
	   answer = answer/10;
   }
  }
   if(is_neg == 1)
   {
	   answer = answer * -1;
   }
     	return  answer/10;
}



int main(int argc, char *argv[])
{
    double v = StringToDouble(argv[1]);
    MathOperation op = GetOperation(argv[2]);
    if (op == UNSUPPORTED)
    {
	    IssueBadOperationError();
    }
    double v2 = StringToDouble(argv[3]);
    double result = 0.;
    switch (op)
    {
       case ADD:
         result = v+v2;
         break;
       case MULT:
	result = v*v2;
	break;
       case DIV:
	result = v/v2;
	break;
       case SUBTRACT:
	result = v-v2;
	break;
       

    }
    printf("%d\n", (int) result);
 
    return 0;
}
