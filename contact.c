#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>
#include "file.h"
#include "populate.h"
#include "populate.c"

int validate_name(char *);
int validate_number(char *);
int validate_email(char *);



void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
	if(sortCriteria==1)
	{
		int n=addressBook -> contactCount;
		Contact temp;
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(strcmp(addressBook -> contacts[j].name,addressBook -> contacts[j+1].name)>0)
				{
					temp=addressBook -> contacts[j];
					addressBook -> contacts[j]=addressBook->contacts[j+1];
					addressBook -> contacts[j+1]=temp;
				}
			}
		}
		for(int i=0;i<addressBook->contactCount;i++)
		{
			printf("%s\n",addressBook->contacts[i].name);
			printf("%s\n",addressBook->contacts[i].phone);
			printf("%s\n",addressBook->contacts[i].email);
			printf("\n");
		}
	}
	
	else if(sortCriteria==2)
	{
		int n=addressBook -> contactCount;
		Contact temp;
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(strcmp(addressBook -> contacts[j].phone,addressBook -> contacts[j+1].phone)>0)
				{
					temp=addressBook -> contacts[j];
					addressBook -> contacts[j]=addressBook->contacts[j+1];
					addressBook -> contacts[j+1]=temp;
				}
			}
		}
		for(int i=0;i<addressBook->contactCount;i++)
		{
			printf("%s\n",addressBook->contacts[i].name);
			printf("%s\n",addressBook->contacts[i].phone);
			printf("%s\n",addressBook->contacts[i].email);
			printf("\n");
		}
	}
    else if(sortCriteria==3)
	{
		int n=addressBook -> contactCount;
		Contact temp;
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1-i;j++)
			{
				if(strcmp(addressBook -> contacts[j].email,addressBook -> contacts[j+1].email)>0)
				{
					temp=addressBook -> contacts[j];
					addressBook -> contacts[j]=addressBook->contacts[j+1];
					addressBook -> contacts[j+1]=temp;
				}
			}
		}
		for(int i=0;i<addressBook->contactCount;i++)
		{
			printf("%s\n",addressBook->contacts[i].name);
			printf("%s\n",addressBook->contacts[i].phone);
			printf("%s\n",addressBook->contacts[i].email);
			printf("\n");
		}
	}
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
	//populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}


	void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
	char str1[1000],str2[1000],str3[1000];
	int res;
	do{
		printf("enter the name:\n");
		getchar();
		scanf("%[^\n]",str1);
		res=validate_name(str1);
	}
	while(res);

	do{
		printf("enter the phone number:\n");
		getchar();
		scanf("%[^\n]",str2);
		
		res=validate_number(str2);
	}
	while(res);


	do{
		printf("enter the email id:\n");
		getchar();
		scanf("%[^\n]",str3);
		
		res=validate_email(str3);
	}
	while(res);

	strcpy(addressBook -> contacts[addressBook -> contactCount].name,str1);
	strcpy(addressBook -> contacts[addressBook -> contactCount].phone,str2);
	strcpy(addressBook -> contacts[addressBook -> contactCount].email,str3);

	addressBook -> contactCount++;
	
	
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    int choice,res,j,count=0;
	char str1[1000];
	 do{
	    printf("Enter what you want to search:\n1. Name 2. Mobile number 3. Email Id\n");
	    scanf("%d",&choice);
        if(choice<1 || choice>3)
        printf("Invalid choice, try again:\n");
    }while(choice<1 || choice>3);
	// printf("Enter what you want to search:\n1. Name 2. Mobile number 3. Email Id\n");
	// scanf("%d",&choice);

	if(choice==1)
	{
        do{
            int dupcount = 0;
            int ind[100];
            printf("Enter the name: ");
            getchar();
            scanf("%[^\n]",str1);
            res = validate_name(str1);
            if(res == 0)
            {
                for(int i=0;i<addressBook -> contactCount;i++)
                {
                    if(strcmp(str1,addressBook -> contacts[i].name) == 0)
                    {
                        ind[dupcount] = i;
                        dupcount++;
                    }
                }
                if(dupcount == 0)
                {
                    printf("Name not found\n");
                    
                }
                else if(dupcount == 1)
                {
                    int idx = ind[0];
                    printf("Name found!\n");
                    printf("%s\n",addressBook -> contacts[idx].name);
                    printf("%s\n",addressBook -> contacts[idx].phone);
                    printf("%s\n",addressBook -> contacts[idx].email);
                    
                }
                else
                {
                    printf("Multiple contacts with same name found!\n");
                    for(int i=0;i<dupcount;i++)
                    {
                        int idx = ind[i];
                        
                        printf("Contact %d\n",i+1);
                        printf("%s\n",addressBook -> contacts[idx].name);
                        printf("%s\n",addressBook -> contacts[idx].phone);
                        printf("%s\n",addressBook -> contacts[idx].email);
                    }
                    char phonein[20];
                    int found = 0;
                    printf("Enter phone number\n");
                    getchar();
                    scanf("%[^\n]",phonein);
                    for(int i=0;i<dupcount;i++)
                    {
                        int idx = ind[i];
                        if(!strcmp(phonein,addressBook -> contacts[idx].phone))
                        {
                            printf("Selected contact:\n");
                            printf("%s\n",addressBook -> contacts[idx].name);
                            printf("%s\n",addressBook -> contacts[idx].phone);
                            printf("%s\n",addressBook -> contacts[idx].email);
                            found = 1;
                            break;
                        }
                    }
                    if(found == 0)
                    printf("No matching contact found!\n");
					
                }
            }

            
            else
            printf("Invalid name entered, please enter again:\n");
        }while(res);
		
    }

	else if(choice==2)
	{
        do{
			int p2=0;
		    printf("Enter the phone number:");
		    getchar();
			scanf("%[^\n]",str1);
		    
		    res=validate_number(str1);
		    if(res==0)
		    {
			    for(int i=0;i<addressBook -> contactCount;i++)
			    {
				    if(!strcmp(str1,addressBook->contacts[i].phone))
				    {
					    p2=1;
					    printf("%s\n",addressBook->contacts[i].name);
					    printf("%s\n",addressBook->contacts[i].phone);
					    printf("%s\n",addressBook->contacts[i].email);
				    }
				}
			    if(p2==0)
			    printf("Phone number not found\n");
		    }
		    else
		    printf("Phone number is Invalid, Enter a valid number\n");
        }
		while(res);
	}


	else if(choice==3)
	{
        do{
			int p3=0;
		    printf("Enter the email: ");
		    getchar();
			scanf("%[^\n]",str1);
		    
		    res=validate_email(str1);
		    if(res==0)
		    {
			    for(int i=0;i<addressBook -> contactCount;i++)
			    {
				    if(!strcmp(str1,addressBook->contacts[i].email))
				    {
					    p3=1;
					    printf("%s\n",addressBook->contacts[i].name);
					    printf("%s\n",addressBook->contacts[i].phone);
					    printf("%s\n",addressBook->contacts[i].email);
				    }
				}
			    if(p3==0)
			    printf("Email not found\n");
		    }
		    else
		    printf("Email is Invalid, Enter a valid email\n");
        }
		while(res);
	}
	else
	printf("Enter a valid choice\n");


}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int choice,count=0;
	char newname[50];
	char str[50],str2[50];
	int ret,k,flag=0,flag1=0,flag2=0;
	printf("enter what to edit:\n1. Name \n2. Phone no\n3. email\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		
		printf("enter the old name:\n");
		// scanf("%[^\n]",str);
		do
		{
			getchar();
			scanf("%[^\n]",str);
			ret=validate_name(str);
			if(ret==0)
			{
				for(int i=0;i<addressBook ->contactCount;i++)
				{
					if(strcmp(str,addressBook->contacts[i].name)==0)
					{
						count++;
						k=i;
						flag=1;

					}
				}
				if(flag!=1)
				printf("name not found.. enter a valid name\n");
				
			}
			else
			printf("enter the valid name\n");
		}
		while(ret);

		int ret1;
		if(count==1)
		{
			printf("enter the new name\n");
			do
			{
				getchar();
				scanf("%[^\n]",newname);
				int ret1=validate_name(newname);
				if(ret1==0)
				{
					strcpy(addressBook->contacts[k].name,newname);
					printf("Name is successfully edited\n");
					break;
				}
				else
				printf("enter a valid name\n");
			}
			while(ret1);
		}
		else if(count>1)
		{
			int ret2;
			printf("multiple contacts are found with the same name\n so enter the mobile number to confirm");
			do
			{
				getchar();
				scanf("%[^\n]",str2);
				ret2=validate_number(str2);
				
				if(ret2==0)
				{
					
					
					for(int i=0;i<addressBook ->contactCount;i++)
					{
						if(strcmp(str2,addressBook ->contacts[i].phone)==0)
						{
							printf("enter the new name\n");
							getchar();
							scanf("%[^\n]",newname);
							strcpy(addressBook ->contacts[i].name,newname);
							printf("name is succesfully edited\n");
							flag1=1;
						}
					}
					if(flag1==0)
					{
						printf("phone number not found..\n");
						break;
					}

				}
				else
				printf("enter a valid phone number\n");
			} while(ret2);
		}
	}
	else if(choice==2)
	{
		char phno[20],newphno[20];
		int ret3;
		printf("enter the old number:\n");
		do
		{
			getchar();
			scanf("%[^\n]",phno);
			ret3=validate_number(phno);
			if(ret3==0)
			{
				for(int i=0;i<addressBook ->contactCount;i++)
				{
					if(strcmp(phno,addressBook->contacts[i].phone)==0)
					{
						k=i;
						flag=1;
					}
				}
				if(flag!=1)
				printf("phone number not found..\n");
				break;
			}
			else
			printf("enter a valid old phone number\n");
		}
		while(ret3);
		int ret4;
		if(flag==1)
		{
			printf("enter the new phone number\n");
			do
			{
				getchar();
				scanf("%[^\n]",newphno);
				ret4=validate_number(newphno);
				if(ret4==0)
				{
					strcpy(addressBook->contacts[k].phone,newphno);
					printf("phone number is successfully edited\n");
					break;
				}
				else if(ret4==1)
				printf("enter a valid phone number\n");
			}
			while(ret4);
		}

	}


	else if(choice==3)
	{
		char eid[20],neweid[20];
		int ret3;
		printf("enter the old email id:\n");
		do
		{
			getchar();
			scanf("%[^\n]",eid);
			ret3=validate_email(eid);
			if(ret3==0)
			{
				for(int i=0;i<addressBook ->contactCount;i++)
				{
					if(strcmp(eid,addressBook->contacts[i].email)==0)
					{
						k=i;
						flag=1;
					}
				}
				if(flag!=1)
				printf("email id not found..\n");
				break;
			}
			else
			printf("enter a valid old email id\n");
		}
		while(ret3);
		if(flag==1)
		{
			printf("enter the new email id \n");
			do
			{
				getchar();
				scanf("%[^\n]",neweid);
				ret3=validate_email(neweid);
				if(ret3==0)
				{
					strcpy(addressBook->contacts[k].email,neweid);
					printf("email id is successfully edited\n");
					break;
				}
				else
				printf("enter a valid email id \n");
			}
			while(ret3);
		}

	}

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	char delname[50];
	int flag=0;
	int count=0;
	int k;

	printf("enter the name you want to delete\n");
	do{
		getchar();
		scanf("%[^\n]",delname);
		
		for(int i=0;i<addressBook -> contactCount;i++)
		{
			if(strcmp(addressBook -> contacts[i].name,delname)==0)
			{
				k=i;
				flag=1;
				count++;
			}
		}
		if(flag!=1)
		printf("name not found enter a valid name\n");
	}
	while(flag!=1);


	if(count==1)
	{
		for(int j=k;j<addressBook ->contactCount;j++)
		{
			addressBook -> contacts[j]=addressBook -> contacts[j+1];
		}
		addressBook ->contactCount--;
		printf("%s is deleted successfully\n",delname);
        

	}
	else if(count>1)
	{
		char phno[11];
		printf("multiple contacts found so enter the phone number to confirm:\n");
		do
		{
			int k;
			flag=1;
			
			getchar();
			scanf("%[^\n]",phno);
			for(int i=0;i<addressBook ->contactCount;i++)
			{
				if(strcmp(phno,addressBook ->contacts[i].phone)==0)
				{
					k=i;
					flag=0;
					for(int j=k;j<addressBook->contactCount;j++)
					addressBook ->contacts[k]=addressBook -> contacts[k+1];
					addressBook->contactCount--;

				}
				
			}
			if(flag!=0)
			printf("number not found enter a valid phone number\n");
		}
		while(flag);

		printf("%s  with number %s successfully deleted \n",delname,phno);
	}

}

