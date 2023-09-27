#include "types.h"

#ifndef PATIENT_H
#define PATIENT_H

#define DEFAULT_PASSWORD 1234
#define ID_SIZE 5

#define sub(x, y) ((x) - (y))

/**
 * patient_t - patient basic information
 * @name: string to hold a name
 * @age: int to hold age number
 * @gender: boolean {0 for men and 1 for women}
 * @ID: string to hold ID number
 */
 
 typedef struct patient_s
 {
	 u8 name[20];
	 u8 age;
	 u8 gender : 1;
	 u8 *ID;
	 
	 struct patient_s *next;
	 struct patient_s *prev;
	 
 }patient_t;
 
 typedef struct reservation_p
 {
	 u8 *time;
	 
	 struct patient_s *pat_rev;
	 
 }rev;
 
 void intro(void) __attribute__((constructor));
 u8 modes(void);
 u8 actions(void);
 void add_patient(patient_t *node);
 void edit_patient();
 void view_record(patient_t *h);
 void today_rev(rev *list);
 void rev_spot(rev *list);
 void cancel_rev(rev *list);
 patient_t *create(void);
 u8 list_count(void);
 u8 str_sim(u8 *str);
 u8 _strlen(u8 *str);
 u8 str_num_check(u8 *str);
 patient_t *str_check(u8 *str);
 
#endif