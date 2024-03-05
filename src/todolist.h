// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// The root object that holds all data for 371todo. This
// class contains Projects, which in turn hold Tasks,
// which have a name, due date, completed status, and tags.
// -----------------------------------------------------

#ifndef TODOLIST_H
#define TODOLIST_H

#include "project.h"

class TodoList
{
private:
    std::vector<Project> todoList;

public:
    TodoList();
    unsigned int size() const;
    Project newProject(std::string projectIdent);
    bool addProject(Project project);
    Project getProject(std::string projectIdent) const;
    bool deleteProject(std::string projectIdent);
    bool load(std::string filename);
    bool save(std::string filename);
    friend bool operator==(const TodoList &c1, const TodoList &c2);
    std::string str() const;
};

#endif // TODOLIST_H
