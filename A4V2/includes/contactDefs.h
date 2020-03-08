/*
 *contactDefs
 *all external functions for contactList
 */

struct contact{
	unsigned long phone_number;
	long first_name_posn;
	long last_name_posn;
	long company_name_posn;
	long email_posn;
	long next;
};

struct info{/*this struct contains all the data to be written in*/
	unsigned long phoneNumber;
	char* firstName;
	char* lastName;
	char* companyName;
	char* email;
};

int strIn(char ** stringPtr);

int name_ascending ( const void * name1, const void * name2);
