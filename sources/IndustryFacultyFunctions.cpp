#include "IndustryFacultyFunctions.h"


void IndustryFacultyFunctions::WriteALine(const std::string &FileName) {
    size_t NumDiscipline = 0;
    std::string name_discipline;
    size_t num_teachers;
    IndustryFaculty NewFaculty;
    CathedraIF NCath;
    Organization NOrg;

    std::cout << "Enter name of faculty" << std::endl;
    getline(std::cin, NewFaculty.NameIF);
    std::cout << "Enter name of NUK" << std::endl;
    getline(std::cin, NewFaculty.NUK);
    std::cout << "Enter number of cathedra" << std::endl;
    std::cin >> NewFaculty.NumCathedra;
    for (size_t i = 0; i < NewFaculty.NumCathedra; ++i) {
        std::cout << "Enter name of cathedra" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, NCath.NameCathedra);
        std::cout << "Enter number of disciplines" << std::endl;
        std::cin >> NumDiscipline;
        for (size_t k = 0; k < NumDiscipline; ++k) {
            std::cout << "Enter name of discipline" << std::endl;
            std::cin >> name_discipline;
            std::cout << "Enter number of teachers" << std::endl;
            std::cin >> num_teachers;
            NCath.Discipline.insert(NCath.Discipline.end(), std::make_pair(name_discipline, num_teachers));
        }
        NewFaculty.AllCathedra.push_back(NCath);
        NCath.Discipline.clear();
    }
    std::cout << "Enter number of organizations" << std::endl;
    std::cin >> NewFaculty.NumOrganizations;
    for (size_t i = 0; i < NewFaculty.NumOrganizations; ++i) {
        std::cout << "Enter name of organization" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, NOrg.NameOrganization);
        std::cout << "Enter number of disciplines" << std::endl;
        std::cin >> NumDiscipline;
        for (size_t k = 0; k < NumDiscipline; ++k) {
            std::cout << "Enter name of discipline" << std::endl;
            std::cin >> name_discipline;
            std::cout << "Enter number of teachers" << std::endl;
            std::cin >> num_teachers;
            NOrg.DisciplineOrg.insert(NOrg.DisciplineOrg.end(), std::make_pair(name_discipline, num_teachers));
        }
        NewFaculty.AllOrganizations.push_back(NOrg);
        NOrg.DisciplineOrg.clear();
    }

    std::cout << NewFaculty << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::ofstream WriteIF(FileName, std::ios::app);
    if (WriteIF.is_open()) {
        WriteIF << '-' << std::endl;
        WriteIF << NewFaculty.NameIF << std::endl;
        WriteIF << NewFaculty.NUK << std::endl;
        WriteIF << NewFaculty.NumCathedra << std::endl;
        for (size_t i = 0; i < NewFaculty.NumCathedra; ++i) {
            WriteIF << '{' << std::endl;
            WriteIF << NewFaculty.AllCathedra[i].NameCathedra << std::endl;
            auto record = [&](auto element) { WriteIF << element.first << ", " << element.second << std::endl; };
            std::for_each(NewFaculty.AllCathedra[i].Discipline.begin(), NewFaculty.AllCathedra[i].Discipline.end(),
                          record);
            std::cout << std::endl;
        }
        WriteIF << '{' << std::endl;
        WriteIF << NewFaculty.NumOrganizations << std::endl;
        for (size_t i = 0; i < NewFaculty.NumOrganizations; ++i) {
            WriteIF << '{' << std::endl;
            WriteIF << NewFaculty.AllOrganizations[i].NameOrganization << std::endl;
            auto record = [&](auto element) { WriteIF << element.first << ", " << element.second << std::endl; };
            std::for_each(NewFaculty.AllOrganizations[i].DisciplineOrg.begin(),
                          NewFaculty.AllOrganizations[i].DisciplineOrg.end(),
                          record);
            std::cout << std::endl;
        }
        WriteIF << '{' << std::endl;
        WriteIF.close();
    } else {
        std::cout << "error_write" << std::endl;
    }
}

