
#ifndef DATABASE_FUNCTIONSFILESYSTEM_H
#define DATABASE_FUNCTIONSFILESYSTEM_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <filesystem>
#include "BasicFacultyFunctions.h"
#include "IndustryFacultyFunctions.h"
#include "GybridFacultyFunctions.h"

std::string RenameFile(const std::string &FileName){
    std::string Name;
    std::filesystem::path path = std::filesystem::current_path();
    std::cout << "Enter new full name of file:" << std::endl;
    std::getline(std::cin, Name);
    std::filesystem::rename(path/FileName, path/Name);
    return Name;
}

void DeleteFile(){
    std::filesystem::path path = std::filesystem::current_path();
    std::string Name;
    std::cout << "enter name of file to delete" << std::endl;
    getline(std::cin, Name);
    std::filesystem::remove(path/Name);
}

void ListOfFiles() {
    std::string path = std::filesystem::current_path();
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        size_t index = 56;
        std::string Substr = entry.path();
        Substr = Substr.substr(index);
        if ((Substr.find(".txt", 0) != std::string::npos) && (Substr != "CMakeCache.txt")) {
            std::cout << Substr << std::endl;
        }
    }

}

void parameters() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Закончить работу: end" << std::endl;
    std::cout << "Закрыть БД: close" << std::endl;
    std::cout << "Добавить новый факультет в конец файла: wrline" << std::endl;
    std::cout << "Вывести всю базу: read" << std::endl;
    std::cout << "Посчитать количество факультетов в файле: countf" << std::endl;
    std::cout << "Посчитать количество уникальных дисциплин на факультете: countd" << std::endl;
    std::cout << "Редактирование записей в БД: change" << std::endl;
    std::cout << "Очистить базу от записей: erase" << std::endl;
    std::cout << "Удалить факультет по названию: deleteline" << std::endl;
    std::cout << "Сохранить выборку из БД в другой файл: save" << std::endl;
    std::cout << "Найти факультет по его названию: find" << std::endl;
    std::cout << "Сортировать факультеты по алфавиту: sorta" << std::endl;
    std::cout << "Сортировать факультеты по количеству кафедр: sortn" << std::endl;
    std::cout << "Вывести факультеты, имеющие больше n кафедр: findc" << std::endl;
    std::cout << "Вывести факультеты, ведущие дисциплину name: findn" << std::endl;
    std::cout << "Изменить название файла: rename" << std::endl;
    std::cout << std::endl;

}

