#include <iostream>
#include <string>

class Student {
protected:
  std::string Name;
  int Age;
  std::string Type;

public:
  Student(std::string name = "", int age = 0, std::string type = "")
      : Name(name), Age(age), Type(type) {}

  std::string getName() { return Name; }
  int getAge() { return Age; }
  std::string getType() { return Type; }

  virtual ~Student() {}
};

class Undergraduate : public Student {
private:
  std::string Specialty;

public:
  Undergraduate(std::string name = "", int age = 0, std::string type = "",
                std::string specialty = "")
      : Student(name, age, type), Specialty(specialty) {}

  std::string getSpecialty() { return Specialty; }
};

class Graduate : public Student {
private:
  std::string Direction;

public:
  Graduate(std::string name = "", int age = 0, std::string type = "",
           std::string direction = "")
      : Student(name, age, type), Direction(direction) {}

  std::string getDirection() { return Direction; }
};

Student *query(Student *students[], const int &n, const std::string &name);

int main() {
  int n, m;
  std::cin >> n;

  Student *students[n];

  for (int i{0}; i < n; i++) {
    std::string name, type, sd;
    int age;
    std::cin >> name >> age >> type >> sd;

    if (type == "Undergraduate") {
      students[i] = new Undergraduate(name, age, type, sd);
    } else if (type == "Graduate") {
      students[i] = new Graduate(name, age, type, sd);
    } else {
      students[i] = new Student(name, age, type);
    }
  }

  std::cin >> m;

  for (int i{0}; i < m; i++) {
    std::string name, attribute;
    std::cin >> name >> attribute;

    Student *s = query(students, n, name);
    if (s == nullptr) {
      std::cout << "none" << std::endl;
    } else {
      if (attribute == "Age") {
        std::cout << s->getAge() << std::endl;
      } else if (attribute == "Type") {
        std::cout << s->getType() << std::endl;
      } else if (attribute == "Specialty") {
        Undergraduate *u = dynamic_cast<Undergraduate *>(s);
        u == nullptr ? std::cout << "none" << std::endl
                     : std::cout << u->getSpecialty() << std::endl;
      } else if (attribute == "Direction") {
        Graduate *g = dynamic_cast<Graduate *>(s);
        g == nullptr ? std::cout << "none" << std::endl
                     : std::cout << g->getDirection() << std::endl;
      } else {
        std::cout << "none" << std::endl;
      }
    }
  }

  return 0;
}

Student *query(Student *students[], const int &n, const std::string &name) {
  for (int i{0}; i < n; i++)
    if (students[i]->getName() == name)
      return students[i];

  return nullptr;
}
