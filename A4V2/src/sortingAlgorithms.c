/*sorting algorithms
 *contains sorting algorithm for ascending alphabetic
 *Jerad Arnold
 *03-25-19
 */

#include <string.h>
#include <strings.h>
#include "contactDefs.h"

typedef struct info info;

int name_ascending ( const void * name1, const void * name2){
	info * ele1 = (info *)name1;
	info * ele2 = (info *)name2;
	
	if(ele1->lastName != NULL && strcmp(ele1->lastName, "")!=0 && ele2->lastName != NULL && strcmp(ele2->lastName, "")!=0){
		return(strcasecmp(ele1->lastName, ele2->lastName));
	}
	else if((ele1->lastName == NULL || strcmp(ele1->lastName, "")==0) && ele2->lastName != NULL && strcmp(ele2->lastName, "")!=0){
		return(strcasecmp(ele1->companyName, ele2->lastName));
	}
	else if(ele1->lastName != NULL && strcmp(ele1->lastName, "")!=0 && (ele2->lastName == NULL || strcmp(ele2->lastName, "")!=0)){
		return(strcasecmp(ele1->lastName, ele2->companyName));
	}
	else{
		return(strcasecmp(ele1->companyName, ele2->companyName));
	}
}
