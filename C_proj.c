#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "patient.h"

patient_t *head = NULL;
patient_t *tail = NULL;

void intro(void)
{
	puts("-------------------------###################---------------------------");
	puts("||*******************************************************************||");
	puts("||******************************CLINC********************************||");
	puts("||************************MANAGEMENT SYSTEM**************************||");
	puts("||*******************************************************************||");
	puts("-------------------------###################---------------------------\n\n");
}


void main(void)
{
	u8 mode, action;
	u8 i = 0;
	u32 passcode;
	patient_t *patient_list = NULL;
	rev time_available[] = {
								{"2:00 PM to 2:30 PM", NULL}, 
								{"2:30 PM to 3:00 PM", NULL},
								{"3:00 PM to 3:30 PM", NULL},
								{"4:00 PM to 4:30 PM", NULL},
								{"4:30 PM to 5:00 PM", NULL},
								{NULL, NULL}
							};
	
	while (1)
	{
		mode = modes();
	
		if (mode == 'a')
		{
			i = 0;
			while (++i)
			{
				puts("Please enter password");
				printf("passcode: ");
				scanf("%d",&passcode);
				if (passcode == DEFAULT_PASSWORD)
					break;
				else
				{
					puts("invalid password");
					printf("[%d] tries left\n", sub(3, i));
				}
				if (i >= 3)
				{
					puts("Invalid Access, Quitting system ...");
					return;
				}
					
			}
			
			puts("----------------------------------------");
			puts("Entering admin mode ...");
			puts("----------------------------------------");
			
			while (1)
			{
				action = actions();
				puts("----------------------------------------");
				
				if (action == 'a')
				{
					add_patient(patient_list);
					puts("----------------------------------------");
				}
				
				else if (action == 'e')
				{
					edit_patient();
					puts("----------------------------------------");
				}
				
				else if (action == 'r')
				{
					rev_spot(time_available);
					puts("----------------------------------------");
				}
				
				else if (action == 'c')
				{
					cancel_rev(time_available);
					puts("----------------------------------------");
				}
				
				else if (action == 'q')
				{
					puts("Quitting admin mode");
					puts("----------------------------------------");
					break;
				}
				
				else
				{
					puts("Invalid action please try again");
					puts("----------------------------------------");
				}
			}
			
		}	
	
		else if (mode == 'u')
		{
			while (1)
			{
				puts("----------------------------------------");
				puts("Entering user mode ...");
				puts("----------------------------------------");
				puts("\tActions available");
				puts("[v] to view patient's record");
				puts("[r] to view today's reservation");
				puts("[q] to quit mode");
				printf("Enter action: ");
				scanf(" %c", &action);
				puts("----------------------------------------");
				if (action == 'v')
				{
					view_record(head);
					puts("----------------------------------------");
				}
				else if (action == 'r')
				{
					today_rev(time_available);
					puts("----------------------------------------");
				}
				else if (action == 'q')
				{
					puts("exiting user's mode ...");
					puts("----------------------------------------");
					break;
				}
				else
				{
					puts("Invalid action please try again");
					puts("----------------------------------------");
				}
			}

		}
		
		else if (mode == 'q')
		{
			puts("Quitting system ...");
			return;
		}
	
		else
		{
			puts("please enter a valid mode!!");
			continue;
		}
	}
	
}

void add_patient(patient_t *node)
{
	u8 gend;
	patient_t *new = create();
	
	printf("[%d] patients reserved\n", list_count());
	
	if (new == NULL)
	{
		puts("Failure in system");
		return;
	}
		
	printf("Enter Patients ID in form of {p####}: ");
	new->ID = (u8 *)malloc(sizeof(char) * 5);
	if (new->ID == NULL)
	{
		puts("Failure in system");
		free(new);
		return;
	}
	scanf("%s", new->ID);
		
	if (_strlen(new->ID) != 5)
	{
		puts("Invalid ID length");
		puts("Failure to add patient ...");
		free(new);
		return;
	}
		
	else if (!str_num_check(new->ID))
	{
		puts("invalid ID type");
		puts("Failure to add patient ...");
		free(new);
		return;
	}
		
	else if (str_check(new->ID))
	{
		puts("ID is already taken");
		puts("Failure to add patient ...");
		free(new);
		return;
	}
		
	else
	{
		puts("Valid ID type !");
		puts("Valid ID length ! \n .....");
		printf("Please enter patients name: ");
		scanf("%s", new->name);
		printf("please enter patients age: ");
		scanf("%d", &(new->age));
		puts("Please enter patients gender");
		printf("M for male and F for female: ");
		scanf(" %c", &gend);
		if (gend != 'M' && gend != 'F')
		{
			puts("invalid gender type");
			puts("Failure to add patient");
			free(new);
			return;
		}
		switch (gend)
		{
			case 'M':
				new->gender = 0;
				break;
			case 'F':
				new->gender = 1;
				break;
		}
			
		puts("patient added succesfuly");
	}
	if (tail == NULL && head == NULL)
	{
		
		head = new;
		tail = new;
		new->next = NULL;
		new->prev = NULL;
		return;
		
	}
	
	else
	{
		
		tail->next = new;
		new->prev = tail;
		tail = new;
		return;
		
	}
}


