#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class student
{
public:
	string name;
	int age;
	double score;

	student(string name, int age, double score) : name(name), age(age), score(score) {}
};

ostream &operator<<(ostream &_os, const student &s)
{
	_os << s.name << " [ age : " << s.age << " , score : " << s.score << "]";
	return _os;
}

bool compare(student st1, student st2)
{
	return st1.age < st2.age;
}

int main()
{
	vector<student> v;
	v.push_back(student("John", 13, 90));
	v.push_back(student("Marry", 21, 80));
	v.push_back(student("Tom", 20, 76.8));
	v.push_back(student("William", 11, 92.5));
	sort(v.begin(), v.end(), compare);
	for (auto i : v)
		cout << i << "\n";

	return 0;
}
