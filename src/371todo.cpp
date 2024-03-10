// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "371todo.h"
#include "lib_cxxopts.hpp"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a TodoList object
//  2. Parse the 'action' argument to decide what action should be taken
//     (json, create, delete, update).  'json' is the easiest to implement, and
//     'update' is the hardest. The details of how these arguments work is in
//     the coursework specification.
//  3. Save the updated TodoList object to the JSON file if there have been
//     changes (calling save() on the TodoList object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[])
{
    auto options = App::cxxoptsSetup();
    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help"))
    {
        std::cout << options.help() << '\n';
        return 0;
    }

    // Open the database and construct the TodoList
    const std::string db = args["db"].as<std::string>();
    TodoList tlObj{};

    // Only uncomment this once you have implemented the load function!
    tlObj.load(db);

    try
    {
        validateArguments(args);
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << error.what();
        return 1;
    }

    const Action a = parseActionArgument(args);
    switch (a)
    {
    case Action::CREATE:
    {
        try
        {
            validateCreateArguments(args);
        }
        catch (const std::runtime_error &error)
        {
            std::cerr << error.what();
            return 1;
        }

        Project newProject{args["project"].as<std::string>()};
        if (args.count("task"))
        {
            Task task{args["task"].as<std::string>()};
            if (args.count("tag"))
            {
                std::string tagLis = args["tag"].as<std::string>();
                std::stringstream test(tagLis);
                std::string segment;
                while (std::getline(test, segment, ','))
                {
                    task.addTag(segment);
                }
            }

            if (args.count("due"))
            {
                Date date{args["due"].as<std::string>()};
                task.setDueDate(date);
            }
            if (args.count("completed"))
            {
                task.setComplete(true);
            }
            if (args.count("incomplete"))
            {
                task.setComplete(false);
            }
            newProject.addTask(task);
        }
        tlObj.addProject(newProject);

        tlObj.save(db);
        break;
    }
    case Action::JSON:
    {
        if (!args.count("project"))
        {
            std::cout << tlObj.str();
            break;
        }

        if (!tlObj.containsProject(args["project"].as<std::string>()))
        {
            std::cerr << "Error: invalid project argument(s).";
            return 1;
        }

        Project project = tlObj.getProject(args["project"].as<std::string>());
        if (!args.count("task"))
        {
            std::cout << project.str();
            break;
        }
        if (!project.containsTask(args["task"].as<std::string>()))
        {
            std::cerr << "Error: invalid task argument(s).";
            return 1;
        }

        Task task = project.getTask(args["task"].as<std::string>());
        if (!args.count("tag"))
        {
            std::cout << task.str();
            break;
        }
        if (!task.containsTag(args["tag"].as<std::string>()))
        {
            std::cerr << "Error: invalid tag argument(s).";
            return 1;
        }

        std::cout << args["tag"].as<std::string>();
        break;
    }
    case Action::UPDATE:
    {
        // Project
        if (!args.count("project"))
        {
            std::cerr << "Error: missing project argument(s).";
            break;
        }

        std::vector<std::string> projectSplit = splitString(args["project"].as<std::string>(), ':');
        if (projectSplit.size() > 2)
        {
            std::cerr << "Error: invalid project argument(s) - format to update project identifier is oldidentifier:newidentifier.";
            return 1;
        }

        if (!tlObj.containsProject(projectSplit[0]))
        {
            std::cerr << "Error: invalid project argument(s) - project not found.";
            return 1;
        }
        Project &project = tlObj.getProject(projectSplit[0]);
        if (projectSplit.size() == 2)
        {
            project.setIdent(projectSplit[1]);
        }

        // Task
        if (!args.count("task"))
        {
            if (args.count("due") || args.count("completed") || args.count("incomplete"))
            {
                std::cerr << "Error: missing task argument(s).";
                return 1;
            }
            break;
        }

        std::vector<std::string> taskSplit = splitString(args["task"].as<std::string>(), ':');
        if (taskSplit.size() > 2)
        {
            std::cerr << "Error: invalid task argument(s) - format to update task identifier is oldidentifier:newidentifier.";
            return 1;
        }

        if (!project.containsTask(taskSplit[0]))
        {
            std::cerr << "Error: invalid project argument(s) - project not found.";
            return 1;
        }
        Task &task = project.getTask(taskSplit[0]);
        if (taskSplit.size() == 2)
        {
            task.setIdent(taskSplit[1]);
        }

        if (args.count("due"))
        {
            Date date{args["due"].as<std::string>()};
            task.setDueDate(date);
        }
        if (args.count("completed"))
        {
            task.setComplete(true);
        }
        if (args.count("incomplete"))
        {
            task.setComplete(false);
        }

        tlObj.save(db);
        break;
    }
    case Action::DELETE:
    {
        if (!args.count("project"))
        {
            std::cerr << "Error: missing project argument(s).";
            return 1;
        }

        if (!tlObj.containsProject(args["project"].as<std::string>()))
        {
            std::cerr << "Error: invalid project argument(s) - project not found.";
            return 1;
        }
        if (!args.count("task"))
        {
            tlObj.deleteProject(args["project"].as<std::string>());
            tlObj.save(db);
            break;
        }

        Project &project = tlObj.getProject(args["project"].as<std::string>());
        if (!project.containsTask(args["task"].as<std::string>()))
        {
            std::cerr << "Error: invalid task argument(s) - task not found.";
            return 1;
        }
        if (!args.count("tag"))
        {
            project.deleteTask(args["task"].as<std::string>());
            tlObj.save(db);
            break;
        }

        Task &task = project.getTask(args["task"].as<std::string>());
        std::vector<std::string> tagLis = splitString(args["tag"].as<std::string>(), ',');

        for (const std::string &tag : tagLis)
        {
            task.deleteTag(tag);
        }
        tlObj.save(db);

        // TODO!!!!! remove multiple tags
        // std::string tagLis = args["tag"].as<std::string>();
        // std::stringstream test(tagLis);
        // std::string segment;
        // std::vector<std::string> seglist;
        // while (std::getline(test, segment, '_'))
        // {
        //     task.addTag(segment);
        // }
        break;
    }
    default:
        throw std::runtime_error("unknown action not implemented");
    }

    return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup()
{
    cxxopts::Options cxxopts("371todo", "Student ID: " + STUDENT_NUMBER + "\n");

    cxxopts.add_options()(
        "db", "Filename of the 371todo database",
        cxxopts::value<std::string>()->default_value("database.json"))(

        "action", "Action to take, can be: 'create', 'json', 'update', 'delete'.",
        cxxopts::value<std::string>())(

        "project",
        "Apply action (create, json, update, delete) to a project. If you want to "
        "add a project, set the action argument to 'create' and the project "
        "argument to your chosen project identifier.",
        cxxopts::value<std::string>())(

        "task",
        "Apply action (create, json, update, detele) to a task. If you want to add "
        "a task, set the action argument to 'create', the project argument to your "
        "chosen project identifier and the task argument to the task identifier).",

        cxxopts::value<std::string>())(

        "tag",
        "Apply action (create, json, delete) to a tag.  If you want to add an tag, "
        "set the action argument to 'create', the project argument to your chosen "
        "project identifier, the task argument to your chosen task identifier, and "
        "the tag argument to a single tag 'tag' or comma seperated list of tags: "
        "'tag1,tag2').  If you are simply retrieving a tag through the json action "
        "(and checking that it exists), set the tag argument to the tag name "
        "(e.g. 'example tag'). The action update is unsupported here.",
        cxxopts::value<std::string>())(

        "completed",
        "When creating or updating a task, set the completed flag to change the "
        "task's state to completed. This flag is not compatible in combination "
        "with the incomplete flag.",
        cxxopts::value<bool>())(

        "incomplete",
        "When creating or updating a task, set the incomplete flag to change the "
        "task's state to incomplete. This flag is not compatible in combination "
        "with the completed flag",
        cxxopts::value<bool>())(

        "due",
        "When creating or updating a task, set the due date flag to change the "
        "task's due date to the one specified as an argument (e.g. '2024-11-23')."
        "Ommitting the argument removes the due date from the task.",
        cxxopts::value<std::string>())(

        "h,help", "Print usage.");

    return cxxopts;
}

// TODO Rewrite this function so that it works. This function should
// case-insensitively check the action argument retrieved from cxxopts and
// convert this to a value from the ACTION enum. If an invalid value is given
// in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args)
{
    std::string input = args["action"].as<std::string>();
    // to lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (!input.compare("create"))
        return Action::CREATE;
    else if (!input.compare("json"))
        return Action::JSON;
    else if (!input.compare("update"))
        return Action::UPDATE;
    else if (!input.compare("delete"))
        return Action::DELETE;

    throw std::invalid_argument("action");
}

/**
 * Validates the existance for project, task and tag.
 *
 * @param args
 */
void App::validateArguments(cxxopts::ParseResult &args)
{
    // check docs, if due or completed or incomplete is included, must include project and task
    bool needProjectAndTask = args.count("due") || args.count("completed") || args.count("incomplete");
    if (args.count("tag") || needProjectAndTask)
    {
        if (!args.count("task") && !args.count("project"))
        {
            throw std::runtime_error("Error: missing project and task argument(s).");
        }
        if (!args.count("task"))
        {
            throw std::runtime_error("Error: missing task argument(s).");
        }
        if (!args.count("project"))
        {
            throw std::runtime_error("Error: missing project argument(s).");
        }
    }
    else if (args.count("task"))
    {
        if (!args.count("project"))
        {
            throw std::runtime_error("Error: missing project argument(s).");
        }
    }
}

/**
 * Validates existance for create action.
 *
 * @param args
 */
void App::validateCreateArguments(cxxopts::ParseResult &args)
{
    // indicates what has been put into the error message and what needs to be put in
    int errorMsgPosition = 0;

    bool isGood = true;
    std::string errorMessage = "Error: missing ";
    if (!args.count("project"))
    {
        isGood = false;
        errorMessage += "project";
    }

    if (args.count("task"))
    {
        errorMsgPosition = 1;
    }
    else
    {
        if (!isGood)
        {
            errorMessage += ", task";
            errorMsgPosition = 1;
        }
    }

    if (args.count("tag"))
    {
        if (errorMsgPosition == 0)
        {
            if (!isGood)
            {
                errorMessage += ", ";
            }
            isGood = false;
            errorMessage += "task";
        }
    }
    else
    {
        if (!isGood)
        {
            errorMessage += ", tag";
        }
    }

    if (!isGood)
    {
        if (!args.count("due"))
        {
            errorMessage += ", due";
        }
        if (!args.count("completed") || !args.count("incomplete"))
        {
            errorMessage += ", completed/incomplete";
        }
        errorMessage += " argument(s).";
        throw std::runtime_error(errorMessage);
    }
}

/**
 * Returns vector of strings split by delimiter.
 *
 * @param string
 * @param delimiter
 * @return std::vector<std::string>&
 */
std::vector<std::string> App::splitString(const std::string &string, const char delimiter)
{
    std::stringstream test(string);
    std::string segment;
    std::vector<std::string> seglist;
    while (std::getline(test, segment, delimiter))
    {
        seglist.push_back(segment);
    }
    return seglist;
}

// TODO Write a function, getJSON, that returns a std::string containing the
// JSON representation of a TodoList object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::cout << getJSON(tlObj);
std::string App::getJSON(TodoList &tlObj)
{
    return tlObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
// JSON representation of a specific Project in a TodoList object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::string p = "project argument value";
//  std::cout << getJSON(tlObj, p);
std::string App::getJSON(TodoList &tlObj, const std::string &p)
{
    auto pObj = tlObj.getProject(p);
    return pObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Task in a TodoList object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::string p = "project argument value";
//  std::string t = "task argument value";
//  std::cout << getJSON(tlObj, p, t);
std::string App::getJSON(TodoList &tlObj, const std::string &p,
                         const std::string &t)
{
    auto pObj = tlObj.getProject(p);
    const auto tObj = pObj.getTask(t);
    return tObj.str();
}

// DONE Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Tag in a TodoList object. If the tag
//  does not exist, return an empty string "".
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::string p = "project argument value";
//  std::string task = "task argument value";
//  std::string tag = "tag argument value";
//  std::cout << getJSON(tlObj, p, task, tag);
std::string App::getJSON(TodoList &tlObj, const std::string &p,
                         const std::string &task, const std::string &tag)
{
    auto pObj = tlObj.getProject(p);
    const auto tObj = pObj.getTask(task);
    return tObj.containsTag(tag) ? tag : "";
}
