#ifndef HELPY_H
#define HELPY_H

#include "Student.h"
#include "UC.h"
#include "Class.h"
#include "Schedule.h"
#include "Request.h"
#include <queue>

class Helpy {
    private:
        vector<Student>& all_students;
        vector<UC>& all_UCs;
        vector<Class>& all_classes;

        // informação do horário
        map<string, list<Block>>& class_blocks,
                                  uc_blocks;

        // mapas usados para processar comandos
        static map<string, int> command, target, what;

        // fila para guardar pedidos
        queue<Request> queuer; 
               
    public:
        // constructor
        Helpy(vector<Student>& students, vector<UC>& UCs, vector<Class>& classes,
              map<string, list<Block>>& c_blocks, map<string, list<Block>>& u_blocks);

        // methods
        void terminal();
        void advanced_mode();
        void guided_mode();

        void processQueue();
        void rewrite_file();
        void log(Request r, string s);
        
        void display_uc_schedule() const;
        void display_uc_classes() const;
        void display_uc_students() const;

        void display_class_schedule() const;
        void display_class_students() const;

        void display_student_schedule() const;
        void display_student_classes() const;
        void display_student_ucs() const;
        
        void display_all_classes() const;
        void display_all_ucs() const;
        void display_all_students() const;

        void add(Request sub);
        void rem(Request sub);
        void change(Request sub);
        string is_valid(Student s, Class& cl, string uc);
        string is_valid_change(Student s, Schedule schedule_, Class& c, set<string> student_ucs);
};

#endif