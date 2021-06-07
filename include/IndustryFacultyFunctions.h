#ifndef DATABASE_INDUSTRYFACULTYFUNCTIONS_H
#define DATABASE_INDUSTRYFACULTYFUNCTIONS_H

#include "IndustryFaculty.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

class IndustryFacultyFunctions : public IndustryFaculty{
public:
    std::string IFNameFile;
    void WriteALine(const std::string &FileName);
    void ReadDB(const std::string &FileName);
    static size_t NumOfFaculty(const std::string &FileName);
    void ReadDBToVector(const std::string &FileName, std::vector<IndustryFaculty> &vectorOfIF);
    void ChangeALine(const std::string &FileName);
    void DeleteALine(const std::string &FileName);
    void ClearDB(const std::string &FileName);
    void SavePartOfDB(const std::string &FileName);
    void SortByAlphabetFaculty(const std::string &FileName);
    void SortByNumCathedra(const std::string &FileName);
    void FindByNumCathedra(const std::string &FileName);
    void FindByNameDiscipline(const std::string &FileName);
};

#endif //DATABASE_INDUSTRYFACULTYFUNCTIONS_H