void edit_patient()
{
	u8 ID_check[5], checker = 0, mode, gend;
	patient_t *tmp = head;
	
	printf("please enter patient ID to edit: ");
	scanf("%s", ID_check);
	tmp = str_check(ID_check);
	if (tmp)
	{
		while (1)
		{
			puts("[n] To edit name");
			puts("[a] To edit age");
			puts("[g] To edit gender {M -> male : F -> female}");
			puts("[q] To quit editing");
			printf("Enter editing mode: ");
			scanf(" %c",&mode);
			switch (mode)
			{
				case 'n': printf("enter new name: "); scanf("%s", tmp->name); break;
				case 'a': printf("enter new age: "); scanf("%d", &(tmp->age)); break;
				case 'g': printf("enter new gender: "); scanf(" %c", &gend);
							switch (gend)
							{
								case 'M':
									tmp->gender = 0;
									break;
								case 'F':
									tmp->gender = 1;
									break;
							}
							break;
				case 'q': puts("quitting mode"); return;
			}
			puts("----------------------------------------");
		}
	}
	else
	{
		puts("ID Entered not found");
		puts("Exiting mode ...");
	}
}

void rev_spot(rev *list)
{
	u8 i = 0, selection, check = 0;
	u8 *ID_pat = (u8 *)malloc(sizeof(u8) * 5);
	patient_t *pat_ptr = (patient_t *)malloc(sizeof(patient_t));
	
	while (1)
	{
		if (!(list[check].pat_rev))
			break;
		check++;
		if (check >= 5)
		{
			puts("No more reservations available");
			puts("exiting mode ...");
			return;
		}
	}
	
	puts("Available reservation time:");
	while (list[i].time)
	{
		if (!(list[i].pat_rev))
			printf("[%d] At time: %s\n",(i + 1) , list[i].time);
		i++;
	}
	puts("Selection between [1] to [5]");
	printf("time selected: ");
	scanf("%d", &selection);
	if (selection < 1 || selection > 5)
	{
		puts("Invalid selection");
		puts("exiting mode ...");
		return;
	}
		
	printf("Enter patient ID to reserve: ");
	scanf("%s", ID_pat);
	pat_ptr = str_check(ID_pat);
	
	if(!(pat_ptr))
	{
		puts("ID not found");
		puts("Exiting mode");
		return;
	}
	
	else
	{
		puts("ID found");
		printf("Patient {%s} is reserved at time {%s}\n", pat_ptr->name, list[selection - 1].time);
		list[selection - 1].pat_rev = pat_ptr;
		
	}
}

void cancel_rev(rev *list)
{
	u8 i = 0, *ID_pat = (u8 *)malloc(sizeof(u8) * 5);
	patient_t *pat_ptr;
	
	printf("Enter patient ID: ");
	scanf("%s", ID_pat);
	pat_ptr = str_check(ID_pat);
	if (!(pat_ptr))
	{
		puts("ID not found");
		puts("exiting mode");
		return;
	}
	
	while (list[i].time)
	{
		if (list[i].pat_rev == pat_ptr)
		{
			printf("Removing patient %s from reserved time %s\n", pat_ptr->name, list[i].time);
			list[i].pat_rev = NULL;
			return;
		}
		i++;
	}
	puts("patient is not reserved in any time");
	puts("exiting mode");
}

void view_record(patient_t *h)
{
	patient_t *tmp = h;
	u8 i = 1;
	
	printf("Patients recorded [%d]\n", list_count());
	
	while (tmp)
	{
		printf("patient no. %d:\n", i);
		printf("\tpatient's ID: %s\n", tmp->ID);
		printf("\tpatient's name: %s\n", tmp->name);
		printf("\tpatient's age: %d\n",tmp->age);
		if (tmp->gender == 0)
			printf("\tpatient's gender: Male\n");
		else
			printf("\tpatient's gender: Female\n");
		tmp = tmp->next;
		i++;
	}
}

void today_rev(rev *list)
{
	u8 i = 0;
	
	while (list[i].time)
	{
		if (list[i].pat_rev)
			printf("Reservation at time %s\t|\t OCCUPIED by {%s}\n", list[i].time, list[i].pat_rev->ID);
		else
			printf("Reservation at time %s\t|\t UNOCCUPIED\n", list[i].time);
		i++;
	}
}