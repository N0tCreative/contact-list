/*
 *stringHandling.c
 *Jerad Arnold
 *07-03-19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*checks if the string was realloc'd properly*/
int isNull(char * ptr){
	if(ptr == NULL){
		printf("Not enough memory to store this string\n");
		free(ptr);
		return 1;
	}
	return 0;	
}

/*allocates enough space for a string of unspecified length*/
int strIn(char ** strPtr){
	int length =1;
	char temp[2] ="0";
	/*gets rid of any previous string*/
	*strPtr = realloc(*strPtr, length*sizeof(char));
	strcpy(*strPtr,"");
	/*reads string from user*/
	while((temp[0] =getchar())!='\n'){
		length++;
		*strPtr = realloc(*strPtr, length*sizeof(char));
		if(isNull(*strPtr)){
			return 0;
		}
		strncat(*strPtr, temp, 1);
	}
	
	return length;/*if empty returns 1*/
}

