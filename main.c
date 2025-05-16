#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_header.h"
#include "menus.c"
#include "file_data_handler.c"

void register_tutor(struct tutor *tutors, int *tutor_count) {
    if ((*tutor_count) == MAX_TUTORS) {
        printf("Maximum tutor limit reached.\n");
        return;
    }

    printf("Enter tutor code: ");
    scanf("%s", tutors[*tutor_count].code);

    printf("Enter tutor name: ");
    scanf(" %[^\n]", tutors[*tutor_count].name);

    printf("Enter tutor password: ");
    scanf("%s", tutors[*tutor_count].password);

    (*tutor_count)++;
    printf("Tutor registered successfully.\n");
}

void add_session(struct session *sessions, int *session_count, struct tutor *tutors, int tutor_count) {
    if ((*session_count) == MAX_SESSIONS) {
        printf("Maximum session limit reached.\n");
        return;
    }

    printf("Enter session code: ");
    scanf("%s", sessions[*session_count].code);

    printf("Enter session title: ");
    scanf(" %[^\n]", sessions[*session_count].title);

    printf("Enter session day: ");
    scanf(" %[^\n]", sessions[*session_count].day);

    printf("Enter session start time: ");
    scanf(" %[^\n]", sessions[*session_count].start_time);

    printf("Enter session location: ");
    scanf(" %[^\n]", sessions[*session_count].location);

    printf("Enter tutor code for the session: ");
    scanf("%s", sessions[*session_count].tutor_code);

    int tutor_found = 0;
    for (int i = 0; i < *session_count; i++) {
        if (strcmp(sessions[i].tutor_code, sessions[*session_count].tutor_code) == 0) {
            printf("Tutor already assigned to another session. Session not added.\n");
            return;
        }
    }

    for (int i = 0; i < tutor_count; i++) {
        if (strcmp(tutors[i].code, sessions[*session_count].tutor_code) == 0) {
            tutor_found = 1;
            break;
        }
    }
    if (!tutor_found) {
        printf("Tutor with code %s does not exist.\n", sessions[*session_count].tutor_code);
        return;
    }

    (*session_count)++;
    printf("Session added successfully.\n");
}

void register_student(struct student *students, int *student_count) {
    if ((*student_count) == MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }

    printf("Enter TP number: ");
    scanf("%s", students[*student_count].tp_number);

    printf("Enter student name: ");
    scanf(" %[^\n]", students[*student_count].name);

    printf("Enter student password: ");
    scanf("%s", students[*student_count].password);
    strcpy(students[*student_count].session_title, "NotAssigned");

    (*student_count)++;
    printf("Student registered successfully.\n");
}

void enroll_student(struct student *students, int student_count, struct session *sessions, int session_count) {
    if (student_count == 0) {
        printf("No students registered.\n");
        return;
    }
    if (session_count == 0) {
        printf("No sessions available.\n");
        return;
    }

    printf("Enter TP number of the student: ");
    char tp_number[20];
    scanf("%s", tp_number);

    int student_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].tp_number, tp_number) == 0) {
            student_index = i;
            break;
        }
    }
    if (student_index == -1) {
        printf("Student with TP number %s not found.\n", tp_number);
        return;
    }

    printf("Available sessions:\n");
    for (int i = 0; i < session_count; i++) {
        printf("%d. %s\n", i + 1, sessions[i].title);
    }

    printf("Enter the session number to enroll in: ");
    int session_number;
    scanf("%d", &session_number);

    if (session_number < 1 || session_number > session_count) {
        printf("Invalid session number.\n");
        return;
    }

    strcpy(students[student_index].session_title, sessions[session_number - 1].title);
    printf("Student enrolled successfully.\n");
}

void list_sessions_and_students(struct session *sessions, int session_count, struct student *students, int student_count, char session_tutor[]) {
    int found_matching_session = 0;
    if (session_count == 0) {
        printf("No sessions available.\n");
        return;
    }

    printf("Sessions:\n");
    for (int i = 0; i < session_count; i++) {
        if (strcmp(sessions[i].tutor_code, session_tutor) == 0) {
            found_matching_session = 1; // Set the flag to indicate a matching session is found

            printf("Session Code: %s\n", sessions[i].code);
            printf("Location: %s\n", sessions[i].location);
            printf("Tutor Code: %s\n", sessions[i].tutor_code);

            printf("Students enrolled:\n");
            int count = 0;
            for (int j = 0; j < student_count; j++) {
                if (strcmp(students[j].session_title, sessions[i].title) == 0) {
                    printf("- %s\n", students[j].name);
                    count++;
                }
            }

            if (count == 0) {
                printf("No students enrolled.\n");
            }
            printf("\n");
        }
    }

    if (!found_matching_session) {
        for (int i = 0; i < session_count; i++) {
            printf("Session Code: %s\n", sessions[i].code);
            printf("Location: %s\n", sessions[i].location);
            printf("Tutor Code: %s\n", sessions[i].tutor_code);

            printf("Students enrolled:\n");
            int count = 0;
            for (int j = 0; j < student_count; j++) {
                if (strcmp(students[j].session_title, sessions[i].title) == 0) {
                    printf("- %s\n", students[j].name);
                    count++;
                }
            }

            if (count == 0) {
                printf("No students enrolled.\n");
            }
            printf("\n");
        }
    }
}

