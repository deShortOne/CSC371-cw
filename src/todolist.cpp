// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
#include <fstream>
#include <iostream>
#include <sstream>

#include "lib_json.hpp"
#include "todolist.h"

using namespace nlohmann; // TODO!!! using namespace for json::parse in save()

// TODO Write a TodoList constructor that takes no parameters and constructs an
//  empty todolist.
//
// Example:
//  TodoList tObj{};
TodoList::TodoList() : todoList(std::vector<Project>()) {}
// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of projects the TodoList contains.
//
// Example:
//  TodoList tObj{};
//  auto size = tObj.size();
unsigned int TodoList::size() const
{
    return this->todoList.size();
}
// TODO Write a function, newProject, that takes one parameter, a project
//  identifier, and returns the Project object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Project object cannot be
//  inserted into the container.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
Project TodoList::newProject(std::string projectIdent)
{
    for (const Project &i : todoList)
    {
        if (!i.getIdent().compare(projectIdent))
        {
            return i;
        }
    }

    Project newProj{projectIdent};
    this->todoList.push_back(newProj);
    return this->todoList[todoList.size() - 1];
}
// TODO Write a function, addProject, that takes one parameter, a Project
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged (see also Project::addTask) and then return false. Throw a
//  std::runtime_error if the Project object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  TodoList tObj{};
//  Project cObj{"projectIdent"};
//  tObj.addProject(cObj);
bool TodoList::addProject(Project project)
{
    for (Project &i : this->todoList)
    {
        if (!i.getIdent().compare(project.getIdent()))
        {
            // for (const Task &j : project.getTasks())
            // {
            //     i.addTask(j);
            // }
            return false;
        }
    }

    this->todoList.push_back(project);
    return true;
}
// TODO Write a function, getProject, that takes one parameter, a Project
//  identifier and returns the Project. If no Project exists, throw an
//  appropriate exception.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
//  auto cObj = tObj.getProject("projectIdent");
Project TodoList::getProject(std::string projectIdent) const
{
    for (const Project &i : this->todoList)
    {
        if (i.getIdent().compare(projectIdent) == 0)
        {
            return i;
        }
    }
    throw std::out_of_range("That project doesn't exist!");
}
// TODO Write a function, deleteProject, that takes one parameter, a Project
//  identifier, and deletes it from the container, and returns true if the
//  Project was deleted. If no Project exists, throw an appropriate exception.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
//  tObj.deleteProject("projectIdent");
bool TodoList::deleteProject(std::string projectIdent)
{
    for (unsigned int i = 0; i < this->todoList.size(); i++)
    {
        if (!this->todoList[i].getIdent().compare(projectIdent))
        {
            this->todoList.erase(this->todoList.begin() + i);
            return true;
        }
    }
    throw std::out_of_range("That project doesn't exist!");
}
// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this TodoList. If the file does open throw
//  an appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two projects with the same key, the projects should be
//  merged (not replaced!). If you encounter two tasks with the same identifier
//  in the same project, only the tags of the tasks should be merged; it is undefined
//  as to which values are picked for the completed status and due date (pick either).
//  Two tasks in different projects can have the same key.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
// {
//     "Project 1" : {
//         "Task 1":  {
//             "completed": true,
//             "due": "2024-11-23",
//             "tags" : ["uni",
//                       "c++",
//                       "programming",
//                       "standard library"
//                       ...
//                      ]
//             ...
//         },
//         "Task 2":  {
//             "completed": false,
//             "tags" : ["uni",
//                       "c++",
//                       "programming",
//                       "inheritance"
//                       ...
//                      ]
//         },
//         ...
//     },
//     "Project 2": {
//         "Task 1": {
//             "completed": true
//         }
//         ...
//     }
// }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Project and Task objects according
//  to the JSON data in the file.
//
// Example:
//  TodoList tObj{};
//  tObj.load("database.json");
bool TodoList::load(std::string filename)
{
    using json = nlohmann::json;
    std::ifstream f(filename);
    json data = json::parse(f);

    for (json::iterator project_iter = data.begin(); project_iter != data.end(); ++project_iter)
    {
        Project newProject{project_iter.key()};
        auto taskList = project_iter.value();

        for (auto task = taskList.begin(); task != taskList.end(); ++task)
        {
            Task newTask{task.key()};

            auto taskValues = task.value();
            if (taskValues.contains("completed"))
            {
                newTask.setComplete(taskValues["completed"].dump().compare("false"));
            }
            if (taskValues.contains("dueDate"))
            {
                std::string jsonToDate = taskValues["dueDate"].dump();
                std::string dateArgs = jsonToDate.substr(1, jsonToDate.length() - 2);
                Date date{};
                date.setDateFromString(dateArgs);
                newTask.setDueDate(date);
            }
            if (taskValues.contains("tags"))
            {
                auto tagLis = taskValues["tags"];
                for (auto tag = tagLis.begin(); tag != tagLis.end(); ++tag)
                {
                    std::string tagName = (*tag).dump();
                    newTask.addTag(tagName.substr(1, tagName.size() - 2));
                }
            }
            newProject.addTask(newTask);
        }
        this->todoList.push_back(newProject); // TODO!!!! Don't like how we have to add at the end
    }
    return false;
}
// TODO Write a function, save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the TodoList object
//  as JSON.
//
// Example:
//  TodoList tObj{};
//  tObj.load("database.json");
//  ...
//  tObj.save("database.json");
bool TodoList::save(std::string filename)
{
    auto jsonToSave = json::parse(this->str());

    std::ofstream myFile;
    myFile.open(filename, std::ios_base::out);
    if (!myFile.is_open())
    {
        throw std::exception();
    }
    myFile << jsonToSave;
    myFile.close();
    return true;
}
// TODO Write an == operator overload for the TodoList class, such that two
//  TodoList objects are equal only if they have the exact same data.
//
// Example:
//  TodoList tObj1{};
//  TodoList tObj2{};
//  if(tObj1 == tObj2) {
//    ...
//  }
// NOT IMPLEMENTED!
bool operator==(const TodoList &c1, const TodoList &c2)
{
    return false;
}
// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the TodoList.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  TodoList tObj{};
//  std::string s = tObj.str();
std::string TodoList::str() const
{
    if (todoList.empty())
    {
        return "{}";
    }
    std::stringstream ss;
    ss << "{";
    for (const Project &project : todoList)
    {
        ss << project.str()
           << ",";
    }
    ss.seekp(-1, ss.cur); // remove last ,

    ss << "}";
    return ss.str();
}
