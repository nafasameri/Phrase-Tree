// Phrase Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "iostream"
#include "conio.h"
#include "string"
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define IsOperator(x) (x=='-'||x=='+'||x=='/'||x=='*')
#define IsHigh(x) (x=='*'||x=='/')
#define IsLow(x)  (x=='-'||x=='+')

template <class T>


class Stack
{
private:
	T s[15];
	int top;
public:
	Stack() { top = -1; }

	bool IsImpty() { return top == -1; }

	bool IsFull() { return top == 14; }

	void Push(string x)
	{
		if (!IsFull())
			s[++top] = x;
	}

	void Push(char x)
	{
		if (!IsFull())
			s[++top] = x;
	}
	
	T Pop()
	{
		T temp = s[top--];
		return temp;
	}

	friend string InfixToPostfix(string str);
	friend string PostfixToInfix(string postfix);
};


string Reverse(string str)
{
	string temp;
	for (int i = str.size()-1; i >= 0; i--)
		temp += str[i];
	return temp;
}

string InfixToPostfix(string str)
{
	Stack<char> stk;
	string temp = "";
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!IsOperator(str[i]))
			temp += str[i];
		else if (IsOperator(str[i]))
			if (stk.IsImpty())
				stk.Push(str[i]);
			else if ((IsHigh(str[i]) && IsHigh(stk.s[stk.top])) || (IsLow(str[i]) && IsLow(stk.s[stk.top])) || IsHigh(stk.s[stk.top]))
			{
				//while (!stk.IsImpty())
				while((IsHigh(str[i]) && IsHigh(stk.s[stk.top])) || (IsLow(str[i]) && IsLow(stk.s[stk.top])) || IsHigh(stk.s[stk.top]))
					temp += stk.Pop();
				stk.Push(str[i]);
			}
			else
				stk.Push(str[i]);
	}
	while (!stk.IsImpty())
		temp += stk.Pop();
	return temp;
}

string PostfixToInfix(string postfix)
{
	Stack<string> stk;
	for (unsigned int i = 0; i < postfix.size(); i++)
	{
		if (!IsOperator(postfix[i]))
			stk.Push(postfix[i]);
		if (IsOperator(postfix[i]))
		{
			string str1 = stk.Pop();
			string str2 = stk.Pop();
			string str = '(' + str2 + postfix[i] + str1 + ')';
			stk.Push(str);
		}
	}
	string temp = "";
	while (!stk.IsImpty())
		temp += stk.Pop();
	return temp;
}

string PrefixToTree(string prefix)
{
	bool flag = false;
	bool flagRight = false;
	bool flagLeft = false;
	string temp = "               ";
	int j = 0;
	for (unsigned int i = 0; i < prefix.size(); i++)
		if (IsOperator(prefix[i]))
		{
			//if()
			temp[i] = prefix[i];
			j = i;
		}
		else if (!IsOperator(prefix[i]))
			if (flag == false)
			{
				temp[2 * j + 1] = prefix[i];
				flag = true;
			}
			else if (flag == true)
			{
				temp[2 * j + 2] = prefix[i];
				flag = false;
			}
 	return temp;
}

void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != hConsole)
	{
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hConsole, pos);
	}
}

void ShowTreeThemeplate()
{
	int temp = 50;
	for (int i = 1; i < 9; i++)
	{
		gotoxy(temp - i, i); cout << "/";
		gotoxy(temp + i, i); cout << "\\";
	}
	gotoxy(40, 10); cout << "/";
	gotoxy(39, 11); cout << "/";
	gotoxy(38, 12); cout << "/";
	gotoxy(37, 13); cout << "/";
	gotoxy(42, 10); cout << "\\";
	gotoxy(43, 11); cout << "\\";
	gotoxy(44, 12); cout << "\\";
	gotoxy(45, 13); cout << "\\";

	gotoxy(58, 10); cout << "/";
	gotoxy(57, 11); cout << "/";
	gotoxy(56, 12); cout << "/";
	gotoxy(55, 13); cout << "/";
	gotoxy(60, 10); cout << "\\";
	gotoxy(61, 11); cout << "\\";
	gotoxy(62, 12); cout << "\\";
	gotoxy(63, 13); cout << "\\";

	gotoxy(35, 15); cout << "/";
	gotoxy(37, 15); cout << "\\";

	gotoxy(45, 15); cout << "/";
	gotoxy(47, 15); cout << "\\";

	gotoxy(53, 15); cout << "/";
	gotoxy(55, 15); cout << "\\";

	gotoxy(63, 15); cout << "/";
	gotoxy(65, 15); cout << "\\";

}

void ShowDataTree(string Array)
{
	gotoxy(50, 0); cout << Array[0];
	gotoxy(41, 9); cout << Array[1];
	gotoxy(59, 9); cout << Array[2];
	gotoxy(36, 14); cout << Array[3];
	gotoxy(46, 14); cout << Array[4];
	gotoxy(54, 14); cout << Array[5];
	gotoxy(64, 14); cout << Array[6];
	gotoxy(34, 16); cout << Array[7];
	gotoxy(38, 16); cout << Array[8];
	gotoxy(44, 16); cout << Array[9];
	gotoxy(48, 16); cout << Array[10];
	gotoxy(52, 16); cout << Array[11];
	gotoxy(56, 16); cout << Array[12];
	gotoxy(62, 16); cout << Array[13];
	gotoxy(66, 16); cout << Array[14];
}


void main()
{
	cout << "Please enter the phraes: ";
	string str;
	cin >> str;
	
	///postfix
	SetConsoleTextAttribute(hConsole, 5);
	cout << "Postfix : " << InfixToPostfix(str) << endl;
	_getch();

	///prefix
	SetConsoleTextAttribute(hConsole, 12);
	cout << "Prefix : " << Reverse(InfixToPostfix(Reverse(str))) << endl;
	_getch();

	///Postfix to infix
	SetConsoleTextAttribute(hConsole, 10);
	cout << "Infix : " << PostfixToInfix(InfixToPostfix(str)) << endl;
	_getch();

	///tree
	SetConsoleTextAttribute(hConsole, 6);
	cout << "Phrase Tree";
	ShowTreeThemeplate();
	ShowDataTree(PrefixToTree(Reverse(InfixToPostfix(Reverse(str)))));
	_getch();
}