void change_admin_password(char *admin_password) {
    printf("Enter current admin password: ");
    char current_password[20];
    scanf("%s", current_password);

    if (strcmp(admin_password, current_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new admin password: ");
    scanf("%s", admin_password);

    FILE *password_file = fopen("admin_password.txt", "w");
    if (password_file == NULL) {
        printf("Error opening file: admin_password.txt\n");
        return;
    }
    fprintf(password_file, "%s\n", admin_password);
    fclose(password_file);

    printf("Admin password changed successfully.\n");
}

int main() {
    struct tutor tutors[MAX_TUTORS];
    int tutor_count = 0;

    struct session sessions[MAX_SESSIONS];
    int session_count = 0;

    struct student students[MAX_STUDENTS];
    int student_count = 0;

    char admin_password[20];
    FILE *password_file = fopen("admin_password.txt", "r");
    if (password_file == NULL) {
        printf("Error opening file: admin_password.txt\n");
        return 1;
    }
    fscanf(password_file, "%[^\n]", admin_password);
    fclose(password_file);

    char session_tutor[20] = "None";

    load_data(tutors, &tutor_count, sessions, &session_count, students, &student_count);

    int user_type;
    printf("Choose user type:\n");

    printf("1. Admin\n");

    printf("2. Tutor\n");

    printf("3. Student\n");

    printf("4. Exit\n");
    
    printf("Enter user type: ");
    scanf("%d", &user_type);

    while (user_type != 4) {
        switch (user_type) {
            case 1: {
                printf("Enter admin password: ");
                char password[20];
                scanf("%s", password);

                if (strcmp(password, admin_password) == 0) {
                    int admin_choice;
                    do {
                        admin_menu();
                        printf("Enter your choice: ");
                        scanf("%d", &admin_choice);

                        switch (admin_choice) {
                            case 1:
                                register_tutor(tutors, &tutor_count);
                                break;
                            case 2:
                                add_session(sessions, &session_count, tutors, tutor_count);
                                break;
                            case 3:
                                register_student(students, &student_count);
                                break;
                            case 4:
                                enroll_student(students, student_count, sessions, session_count);
                                break;
                            case 5:
                                list_sessions_and_students(sessions, session_count, students, student_count, session_tutor);
                                break;
                            case 6:
                                change_admin_password(admin_password);
                                break;
                            case 7:
                                save_data(tutors, tutor_count, sessions, session_count, students, student_count);
                                printf("Exiting...\n");
                                break;
                            default:
                                printf("Invalid choice.\n");
                                break;
                        }
                    } while (admin_choice != 7);
                } else {
                    printf("Incorrect admin password.\n");
                }

                break;
            }
            case 2: {
                printf("Enter tutor code: ");
                char tutor_code[10];
                scanf("%s", tutor_code);
                printf("Enter tutor password: ");
                char tutor_password[20];
                scanf("%s", tutor_password);

                int tutor_index = -1;
                for (int i = 0; i < tutor_count; i++) {
                    if (strcmp(tutors[i].code, tutor_code) == 0 && strcmp(tutors[i].password, tutor_password) == 0) {
                        tutor_index = i;
                        break;
                    }
                }
                if (tutor_index == -1) {
                    printf("Tutor with code %s not found.\n", tutor_code);
                    break;
                }

                int tutor_choice;
                do {
                    tutor_menu();
                    printf("Enter your choice: ");
                    scanf("%d", &tutor_choice);

                    switch (tutor_choice) {
                        case 1:
                            list_sessions_and_students(sessions, session_count, students, student_count, tutor_code);
                            break;
                        case 2:
                            printf("Exiting...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                } while (tutor_choice != 2);

                break;
            }
            case 3: {
                printf("Enter TP number: ");
                char tp_number[20];
                scanf("%s", tp_number);
                printf("Enter student password: ");
                char student_password[20];
                scanf("%s", student_password);

                int student_index = -1;
                for (int i = 0; i < student_count; i++) {
                    if (strcmp(students[i].tp_number, tp_number) == 0 && strcmp(students[i].password, student_password) == 0) {
                        student_index = i;
                        break;
                    }
                }
                if (student_index == -1) {
                    printf("Student with TP number %s not found.\n", tp_number);
                    break;
                }

                int student_choice;
                do {
                    student_menu();
                    printf("Enter your choice: ");
                    scanf("%d", &student_choice);

                    switch (student_choice) {
                        case 1:
                            list_sessions_and_students(sessions, session_count, students, student_count, session_tutor);
                            break;
                        case 2:
                            enroll_student(students, student_count, sessions, session_count);
                            break;
                        case 3:
                            printf("Exiting...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                } while (student_choice != 3);

                break;
            }
            default:
                printf("Invalid user type.\n");
                break;
        }

        printf("\nChoose user type:\n");
        printf("\n");
        printf("1. Admin\n");
        printf("\n");
        printf("2. Tutor\n");
        printf("\n");
        printf("3. Student\n");
        printf("\n");
        printf("4. Exit\n");
        printf("\n");
        printf("Enter user type: ");
        scanf("%d", &user_type);
    }

    save_data(tutors, tutor_count, sessions, session_count, students, student_count);
    printf("Exiting...\n");

    return 0;
}
