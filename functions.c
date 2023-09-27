#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "types.h"

extern patient_t *head;
extern patient_t *tail;
u8 _strlen(u8 *str)
{
	u8 count = 0;
	
	while (str[count])
		count++;
	
	return (count);
}

u8 str_num_check(u8 *str)
{
	u8 i = 0;
	if (str[i] != 'p')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
			continue;
		}
		else
			return (0);
	}
	
	return (1);
}

u8 list_count(void)
{
	u8 count = 0;
	patient_t *tmp = head;
	
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	
	return (count);
}

u8 str_sim(u8 *str)
{
	patient_t *tmp = head;
	u8 *tmp_str = NULL, i = 0;
	if (head == NULL && tail == NULL)
		return (0);
	while (tmp)
	{
		tmp_str = tmp->ID;
		while (tmp_str[i])
		{
			if (tmp_str[i] != str[i])
				return (0);
			i++;
		}
		tmp = tmp->next;
		i = 0;
	}
	return (1);
}

/**
 * modes - function that chooses mode type
 * Return: mode type.
 */

u8 modes(void)
{
	u8 tmp;
	
	puts("*****************************************************");
	puts("Please enter mode. [q] to exit the program");
	puts("Enter [a] for admin mode || Enter [u] for user mode");
	scanf(" %c",&tmp);
	puts("*****************************************************");
	return (tmp);
}

u8 actions(void)
{
	u8 tmp;
	
	puts("\tActions Available: ");
	puts("[a]: Add new patient record");
	puts("[e]: Edit patient record");
	puts("[r]: reserve a slot with doctor");
	puts("[c]: cancel reservation");
	puts("[q]: Exiting admin mode");
	printf("Enter action: ");
	scanf(" %c", &tmp);
	
	return (tmp);
}

patient_t *create(void)
{
	patient_t *new = (patient_t *)malloc(sizeof(patient_t));

	new->next = NULL;
	new->prev = NULL;
	return (new);
}

patient_t *str_check(u8 *str)
{
	u8 checker = 0, i = 0;
	patient_t *tmp = head;
	
	while (tmp && i < 5)
	{
		if (tmp->ID[i] == str[i])
		{
			checker++;
			i++;
			if (checker == 5)
				return (tmp);
			continue;
		}
		else
		{
			checker = 0;
			i = 0;
			tmp = tmp->next;
		}
		
		
	}
	return (NULL);
}
