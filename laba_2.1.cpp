// laba_2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma warning(disable : 4996)
using namespace std;



struct user
{
	char login[50];
	long long pin;
	bool exist = true;
}User, ExistUser;

struct ticket
{
	char namestation[50];
	double cost;
	int id;
	bool exist = true;
}Station;

long long Hesh(char* array)
{
	const int k = 31, mod = 1e9 + 7;
	long long h = 0, m = 1;
	long size = (sizeof(array)) / sizeof(array[0]);

	for (int i = 0; i < size; i++) {
		int x = (int)(array[i] - 'a' + 1);
		h = (h + m * x) % mod;
		m = (m * k) % mod;
	}
	return h;
}

bool IsNotNewUser(const user& NewUser)
{
	FILE* fp;
	bool isnot = false;
	user ExistUser;
	fp = fopen("users.bin", "rb");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		fread(&ExistUser, sizeof(user), 1, fp);
		if (strcmp(ExistUser.login, NewUser.login) == 0)
		{
			isnot = true;
			fclose(fp);
			return true;
		}
	}
	return false;
}

void ReadUser()
{

	FILE* fp;
	fp = fopen("users.bin", "rb");
	fseek(fp, sizeof(User), SEEK_END);
	long size = ftell(fp);
	fseek(fp, sizeof(User), SEEK_SET);
	int number = size / sizeof(user);
	user* User = new user[number];

	while (!feof(fp))
	{

		for (int i = 0; i < number - 2; i++)
		{
			fread(&User[i], sizeof(user), number, fp);
			{
				cout << "User login " << User[i].login << endl;
				cout << "User password " << User[i].pin << endl;
				cout << "Flag of existence: " << User[i].exist << endl;
				cout << endl;
			}

		}
	}
	fclose(fp);
}

void ReadStations()
{
	FILE* f;
	f = fopen("station.bin", "rb");
	fseek(f, sizeof(Station), SEEK_END);
	long size = ftell(f);
	fseek(f, sizeof(Station), SEEK_SET);
	int number = size / sizeof(ticket);
	ticket* Station = new ticket[number];

	while (!feof(f))
	{
		for (int i = 0; i < number - 2; i++)
		{
			fread(&Station[i], sizeof(ticket), number, f);
			cout << "Station's name: " << Station[i].namestation << endl;
			cout << "Train's cost: " << Station[i].cost << endl;
			cout << "Train's id: " << Station[i].id << endl;
			cout << "Train's exsistens: " << Station[i].exist << endl;
			cout << endl;
		}
	}

	fclose(f);

}

void StationID()
{
	FILE* f;
	f = fopen("station.bin", "rb");
	fseek(f, sizeof(Station), SEEK_END);
	long size = ftell(f);
	fseek(f, sizeof(Station), SEEK_SET);
	int number = size / sizeof(ticket);
	ticket* Station = new ticket[number];
	while (!feof(f))
	{
		for (int i = 0; i < number - 2; i++)
		{
			fread(&Station[i], sizeof(ticket), number, f);
		}
	}
}

void DeleteUser()
{
	FILE* fp;
	FILE* fs;
	user ExistUser;
	fs = fopen("deletestudent.bin", "wb");
	user NewUser;
	fp = fopen("users.bin", "rb");
	fseek(fp, sizeof(User), SEEK_END);
	long size = ftell(fp);
	fseek(fp, sizeof(User), SEEK_SET);
	int number = size / sizeof(user);
	cout << "Enter login: "; cout << endl;
	cin >> NewUser.login;
	user* User = new user[number];
	while (!feof(fp))
	{
		for (int i = 0; i < number; i++)
		{
			fread(&User[i], sizeof(user), number, fp);
			if (strcmp(User[i].login, NewUser.login) == 0)
			{
				fread(&User[i], sizeof(User[i]), 1, fp);
				fwrite(&User[i].login, sizeof(User[i].login), 1, fs);
				fwrite(&User[i].pin, sizeof(User[i].pin), 1, fs);
				User[i].exist = false;
				/*NewUser.exist = User[i].exist;*/
				fwrite(&User[i].exist, sizeof(User[i].exist), 1, fs);
				cout << "Delete user " << User[i].login << endl;
				cout << "Delete user " << User[i].exist << endl;
			}
		}
	}
	fclose(fs);
	fclose(fp);
}

//void sql(char str[])
//{
//	char** words = NULL, * pntr = NULL;
//	int counter = 0;
//	for (pntr = strtok(str, " "); pntr != NULL; pntr = strtok(NULL, " ")) {
//		if ((words = (char**)realloc(words, sizeof(char*) * (counter + 1))) == NULL) {
//			cout << "Error!" << endl;
//			exit(5);
//		}
//		if ((words[counter] = _strdup(pntr)) == NULL) {
//			cout << "Error!";
//			exit(5);
//		}
//		++counter;
//	}
//	if (strcmp(words[counter - 3], "users") == 0) {
//		if ((strcmp(words[counter - 2], "login") == 0)) {
//			ReadUser(words[counter - 1]);
//		}
//	}
//}

bool IsNotNewStation(const ticket& NewStation)
{
	FILE* f;
	bool isnotnew = false;
	ticket ExistStation;
	f = fopen("station.bin", "rb");
	fseek(f, 0, SEEK_SET);
	while (!feof(f))
	{
		fread(&ExistStation, sizeof(ticket), 1, f);
		if (strcmp(ExistStation.namestation, NewStation.namestation) == 0)
		{
			isnotnew = true;
			fclose(f);
			return true;
		}
	}
	return false;
}

