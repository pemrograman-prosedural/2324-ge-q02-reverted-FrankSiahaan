// 12S23016 - Frank Niroy Siahaan
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"

int main(int _argc, char **_argv)
{
    struct student_t *students = malloc(50 * sizeof(struct student_t));
    struct dorm_t *dorms = malloc(50 * sizeof(struct dorm_t));
    char cmd[255];
    char id[12];
    char name[40];
    char year[5];
    char names[200];
    char *token;
    unsigned short capacity;
    int i = 0; 
    int j = 0;
    int student_index = -1;
    int dorm_index = -1;
    int oldindex = -1;
    char names1[200];
    

    while (1)
    {
        fgets(cmd, sizeof(cmd), stdin);
        
      
        if (cmd[strlen(cmd) - 1] == '\n' || cmd[strlen(cmd) - 1] == '\r')
        {
            cmd[strlen(cmd) - 1] = '\0';
        }

        if (strcmp(cmd, "---") == 0)
        {
            break;
        }
        else
        {
            token = strtok(cmd, "#");
            if (strcmp(token, "student-add") == 0)
            {
                token = strtok(NULL, "#");
                strcpy(id, token);

                token = strtok(NULL, "#");
                strcpy(name, token);

                token = strtok(NULL, "#");
                strcpy(year, token);

                token = strtok(NULL, "#");
                if (strcmp(token, "male") == 0)
                {
                    students[i] = create_student(id, name, year, GENDER_MALE);
                }
                else if (strcmp(token, "female") == 0)
                {
                    students[i] = create_student(id, name, year, GENDER_FEMALE);
                }
                i++;
            }
            else if (strcmp(token, "student-print-all") == 0)
            {
                void (*pf) (struct student_t *student, int y);
                pf = print_student;
                pf(students, i);
            } 
            else if (strcmp(token, "student-print-all-detail") == 0) {
                void (*pf) (struct student_t *student, int y);
                pf = print_student_detail;
                pf(students, i);
            }
            else if (strcmp(token, "dorm-print-all-detail") == 0) {
                void (*pf) (struct dorm_t *dorm, int y);
                pf = print_dorm_detail;
                pf(dorms, j);
            }
            else if (strcmp(token, "dorm-add") == 0) {
                token = strtok(NULL, "#");
                strcpy(name, token);

                token = strtok(NULL, "#");
                capacity = atoi(token);

                token = strtok(NULL, "#");
                 if (strcmp(token, "male") == 0)
                {
                    dorms[j] = create_dorm(name, capacity, GENDER_MALE);
                }
                else if (strcmp(token, "female") == 0)
                {
                    dorms[j] = create_dorm(name, capacity, GENDER_FEMALE);
                }
                j++;
            }
            else if (strcmp(token, "dorm-print-all") == 0) {
                void (*pf) (struct dorm_t *dorm, int y);
                pf = print_dorm;
                pf(dorms, j);
            }
            else if (strcmp(token, "assign-student") == 0) {
                token = strtok(NULL, "#");
                strcpy(id, token);

                token = strtok(NULL, "#");
                strcpy(names, token);

                student_index = -1;
                dorm_index = -1;
                for (int s = 0; s < i; ++s)
                {
                    if (strcmp(students[s].id, id) == 0)
                    {
                        student_index = s; 
                        break;
                    }
                }   
                for (int d = 0; d < i; ++d)
                {
                    if (strcmp(dorms[d].name, names) == 0)
                    {
                        dorm_index = d;  
                        break;  
                    }
                }   
                assign_student(&students[student_index], &dorms[dorm_index], id, names, student_index, dorm_index);
            } else if (strcmp(token, "move-student") == 0) {
                token = strtok(NULL, "#");
                strcpy(id, token);

                token = strtok(NULL, "#");
                strcpy(names, token);

                for (int g = 0; g < i; g++)
                {
                    if (strcmp(id, students[g].id) == 0)
                    {
                        student_index = g;
                        break;
                    }
                }
                for (int d = 0; d < j; d++)
                {
                    if (strcmp(names, dorms[d].name) == 0)
                    {
                        dorm_index = d;
                        break;
                    }
                }
                if (students[student_index].dorm == NULL)
                {
                    assign_student(&students[student_index], &dorms[dorm_index], id, names, student_index, dorm_index);
                } else if (dorm_index != -1)
                {
                        for (int c = 0; c < j; c++)
                        {
                        if (strcmp(students[student_index].dorm->name, dorms[c].name) == 0)
                        {
                            oldindex = c;
                            break;
                        }
                        }
                        move_student(students, dorms, dorm_index, oldindex, student_index);
                   
                }
            } else if (strcmp(token, "dorm-empty") == 0) {
               token = strtok(NULL, "#");
                strcpy(names1, token);

                for (int x = 0; x < j; x++) {
                    if (strcmp(names1 ,dorms[x].name) == 0) {
                        dorm_index = x;
                        dorm_empty(students, dorms, i, j, names1);
                        break;
                    }
                }
            }
        }
    }

    free(students);
    free(dorms);
    return 0;
}
