/*

This system simplifies the management of hostel accommodations, making it easier to allocate and manage student rooms.
The end user for this system is warden.
The capacity of each room is assumed to be 3 students.

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class hostel
{
		int room_number;
		char name[50];
		char address[50];
		char phone_number[10];
		char course[50];
	public:
		int menu();
		int add_room();
		int display_room();
		int rooms_sel();
		int edit_sel();
		int check_avail(int);
		int modify_room(int);
		int delete_record(int);
		int transfer_student();
};

//to display the main menu
int hostel::menu()
{
	int choice = 0;
	while (choice != 6)
	{
		cout << "\n\n\n\n\n\t-------------------------------------";
		cout << "\n\t\t ----MAIN MENU----";
		cout << "\n\t-------------------------------------";
		
		cout << "\n\n\n\t1.Press 1 to Book A Room";
		cout << "\n\t2.Press 2 to Display Student Record";
		cout << "\n\t3.Press 3 to Check for Rooms Allotted";
		cout << "\n\t4.Press 4 to Edit Record";
		cout << "\n\t6.Press 5 to Exit";
		cout << "\n\n\tEnter Your Desired Choice: ";
		cin >> choice;
		
		switch (choice)
		{
			case 1:
				add_room();
				break;
			case 2:
				display_room();
				break;
			case 3:
				rooms_sel();
				break;
			case 4:
				edit_sel();
				break;
			case 5:
				exit(0);
				
			default:
				{
					cout << "\n\n\t\t\tWRONG CHOICE!!!";
				}
		}
	}
	return 0;
}

//to add a new student to a particular room
int hostel::add_room()
{
    int r, flag, count;
    ifstream fin("Record.txt", ios::in);
    ofstream fout("Record.txt", ios::app);
    cout << "\n--------------------------------------";
    cout << "\n\t ENTER STUDENT DETAILS :";
    cout << "\n--------------------------------------";
    cout << "\n\n Room number: ";
    cin >> r;
    count = check_avail(r);
    if (count >= 3)
    {
        cout << "\n\t\tTHE ROOM IS ALREADY FULL!!!";
    }
    else
    {
        room_number = r;
        cout << "\n Enter your Name: ";
        fflush(stdin);
        cin.getline(name, 50);
        cout << "\n Enter Address: ";
        fflush(stdin);
        cin.getline(address, 50);
        cout << "\n Enter Phone Number: ";
        fflush(stdin);
        cin.getline(phone_number, 10);
        cout << "\n Enter Course: ";
        fflush(stdin);
        cin.getline(course, 50);
        cout << endl;
        fout.write((char*)this, sizeof(*this));
        cout << "\n\n\tROOM ALLOTTED!!!";
    }
    fin.close();
    fout.close();
    return 0;
}

int hostel::display_room()
{
	ifstream fin("Record.txt", ios::in);
	char searchName[50];
	
	cout << "\n Enter Student Name to search: ";
	cin.ignore();
	cin.getline(searchName, 50);
	bool studentFound = false;
	
	while (fin.read((char*)this, sizeof(*this)))
	{
		if (strcmp(name, searchName) == 0)
		{
			cout << "\n--------------------------------------------------------";
			cout << "\n\t\tHERE ARE THE STUDENT DETAILS:";
			cout << "\n----------------------------------------------------------";
			cout << "\n Student Name: " << name;
			cout << "\n Room number: " << room_number;
			cout << "\n Address: " << address;
			cout << "\n Phone number. " << phone_number;
			cout << "\n Course: " << course;
			studentFound = true;
		}
	}

	if (!studentFound)
	{
		cout << "\n SORRY!!! NO STUDENT IS FOUND WITH THE NAME : " << searchName ;
	}

	fin.close();
	return 0;
}

//display the data of selected or occupied rooms
int hostel::rooms_sel()
{
	ifstream fin("Record.txt", ios::in);
	hostel records[100]; // Assuming a maximum of 100 records
	int count = 0;
	int totalstudents = 0; // Counter for total students who have been allotted with a room
	
	while (fin.read((char *)&records[count], sizeof(records[count])))
	{
		count++;
		totalstudents++;
	}

	cout << "\n\nTOTAL NUMBER OF STUDENTS : " << totalstudents;

	cout << "\n\n\n------------------------------------------------------------";
	cout << "\n  Here is the list of Allotted Rooms :";
	cout << "\n------------------------------------------------------------\n\n";
	
	cout << endl << "Room Number" << setw(25) << "Student Name" << setw(21) << "Address" << setw(25) << "Phone number" << setw(20) << "Course";

	// Sort the array based on room numbers
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (records[j].room_number > records[j + 1].room_number)
			{
				hostel temp = records[j];
				records[j] = records[j + 1];
				records[j + 1] = temp;
			}
		}
	}

	// Display the sorted records
	for (int i = 0; i < count; i++)
	{
		cout << endl <<setw(7)<< records[i].room_number << setw(25) << records[i].name << setw(25) << records[i].address << setw(23) << records[i].phone_number << setw(22) << records[i].course;
	}
	fin.close();
	return 0;
}

//to edit the information a a particular room out of all the selected rooms.
int hostel::edit_sel()
{
	int choice, r;
	cout << "\n---------------------------------------";
	cout << "\n        -----EDIT MENU-----" << endl;
	cout << "---------------------------------------\n" << endl;
	
	cout << "1.Modify Student Record." << endl;
	cout << "2.Transfer Student to Another Room." << endl;
	cout << "3.Delete Student Record." << endl;
	cout << "ENTER YOUR CHOICE :";
	cin >> choice;

	switch (choice)
	{
		case 1:
			cout << "\n Enter Room Number: ";
			cin >> r;
			modify_room(r);
			break;
		case 2:
			transfer_student();
			break;
		case 3:
			cout << "\n Enter Room Number: ";
			cin >> r;
			delete_record(r);
			break;
		default:
			cout << "\nSorry!!! Wrong Choice!!";
	}
	return 0;
}

//delete the record of a particular student.
int hostel::delete_record(int r)
{
	int flag = 0;
	char ch;
	ifstream fin("Record.txt", ios::in);
	ofstream fout("temp.txt", ios::out);
	cout << "\n\nEnter the name of student whose record is to be deleted: ";
	cin.ignore();
	char studentName[50];
	cin.getline(studentName, 50);

	while (fin.read((char*)this, sizeof(*this)))
	{
		if (room_number == r && strcmp(name, studentName) == 0)
		{
			cout << "\n Student Name: " << name;
			cout << "\n Address: " << address;
			cout << "\n Phone Number: " << phone_number;
			cout << "\n Course: " << course;
			cout << "\n\n Are you sure you want to delete this record (y/n)? : ";
			cin >> ch;

			if (ch == 'n')
				fout.write((char*)this, sizeof(*this));
			flag = 1;
		}
		else
		{
			fout.write((char*)this, sizeof(*this));
		}
	}
	fin.close();
	fout.close();

	if (flag == 0)
	{
		cout << "\nSorry, either the room number or student name is incorrect or vacant.";
	}
	else
	{
		remove("Record.txt");
		rename("temp.txt", "Record.txt");
	}
	return 0;
}

//to transfer a particular student from one room to another
int hostel::transfer_student()
{
    int old_room, new_room;
    char studentName[50];
    cout << "\nEnter the name of the student to transfer: ";
    cin.ignore(); // Clear the input buffer
    cin.getline(studentName, 50);

    cout << "\nEnter the current room number of the student: ";
    cin >> old_room;

    cout << "\nEnter the new room number to transfer the student: ";
    cin >> new_room;

    // Check if the new room is available
    int count = check_avail(new_room);
    if (count >= 3)
    {
        cout << "\n\t\tTHE NEW ROOM IS ALREADY FULL!!!";
        return 0;
    }

    ifstream fin("Record.txt", ios::in);
    ofstream fout("temp.txt", ios::out);
    int flag = 0;

    while (fin.read((char*)this, sizeof(*this)))
    {
        if (strcmp(name, studentName) == 0 && room_number == old_room)
        {
            flag = 1;
            room_number = new_room;
            fout.write((char*)this, sizeof(*this));
            cout << "\nStudent " << name << " transferred from room " << old_room << " to room " << new_room;
        }
        else
        {
            fout.write((char*)this, sizeof(*this));
        }
    }

    fin.close();
    fout.close();
    if (flag == 0)
    {
        cout << "\nStudent " << studentName << " not found in room " << old_room;
    }
    else
    {
        remove("Record.txt");
        rename("temp.txt", "Record.txt");
    }
    return 0;
}

//to modify all the details (name, address, phone number, course) of a student of a particular room
int hostel::modify_room(int room_)
{
	long position;
	int flag = 0;
	fstream file("Record.txt", ios::in | ios::out | ios::binary);
	cout << "\n\nEnter the name of student whose record is to be modified: ";
	cin.ignore();
	char studentName[50];
	cin.getline(studentName, 50);

	while (!file.eof())
	{
		position = file.tellg();
		file.read(reinterpret_cast<char*>(this), sizeof(*this));
		if (room_number == room_ && strcmp(name, studentName) == 0)
		{
			cout << "\n ***********************";
			cout << "\n  ENTER THE NEW DETAILS";
			cout << "\n ***********************";
			
			cout << "\n Enter your Name: \t";
			fflush(stdin);
			cin.getline(name,50);
	
			cout << "\n Enter Address: \t";
			fflush(stdin);
			cin.getline(address,50);
			
			cout << "\n Enter Phone Number:\t";
			fflush(stdin);
			cin.getline(phone_number,10);
			
			cout << "\n Enter Course: \t";
			fflush(stdin);
			cin.getline(course,50);
	
			file.seekp(position);
			file.write(reinterpret_cast<char*>(this), sizeof(*this));
			cout << "\n\tRECORD HAS BEEN MODIFIED SUCCESSFULLY!!!";
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		cout << "\n Sorry your desired room no. is vacant or the student name is not found. ";

	file.close();
	return 0;
}

//checks the availability of room.
int hostel::check_avail(int r)
{
	int count = 0;
	ifstream fin("Record.txt", ios::in);
	while (fin.read((char*)this, sizeof(*this)))
	{
		if (room_number == r)
		{
			count++;
		}
	}
	
	fin.close();
	return count;
}

int main()
{
	hostel h;
	cout << "\n\t\t\t\t\t\t    **********************************";
	cout << "\n\t\t\t\t\t\t         HOSTEL MANAGEMENT SYSTEM  ";
	cout << "\n\t\t\t\t\t\t    **********************************";
	h.menu();
	return 0;
}
