void load_data(struct tutor *tutors, int *tutor_count, struct session *sessions, int *session_count, struct student *students, int *student_count) {
    // Load tutors from file
    FILE *tutor_file = fopen("tutors.txt", "r");
    if (tutor_file == NULL) {
        printf("Error opening file: tutors.txt\n");
        return;
    }
    while ((*tutor_count) < MAX_TUTORS && fscanf(tutor_file, "%[^,],%[^,],%[^\n]\n", tutors[*tutor_count].code, tutors[*tutor_count].name, tutors[*tutor_count].password) == 3) {
        (*tutor_count)++;
    }
    fclose(tutor_file);

    // Load sessions from file
    FILE *session_file = fopen("sessions.txt", "r");
    if (session_file == NULL) {
        printf("Error opening file: sessions.txt\n");
        return;
    }
    while ((*session_count) < MAX_SESSIONS && fscanf(session_file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", sessions[*session_count].code, sessions[*session_count].title, sessions[*session_count].day, sessions[*session_count].start_time, sessions[*session_count].location, sessions[*session_count].tutor_code) == 6) {
        (*session_count)++;
    }
    fclose(session_file);

    // Load students from file
    FILE *student_file = fopen("students.txt", "r");
    if (student_file == NULL) {
        printf("Error opening file: students.txt\n");
        return;
    }
    while ((*student_count) < MAX_STUDENTS && fscanf(student_file, "%[^,],%[^,],%[^,],%[^\n]\n", students[*student_count].tp_number, students[*student_count].name, students[*student_count].password, students[*student_count].session_title) == 4) {
        (*student_count)++;
    }
    fclose(student_file);
}

void save_data(struct tutor *tutors, int tutor_count, struct session *sessions, int session_count, struct student *students, int student_count) {
    // Save tutors to file
    fclose(fopen("tutors.txt", "w"));

    FILE *tutor_file = fopen("tutors.txt", "a");
    if (tutor_file == NULL) {
        printf("Error opening file: tutors.txt\n");
        return;
    }
    for (int i = 0; i < tutor_count; i++) {
        fprintf(tutor_file, "%s,%s,%s\n", tutors[i].code, tutors[i].name, tutors[i].password);
    }
    fclose(tutor_file);

    // Save sessions to file
    fclose(fopen("sessions.txt", "w"));

    FILE *session_file = fopen("sessions.txt", "a");
    if (session_file == NULL) {
        printf("Error opening file: sessions.txt\n");
        return;
    }
    for (int i = 0; i < session_count; i++) {
        fprintf(session_file, "%s,%s,%s,%s,%s,%s\n", sessions[i].code, sessions[i].title, sessions[i].day, sessions[i].start_time, sessions[i].location, sessions[i].tutor_code);
    }
    fclose(session_file);

    // Save students to file
    fclose(fopen("students.txt", "w"));

    FILE *student_file = fopen("students.txt", "a");
    if (student_file == NULL) {
        printf("Error opening file: students.txt\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        fprintf(student_file, "%s,%s,%s,%s\n", students[i].tp_number, students[i].name, students[i].password, students[i].session_title);
    }
    fclose(student_file);
}