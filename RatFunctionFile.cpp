#include <bits/stdc++.h>
#include "RatHeaderFile.h"
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;
//struct Customer
struct Customer;

//Split Function
vector<string> split(const string &line, char delim)
{
	vector<string> tempLine;
	istringstream ss(line);
	string item;
	while(getline(ss,item,delim))
	{
		tempLine.push_back(item);
	}
	return tempLine;
}

//Read from the file function
void readFileCustomer(Customer *customerArray,int *size,string customerFile)
{
	ifstream inData;
	string line="";
	int i=0;
	inData.open(customerFile);
	if(inData.good())
	{
	        cout<<"\nReading from the "<<customerFile<<" File..."<<endl;
		while(getline(inData, line))
		{
			if(count(line.begin(),line.end(),'.')!=1 || count(line.begin(),line.end(),':')!=2)
			{
				cerr<<"Format does not match"<<endl;
				system("pause");
			}
			if(i<10)
			{
				vector<string> columns = split(line,':');
				vector<string> last = split(columns[2],'.');
				//checking if customer name or project name is empty or not
                                if(columns[0].empty() || columns[1].empty())
                                {
                                        cerr<<"Customer name or Project name can not be empty!System Exit!"<<endl;
                                        system("pause");
                                }
				customerArray[i]={columns[0],columns[1],last[0]};
				char arrayOfParts[last[0].length()];
                              	strcpy(arrayOfParts,last[0].c_str());
				//checking customer size
				if(sizeof(arrayOfParts)>=11)
				{
					cerr<<"Number of robot part is more than 10!System Exit!"<<endl;
					system("pause");
				}
				i++;
			}
			else
			{
				cerr<<"The file has more than 10 customers: The max number customer is 10!\nSYSTEM EXIT!"<<endl;
				system("pause");
			}
		}
		*size=i;
		inData.close();
	}
	else
	{
		*size=0;
		cout<<"Unable to open the file!"<<endl;
		system("PAUSE");
  	}
}
//print customer
void printCustomer(Customer *customerArray,int size)
{
	cout<<"Customer Name\tRobot Name\tRobot Parts"<<endl;
	for(int i=0;i<size;i++)
    	{
            cout<<customerArray[i].customerName<<"\t\t"<<customerArray[i].robotName<<"\t\t"<<customerArray[i].robotParts<<endl;
        }
}

//PARTS
struct Parts;
void readFileParts(Parts *partsArray,int *size,const string partsFile)
{
    ifstream inData;
	string line="";
	int i=0;
	char letterOrder='A';
	inData.open(partsFile);
	if(inData.is_open())
	{
		int numLines=0;
	   	cout<<"\nReading from "<<partsFile<<" Fthe File..."<<endl;
		while(getline(inData, line))
		{
			if(count(line.begin(),line.end(),'.')!=1 || count(line.begin(),line.end(),':')!=4)
                        {
                                cerr<<"Format does not match"<<endl;
				system("pause");
                        }
			numLines++;
			vector<string> columns = split(line,':');
			vector<string> last = split(columns[4],'.');
			string code=columns[0];
			//check the content 
			if(columns[0].empty() || columns[1].empty() || columns[2].empty() || columns[3].empty() || last[0].empty())
			{
				cerr<<"The Content of the file Part is not the same!"<<endl;
                                	system("pause");
			} 
			//if(code.length()==1)	//Checking part code is single letter
			//{
			//	if(isupper(code[0]))	//Checking part code is capital letter
			//	{
			//		code=columns[0];
			//	}
			//	else
			//	{
			//		cerr<<"The Part Code should be Capital Letter! System Exit!"<<endl;
			//		system("pause");
			//	}
			//}
			//else
			//{
			//	cerr<<"The Part Code Should Be Single Letter! System Exit!"<<endl;
			//	system("pause");
			//}
			//if(numLines>=6 || (letterOrder) != code[0])
                        //{
                          //      cerr<<"The Content of the file Part is not the same! Number of the line is more than 5!"<<endl;
                            //    system("pause");
                        //}
                        //++letterOrder;  
			try	//checking if max, min and complexity is number
			{
				partsArray[i]={code[0],columns[1],stoi(columns[2]),stoi(columns[3]),stoi(last[0])};
			}
			catch(exception e)
			{
				cerr<<"Minimum, Maximum and Complexity should be number"<<endl;
				system("pause");
			}
			i++;
		}
		*size=i;
		inData.close();
	}
	else
	{
		*size=0;
		cout<<"Unable to open the file!"<<endl;
		system("PAUSE");
  	}
}
//Print Parts
void printParts(Parts *partsArray,int size)
{
	cout<<"Part Code\tPartName\tMinimum\tMaximum\tComplexity"<<endl;
	for(int i=0;i<size;i++)
    	{
        	cout<<partsArray[i].partCode<<"\t\t"<<partsArray[i].partName<<"\t\t"<<partsArray[i].minLimit
        	<<"\t"<<partsArray[i].maxLimit<<"\t"<<partsArray[i].complexity<<endl;
        }
}
//  Checking Max and Min in builder project
void ListOfPartsCheck(Parts *partsArray,int size,Customer *customerArray,int custSize)
{
	int countPart=0;
	for(int i=0;i<custSize;i++)
	{
		string CustomerParts=customerArray[i].robotParts;
		char arrayCustParts[CustomerParts.length()+1];
		strcpy(arrayCustParts,CustomerParts.c_str());
		for(int i=0;i<size;i++)
		{
			for(char c:arrayCustParts)
			{
				if(c==partsArray[i].partCode)
				{
					countPart++;
				}
			}
			if(countPart>=partsArray[i].maxLimit+1 || countPart<=partsArray[i].minLimit-1)
			{
				cerr<<customerArray[i].customerName<<" :"<<partsArray[i].partName<<" reached max or min number parts."<<endl;
				system("pause");
			}
			countPart=0;
		}
	}
}
//BUILDER
struct Builders;
void readFileBuilders(Builders *buildersArray,int *size,string builderFile)
{
        ifstream inData;
        string line="";
        int i=0;
        inData.open(builderFile);
        if(inData.is_open())
        {
            cout<<"\nReading from "<<builderFile<<" the File..."<<endl;
            while(getline(inData, line))
            {
		if(count(line.begin(), line.end(), ':')!=2 || count(line.begin(), line.end(), '.')!=1)
		{
			cerr<<"Format does not match"<<endl;
			system("pause");
		}
		if(i<5)		//if builder is more than 5
		{
                	vector<string> columns = split(line,':');
                	vector<string> last = split(columns[2],'.');
			//checking if the builder name is empty or not
			if(columns[0].empty())
			{
				cerr<<"Builder number "<<i+1<<" does not have name! System Exit!"<<endl;
				system("pause");
			}
			if(stoi(last[0])<11 && stoi(last[0])>0 && stoi(columns[1])>1 && stoi(columns[1])<100)		//if ability and vari are not int
			{
				try
				{
					buildersArray[i]={columns[0],stoi(columns[1]),stoi(last[0])};
        	        		i++;
				}
				catch(exception e)
				{
					cerr<<"Ability and Variability should be number"<<endl;
					system("pause");
				}
			}
			else if(stoi(last[0])>=11 && stoi(last[0])<=0)
			{
				cerr<<"variability is greater than 10 or less than 0! System Exit!"<<endl;
				system("pause");
			}
			else if(stoi(columns[1])<=0 || stoi(columns[1])>=100)
			{
				cerr<<"Ability is greater than 99 or less than 1! System Exit!"<<endl;
                                system("pause");
			}
		}
		else
		{
			cerr<<"The number of builder is more than 5! System Exit!"<<endl;
			system("pause");
		}
            }
            *size=i;
            inData.close();
        }
        else
        {
            *size=0;
            cout<<"Unable to open the file!"<<endl;
            system("PAUSE");
        }
}
//Print Builders
void printBuilders(Builders *buildersArray,int size)
{
	cout<<"Builder Name\tAbility\tVariability"<<endl;
        for(int i=0;i<size;i++)
    	{
        	cout<<buildersArray[i].name<<"\t"<<buildersArray[i].ability<<"\t"<<buildersArray[i].variability<<endl;
        }
}

