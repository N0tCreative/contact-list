/*contact list app
 *sorts a contact list in alphabetical order and adds more constraints to original contact list
 *Jerad Arnold
 *03-25-19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactDefs.h"

typedef struct info info;
typedef struct contact contact;

int delete(info* contactsInfo, int size, int element);

int main(){
	int i;
	int flag =0;
	int flag2 =0;
	int flag3 =0;
	int atPos;
	int periodPos;
	int selection;
	int numContacts =0;
	int strSize[4] = {0,0,0,0};
	char * temp =NULL;
	char * yesNo =NULL;
	char * yesNo2 =NULL;
	info * contactsInfo;
	info tempInfo;
	contact positions;
	FILE * list =fopen("myContactList.db", "rb");
	
	/*if the file exists read it*/
	if(list != NULL){
		numContacts++;
		/*reading all the contacts from the file into dynamic structs*/
		contactsInfo = malloc(sizeof(info));
		if(contactsInfo ==NULL){
			printf("Ran out of memory :(\n");
			return -1;
		}
		while(1){/*start of reading contacts into an array of info*/
			/*start reading contact info and see if there are any strings to read*/
			fread(&(positions.phone_number), sizeof(unsigned long), 1, list);
			
			if((positions.phone_number) == 0){
				numContacts--;
				contactsInfo = realloc(contactsInfo, sizeof(info)*numContacts);
				if(contactsInfo ==NULL){
					printf("Ran out of memory :(\n");
					return -1;
				}
				break;
			}
			fread(&(positions.first_name_posn), sizeof(long), 1, list);
			fread(&(positions.last_name_posn), sizeof(long), 1, list);
			fread(&(positions.company_name_posn), sizeof(long), 1, list);
			fread(&(positions.email_posn), sizeof(long), 1, list);
			fread(&(positions.next), sizeof(long), 1, list);
			
			/* if there are strings it starts to read them*/
			contactsInfo[numContacts-1].phoneNumber = positions.phone_number;/* something is writing out of size here & needs to be fixed*/
			/*if the first name exists then find the right size and copy it into the struct*/
			if(positions.first_name_posn !=0){
				if(positions.last_name_posn !=0){
					strSize[0]=(int)(positions.last_name_posn -positions.first_name_posn);
				}
				else if(positions.company_name_posn !=0){
					strSize[0]=(int)(positions.company_name_posn -positions.first_name_posn);
				}
				else if(positions.email_posn !=0){
					strSize[0]=(int)(positions.email_posn -positions.first_name_posn);
				}
				else{
					strSize[0]=(int)(positions.next -positions.first_name_posn);
				}
				contactsInfo[numContacts-1].firstName = malloc(strSize[0] *sizeof(char));
				if(contactsInfo[numContacts-1].firstName ==NULL){
					printf("Ran out of memory :(\n");
					return -1;
				}
				fread(contactsInfo[numContacts-1].firstName, sizeof(char), strSize[0], list);
			}
			
			/*if last name exists then find the right size and copy it into the struct*/
			if(positions.last_name_posn !=0){
				if(positions.company_name_posn !=0){
					strSize[1]=(int)(positions.company_name_posn -positions.last_name_posn);
				}
				else if(positions.email_posn !=0){
					strSize[1]=(int)(positions.email_posn -positions.last_name_posn);
				}
				else{
					strSize[1]=(int)(positions.next -positions.last_name_posn);
				}
				contactsInfo[numContacts-1].lastName = malloc(strSize[1] *sizeof(char));
				if(contactsInfo[numContacts-1].lastName ==NULL){
					printf("Ran out of memory :(\n");
					return -1;
				}
				fread(contactsInfo[numContacts-1].lastName, sizeof(char), strSize[1], list);
			}
			
			/*if company name exists then find the right size and copy it into the struct*/
			if(positions.company_name_posn !=0){
				if(positions.email_posn !=0){
					strSize[2]=(int)(positions.email_posn -positions.company_name_posn);
				}
				else{
					strSize[2]=(int)(positions.next -positions.company_name_posn);
				}
				contactsInfo[numContacts-1].companyName = malloc(strSize[2] *sizeof(char));
				if(contactsInfo[numContacts-1].companyName ==NULL){
					printf("Ran out of memory :(\n");
					return -1;
				}
				fread(contactsInfo[numContacts-1].companyName, sizeof(char), strSize[2], list);
			}
			
			/*if email exists then find the right size and copy it into the struct*/
			if(positions.email_posn !=0){
				strSize[3]=(int)(positions.next -positions.email_posn);
				contactsInfo[numContacts-1].email = malloc(strSize[3] *sizeof(char));
				if(contactsInfo[numContacts-1].email ==NULL){
					printf("Ran out of memory :(\n");
					return -1;
				}
				fread(contactsInfo[numContacts-1].email, sizeof(char), strSize[3], list);
			}
			numContacts++;
			contactsInfo = realloc(contactsInfo, sizeof(info)*numContacts);
			contactsInfo[numContacts-1].firstName = NULL;
			contactsInfo[numContacts-1].lastName = NULL;
			contactsInfo[numContacts-1].companyName = NULL;
			contactsInfo[numContacts-1].email = NULL;
			if(contactsInfo == NULL){
				printf("Ran out of memory :(\n");
				return -1;
			}
			positions.phone_number = 0;/*sets the value to 0 to check if new value is added*/
		}/*end of reading contacts into a struct loop*/
		fclose(list);
	}
	
	do{/*main menu loop*/
		/*sort the array*/
		if(numContacts > 1){
			qsort((void*)contactsInfo,numContacts, sizeof(info), name_ascending);
		}
		
		/*display entire list*/
		printf("Number of Contacts = %d\n", numContacts);
		for(i =0; i<numContacts; i++){
			/*if there is one name or more display the starting letter of the last name first*/
			if(i==0 && numContacts>0){
				if(contactsInfo[i].lastName!=NULL){
					printf("%c\n", contactsInfo[i].lastName[0]);
				}
				else{
					printf("%c\n", contactsInfo[i].companyName[0]);
				}
			}
			/*for any name after this, check if the previous name had the same starting letter and if not display the starting letter of last name*/
			else{
				if(contactsInfo[i].lastName!=NULL && contactsInfo[i-1].lastName!=NULL){
					if(contactsInfo[i].lastName[0] != contactsInfo[i-1].lastName[0]){
						printf("%c\n", contactsInfo[i].lastName[0]);
					}
				}
				else if(contactsInfo[i].lastName==NULL && contactsInfo[i-1].lastName!=NULL){
					if(contactsInfo[i].companyName[0] != contactsInfo[i-1].lastName[0]){
						printf("%c\n", contactsInfo[i].lastName[0]);
					}
				}
				else if(contactsInfo[i].lastName!=NULL && contactsInfo[i-1].lastName==NULL){
					if(contactsInfo[i].lastName[0] != contactsInfo[i-1].companyName[0]){
						printf("%c\n", contactsInfo[i].lastName[0]);
					}
				}
				else{
					if(contactsInfo[i].companyName[0] != contactsInfo[i-1].companyName[0]){
						printf("%c\n", contactsInfo[i].lastName[0]);
					}
				}
			}
			
			if(contactsInfo[i].lastName!=NULL && strcmp(contactsInfo[i].lastName, "") !=0){
				printf("\t%d. %s\n", i+1, contactsInfo[i].lastName);
			}
			else{
				printf("\t%d. %s\n", i+1, contactsInfo[i].companyName);
			}
		}/*end of display contact loop*/
		
		/*prompt choice*/
		do{/*keeps asking for input if none is valid*/
			printf("Action: ");
			strIn(&yesNo);
			/*if the user inputed a number*/
			if(sscanf(yesNo, "%d", &selection)){/*selects a contact if valid*/
				if(selection>0 && selection<= numContacts){
					selection--;
					flag =1;
					/*use function to display all info related to contact*/
					printf("Contact #%d\n", selection+1);
					printf("First Name: %s\n", contactsInfo[selection].firstName);
					printf("Last Name: %s\n", contactsInfo[selection].lastName);
					printf("Company Name: %s\n", contactsInfo[selection].companyName);
					printf("Phone Number: %lu\n", contactsInfo[selection].phoneNumber);
					printf("Email: %s\n", contactsInfo[selection].email);
					do{
						printf("Action: ");
						strIn(&yesNo);
						if(strcmp(yesNo, "E")==0){
							flag3 =1;
							printf("First Name:");
							strSize[0] = strIn(&(tempInfo.firstName));
							do{
								printf("Last Name:");
								strSize[1] = strIn(&(tempInfo.lastName));
								printf("Company Name:");
								strSize[2] = strIn(&(tempInfo.companyName));
							}while(strlen(tempInfo.lastName) !=0 || strlen(tempInfo.companyName) !=0);
							do{
								printf("Phone Number (enter only numbers):");
								strSize[3] = strIn(&temp);
								if(strSize[3]==8 || strSize[3]==11){/*strSize includes null terminator so actual peramters are increased by 1*/
									if(sscanf(temp, "%lu", &(tempInfo.phoneNumber))){
										flag2=1;
									}
								}
							}while(flag2 ==0);
							flag2 =0;
							do{/*only takes a vaild email or none at all*/
								printf("Email:");
								strSize[3] = strIn(&(tempInfo.email));
								if(strSize[3] ==1){/*strIn returns 1 if there is an empty string*/
									flag2=1;
								}
								else{/*checks if the email fits the parameters*/
									for(i=0; i< strlen(contactsInfo[numContacts-1].email); i++){
										if(contactsInfo[numContacts-1].email[i] == '@'){
											atPos =i;
										}
										else if(contactsInfo[numContacts-1].email[i] == '.'){
											periodPos =i;
										}
									}
									if(atPos !=0 && atPos<periodPos-1 && periodPos != i-1){
										flag2 =1;
									}
								}
							}while(flag2==0);
							flag2=0;
							printf("Action: ");
							do{
								strIn(&yesNo2);
								if(strcmp(yesNo2, "S")==0){/*free all strings in the contact and then overwrite them with the new values*/
									free(contactsInfo[selection].firstName);
									free(contactsInfo[selection].lastName);
									free(contactsInfo[selection].companyName);
									free(contactsInfo[selection].email);
									contactsInfo[selection] = tempInfo;
									flag2=1;
								}
								else if(strcmp(yesNo2, "D")==0){
									numContacts =delete(contactsInfo, numContacts, selection);
									flag2 =1;
								}
								else if(strcmp(yesNo2, "R")==0){
									flag2 =1;
								}
							}while(flag2 ==0);
							flag2 =0;
						}/*end of edit statement*/
						else if(strcmp(yesNo, "D")==0){
							numContacts =delete(contactsInfo, numContacts, selection);
							flag3=1;
						}
						else if(strcmp(yesNo, "R")==0){
							flag3 =1;
						}
					}while(flag3 ==0);
					flag3=0;
				}
				else{
					printf("Number not in range\n");
				}
			}
			else if(strcmp(yesNo, "A")==0){/*adds a contact with requirements*/
				flag=1;
				/*open add contact function*/
				numContacts++;
				contactsInfo =realloc(contactsInfo, sizeof(info)*numContacts);
				contactsInfo[numContacts-1].firstName = NULL;
				contactsInfo[numContacts-1].lastName = NULL;
				contactsInfo[numContacts-1].companyName = NULL;
				contactsInfo[numContacts-1].email = NULL;
				
				printf("First Name:");
				strSize[0] = strIn(&(contactsInfo[numContacts-1].firstName));
				do{
					printf("Last Name:");
					strSize[1] = strIn(&(contactsInfo[numContacts-1].lastName));
					printf("Company Name:");
					strSize[2] = strIn(&(contactsInfo[numContacts-1].companyName));
				}while(strlen(contactsInfo[numContacts-1].lastName) ==0 && strlen(contactsInfo[numContacts-1].companyName) ==0);
				do{
					printf("Phone Number (enter only numbers):");
					strSize[3] = strIn(&temp);
					if(strSize[3]==8 || strSize[3]==11){/*strSize includes null terminator so actual peramters are increased by 1*/
						if(sscanf(temp, "%lu", &(contactsInfo[numContacts-1].phoneNumber))){
							flag2=1;
						}
					}
				}while(flag2 ==0);
				flag2 =0;
				do{/*only takes a vaild email or none at all*/
					printf("Email:");
					strSize[3] = strIn(&(contactsInfo[numContacts-1].email));
					if(strSize[3] ==1){/*strIn returns 1 if there is an empty string*/
						flag2=1;
					}
					else{/*checks if the email fits the parameters*/
						for(i=0; i< strlen(contactsInfo[numContacts-1].email); i++){
							if(contactsInfo[numContacts-1].email[i] == '@'){
								atPos =i;
							}
							else if(contactsInfo[numContacts-1].email[i] == '.'){
								periodPos =i;
							}
						}
						if(atPos !=0 && atPos<periodPos-1 && periodPos != i-1){
							flag2 =1;
						}
					}
				}while(flag2==0);
				flag2=0;
				do{
					printf("Action: ");
					strIn(&yesNo2);
					if(strcmp(yesNo2, "S")==0){
						flag3=1;
					}
					else if(strcmp(yesNo2, "R")==0){
						flag3=1;
						numContacts--;
						contactsInfo =realloc(contactsInfo, sizeof(info)*numContacts);
					}
				}while(flag3 ==0);
				flag3=0;
			}
			else if(strcmp(yesNo, "X")==0){/*exits program*/
				flag =1;
			}
		}while(flag ==0);
		flag =0;
	}while(strcmp(yesNo,"X")!=0);/*end of main menu loop*/
	
	/*output all info to the file before ending the program*/
	if(numContacts > 1){
		qsort((void*)contactsInfo,numContacts, sizeof(info), name_ascending);
	}
	else if(numContacts == 1){}
	else{
		return 0;
	}
	atPos =0;
	list =fopen("myContactList.db", "wb");
	for(i =0; i< numContacts; i++){/*set the positions of all strings and writes them to the file*/
		positions.phone_number = contactsInfo[i].phoneNumber;
		atPos += sizeof(struct contact);
		if(strlen(contactsInfo[i].firstName) !=0){
			positions.first_name_posn = atPos;
			atPos += strlen(contactsInfo[i].firstName)+1;
		}
		else{
			positions.first_name_posn = 0;
		}
		
		if(strlen(contactsInfo[i].lastName) !=0){
			positions.last_name_posn = atPos;
			atPos += strlen(contactsInfo[i].lastName)+1;
		}
		else{
			positions.last_name_posn = 0;
		}
		
		if(strlen(contactsInfo[i].companyName) !=0){
			positions.company_name_posn = atPos;
			atPos += strlen(contactsInfo[i].companyName)+1;
		}
		else{
			positions.company_name_posn = 0;
		}
		
		if(strlen(contactsInfo[i].email) !=0){
			positions.email_posn = atPos;
			atPos += strlen(contactsInfo[i].email)+1;
		}
		else{
			positions.email_posn = 0;
		}
		positions.next = atPos;
		
		fwrite(&(positions), sizeof(contact), 1, list);
		fwrite(contactsInfo[i].firstName, sizeof(char), strlen(contactsInfo[i].firstName)+1, list);
		fwrite(contactsInfo[i].lastName, sizeof(char), strlen(contactsInfo[i].lastName)+1, list);
		fwrite(contactsInfo[i].companyName, sizeof(char), strlen(contactsInfo[i].companyName)+1, list);
		fwrite(contactsInfo[i].email, sizeof(char), strlen(contactsInfo[i].email)+1, list);
		
	}
	fclose(list);
	
	/*free all contacts before the program closes*/
	for(i =0; i< numContacts; i++){
		free(contactsInfo[i].firstName);
		free(contactsInfo[i].lastName);
		free(contactsInfo[i].companyName);
		free(contactsInfo[i].email);
	}
	free(temp);
	free(yesNo);
	free(yesNo2);
	if(numContacts !=0){
		free(contactsInfo);
	}
	
	return 1;
}

/*deletes a specific element in the info array*/
int delete(info * contactsInfo, int size, int element){
	int i;
	free(contactsInfo[element].firstName);
	free(contactsInfo[element].lastName);
	free(contactsInfo[element].companyName);
	free(contactsInfo[element].email);
	for(i=element; i<size-1; i++){
		contactsInfo[i] = contactsInfo[i+1];
	}
	contactsInfo = realloc(contactsInfo, sizeof(info)*size-1);
	return size-1;
}
