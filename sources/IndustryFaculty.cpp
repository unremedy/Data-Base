#include "IndustryFaculty.h"
#include "IndustryFacultyFunctions.h"
#include <iostream>
#include <set>


size_t IndustryFaculty::FindFaculty(const std::string &FileName) {
    IndustryFacultyFunctions InFa;
    std::vector<IndustryFaculty> OldVectorOfBF;
    InFa.ReadDBToVector(FileName, OldVectorOfBF);
    std::string Name;
    size_t NumFac = IndustryFacultyFunctions::NumOfFaculty(FileName);
    std::vector<std::string> NameFacVec(NumFac);
    size_t index = 0;
    for (size_t j = 0; j < NumFac; ++j) {
        NameFacVec[j] = OldVectorOfBF[j].NameIF;
    }

    auto Print = [](auto element) {
        std::cout << "faculty:" << std::endl;
        std::cout << element << std::endl;
    };
    std::for_each(OldVectorOfBF.begin(), OldVectorOfBF.end(), Print);
    std::cout << std::endl;

    std::cout << "name of faculty to find: " << std::endl;
    getline(std::cin, Name);
    index = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));
    return index;
}

size_t IndustryFaculty::NumOfUniqueDisciplines(const std::string &FileName) {
    IndustryFacultyFunctions InFa;
    std::vector<IndustryFaculty> OldVectorOfIF;
    InFa.ReadDBToVector(FileName, OldVectorOfIF);
    size_t position = InFa.FindFaculty(FileName);
    std::set<std::string> VecDisciplines;
    for (size_t i = 0; i < OldVectorOfIF[position].NumCathedra; ++i) {
        auto fill = [&](auto element) { VecDisciplines.insert(element.first); };
        std::for_each(OldVectorOfIF[position].AllCathedra[i].Discipline.begin(),
                      OldVectorOfIF[position].AllCathedra[i].Discipline.end(), fill);
    }

    for (size_t i = 0; i < OldVectorOfIF[position].NumOrganizations; ++i) {
        auto fill = [&](auto element) { VecDisciplines.insert(element.first); };
        std::for_each(OldVectorOfIF[position].AllOrganizations[i].DisciplineOrg.begin(),
                      OldVectorOfIF[position].AllOrganizations[i].DisciplineOrg.end(), fill);
    }
    return VecDisciplines.size();
}
