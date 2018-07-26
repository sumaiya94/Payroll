# include <iostream>
# include <fstream>
# include <iomanip>
# include <string>
# include <limits>

using namespace std;

const int SIZE = 500;
const double medprem = 10.0;

ofstream ofs("Payroll");

// Calculate gross pay according to the hours worked
double calcpay(int hours, double rate)
{
	// Calculate gross pay for regular pay
	if ((hours > 0) && (hours < 41))
	{
		return (hours * rate);
	}

	// Calculate gross pay for overtime
	if ((hours > 40) && (hours < 61))
	{
		return (hours - 40) * (1.5 * rate) + (40 * rate);
	}

	// Calculate gross pay for double time
	if ((hours > 60) && (hours < 101))
	{
		return (hours - 60) * (2 * rate) + 20 * (1.5 * rate) + (40 * rate);
	}
}

// Print the pay stub with the deductions and employee information
void print (string name1, int num, int hours, int rate, double grosspay, double fedtax, double statetax, double fica, double k,
	double medicaid, double medicare, double netpay, double deduc)
{
	
	ofs << "************************************************************************************" << endl;

	// Round all decimals to two decimal points
	ofs << setprecision(2) << fixed;

	// Print the values for the pay stubs
	ofs << setw(3) << left << "*" << setw(12) << "Employee"<< setw(12) << left << "Employee"<< setw(16) << left << "Company"
		<< setw(22) << right << "Deductions" << setw(10) << "Pay" << setw(9) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(6) << right << "Name" << setw(13) << "Number" << setw(10) << "Name" 
		<< setw(52) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(12) << left << name1 << setw(5) << right << num << setw(13) << "Atlar Co"
		<< setw(20) << right << "Gross Pay" << setw(20) << right << "$" << setw(8) << grosspay << setw(3) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "Federal Tax" << setw(3) << "$" << setw(8) << fedtax 
		<< setw(20) << right << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "State Tax" << setw(3) << "$" << setw(8) << statetax 
		<< setw(20) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "FICA" << setw(3) << "$" << setw(8) << fica 
		<< setw(20)  << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "401K" << setw(3) << "$" << setw(8) << k
		<< setw(20) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "Medical Prem." << setw(3) << "$" << setw(8) << medprem 
		<< setw(20) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "Medicaid" << setw(3) << "$" << setw(8) << medicaid
		<< setw(20) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "Medicare" << setw(3) << "$" << setw(8) << medicare 
		<< setw(20) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << " Total Deductions" << setw(3) << "$" << setw(8) << deduc 
		<< setw(20) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(18) << left << "Hours Worked" << setw(3) << right << hours << setw(60) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(18) << left << "Hourly Rate" << setw(3) << right << rate << setw(60) << "*" << endl;
	ofs << setw(3) << left << "*" << setw(50) << right << "Net Pay" << setw(20) << right << "$" << setw(8) << netpay 
		<< setw(3) << "*" << endl;

	ofs << "************************************************************************************" << endl;
	
	// Print ten blank lines
	for (int i = 0; i < 10; i++)
	{
		ofs << endl;
	}
}

// Print the error stub: employee name, number, and the wrong input (hour or rate)
void printerr(string name2[], int nbr[], int ehour[], int erate[], int toterr)
{
	ofs << "____________________________________________________________________________________" << endl;
	ofs << setw(2) << left << "|" << "The following number of records failed for processing: " << toterr 
		<< setw(26) << right << "|" << endl;
	ofs << setw(2) << left << "|" << "Employee Name   " << "Employee Number   " << "Date of Payment   " << "Reason"
		<< setw(24) << right << "|" << endl;

	// Print all the wrong inputs
	for (int i = 0; i < toterr; i++)
	{
		// Print the wrong hours worked
		if ((ehour[i] < 1) || (ehour[i] > 100))
		{
			ofs << setw(2) << left << "|"  << setw(16) << left << name2[i] << setw(18) << left << nbr[i] << setw(18) << left << "3/19/17  " 
				<< "Incorrect Hours Worked " << "[" << setw(3) << right << ehour[i] << setw(2) << left << "]" << "|"  << endl;
		}

		// Print the wrong hourly rate
		if ((erate[i] < 10) || (erate[i] > 100))
		{
			ofs << setw(2) << left << "|"  << setw(16) << left << name2[i] << setw(18) << left << nbr[i] << setw(18) << "3/19/17  " 
				<< "Incorrect Hourly Rate " << setw (2) << right << "[" << setw(3) << right << erate[i] << setw(2) << left << "]" 
				<< setw(1) << right << "|"  << endl;
		}
	}

	ofs << "____________________________________________________________________________________" << endl;

}

