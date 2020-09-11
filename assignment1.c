/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Harrison Crowe-Maxwell
 * Student ID: 13542004
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 * 
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database.txt"
#define MAX_CHAR 1000

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/

struct date_time {
    int month, day, hour, minute;
};
typedef struct date_time date_time_t;

struct flight {
    char flightcode[MAX_FLIGHTCODE_LEN+1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN+1];
    date_time_t arrival_dt;
};
typedef struct flight flight_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void print_menu(void);
int check_flight_code_char(char c, int f2);
int check_departure(int date[4]);
int check_city_code(char c[MAX_CITYCODE_LEN+1]);
int add_flight(int total_flights);
void display_destination_flights(int total_flights);
void save_flights(int total_flights);
void create_flight_instance(char c[50], int total_flights);
int reset_flights(int total_flights);
int load_flights(int total_flights);

/*******************************************************************************
 * Main
 Gets user input and uses a switch case to determine and route to the option chosen
*******************************************************************************/
flight_t flights[MAX_NUM_FLIGHTS];


int main(void) {
    char i;
    int run = 1, input, total_flights = 0; 

    while (run==1) {
        print_menu();
        scanf(" %c", &i);
        input = i - '0';
        switch(input) {
            case 1: 
                if (total_flights<MAX_NUM_FLIGHTS) {
                    total_flights = add_flight(total_flights);
                } else {
                    printf("Cannot add more flights - memory full\n");
                }
                break;
            case 2:
                display_destination_flights(total_flights);
                break;
            case 3:
                save_flights(total_flights);
                break;
            case 4:
                total_flights = load_flights(total_flights);
                break;
            case 5:
                run = 0;
                break;
            default:
                input = 0;
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}

/*******************************************************************************
 * 

*******************************************************************************/
int check_flight_code_char(char c, int f2) {
    int valid = 0;
    int test = (int)c;
    if (f2 == 1) {
        if (test>40 && test<91) {
            valid = 1;
        }
    } else {
        if (test>47 && test<58) {
            valid = 1;
        }
    }
    return valid;
}
/*******************************************************************************
 * 

*******************************************************************************/
int check_departure(int date[4]) {
    int valid = 0;
    if (date[0]>0 && date[0]<13) {
        valid++;
    }
    if (date[1]>0 && date[1]<32) {
        valid++;
    }
    if (date[2]>0 && date[2]<24) {
        valid++;
    }
    if (date[3]>0 && date[3]<60) {
        valid++;
    }
    if (valid >= 4) {
        return 1;
    }
    return 0;
}
/*******************************************************************************
 * 

*******************************************************************************/
int check_city_code(char c[MAX_CITYCODE_LEN+1]) {
    int i, test, valid = 0;
    if (strlen(c)<=MAX_CITYCODE_LEN) {
        for (i=0; i<MAX_CITYCODE_LEN; i++) {
            test = (int)c[i];
            if (test>40 && test<91) {
                valid++;
            }
        }
    }
    if (valid >= 3) {
        return 1;
    }
    return 0;
}
/*******************************************************************************
 * 

*******************************************************************************/
int add_flight(int total_flights) {
    char fc[MAX_FLIGHTCODE_LEN+1]; int valid = 0, check =0, first_2;
    int i, valid_count, length; char temp; int date[4]; flight_t added_flight;
    char city_code[MAX_CITYCODE_LEN+1];

    while (valid==0) {
        valid_count = 0; first_2 = 0;
        printf("Enter flight code>\n");
        scanf("%s", fc);
        length = strlen(fc);
        if (length>2 && length<MAX_FLIGHTCODE_LEN+1) {
            for (i=0; i<length; i++) {
                first_2 = 0;
                temp = fc[i];
                if (i>1) {
                    first_2 = 0;
                } else {
                    first_2 = 1;
                }
                check = check_flight_code_char(temp, first_2);
                if (check == 1) {
                    valid_count++;
                }
            }
        }
        if (valid_count >= length) {
            valid = 1;
        } else {
            printf("Invalid flight code\n");
        }
    }
    memcpy(added_flight.flightcode, fc, MAX_FLIGHTCODE_LEN+1);

    printf("Enter departure info for the flight leaving SYD.\n");
    valid = 0;
    while (valid==0) {
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d", &date[0], &date[1], &date[2], &date[3]);
        check = check_departure(date);
        if (check == 1) {
            valid = 1;
        } else {
            printf("Invalid input\n");
        }
    }
    added_flight.departure_dt.month = date[0];
    added_flight.departure_dt.day = date[1];
    added_flight.departure_dt.hour = date[2];
    added_flight.departure_dt.minute = date[3];

    valid = 0;
    while (valid==0) {
        printf("Enter arrival city code>\n");
        scanf("%s", city_code);
        check = check_city_code(city_code);
        if (check == 1) {
            valid = 1;
        } else {
            printf("Invalid input\n");
        }
    }
    memcpy(added_flight.arrival_city, city_code, MAX_CITYCODE_LEN+1);

    printf("Enter arrival info.\n");
    valid = 0;
    while (valid==0) {
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d", &date[0], &date[1], &date[2], &date[3]);
        check = check_departure(date);
        if (check == 1) {
            valid = 1;
        } else {
            printf("Invalid input\n");
        }
    }
    added_flight.arrival_dt.month = date[0];
    added_flight.arrival_dt.day = date[1];
    added_flight.arrival_dt.hour = date[2];
    added_flight.arrival_dt.minute = date[3];

    flights[total_flights] = added_flight;
    total_flights = total_flights+1;

    return total_flights;

}
/*******************************************************************************
 * 

*******************************************************************************/
void display_destination_flights(int total_flights) {
    int i;
    printf("Flight Origin          Destination\n");
    printf("------ --------------- ---------------\n");
    for (i=0; i<total_flights; i++) {
        printf("%s    SYD %02d-%02d %02d:%02d %.3s %02d-%02d %02d:%02d\n",
        flights[i].flightcode, flights[i].departure_dt.month, flights[i].departure_dt.day,
        flights[i].departure_dt.hour, flights[i].departure_dt.minute, flights[i].arrival_city,
        flights[i].arrival_dt.month, flights[i].arrival_dt.day, flights[i].arrival_dt.hour, 
        flights[i].arrival_dt.minute);
    }
}
/*******************************************************************************
 * 

*******************************************************************************/
void save_flights(int total_flights) {
    FILE *fptr; int i;
    fptr = fopen(DB_NAME, "w");
    if (fptr != NULL) {
        for (i=0; i<total_flights; i++) {
            fprintf(fptr, "%s %d %d %d %d %.3s %d %d %d %d*",
            flights[i].flightcode, flights[i].departure_dt.month, flights[i].departure_dt.day,
            flights[i].departure_dt.hour, flights[i].departure_dt.minute, flights[i].arrival_city,
            flights[i].arrival_dt.month, flights[i].arrival_dt.day, flights[i].arrival_dt.hour, 
            flights[i].arrival_dt.minute);
        }
    }
    fclose(fptr);
}
/*******************************************************************************
 * 

*******************************************************************************/
void create_flight_instance(char c[50], int total_flights) {
    int i = total_flights; flight_t create_flight;
    int dmo, dd, dh, dmi, amo, ad, ah, ami;
    char create[50], temp_fc[MAX_FLIGHTCODE_LEN+1], temp_dest[MAX_CITYCODE_LEN+1];
    strcpy(create, c);
    sscanf(create, "%s %d %d %d %d %s %d %d %d %d", temp_fc, 
    &dmo, &dd, &dh, &dmi, temp_dest, &amo, &ad, &ah, &ami);

    memcpy(create_flight.flightcode, temp_fc, MAX_FLIGHTCODE_LEN+1);
    memcpy(create_flight.arrival_city, temp_dest, MAX_CITYCODE_LEN+1);

    create_flight.departure_dt.month = dmo;
    create_flight.departure_dt.day = dd;
    create_flight.departure_dt.hour = dh;
    create_flight.departure_dt.minute = dmi;

    create_flight.arrival_dt.month = amo;
    create_flight.arrival_dt.day = ad;
    create_flight.arrival_dt.hour = ah;
    create_flight.arrival_dt.minute = ami;

    flights[i] = create_flight;
}

int reset_flights(int total_flights) {
    flight_t reset[MAX_NUM_FLIGHTS];
    memcpy(reset[0].flightcode, "AA0", MAX_FLIGHTCODE_LEN+1);
    memcpy(flights, reset, sizeof(reset));
    return 0;
}

/*******************************************************************************
 * 

*******************************************************************************/
int load_flights(int total_flights) {
    total_flights = reset_flights(total_flights);
    char c[MAX_CHAR] = " ", b[MAX_CHAR];
    FILE *fptr;
    fptr = fopen(DB_NAME, "r");
    if (fptr != NULL) {
        while (fgets(b, MAX_CHAR, fptr) != NULL) {
            strcat(c, b);
        }
    }
    fclose(fptr);
    char * set = strtok(c, "*");
    while (set != NULL) {
        if (strstr(set, "0") != NULL || strstr(set, "1") != NULL ||
        strstr(set, "2") != NULL || strstr(set, "3") != NULL || strstr(set, "4") != NULL ||
        strstr(set, "5") != NULL || strstr(set, "6") != NULL || strstr(set, "7") != NULL ||
        strstr(set, "8") != NULL || strstr(set, "0") != NULL) {
            create_flight_instance(set, total_flights);
            total_flights++;
        }
        set = strtok(NULL, "*");
    }
    return total_flights;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu(void) {
    printf("\n"
    "1. add a flight\n"
    "2. display all flights to a destination\n"
    "3. save the flights to the database file\n"
    "4. load the flights from the database file\n"
    "5. exit the program\n"
    "Enter choice (number between 1-5)>\n");
}