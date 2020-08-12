//contain main() funcation
#include <iostream>
#include <vector>
#include "RatHeaderFile.h"
using namespace std;

int main(int argc, char *argv[])
{
	string customerFile;
        string partsFile;
        string builderFile;
        string outputFile;
	if(argc==5)
	{
		customerFile=argv[1];
		partsFile=argv[2];
		builderFile=argv[3];
		outputFile=argv[4];
	}
	else
	{
		cerr<<"Number of argument does not match!"<<endl;
		system("pause");
	}
	//CUSTOMER
	int customerSize=10;
	Customer customerArray[customerSize];
	readFileCustomer(customerArray,&customerSize,customerFile);
	printCustomer(customerArray,customerSize);

	//PARTS
	int partsSize=10;
	Parts partsArray[partsSize];
	readFileParts(partsArray,&partsSize,partsFile);
	printParts(partsArray,partsSize);

	//Check Max and Min for Customer Parts
	ListOfPartsCheck(partsArray,partsSize,customerArray,customerSize);
	//BUILDER
	int buildersSize=5;
	Builders buildersArray[buildersSize];
	readFileBuilders(buildersArray,&buildersSize,builderFile);
	printBuilders(buildersArray,buildersSize);

	//random Builder Per Customer
	builderPerCustomer(customerArray,buildersArray,customerSize,buildersSize,partsArray,partsSize,outputFile);
	return 0;
}