int validate_name(char *s)
{
	int len=0,flag;
	while(s[len] != '\0')
	{
		if (isalpha(s[len]) || s[len]==' ')
		flag=1;
		else
		{
			flag=0;
			break;
		}
		len++;
	}
	if(flag==1)
	return 0;
	else
	return 1;
}




int validate_number(char *s)
{
	int len=0,flag;
	while(s[len] != '\0')
	{
		if (isdigit(s[len]))
		flag=1;
		else
		{
			flag=0;
			break;
		}
		len++;
	}
	if(flag==1 && len==10)
	return 0;
	else
	return 1;
}


int validate_email(char *s)
{
	int len=0,flag,flag1,count=0;

	while(s[len] != '\0')
	{
        if (isalnum(s[len]))
        {
            if(islower(s[len]))
            flag=0;
            else if(isdigit(s[len]))
            flag=0;
            else
            {
                flag=1;
                break;
            }
        }

        else if(s[len]=='@')
        {
            count++;
            
        }
        else if(s[len]=='.')
        flag=0;
		else
		{
			flag=1;
			break;
		}
		len++;
	}
    if(count!=1)
    {
        flag=1;
    }
    
    if(isalnum(s[len-1]) && isalnum(s[0]))
    {
        flag1=0;
    }
    else{
        flag1=1;
    }


	if(flag==0 && flag1==0)
	return 0;
	else
	return 1;
}































// addressBook -> contacts[addressBook -> contactCount].name