//*********************REPORT**********************************************
//return robot complexity function
int  robotComplexity(string listOfParts,Parts *partsArray,int size)
{
	int total=0;
	//converting to char array
	char arrayOfParts[listOfParts.length()+1];
	strcpy(arrayOfParts,listOfParts.c_str());
	for(int i=0;i<size;i++)
	{
		for(char part:arrayOfParts)
		{
			if(part==partsArray[i].partCode)
			{
				total+=partsArray[i].complexity;//if it exist in in File Part then sum 
			}
		}
	}
	if(total>100)
	{
		return 100;
	}
	return total+20;
}
//robot variability function
int robotVariability(string listOfParts,int variability)
{
	char arrayOfParts[listOfParts.length()];
	return 5+sizeof(arrayOfParts)+variability;
}
//Assign builder to the customer randomly
void builderPerCustomer(Customer *customerArray,Builders *buildersArray, int customerSize,int buildersSize,Parts *partsArray,int partsSize,string outputFile)
{
    ofstream outData;
    outData.open(outputFile);
    if(outData.good())
    {
        outData<<"\n-------Assigning Builder to Customer-------"<<endl;
        //random Index for builder
        uniform_int_distribution<unsigned> uniform(0,buildersSize);
        default_random_engine randEng;
        int countAttempt;
        for(int i=0;i<customerSize;i++)
        {
            countAttempt=0;
            //Report the customer name, project name, builder name, and the distribution
            Builders randomBuilder=buildersArray[uniform(randEng)];
            int totalComplexity=robotComplexity(customerArray[i].robotParts,partsArray,partsSize);
            int robotVari=robotVariability(customerArray[i].robotParts,randomBuilder.variability);
            int randDistrivution;
            normal_distribution<> uniformDistribution(randomBuilder.ability,robotVari);
	    bool flag=true;
            while(countAttempt<3 && flag)
            {
                if(countAttempt==0)
                {
                    outData<<"First Attempt"<<endl;
                    randDistrivution=uniformDistribution(randEng)+5;
                }
                else if(countAttempt==1)
                {
                    outData<<"----Second Attempt----"<<endl;
                    randDistrivution=uniformDistribution(randEng)+10;
                }
		else if(countAttempt==2)
                {
                    outData<<"----Last Attempt----"<<endl;
                    randDistrivution=uniformDistribution(randEng);
                }
                outData<<customerArray[i].customerName<<":"<<customerArray[i].robotName<<":"<<randomBuilder.name<<":"<<randDistrivution<<endl;
                //Condition on success of builder
                if(randDistrivution>=totalComplexity)
                {
                    outData<<" The build was successful."<<endl;
                    flag=false;
                }
                else
                {
                    outData<<randDistrivution<<" is less than "<<totalComplexity<<". The build was unseccessful!"<<endl;
                    countAttempt++;
                }
            }
            outData<<"------------------------------------------"<<endl;
        }
    }
    else
    {
        outData<<"Opening File failed!!!!"<<endl;
    }
}