void IndustryFacultyFunctions::ReadDB(const std::string &FileName) {
    IndustryFaculty NewFaculty;
    std::string String;
    std::ifstream ReadBF(FileName, std::ios::in);
    if (ReadBF.is_open()) {
        while (!ReadBF.eof()) {
            getline(ReadBF, String);
            std::cout << String << std::endl;
        }
        ReadBF.close();
    } else {
        std::cout << "error_read" << std::endl;
    }
}

size_t IndustryFacultyFunctions::NumOfFaculty(const std::string &FileName) {

    size_t counter = 0;
    std::string String;
    std::ifstream ReadBF(FileName, std::ios::in);
    if (ReadBF.is_open()) {
        while (!ReadBF.eof()) {
            getline(ReadBF, String);
            if (String == "-") {
                ++counter;
            }
        }
        ReadBF.close();
    } else {
        std::cout << "error_read" << std::endl;
    }
    return counter;
}

void IndustryFacultyFunctions::ReadDBToVector(const std::string &FileName, std::vector<IndustryFaculty> &vectorOfIF) {
    size_t NumFac = NumOfFaculty(FileName);
    std::string name_discipline;
    size_t num_teachers;
    IndustryFaculty NewFaculty;
    CathedraIF NCath;
    Organization NOrg;
    std::string String;
    std::ifstream ReadIF(FileName, std::ios::in);
    if (ReadIF.is_open()) {
        for (size_t k = 0; k < NumFac; ++k) {
            getline(ReadIF, String);
            getline(ReadIF, NewFaculty.NameIF);
            getline(ReadIF, NewFaculty.NUK);
            ReadIF >> NewFaculty.NumCathedra;
            ReadIF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(ReadIF, String);
            for (size_t i = 0; i < NewFaculty.NumCathedra; ++i) {
                getline(ReadIF, NCath.NameCathedra);
                do {
                    getline(ReadIF, String);
                    if (String != "{") {
                        size_t pos = String.find(',');
                        name_discipline = String.substr(0, pos);
                        num_teachers = std::stoi(String.substr(pos + 2));
                        NCath.Discipline.insert(NCath.Discipline.end(), std::make_pair(name_discipline, num_teachers));
                    }
                } while (String != "{");

                NewFaculty.AllCathedra.push_back(NCath);
                NCath.Discipline.clear();
            }
            ReadIF >> NewFaculty.NumOrganizations;
            ReadIF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(ReadIF, String);
            for (size_t i = 0; i < NewFaculty.NumOrganizations; ++i) {
                getline(ReadIF, NOrg.NameOrganization);
                do {
                    getline(ReadIF, String);
                    if (String != "{") {
                        size_t pos = String.find(',');
                        name_discipline = String.substr(0, pos);
                        num_teachers = std::stoi(String.substr(pos + 2));
                        NOrg.DisciplineOrg.insert(NOrg.DisciplineOrg.end(),
                                                  std::make_pair(name_discipline, num_teachers));
                    }
                } while (String != "{");

                NewFaculty.AllOrganizations.push_back(NOrg);
                NOrg.DisciplineOrg.clear();
            }

            vectorOfIF.push_back(NewFaculty);
            NewFaculty.Destruct();
        }
        ReadIF.close();
    }
}