void AdminMenu()
{

	int number;
	cout << "--------------------------------------------" << endl;
	cout << "Enter what you want to do:" << endl;
	cout << "1) Read all users' information" << endl;
	cout << "2) Delete user" << endl;
	cout << "3) Create new station" << endl;
	cout << "4) Read all stations' information" << endl;
	cout << "--------------------------------------------" << endl;
	cin >> number; cout << endl;
	switch (number)
	{
	case 1:
	{
		ReadUser();
		return AdminMenu();
	}
	break;
	case 2:
	{
		DeleteUser();
		return AdminMenu();
	}
	break;
	case 3:
	{
		FILE* f;
		ticket NewStation;
		f = fopen("station.bin", "ab");
		fseek(f, 0, SEEK_SET);
		cout << "Enter name of Station: ";
		cout << endl;
		cin >> NewStation.namestation;
		while (!feof(f))
		{

			if (IsNotNewStation(NewStation) == true)
			{
				cout << "This station is already exist." << endl;
				return AdminMenu();
			}
			else
			{
				cout << "Enter cost of train"; cout << endl;
				cin >> NewStation.cost;
				cout << "Enter id of train"; cout << endl;
				cin >> NewStation.id;
				cout << "Exsistens " << Station.exist; cout << endl;
				fwrite(&NewStation, sizeof(NewStation), 1, f);
				cout << "New station " << NewStation.namestation << " was created." << endl;
				fclose(f);
				return AdminMenu();
			}
		}
	}
	break;
	case 4:
	{
		ReadStations();
		return AdminMenu();
	}
	break;
	}

}

void UserMenu()
{
	int number;
	cout << "--------------------------------------------" << endl;
	cout << "Choose: " << endl;
	cout << "1) See all stations" << endl;
	cout << "2) Buying a ticket" << endl;
	cout << "3) Exit" << endl;
	cout << "--------------------------------------------" << endl;
	cin >> number; cout << endl;
	switch (number)
	{
	case 1:
	{
		ReadStations();
		return UserMenu();
	}
	break;
	case 2:
	{
		FILE* f;
		f = fopen("station.bin", "rb");
		fseek(f, sizeof(Station), SEEK_END);
		long size = ftell(f);
		fseek(f, sizeof(Station), SEEK_SET);
		int number = size / sizeof(ticket);
		ticket* Station = new ticket[number];
		int k;
		int choose;
		cout << "Choose station from 0 to " << number - 3 << endl;
		ReadStations();
		cin >> k;
		int tickets;
		while (!feof(f))
		{
			fread(&Station->namestation, sizeof(Station->namestation), number, f);
			fread(&Station->cost, sizeof(Station->cost), number, f);
			cout << "You choose station " << Station[k].namestation << endl;
			cout << "Are you sure? (1-yes) (2-no)" << endl;
			cin >> choose;
			switch (choose)
			{
			case(1):
			{
				cout << "How many tickets you need?" << endl;
				cin >> tickets;
				cout << "Cost: " << tickets * Station[k].cost << endl;
				cout << "You bought " << tickets << " ticket(s) from Kyiv to " << Station[k].namestation << endl;
				return UserMenu();
			}
			break;
			case 2:
			{
				return UserMenu();
			}
			break;
			}
		}
		fclose(f);
		return UserMenu();
	}
	break;
	case 3:
	{
		cout << "Thanks for your trust in us. Bye!" << endl;
		system("pause");
	}
	break;
	}
}

int main()
{
	cout << "Enter 1 for login or 2 for register" << endl;
	int key;
	cin >> key; cout << endl;

	switch (key)
	{
	case 1:
	{
		user NewUser, ExistUser;
		FILE* fp = fopen("users.bin", "rb");
		fseek(fp, 0, SEEK_SET);
		if ((fp) == NULL)
		{
			cout << "Cannot open file" << endl;
			return NULL;
		}
		cout << "Enter login: "; cout << endl;
		cin >> NewUser.login;
		cout << "Enter parol: "; cout << endl;
		char pass[50];
		cin >> pass;
		NewUser.pin = Hesh(pass);
		cout << "--------------------------------------------" << endl;
		bool IsLogPerson = false;
		while (!feof(fp))
		{
			fread(&ExistUser, sizeof(ExistUser), 1, fp);

			if (IsNotNewUser(NewUser) == true)
			{
				if (ExistUser.pin == NewUser.pin)
				{
					IsLogPerson = true;
				}

			}
			else
			{
				cout << "Uncorrect login! Try again." << endl;
				return main();
			}

		}
		if (IsLogPerson = false)
		{
			cout << "Uncorrect password!" << endl;
			return main();
		}
		else
		{
			char loggin[50] = "kate";
			if (strcmp(NewUser.login, loggin) == 0)
			{
				cout << "Hi admin" << endl;
				AdminMenu();
			}
			else
			{
				cout << "Hey user" << endl;
				UserMenu();
			}
		}
	}
	break;

	case 2:
	{
		FILE* fp;
		char login[50], parol[50];
		user NewUser;
		fp = fopen("users.bin", "ab");
		fseek(fp, 0, SEEK_SET);
		cout << "Enter login: "; cout << endl;
		cin >> NewUser.login;
		cout << "Enter parol: "; cout << endl;
		char pass[50];
		cin >> pass;
		NewUser.pin = Hesh(pass);
		while (!feof(fp))
		{

			if (IsNotNewUser(NewUser) == true)
			{
				cout << "This login is already taken. Try another one." << endl;
				return main();
			}
			else
			{
				fwrite(&NewUser, sizeof(NewUser), 1, fp);
				fclose(fp);
				cout << "You are registed." << endl;
				return main();
			}

		}
	}
	break;
	}
}
