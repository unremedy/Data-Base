#include "GybridFacultyFunctions.h"

IndustryFacultyFunctions IF;
//BasicFacultyFunctions BF;

void GybridFacultyFunctions::WriteALine_G(const std::string &FileName) {
    /*std::string String;
    std::cout << "write industry of basic faculty? " << std::endl;
    getline(std::cin, String);
    if(String == "industry"){
        IF.WriteALine(FileName);
    } else if(String == "basic"){
        BF.WriteALine(FileName);
    }*/
    std::cout << "type 0 if you don`t need basic organizations " << std::endl;
    IF.WriteALine(FileName);
}
void GybridFacultyFunctions::ReadDB_G(const std::string &FileName) {
    IF.ReadDB(FileName);
}
size_t GybridFacultyFunctions::NumOfFaculty_G(const std::string &FileName) {
    return IndustryFacultyFunctions::NumOfFaculty(FileName);
}
void GybridFacultyFunctions::ReadDBToVector_G(const std::string &FileName, std::vector<IndustryFaculty> &vectorOfBF) {
    IF.ReadDBToVector(FileName,vectorOfBF);
}
void GybridFacultyFunctions::ChangeALine_G(const std::string &FileName) {
    IF.ChangeALine(FileName);
}

void GybridFacultyFunctions::DeleteALine_G(const std::string &FileName) {
    IF.DeleteALine(FileName);
}
void GybridFacultyFunctions::ClearDB_G(const std::string &FileName) {
    IF.ClearDB(FileName);
}
void GybridFacultyFunctions::SavePartOfDB_G(const std::string &FileName) {
    IF.SavePartOfDB(FileName);
}
void GybridFacultyFunctions::SortByAlphabetFaculty_G(const std::string &FileName) {
    IF.SortByAlphabetFaculty(FileName);
}
void GybridFacultyFunctions::SortByNumCathedra_G(const std::string &FileName) {
    IF.SortByNumCathedra(FileName);
}
void GybridFacultyFunctions::FindByNumCathedra_G(const std::string &FileName) {
    IF.FindByNumCathedra(FileName);
}
void GybridFacultyFunctions::FindByNameDiscipline_G(const std::string &FileName) {
    IF.FindByNameDiscipline(FileName);
}