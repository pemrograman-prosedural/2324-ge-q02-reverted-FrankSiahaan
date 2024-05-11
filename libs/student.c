#include "student.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */
struct student_t create_student(char *_id, char *_name, char *_year, enum gender_t _gender)
{
  struct student_t std;
  strcpy(std.id, _id);
  strcpy(std.name, _name);
  strcpy(std.year, _year);
  std.gender = _gender;
  std.dorm = NULL;

  return std;
}

void print_student(struct student_t *_student, int jumlah)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (_student[i].gender == 0)
        {
            printf("%s|%s|%s|male\n", _student[i].id, _student[i].name, _student[i].year);
        }else {
            printf("%s|%s|%s|female\n", _student[i].id, _student[i].name, _student[i].year);
        }
        
    }
}

void print_student_detail(struct student_t *_student, int jumlah){
    for (int i = 0; i < jumlah; i++)
    {
        if (_student[i].dorm == NULL)
        {
            if (_student[i].gender == 0)
        {
            printf("%s|%s|%s|male|unassigned\n", _student[i].id, _student[i].name, _student[i].year);
        }else {
            printf("%s|%s|%s|female|unassigned\n", _student[i].id, _student[i].name, _student[i].year);
        }
        }else {
            if (_student[i].gender == 0)
        {
            printf("%s|%s|%s|male|%s\n", _student[i].id, _student[i].name, _student[i].year, _student[i].dorm->name);
        }else {
            printf("%s|%s|%s|female|%s\n", _student[i].id, _student[i].name, _student[i].year, _student[i].dorm->name);
        }
        } 
    }
}

void assign_student(struct student_t *_student, struct dorm_t *_dorm, char *id, char *names) {
    if (_dorm->gender == _student->gender)
    {
        if (_dorm->capacity > _dorm->residents_num)
        {
            _student->dorm = _dorm;
            _dorm->residents_num++;
        } else {
            _student->dorm = NULL;
        }
        
    }
    
}

void move_student(struct student_t *_student, struct dorm_t *new_dorm ,struct dorm_t *old_dorm, int dorm_index, int oldindex, int student_index) {
  if (new_dorm->gender == _student->gender)
    {
        if (new_dorm->capacity > new_dorm->residents_num)
        {
            new_dorm[dorm_index].residents_num++;
            strcpy(_student[student_index].dorm->name, new_dorm->name);
            old_dorm[oldindex].residents_num--;
        }   
        
    }
}
void dorm_empty(struct student_t *_student, struct dorm_t *_dorm, int jumlah, char *names1, int student_index){
    for (int i = 0; i < student_index; i++)
    {
        strcpy(_student[i].dorm->name, "unassigned");
        _dorm[i].residents_num--;        
    }
    
}

