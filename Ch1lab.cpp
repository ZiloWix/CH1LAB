#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

const double q = 0.947; // 0.974 - ��� �������� , 0.947 - ��������������� ���������
const double solve = 0.653271187094403;//1 - pow(2,1.0/3)-pow(2,2.0/3) - ��� ��������, 0.653271187094403 - ��������������� ���������
ofstream file, fefile, refile;


// �������
inline double f(double x)
{
	double coeff;
	//coeff = (11 - 0.33) + 0.66 * ((double)rand() / RAND_MAX); //������ � �����. ���������� 3%
	//coeff = (11 - 0.22) + 0.44 * ((double)rand() / RAND_MAX); //������ � �����. ���������� 2%
	//coeff = (11 - 0.11) + 0.22 * ((double)rand() / RAND_MAX); //������ � �����. ���������� 1%
	coeff = 11; // ��� ����������
	return (x - 0.09523809523 * (x * x * x - 3 * x * x - 3 * x + coeff));
}

// ��������������� ���������
inline double f2(double x)
{
	double coeff;
	coeff = (1 - 0.03) + 0.06 * ((double)rand() / RAND_MAX); //������ � �����. ���������� 3%
	//coeff = (1 - 0.02) + 0.04 * ((double)rand() / RAND_MAX); //������ � �����. ���������� 2%
	//coeff = (1 - 0.01) + 0.02 * ((double)rand() / RAND_MAX); //������ � �����. ���������� 1%
	//coeff = 1; // ��� ����������
	//return (coeff * x * sin(x) - cos(x));
	return (x - 0.55555555555 * (2 * x * sin(x) - cos(x*coeff)));

}

//����������� �����������
inline double facterror(double x)
{
	return fabs(solve - x);
}

//������������� �����������
inline double relativeerror(double x)
{
	return fabs(facterror(x) / solve) * 100.0;
}

//���������� � �����
void saveinfile(int i, double x3)
{
	file << i << endl;
	refile << setprecision(15) << relativeerror(x3) << endl;
}

int main()
{
	//file.open("pol_3_iterations.txt");
	//refile.open("pol_3_relativeeror.txt");

	int i = 1;
	double x0, x1, x2, x3, X2, err = 0.0001;

	x0 = 0.4; // (-2) - ��� ��������, 0.4 - ��������������� ���������
	x1 = f2(x0);
	x2 = f2(x1);
	
	do
	{
		X2 = (x2 * x0 - x1 * x1) / (x2 - 2 * x1 + x0);
		x3 = f2(X2); 
		
		saveinfile(i, x3);

		/*cout << setw(10) << i << "  ---  " << setprecision(15) << x3 << endl
			<< "fact error  ---  " << setprecision(15) << facterror(x3) << endl
			<< "rela error  ---  " << setprecision(15) << relativeerror(x3) << endl;*/

		if (fabs(x3 - X2) > err * (1.0 - q) / q && (x2 - 2 * x1 + x0) != 0)
		{
			x0 = X2;
			x1 = x3;
			x2 = f2(x1);
		}

		i++;
	} while (fabs(x3 - X2) >  err * (1.0 - q) / q && (x2 - 2 * x1 + x0) != 0);
	cout << "rela error  ---  " << setprecision(15) << relativeerror(x3) << endl;
	//file.close();
	//refile.close();
	return 0;
}
