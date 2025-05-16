#define MAX_TUTORS 10
#define MAX_SESSIONS 10
#define MAX_STUDENTS 100

struct tutor {
    char code[10];         // Tutor code
    char name[50];         // Tutor name
    char password[20];     // Tutor password
};

struct session {
    char code[10];             // Session code
    char title[50];            // Session title
    char day[20];              // Session day
    char start_time[20];       // Session start time
    char location[50];         // Session location
    char tutor_code[10];       // Tutor code associated with the session
};

struct student {
    char tp_number[20];         // Student TP number
    char name[50];              // Student name
    char password[20];          // Student password
    char session_title[50];     // Title of the session the student is attending
};

