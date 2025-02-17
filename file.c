#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    int contactnumbers=addressBook ->contactCount;
    FILE *fptr;
    fptr=fopen("addressBook.csv","w");
    if(fptr==NULL)
    {
        printf("address invalid\n");
        return;
    }
    for(int i=0;i<contactnumbers;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("Contacts are succesfullly saved to addressbook.csv\n");
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    int *numc = &(addressBook->contactCount);
    FILE *fptr;
    fptr=fopen("addressBook.csv","r");
    if(fptr==NULL)
    {
        printf("address invalid\n");
        return;
    }
    int i=0;
    while(fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email)!=EOF)
    {
        i++;
    }
    *numc=i;
    fclose(fptr);
    printf("Contacts are loaded from addressBook.csv\n");
}
