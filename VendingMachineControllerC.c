#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<wiringPi.h>

struct machine {
char name[8];
int index, pin, status;			//Machine Structure
char location [16];
};

int n;
struct machine *mem;    		//Global Variables
int b=0;
int Index ;

void updateStatus(){			//Updates Status of machine (also will show LED if status =1)
int j;

printf("Enter the Index Number of the Machine you wish to update: ");
scanf("%d", &j);
int test = (mem+j)->status;

if (test == 1){
	char cmd[255]={0};
	printf("Status = 1 \n");			//test while LED is not in
	sprintf (cmd, "gpio -g write %d %d", 23, 1);
	system(cmd);
};

if(test == 0){
	char cmd[255]={0};
	printf("Status = 0");
	sprintf(cmd, "gpio -g write %d %d", 23, 0);
	system(cmd);
	};

printf("The Current Status for Machine Number is: %d \n", (mem+j)-> status);
printf("Do you Wish to change status? 1 = yes 0 = no ?\n");					//Takes in users choice
int choice;
scanf("%d", &choice);


if (choice == 1){
	int i;
	printf("Enter Machines new Status (1 for stocked, 0 for empty)");
	scanf("%d", &(mem+j)->status);
}

if (choice == 0){
	printf("Press Enter to return to Menu");		//Return to menu for loop
	int o;
	char buf[10];
	for (o=0; o<2; ++o){							//Return to menu for loop
	fgets(buf, 10, stdin);
		};
	}
}

void deleteMachine() {				//Deletes Machine by index number
int j;
int num = 0;

printf("Enter the Index Number of the Machine you want to delete: ");	//
scanf("%d", &j);														//
(mem+j)->index = 0;														//
strcpy((mem+j)->name, "");												//
(mem+j)->pin = 0;														//
(mem+j)->status = 9;													//this function overwrites data on selected machine
strcpy((mem+j)->location,"");											//Machine will state that it is deleted in show machine
printf("Machine: %d", (mem+j)->status, "has been deleted \n");			//
printf("Press Enter to return to Menu");								//
int f;
char buf[10];

for (f=0;f<2;f++){
	fgets(buf, 10, stdin);			//Return to menu loop
	};
}


void searchIndex(){				//searches machines by index number
int j;

printf("Enter the Index Number of the machine: ");				
scanf("%d", &j);												

printf("Displaying Information of Machine number: %d \n", j);


printf("Machine name: %s \n", (mem+j) -> name);
printf("Machine pin: %d \n", (mem+j) -> pin);
printf("Machine Status: %d \n",(mem+j) -> status);
printf("Machine Location: %s \n",(mem+j) -> location);
printf("\n");

printf("Press Enter to return to Menu");
int f;
char buf[10];

for(f=0; f<2; f++){					//Return to menu
	fgets(buf, 10, stdin);
	};
}

void addMachine(){			// Add Machine Function
int i = Index + 1;

printf("Please Enter Machines Information\n");


printf("Enter Machine Index Number: ");
scanf("%d", &(mem+i)->index);

printf("Enter Machine Name: ");
scanf("%s", &(mem+i)->name);

printf("Enter Machine pin: ");
scanf("%d", &(mem+i)->pin);

printf("Enter Machine Status:(1 for stocked, 0 for empty) ");
scanf ("%d", &(mem+i)->status);

printf("Enter Machine Location: ");
scanf("%s", &(mem+i)->location);

printf("\n");


printf("Machine Added! Press Enter to return to menu");
int o;
char buf[10];
for (o=0; o<2; ++o){
fgets(buf, 10, stdin);
};
}

char showMachine(){                  //shows all machines
int i;
printf("Displaying machine information\n");
for(i=0;i<Index+1;++i){

if ((mem+i)->index == 0){					//Runs a check against the index in structure 
	printf("Machine has been Deleted\n");	//If the machine has been deleted index will be set to 0
}											//Will state the machine has been deleted if this is the case
else
printf("Machine Index: %d \n", (mem+i)->index);
printf("Name: %s \n", (mem+i)->name);
printf("Pin: %d \n", (mem+i)->pin);
printf("Machine Status: %d \n",(mem+i)->status);
printf("Location: %s \n", (mem+i)->location);
printf("\n");
}

printf("Press Enter to Return to Menu");
int o;
char buf[10];
for (o=0; o<2; ++o){
fgets(buf, 10, stdin);
};
}

  int main(void){

mem = (struct machine*) malloc (6 * sizeof(struct machine));
char option; // userinput
bool isRunning = true; //while loop
Index = 0;
while (isRunning==true){
system("clear"); //screen Clear
fflush(stdin);

puts ("\n[1]Add Machine"
"\n[2]Show All Machines"
"\n[3]Search By Index"
"\n[4]Delete Machine"
"\n[5]Update Status"
"\n[6]Exit");

option = getchar();
switch(option){

case '1':		//add machine
addMachine();
Index++;
	break;
case '2':
showMachine();		//show machine
	break;
case '3':
searchIndex();		//Search machine by index number
	break;
case '4':
deleteMachine();	//Delete machine by index number
	break;
case '5':
updateStatus();		//Updates Machine status
	break;
case '6':		// Exits Program
	isRunning = false;
	return 0;

}
}
return 0;
}