// Print the total of all stubs, total pay stubs, total error stubs, total gross pay, and total net pay
void totprint(int totpay, int toterr, double totgross, double totnet)
{
	// Print ten blank lines
	for (int i = 0; i < 10; i++)
	{
		ofs << endl;
	}

	ofs << "*************TOTAL************" << endl;

	// Total stubs
	int allstubs = 0;
	allstubs = totpay + toterr; 

	int set1 = 22;
	int set2 = 8;

	ofs << setw(set1) << left << "Total records:" << setw(set2) << right << allstubs << endl;
	ofs << setw(set1) << left << "Total pay stubs:" << setw(set2) << right << totpay << endl;
	ofs << setw(set1) << left << "Total error stubs:" << setw(set2) << right << toterr << endl;
	ofs << setw(set1) << left << "Total for payroll:" << setw(set2) << right << totgross << endl;
	ofs << setw(set1) << left << "Total for net pay:" << setw(set2) << right << totnet << endl;
}

// Prompt user to enter employee information for payroll or quit 
void menu()
{
	int option = 0;

	double grosspay = 0.0;
	double netpay = 0.0;
	double fedtax = 0.0;
	double statetax = 0.0;
	double fica = 0.0;
	double k = 0.0;
	double medicaid = 0.0;
	double medicare = 0.0;
	double deduc = 0.0;
	double totgross = 0.0;
	double totnet = 0.0;
	double totpay = 0.0;

	int i = 0;

	int ehour[SIZE];
	int erate[SIZE];
	string name2[SIZE];
	int nbr[SIZE];
	int toterr = 0;

	while (option != 2)
	{
		// Display options to enter employee information or quit
		cout << "1: Enter employee information" << endl;
		cout << "2: Quit" << endl;
		cout << "Enter 1 or 2: ";

		cin >> option;
		
		switch (option)
		{
		// Enter employee information
		case 1: 
		{
			string name1 = "";
			int num = 0;
			int hours = 0;
			double rate = 0.0;

			cout << "Enter employee name: ";
			cin >> name1;

			cout << "Enter employee number: ";
			cin >> num;
						
			cout << "Enter hours worked: ";
			cin >> hours;

			cout << "Enter hourly rate: ";
			cin >> rate;

			

			// If hours or rate is not in the correct range put values in array so it could print in the error stub
			if ((hours < 1) || (hours > 100) || (rate < 10) || (rate > 100))
			{

				ehour[i] = hours;
				erate[i] = rate;
				name2[i] = name1;
				nbr[i] = num;
				i++;
				// total error stubs
				toterr++;

				break;
			}
						
			// Else print payroll stub
			else 
			{

				double grosspay = 0.0;
				double netpay = 0.0;
				double fedtax = 0.0;
				double statetax = 0.0;
				double fica = 0.0;
				double k = 0.0;
				double medicaid = 0.0;
				double medicare = 0.0;
				double deduc = 0.0;
				double totgross = 0.0;
				double totnet = 0.0;
				double totpay = 0.0;

				// Calculate gross pay
				grosspay = calcpay(hours, rate);

				// Get total gross pay of all the payroll stubs
				totgross += grosspay;

				// Get all the deductions
				fedtax = grosspay * 0.2;
				statetax = grosspay * 0.05;
				fica = grosspay * 0.08;
				k = grosspay * 0.06;
				medicaid = grosspay * 0.02;
				medicare = grosspay * 0.03;

				// Total of all the deductions
				deduc = (fedtax + statetax + fica + k + medprem + medicaid + medicare);

				// Calculate net pay
				netpay = grosspay - deduc;

				// Total of all the net pays
				totnet += netpay;

				// Print the pay roll
				print(name1, num, hours, rate, grosspay, fedtax, statetax, fica, k, medicaid, medicare, netpay, deduc);

				// Get the payroll count
				totpay++;

				break;
			}
		}

		case 2:
		{
			// Print the error stub
			printerr(name2, nbr, ehour, erate, toterr);

			// Print the total pay stubs, error stubs, gross pay, and net pay
			totprint(totpay, toterr, totgross, totnet);
			break;
		}

		default:
		{
			// Prompt user to enter only one or two
			cout << "Error. You did not enter 1 or 2." << endl;
			cout << endl;

			break;
		}
		}
	}
}

// Main 
int main()
{
	menu();
	ofs.close();
	return 0;
}

