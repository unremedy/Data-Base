#include "BasicFaculty.h"
#include "BasicFacultyFunctions.h"
#include <iostream>
#include <set>



size_t BasicFaculty::FindFaculty(const std::string &FileName) {
    BasicFacultyFunctions BaFa;
    std::vector<BasicFaculty> OldVectorOfBF;
    BaFa.ReadDBToVector_B(FileName, OldVectorOfBF);
    std::string Name;
    size_t NumFac = BasicFacultyFunctions::NumOfFaculty_B(FileName);
    std::vector<std::string> NameFacVec(NumFac);
    size_t index = 0;
    for (size_t j = 0; j < NumFac; ++j) {
        NameFacVec[j] = OldVectorOfBF[j].NameBF;
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

size_t BasicFaculty::NumOfUniqueDisciplines(const std::string &FileName) {
    BasicFacultyFunctions BaFa;
    std::vector<BasicFaculty> OldVectorOfBF;
    BaFa.ReadDBToVector_B(FileName, OldVectorOfBF);
    size_t position = BaFa.FindFaculty(FileName);
    std::set<std::string> VecDisciplines;
    for (size_t i = 0; i < OldVectorOfBF[position].NumCathedra; ++i) {
        auto fill = [&](auto element) { VecDisciplines.insert(element.first); };
        std::for_each(OldVectorOfBF[position].AllCathedra[i].Discipline.begin(),
                      OldVectorOfBF[position].AllCathedra[i].Discipline.end(), fill);
    }

    return VecDisciplines.size();
}
