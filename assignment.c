#include <stdio.h>
#include<string.h>


 // clientData structure definition
 struct PatientRecord {
     int ID;
     char Name[30];
     char CNIC[15];
     int phone_number;
     char disease[30];
     char is_admitted[12];
 };

int enterchoice(void);
 void textFile(FILE *readPtr);
 void updateRecord(FILE *fPtr);
 void newRecord(FILE *fPtr);
 void deleteRecord(FILE *fPtr);

 int main(void)
  {
     FILE *cfPtr = NULL; // accounts.dat file pointer

     // fopen opens the file; exits if file cannot be opened
     if ((cfPtr = fopen("accounts.dat", "w+")) == NULL) {
     puts("File could not be opened.");
     }
     else {
                 int choice=0;
         while ((choice=enterchoice())!= 6)
         {
             switch (choice)
              {

                 case 1: // create text file from record file
                 textFile(cfPtr);
                 break;
                 case 2: // update record
                 updateRecord(cfPtr);
                 break;
                 case 3: // create record
                 newRecord(cfPtr);
                 break;
                 case 4: // delete existing record
                 deleteRecord(cfPtr);
                 break;
                 default: // display message for invalid choice
                 puts("Incorrect choice");
                 break;

              }
          }

            fclose(cfPtr); // fclose closes the file
    }
}

 // create formatted text file for printing
 void textFile(FILE *readPtr) {
 FILE *writePtr = NULL; // accounts.txt file pointer

 // fopen opens the file; exits if file cannot be opened
 if ((writePtr = fopen("accounts.txt", "w")) == NULL) {
 puts("File could not be opened.");
 }

 else {
 rewind(readPtr); // sets pointer to beginning of file
 fprintf(writePtr, "%-10s%-31s%-16s%-15s%-31s%-13s\n",
 "ID", "Name", "CNIC","phone_number","disease","is_admitted");

 // copy all records from random-access file into text file
 while (!feof(readPtr)) {
 // create clientData with default information
 struct PatientRecord patient =  {0, "", "",0, "", ""};
 size_t result =fread(&patient, sizeof(struct PatientRecord), 1, readPtr);

 // write single record to text file
 if (result != 0 && patient.ID != 0) {
 fprintf(writePtr, "%-10d%-31s%-16s%-15d%-31s%-13s\n", patient.ID, patient.Name,
     patient.CNIC, patient.phone_number, patient.disease, patient.is_admitted);
 }
 }

 fclose(writePtr); // fclose closes the file
 }
 }

 // update balance in record
 void updateRecord(FILE *fPtr)
  {
      printf("%s", "Enter account to update (1 - 100): ");
      int ID = 0; // account number
      scanf("%d", &ID);

      // move file pointer to correct record in file
      fseek(fPtr, (ID - 1) * sizeof(struct PatientRecord), SEEK_SET);

     // read record from file
      struct PatientRecord patient = {0, "", "",0, "", ""};
     fread(&patient, sizeof(struct PatientRecord), 1, fPtr);

     // display error if account does not exist
     if (patient.ID == 0)
     {
         printf("Account %d has no information.\n", ID);
     }
     else
      { // update record
     printf("%-10d%-31s%-16s%-15d%-31s%-13s\n\n", patient.ID, patient.Name,
     patient.CNIC, patient.phone_number, patient.disease, patient.is_admitted);

     // request transaction amount from user
     printf("%s", "Enter New Phone number: ");
     int num=0; // transaction amount
     scanf("%d", &num);
     patient.phone_number = num; // update record balance

     printf("%-10d%-31s%-16s%-15d%-31s%-13s\n", patient.ID, patient.Name,
     patient.phone_number,patient.disease, patient.is_admitted);

    // move file pointer to correct record in file
     fseek(fPtr, (ID - 1) * sizeof(struct PatientRecord), SEEK_SET);

     // write updated record over old record in file
     fwrite(&patient, sizeof(struct PatientRecord), 1, fPtr);
     }
 }

 // create and insert record
 void newRecord(FILE *fPtr) {
 // obtain number of account to create
 printf("%s", "Enter new account number (1 - 100): ");
 int ID = 0; // account number
 scanf("%d", &ID);

 // move file pointer to correct record in file
 fseek(fPtr, (ID - 1) * sizeof(struct PatientRecord), SEEK_SET);

 // read record from file
 struct PatientRecord patient =  {0, "", "",0, "", ""};
 fread(&patient, sizeof(struct PatientRecord), 1, fPtr);

 // display error if account already exists
 if (patient.ID != 0) {
 printf("Account %d already contains information.\n",
 patient.ID);
 }
 else { // create record
 // user enters last name, first name and balance
 printf("%s", "Enter ID, Name, CNIC, phone_number, disease, is_admitted\n? ");
 scanf("%-1d%-31s%-16s%-15d%-31s%-13s\n", &patient.ID, patient.Name,
     &patient.phone_number,patient.disease, patient.is_admitted);

 patient.ID=ID;

// move file pointer to correct record in file
 fseek(fPtr, (patient.ID - 1) * sizeof(struct PatientRecord),
 SEEK_SET);

 // insert record in file
 fwrite(&patient, sizeof(struct PatientRecord), 1, fPtr);
 }
 }

// delete an existing record
 void deleteRecord(FILE *fPtr) {
 // obtain number of account to delete
 printf("%s", "Enter account number to delete (1 - 100): ");
 int ID = 0; // account number
 scanf("%d", &ID);



 // move file pointer to correct record in file
 fseek(fPtr, (ID - 1) * sizeof(struct PatientRecord), SEEK_SET);

 // read record from file
 struct PatientRecord patient =  {0, "", "",0, "", ""};
 fread(&patient, sizeof(struct PatientRecord), 1, fPtr);

 // display error if record does not exist
 if (patient.ID == 0) {
 printf("Account %d does not exist.\n", ID);
 }
 else { // delete record
 // move file pointer to correct record in file
 fseek(fPtr, (ID - 1) * sizeof(struct PatientRecord), SEEK_SET);

 struct PatientRecord blankClient = {0, "", "", 0}; // blank client

 // replace existing record with blank record
 fwrite(&blankClient, sizeof(struct PatientRecord), 1, fPtr);
 }
}
int enterchoice(void)
{
     int menuchoice = 0;
                      printf("%s", "\nEnter your choice\n"
             "1 - store a formatted text file of accounts called\n"
             " \"accounts.txt\" for printing\n"
             "2 - add a new account\n"
             "3 - update an account\n"
             "4 - delete an account\n"
             "5 - search a patient\n"
             "6 - end program\n? ");
              scanf("%d", &menuchoice);
              return menuchoice;
         // enable user to specify action
}