void IndustryFacultyFunctions::ChangeALine(const std::string &FileName) {
    size_t NumDiscipline = 0;
    CathedraIF NCath;
    Organization NOrg;
    std::string name_discipline;
    size_t num_teachers;
    size_t number = 0;
    size_t index = 0;
    size_t NumFac = NumOfFaculty(FileName);
    std::vector<std::string> NameFacVec(NumFac);
    std::vector<std::string>::iterator ItNameFacVec;
    std::vector<IndustryFaculty> VectorOfIF;
    ReadDBToVector(FileName, VectorOfIF);
    std::string Name;
    size_t Case = 0;

    std::cout << "enter name of faculty for changes: " << std::endl;
    getline(std::cin, Name);
    for (size_t j = 0; j < NumFac; ++j) {
        NameFacVec[j] = VectorOfIF[j].NameIF;
    }
    index = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));
    std::cout << "which parameter you want to change: " << std::endl;
    std::cout << "1: NameIF\n2: NUK\n3: NumCathedra\n4: NumOrganizations" << std::endl;
    std::cin >> Case;
    switch (Case) {
        case 1:
            std::cout << "enter new industry faculty name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, Name);
            VectorOfIF[index].NameIF = Name;
            break;
        case 2:
            std::cout << "enter new NUK name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, Name);
            VectorOfIF[index].NUK = Name;
            break;
        case 3:
            std::cout << "enter 1 to add cathedra, enter 2 to delete cathedra: " << std::endl;
            std::cin >> number;
            switch (number) {
                case 1:
                    std::cout << "Enter name of cathedra" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, NCath.NameCathedra);
                    std::cout << "Enter number of disciplines" << std::endl;
                    std::cin >> NumDiscipline;
                    for (size_t k = 0; k < NumDiscipline; ++k) {
                        std::cout << "Enter name of discipline" << std::endl;
                        std::cin >> name_discipline;
                        std::cout << "Enter number of teachers" << std::endl;
                        std::cin >> num_teachers;
                        NCath.Discipline.insert(NCath.Discipline.end(), std::make_pair(name_discipline, num_teachers));
                    }
                    VectorOfIF[index].AllCathedra.push_back(NCath);
                    ++VectorOfIF[index].NumCathedra;
                    break;
                case 2:
                    if (VectorOfIF[index].NumCathedra == 1) {
                        std::cout << "faculty can't be without at least 1 cathedra" << std::endl;
                        break;
                    }
                    VectorOfIF[index].AllCathedra.pop_back();
                    --VectorOfIF[index].NumCathedra;
                    break;

            }
            number = 0;
            break;
        case 4:
            std::cout << "enter 1 to add organization, enter 2 to delete organization: " << std::endl;
            std::cin >> number;
            switch (number) {
                case 1:
                    std::cout << "Enter name of organization" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, NOrg.NameOrganization);
                    std::cout << "Enter number of disciplines" << std::endl;
                    std::cin >> NumDiscipline;
                    for (size_t k = 0; k < NumDiscipline; ++k) {
                        std::cout << "Enter name of discipline" << std::endl;
                        std::cin >> name_discipline;
                        std::cout << "Enter number of teachers" << std::endl;
                        std::cin >> num_teachers;
                        NOrg.DisciplineOrg.insert(NOrg.DisciplineOrg.end(),
                                                  std::make_pair(name_discipline, num_teachers));
                    }
                    VectorOfIF[index].AllOrganizations.push_back(NOrg);
                    ++VectorOfIF[index].NumOrganizations;
                    break;
                case 2:
                    if (VectorOfIF[index].NumOrganizations == 1) {
                        std::cout << "faculty can't be without at least 1 organization" << std::endl;
                        break;
                    }
                    VectorOfIF[index].AllOrganizations.pop_back();
                    --VectorOfIF[index].NumOrganizations;
                    break;
            }
            break;


    }

    std::ofstream ChangeIF(FileName, std::ios::out);
    if (ChangeIF.is_open()) {
        for (size_t k = 0; k < NumFac; ++k) {
            ChangeIF << '-' << std::endl;
            ChangeIF << VectorOfIF[k].NameIF << std::endl;
            ChangeIF << VectorOfIF[k].NUK << std::endl;
            ChangeIF << VectorOfIF[k].NumCathedra << std::endl;
            for (size_t i = 0; i < VectorOfIF[k].NumCathedra; ++i) {
                ChangeIF << '{' << std::endl;
                ChangeIF << VectorOfIF[k].AllCathedra[i].NameCathedra << std::endl;
                auto record = [&](auto element) { ChangeIF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfIF[k].AllCathedra[i].Discipline.begin(),
                              VectorOfIF[k].AllCathedra[i].Discipline.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeIF << '{' << std::endl;
            ChangeIF << VectorOfIF[k].NumOrganizations << std::endl;
            for (size_t i = 0; i < VectorOfIF[k].NumOrganizations; ++i) {
                ChangeIF << '{' << std::endl;
                ChangeIF << VectorOfIF[k].AllOrganizations[i].NameOrganization << std::endl;
                auto record = [&](auto element) { ChangeIF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfIF[k].AllOrganizations[i].DisciplineOrg.begin(),
                              VectorOfIF[k].AllOrganizations[i].DisciplineOrg.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeIF << '{' << std::endl;
        }
        ChangeIF.close();
    }
}

void IndustryFacultyFunctions::ClearDB(const std::string &FileName) {
    std::ofstream ChangeIF(FileName, std::ios::out);
    if (ChangeIF.is_open()) {
        ChangeIF << ' ' << std::endl;
        ChangeIF.close();
    }
}

void IndustryFacultyFunctions::SavePartOfDB(const std::string &FileName) {
    std::vector<IndustryFaculty> OldVectorOfIF;
    std::vector<IndustryFaculty> VectorOfIF;
    ReadDBToVector(IFNameFile, OldVectorOfIF);
    std::string Name;
    size_t index1 = 0;
    size_t index2 = 0;
    size_t NumFac = NumOfFaculty(IFNameFile);
    std::vector<std::string> NameFacVec(NumFac);

    for (size_t j = 0; j < NumFac; ++j) {
        NameFacVec[j] = OldVectorOfIF[j].NameIF;
    }
    std::cout << "enter first name of faculty: " << std::endl;
    getline(std::cin, Name);
    index1 = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));

    std::cout << "enter second name of faculty: " << std::endl;
    getline(std::cin, Name);
    index2 = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));
    for (size_t i = index1; i < index2 - index1 + 2; ++i) {
        VectorOfIF.push_back(OldVectorOfIF[i]);
    }
    std::ofstream ChangeIF(FileName, std::ios::out);
    if (ChangeIF.is_open()) {
        for (size_t k = 0; k < index2 - index1 + 1; ++k) {
            ChangeIF << '-' << std::endl;
            ChangeIF << VectorOfIF[k].NameIF << std::endl;
            ChangeIF << VectorOfIF[k].NUK << std::endl;
            ChangeIF << VectorOfIF[k].NumCathedra << std::endl;
            for (size_t i = 0; i < VectorOfIF[k].NumCathedra; ++i) {
                ChangeIF << '{' << std::endl;
                ChangeIF << VectorOfIF[k].AllCathedra[i].NameCathedra << std::endl;
                auto record = [&](auto element) { ChangeIF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfIF[k].AllCathedra[i].Discipline.begin(),
                              VectorOfIF[k].AllCathedra[i].Discipline.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeIF << '{' << std::endl;
            ChangeIF << VectorOfIF[k].NumOrganizations << std::endl;
            for (size_t i = 0; i < VectorOfIF[k].NumOrganizations; ++i) {
                ChangeIF << '{' << std::endl;
                ChangeIF << VectorOfIF[k].AllOrganizations[i].NameOrganization << std::endl;
                auto record = [&](auto element) { ChangeIF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfIF[k].AllOrganizations[i].DisciplineOrg.begin(),
                              VectorOfIF[k].AllOrganizations[i].DisciplineOrg.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeIF << '{' << std::endl;
        }
        ChangeIF.close();
    } else {
        std::cout << "error_read" << std::endl;
    }
}

void IndustryFacultyFunctions::DeleteALine(const std::string &FileName) {
    IndustryFacultyFunctions InFa;
    size_t position = InFa.FindFaculty(FileName);
    size_t NumFac = NumOfFaculty(FileName) - 1;
    std::vector<IndustryFaculty> VectorOfIF;
    ReadDBToVector(FileName, VectorOfIF);
    VectorOfIF.erase(VectorOfIF.begin() + position);
    std::ofstream ChangeIF(FileName, std::ios::out);
    if (ChangeIF.is_open()) {
        for (size_t k = 0; k < NumFac; ++k) {
            ChangeIF << '-' << std::endl;
            ChangeIF << VectorOfIF[k].NameIF << std::endl;
            ChangeIF << VectorOfIF[k].NUK << std::endl;
            ChangeIF << VectorOfIF[k].NumCathedra << std::endl;
            for (size_t i = 0; i < VectorOfIF[k].NumCathedra; ++i) {
                ChangeIF << '{' << std::endl;
                ChangeIF << VectorOfIF[k].AllCathedra[i].NameCathedra << std::endl;
                auto record = [&](auto element) { ChangeIF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfIF[k].AllCathedra[i].Discipline.begin(),
                              VectorOfIF[k].AllCathedra[i].Discipline.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeIF << '{' << std::endl;
            ChangeIF << VectorOfIF[k].NumOrganizations << std::endl;
            for (size_t i = 0; i < VectorOfIF[k].NumOrganizations; ++i) {
                ChangeIF << '{' << std::endl;
                ChangeIF << VectorOfIF[k].AllOrganizations[i].NameOrganization << std::endl;
                auto record = [&](auto element) { ChangeIF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfIF[k].AllOrganizations[i].DisciplineOrg.begin(),
                              VectorOfIF[k].AllOrganizations[i].DisciplineOrg.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeIF << '{' << std::endl;
        }
        ChangeIF.close();
    }
}

void IndustryFacultyFunctions::SortByAlphabetFaculty(const std::string &FileName) {
    std::vector<IndustryFaculty> VectorOfIF;
    ReadDBToVector(FileName, VectorOfIF);
    std::sort(VectorOfIF.begin(), VectorOfIF.end(), [](const IndustryFaculty &a, const IndustryFaculty &b) {
        return a.NameIF < b.NameIF;
    });

    auto Print = [](auto element) {
        std::cout << "faculty:" << std::endl;
        std::cout << element << std::endl;
    };
    std::for_each(VectorOfIF.begin(), VectorOfIF.end(), Print);
    std::cout << std::endl;
}

void IndustryFacultyFunctions::SortByNumCathedra(const std::string &FileName) {
    std::vector<IndustryFaculty> VectorOfBF;
    ReadDBToVector(FileName, VectorOfBF);
    std::sort(VectorOfBF.begin(), VectorOfBF.end(), [](const IndustryFaculty &a, const IndustryFaculty &b) {
        return a.NumCathedra <= b.NumCathedra;
    });

    auto Print = [](auto element) {
        std::cout << "faculty:" << std::endl;
        std::cout << element << std::endl;
    };
    std::for_each(VectorOfBF.begin(), VectorOfBF.end(), Print);
    std::cout << std::endl;
}

void IndustryFacultyFunctions::FindByNumCathedra(const std::string &FileName) {
    std::vector<IndustryFaculty> VectorOfBF;
    ReadDBToVector(FileName, VectorOfBF);
    size_t number = 0;
    size_t counter = 0;
    std::cout << "Enter minimum number of cathedra " << std::endl;
    std::cin >> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (size_t i = 0; i < VectorOfBF.size(); ++i) {
        if (VectorOfBF[i].NumCathedra > number) {
            std::cout << "faculty:" << std::endl;
            std::cout << VectorOfBF[i] << std::endl;
            ++counter;
        }
    }
    if (counter == 0) {
        throw 1;
    }
}

void IndustryFacultyFunctions::FindByNameDiscipline(const std::string &FileName) {

    std::vector<IndustryFaculty> VectorOfBF;
    ReadDBToVector(FileName, VectorOfBF);
    std::string Name;
    size_t counter = 0;
    std::cout << "Enter name of discipline to find in faculty " << std::endl;
    getline(std::cin, Name);
    for (size_t i = 0; i < VectorOfBF.size(); ++i) {
        for (size_t k = 0; k < VectorOfBF[i].NumCathedra; ++k) {
            for (auto it = VectorOfBF[i].AllCathedra[k].Discipline.begin();
                 it != VectorOfBF[i].AllCathedra[k].Discipline.end(); ++it) {
                if (it->first == Name) {
                    ++counter;
                    std::cout << "faculty:" << std::endl;
                    std::cout << VectorOfBF[i] << std::endl;
                    k = VectorOfBF[i].NumCathedra;
                    break;
                }
            }

        }

    }
    for (size_t i = 0; i < VectorOfBF.size(); ++i) {
        for (size_t k = 0; k < VectorOfBF[i].NumOrganizations; ++k) {
            for (auto it = VectorOfBF[i].AllOrganizations[k].DisciplineOrg.begin();
                 it != VectorOfBF[i].AllOrganizations[k].DisciplineOrg.end(); ++it) {
                if (it->first == Name) {
                    ++counter;
                    std::cout << "faculty:" << std::endl;
                    std::cout << VectorOfBF[i] << std::endl;
                    k = VectorOfBF[i].NumCathedra;
                    break;
                }
            }

        }

    }
    if (counter == 0) {
        throw 2;
        //std::cout << "Faculty with such discipline name not found" << std::endl;
    }


}