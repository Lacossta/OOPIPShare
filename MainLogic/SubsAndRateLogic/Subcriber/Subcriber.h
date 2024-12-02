#ifndef KURSACH_SUBCRIBER_H
#define KURSACH_SUBCRIBER_H

using namespace std;
#include <string>
#include <vector>


// Id isblock name surname midName age phone rate date
class Subcriber {
private:
    vector<Subcriber> subcribers;
protected:
    int subId;
    bool isblock = false;
    int age;
    int rateId;
    string connectDate;
    string phone;
    string surname;
    string name;
    string midName;

public:
    int getSubId() const;
    void setSubId(int subId);

    bool getIsblock() const;
    void setIsblock(bool isblock);

    int getAge() const;
    void setAge(int age);

    int getRateId() const;
    void setRateId(int rateId);

    const string &getConnectDate() const;
    void setConnectDate(const string &connectDate);

    const string &getPhone() const;
    void setPhone(const string &phone);

    const string &getSurname() const;
    void setSurname(const string &surname);

    const string &getName() const;
    void setName(const string &name);

    const string &getMidName() const;
    void setMidName(const string &midName);

    const vector<Subcriber> &getSubcribers() const;
    void setSubcribers(const vector<Subcriber> &subcribers);

public:

    Subcriber();

    void AddAmountRepairs() const;

    Subcriber(int subId, bool isblock, int age, int rateId, string connectDate,
              string phone, string surname, string name, string midName);

    int generateId();

    void addSubcriber(const Subcriber &subcriberLoad);

    void DisplaySingleSubcriber(int subId, bool isblock, int age, int rateId, string connectDate,
                                string phone, string surname, string name, string midName);

    void DisplaySingleSubcriber(int age, int rateId, string connectDate,
                                string phone, string surname, string name, string midName);

};

extern Subcriber subcriber;

#endif //KURSACH_SUBCRIBER_H