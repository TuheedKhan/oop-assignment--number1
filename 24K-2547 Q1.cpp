#include <iostream>
#include <string>
using namespace std;

class Mentor; 

class Student {
private:
    int age;
    string studentID, name;
    string sportsInterests[100]; 
    int sportsInterestsCount; 
    Mentor* mentorAssigned;

public:
    Student(string studentID, string name, int age) : studentID(studentID), name(name), age(age) {
        mentorAssigned = nullptr;
        sportsInterestsCount = 0;
    }

    void registerForMentorship(Mentor& m);
    void viewMentorDetails();
    void updateSportsInterests(const string& sport);
    void removeMentorship();

    string getStudentID() const { return studentID; }

    string getName() const { return name; }

    int getAge() const { return age; }

    int getSportsInterestsCount() const { return sportsInterestsCount; }

    string getSportsInterest(int index) const { return sportsInterests[index]; }

    Mentor* getMentorAssigned() const { return mentorAssigned; }
};

class Mentor {
private:
    int maxLearners;
    string mentorID, name;
    string sportsExpertise[100]; 
    int sportsExpertiseCount; 
    Student* assignedLearners[100];
    int assignedLearnersCount; 

public:
    Mentor(string mentorID, string name, int maxLearners = 0) : mentorID(mentorID), name(name), maxLearners(maxLearners) {}

    void assignLearner(Student& s);
    void removeLearner(Student& s);
    void viewLearners();
    void provideGuidance();

    string getMentorID() const { return mentorID; }

    string getName() const { return name; }

    int getMaxLearners() const { return maxLearners; }

    int getSportsExpertiseCount() const { return sportsExpertiseCount; }

    string getSportsExpertise(int index) const { return sportsExpertise[index]; }

    int getAssignedLearnersCount() const { return assignedLearnersCount; }

    Student* getAssignedLearner(int index) const { return assignedLearners[index]; }

    void addSportsExpertise(const string& sport) {
        if (sportsExpertiseCount < 100) {
            sportsExpertise[sportsExpertiseCount++] = sport;
        } else {
            cout << "Sports expertise list is full." << endl;
        }
    }
};

class Sport {
private:
    string sportID, name, description;
    string requiredSkills[100]; 
    int requiredSkillsCount; 

public:
    Sport(string sportID, string name, string description) : sportID(sportID), name(name), description(description) {
        requiredSkillsCount = 0;
    }

    void addSkill(const string& skill) {
        if (requiredSkillsCount < 100) {
            requiredSkills[requiredSkillsCount++] = skill;
        } else {
            cout << "Required skills list is full." << endl;
        }
    }

    void removeSkill(const string& skill) {
        for (int i = 0; i < requiredSkillsCount; i++) {
            if (requiredSkills[i] == skill) {
               
                for (int j = i; j < requiredSkillsCount - 1; j++) {
                    requiredSkills[j] = requiredSkills[j + 1];
                }
                requiredSkillsCount--;
                cout << "Skill removed: " << skill << endl;
                return;
            }
        }
        cout << "Skill not found: " << skill << endl;
    }

    string getSportID() const { return sportID; }

    string getName() const { return name; }

    string getDescription() const { return description; }

    int getRequiredSkillsCount() const { return requiredSkillsCount; }

    string getRequiredSkill(int index) const { return requiredSkills[index]; }

};

class Skill {
private:
    string skillID, skillName, description;

public:

    Skill(string skillID, string skillName, string description) : skillID(skillID), skillName(skillName), description(description) {}

    void showSkillDetails() {
        cout << "Skill ID: " << skillID << "\nSkill Name: " << skillName << "\nDescription: " << description << endl;
    }

    void updateSkillDescription(const string& newDescription) { description = newDescription; }

    string getSkillID() const { return skillID; }
    string getSkillName() const { return skillName; }
    string getDescription() const { return description; }
};


void Student::registerForMentorship(Mentor& m) {
    if (mentorAssigned == nullptr) {
        m.assignLearner(*this);
        mentorAssigned = &m;
    } else {
        cout << "Already assigned to a mentor." << endl;
    }
}


void Student::viewMentorDetails() {
    if (mentorAssigned != nullptr) {
        cout << "Mentor ID: " << mentorAssigned->getMentorID() << "\nMentor Name: " << mentorAssigned->getName() << endl;
    } else {
        cout << "No mentor assigned." << endl;
    }
}


void Student::updateSportsInterests(const string& sport) {
    if (sportsInterestsCount < 100) {
        sportsInterests[sportsInterestsCount++] = sport;
    } else {
        cout << "Sports interests list is full." << endl;
    }
}


void Student::removeMentorship() {
    if (mentorAssigned != nullptr) {
        mentorAssigned->removeLearner(*this);
        mentorAssigned = nullptr;
    } else {
        cout << "No mentor assigned." << endl;
    }
}


void Mentor::assignLearner(Student& s) {

    if (assignedLearnersCount < maxLearners) {
        assignedLearners[assignedLearnersCount++] = &s;
        cout << s.getName() << " assigned to mentor " << name << endl;
    } else {
        cout << "Mentor " << name << " has reached maximum capacity." << endl;
    }
}


void Mentor::removeLearner(Student& s) {
    for (int i = 0; i < assignedLearnersCount; i++) {
        if (assignedLearners[i] == &s) {
         
            for (int j = i; j < assignedLearnersCount - 1; j++) {
                assignedLearners[j] = assignedLearners[j + 1];
            }
            assignedLearnersCount--;
            cout << s.getName() << " removed from mentor " << name << endl;
            return;
        }
    }
    cout << s.getName() << " is not assigned to mentor " << name << endl;
}

void Mentor::viewLearners() {
    cout << "Learners assigned to mentor " << name << ":\n";
    for (int i = 0; i < assignedLearnersCount; i++) {
        cout << assignedLearners[i]->getName() << endl;
    }
}

void Mentor::provideGuidance() {
    cout << "Providing guidance to learners..." << endl;
}

int main() {

    Student arsalan("S001", "Arsalan", 20);
    Mentor ali("M001", "Ali", 3);

    arsalan.updateSportsInterests("American Football");
    ali.addSportsExpertise("American Football");

    arsalan.registerForMentorship(ali);
    arsalan.viewMentorDetails();
    ali.viewLearners();

    arsalan.removeMentorship();
    ali.viewLearners();

    return 0;
}