void ChooseTheFile() {
    std::string Name;
    std::string Command;
    parameters();
    while (Command != "end") {
        std::cout << "Вывести список всех баз данных: show" << std::endl;
        std::cout << "Начать работу: start" << std::endl;
        std::cout << "Удалить файл: delete" << std::endl;
        std::getline(std::cin, Command);
        if (Command == "show") {
            ListOfFiles();
        }else if(Command == "delete"){
            ListOfFiles();
            DeleteFile();
        }else if (Command == "start") {
            std::cout << "Choose the type of DB you want to work with: Basic, Industry or Gybrid\n" << std::endl;
            getline(std::cin, Name);
            if (Name == "Basic") {
                BasicFacultyFunctions BF;
                std::cout << "Создать новую базу: create" << std::endl;
                std::cout << "Работать с уже существующей БД: work" << std::endl;
                std::getline(std::cin, Command);
                if (Command == "create") {
                    std::cout << "type name of new file" << std::endl;
                    getline(std::cin, Name);
                    BF.WriteALine_B(Name);
                } else if (Command == "work") {
                    ListOfFiles();
                    std::cout << "Choose Basic DB file. Letter B_:\n " << std::endl;
                    getline(std::cin, Name);
                    BF.BFNameFile = Name;

                    while (Command != "close") {
                        std::cout << "Choose command: " << std::endl;
                        std::getline(std::cin, Command);
                        if (Command == "wrline") {
                            BF.WriteALine_B(BF.BFNameFile);
                        } else if (Command == "read") {
                            BF.ReadDB_B(BF.BFNameFile);
                        } else if (Command == "countf") {
                            std::cout << BF.NumOfFaculty_B(BF.BFNameFile) << std::endl;
                        } else if (Command == "change") {
                            BF.ChangeALine_B(BF.BFNameFile);
                        } else if (Command == "erase") {
                            BF.ClearDB_B(BF.BFNameFile);
                        } else if (Command == "save") {
                            std::cout << "enter name of file where to save" << std::endl;
                            getline(std::cin, Name);
                            BF.SavePartOfDB_B(Name);
                        } else if(Command == "find"){
                            size_t ind = BF.FindFaculty(BF.BFNameFile);
                            if(ind == BF.NumOfFaculty_B(BF.BFNameFile)){
                                std::cout << "faculty not found" << std::endl;
                            } else {
                                std::cout << "faculty position: " << ind + 1 << std::endl;
                            }
                        } else if (Command == "deleteline"){
                            BF.DeleteALine_B(BF.BFNameFile);
                        } else if(Command == "countd"){
                            std::cout << BF.NumOfUniqueDisciplines(BF.BFNameFile) << std::endl;
                        } else if (Command == "sorta") {
                            BF.SortByAlphabetFaculty_B(BF.BFNameFile);
                        }else if (Command == "findc") {
                            BF.FindByNumCathedra_B(BF.BFNameFile);
                        }else if (Command == "sortn") {
                            BF.SortByNumCathedra_B(BF.BFNameFile);
                        }else if (Command == "findn") {
                            BF.FindByNameDiscipline_B(BF.BFNameFile);
                        }else if (Command == "rename") {
                            BF.BFNameFile = RenameFile(BF.BFNameFile);
                        }

                    }
                } else{
                    std::cout << "unknown command, try again" << std::endl;
                    continue;
                }
            } else if(Name == "Industry"){
                IndustryFacultyFunctions IF;
                std::cout << "Создать новую базу: create" << std::endl;
                std::cout << "Работать с уже существующей БД: work" << std::endl;
                std::getline(std::cin, Command);
                if (Command == "create") {
                    std::cout << "type name of new file" << std::endl;
                    getline(std::cin, Name);
                    IF.WriteALine(Name);
                } else if (Command == "work") {
                    ListOfFiles();
                    std::cout << "Choose Industry DB file. Letter I_:\n " << std::endl;
                    getline(std::cin, Name);
                    IF.IFNameFile = Name;
                    while (Command != "close") {
                        std::cout << "Choose command: " << std::endl;
                        std::getline(std::cin, Command);
                        if (Command == "wrline") {
                            IF.WriteALine(IF.IFNameFile);
                        } else if (Command == "read") {
                            IF.ReadDB(IF.IFNameFile);
                        } else if (Command == "countf") {
                            std::cout << IF.NumOfFaculty(IF.IFNameFile) << std::endl;
                        } else if (Command == "change") {
                            IF.ChangeALine(IF.IFNameFile);
                        } else if (Command == "erase") {
                            IF.ClearDB(IF.IFNameFile);
                        } else if (Command == "save") {
                            std::cout << "enter name of file where to save" << std::endl;
                            getline(std::cin, Name);
                            IF.SavePartOfDB(Name);
                        } else if(Command == "find"){
                            size_t ind = IF.FindFaculty(IF.IFNameFile);
                            if(ind == IF.NumOfFaculty(IF.IFNameFile)){
                                std::cout << "faculty not found" << std::endl;
                            } else {
                                std::cout << "faculty position: " << ind + 1 << std::endl;
                            }
                        } else if (Command == "deleteline"){
                            IF.DeleteALine(IF.IFNameFile);
                        } else if(Command == "countd"){
                            std::cout << IF.NumOfUniqueDisciplines(IF.IFNameFile) << std::endl;
                        } else if (Command == "sorta") {
                            IF.SortByAlphabetFaculty(IF.IFNameFile);
                        }else if (Command == "findc") {
                            IF.FindByNumCathedra(IF.IFNameFile);
                        }else if (Command == "sortn") {
                            IF.SortByNumCathedra(IF.IFNameFile);
                        }else if (Command == "findn") {
                            IF.FindByNameDiscipline(IF.IFNameFile);
                        }else if (Command == "rename") {
                            IF.IFNameFile = RenameFile(IF.IFNameFile);
                        }

                    }
                } else{
                    std::cout << "unknown command, try again" << std::endl;
                    continue;
                }
            } else if(Name == "Gybrid"){
                GybridFacultyFunctions GF;
                IndustryFacultyFunctions IF;
                std::cout << "Создать новую базу: create" << std::endl;
                std::cout << "Работать с уже существующей БД: work" << std::endl;
                std::getline(std::cin, Command);
                if (Command == "create") {
                    std::cout << "type name of new file" << std::endl;
                    getline(std::cin, Name);
                    GF.WriteALine_G(Name);
                } else if (Command == "work") {
                    ListOfFiles();
                    std::cout << "Choose Gybrid DB file. Letter G_:\n " << std::endl;
                    getline(std::cin, Name);
                    GF.GFNameFile = Name;
                    while (Command != "close") {
                        std::cout << "Choose command: " << std::endl;
                        std::getline(std::cin, Command);
                        if (Command == "wrline") {
                            GF.WriteALine_G(GF.GFNameFile);
                        } else if (Command == "read") {
                            GF.ReadDB_G(GF.GFNameFile);
                        } else if (Command == "countf") {
                            std::cout << GF.NumOfFaculty_G(GF.GFNameFile) << std::endl;
                        } else if (Command == "change") {
                            GF.ChangeALine_G(GF.GFNameFile);
                        } else if (Command == "erase") {
                            GF.ClearDB_G(GF.GFNameFile);
                        } else if (Command == "save") {
                            std::cout << "enter name of file where to save" << std::endl;
                            getline(std::cin, Name);
                            GF.SavePartOfDB_G(Name);
                        } else if(Command == "find"){
                            size_t ind = IF.FindFaculty(GF.GFNameFile);
                            if(ind == GF.NumOfFaculty_G(GF.GFNameFile)){
                                std::cout << "faculty not found" << std::endl;
                            } else {
                                std::cout << "faculty position: " << ind + 1 << std::endl;
                            }
                        } else if (Command == "deleteline"){
                            GF.DeleteALine_G(GF.GFNameFile);
                        } else if(Command == "countd"){
                            std::cout << IF.NumOfUniqueDisciplines(GF.GFNameFile) << std::endl;
                        } else if (Command == "sorta") {
                            GF.SortByAlphabetFaculty_G(GF.GFNameFile);
                        }else if (Command == "findc") {
                            GF.FindByNumCathedra_G(GF.GFNameFile);
                        }else if (Command == "sortn") {
                            GF.SortByNumCathedra_G(GF.GFNameFile);
                        }else if (Command == "findn") {
                            GF.FindByNameDiscipline_G(GF.GFNameFile);
                        }else if (Command == "rename") {
                            GF.IFNameFile = RenameFile(GF.GFNameFile);
                        }

                    }
                }else{
                    std::cout << "unknown command, try again" << std::endl;
                    continue;
                }
            }
            std::cout << "unknown type, try again" << std::endl;
        } else {
            std::cout << "unknown command, try again" << std::endl;
            continue;
        }
    }
}


#endif //DATABASE_FUNCTIONSFILESYSTEM_H
