#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
class student
{
private:
	friend class database;
	string studentID;
	string name;
	string gender;
	int age;
	string choice;
	student *next;
};
class database
{
private:
	student *first;
	int studentNUM;

	bool isEmpty();
	void SmpDisplay(student *student);
	void HeadDisplay();
	void search(string& id,student *&ans,student *&previous);
public:
	database() :first(0), studentNUM(0) {}
	~database(){delete[] first;}
	void BulidDatabase();
	void InsertStu();
	void DeleteStu();
	void FindStu();
	void ReviseInfo();
	void StatDatabase();
};
bool database::isEmpty()
{
	return studentNUM == 0;
}
void database::SmpDisplay(student *student)
{
	cout << setw(10) << setfill(' ') << left << student->studentID
		<< setw(10) << setfill(' ') << left << student->name
		<< setw(5) << setfill(' ') << left << student->gender
		<< setw(5) << setfill(' ') << left << student->age
		<< student->choice << endl;
}
void database::HeadDisplay()
{
	cout << setw(10) << setfill(' ') << left << "考号"
		<< setw(10) << setfill(' ') << left << "姓名"
		<< setw(5) << setfill(' ') << left << "性别"
		<< setw(5) << setfill(' ') << left << "年龄"
		<< "报考类别" << endl;
}
void database::search(string& id, student *&ans, student *&previous)
{
	ans = first, previous = NULL;
	while (ans != NULL)
	{
		if (ans->studentID == id)
			return;
		previous = ans;
		ans = ans->next;
	}
	ans = previous = NULL;
}
void database::BulidDatabase()
{
	cout << "首先请建立考生信息系统！" << endl << "请输出考生人数：";
	cin >> studentNUM;
	if (studentNUM <= 0)
	{
		cout << "对不起，您输入的考生人数非法。" << endl;
		return;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;

	student *newSTU, *lastSTU = NULL;
	for (int i = studentNUM; i; i--)
	{
		newSTU = new student;
		cin >> newSTU->studentID >> newSTU->name >> newSTU->gender
			>> newSTU->age >> newSTU->choice;
		if (i == studentNUM)
			first = newSTU;
		else
			lastSTU->next = newSTU;
		lastSTU = newSTU;
	}
	lastSTU->next = NULL;
	cout << "恭喜！信息系统已创建完成！" << endl;
}
void database::InsertStu()
{
	int index;
	student *one = new student;

	cout << "请输入你要插入的考生的位置：";
	cin >> index;
	if (index <= 0 || index > studentNUM + 1)
	{
		cout << "对不起：输入非法，无法插入到相应位置。" << endl;
		return;
	}
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
	cin >> one->studentID >> one->name >> one->gender
		>> one->age >> one->choice;
	studentNUM++;

	if (index == 1)
	{
		one->next = first;
		first = one;
	}
	else
	{
		student *temp = first;
		for (int i = index - 2; i; i--)
			temp = temp->next;
		one->next = temp->next;
		temp->next = one;
	}
}
void database::DeleteStu()
{
	if (isEmpty())
	{
		cout << "对不起：目前没有考生可以删除。" << endl;
		return;
	}

	string id;
	cout << "请输入你要删除的考生的考号：";
	cin >> id;

	student *StudentToDel, *previousStudent;
	search(id, StudentToDel, previousStudent);
	if (StudentToDel == NULL)
	{
		cout << "对不起：没有找到相关考生。" << endl;
		return;
	}

	studentNUM--;
	if (previousStudent == NULL)
		first = StudentToDel->next;
	else
		previousStudent->next = StudentToDel->next;
	delete StudentToDel;
}
void database::FindStu()
{
	if (isEmpty())
	{
		cout << "对不起：目前没有考生可供查找。" << endl;
		return;
	}

	string id;
	cout << "请输入你要查找的考生的考号：";
	cin >> id;

	student *StudentToFind,*temp;
	search(id, StudentToFind, temp);
	if (StudentToFind == NULL)
	{
		cout << "对不起：没有找到相关考生。" << endl;
		return;
	}

	HeadDisplay();
	SmpDisplay(StudentToFind);
}
void database::ReviseInfo()
{
	if (isEmpty())
	{
		cout << "对不起：目前没有考生可供修改。" << endl;
		return;
	}

	string id;
	cout << "请输入你要修改的考生的考号：";
	cin >> id;

	student *StudentToFind, *temp;
	search(id, StudentToFind, temp);
	if (StudentToFind == NULL)
	{
		cout << "对不起：没有找到相关考生。" << endl;
		return;
	}

	int itemToRevise;
	cout << "请输入你要修改项目（1为考号，2为姓名，3为性别，4为年龄，5为报考类别）"<<endl;
	cout << "请输入你要修改项目：";
	cin >> itemToRevise;

	switch (itemToRevise)
	{
	case 1:
		cout << "请输入新的考号：";
		cin >> StudentToFind->studentID;
		break;
	case 2:
		cout << "请输入新的姓名：";
		cin >> StudentToFind->name;
		break;
	case 3:
		cout << "请输入新的性别：";
		cin >> StudentToFind->gender;
		break;
	case 4:
		cout << "请输入新的年龄：";
		cin >> StudentToFind->age;
		break;
	case 5:
		cout << "请输入新的报考类别：";
		cin >> StudentToFind->choice;
		break;
	default:
		cout << "对不起：输入的项目不存在。" << endl;
	}
}
void database::StatDatabase()
{
	if (isEmpty())
	{
		cout << "目前数据库中暂无考生。" << endl;
		return;
	}
	cout << "目前共有" << studentNUM << "名考生。" << endl;
	HeadDisplay();

	student *student = first;
	while (student != NULL)
	{
		SmpDisplay(student);
		student = student->next;
	}
}
int main()
{
	database db;
	db.BulidDatabase();

	bool exit = 0;
	while (!exit)
	{
		cout << endl;

		int funTodo;
		cout << "请输入你要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
		cout << "请输入你要进行的操作：";
		cin >> funTodo;

		switch (funTodo)
		{
		case 1:
			db.InsertStu();
			break;
		case 2:
			db.DeleteStu();
			break;
		case 3:
			db.FindStu();
			break;
		case 4:
			db.ReviseInfo();
			break;
		case 5:
			db.StatDatabase();
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "对不起：输入的操作不存在。" << endl;
		}
	}
}
