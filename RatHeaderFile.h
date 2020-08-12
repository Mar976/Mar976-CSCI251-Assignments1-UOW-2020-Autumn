#include <string>
#include <vector>
using namespace std;
//CUSTOMER
struct Customer
{
        string customerName;
        string robotName;
        string robotParts;
};
void readFileCustomer(Customer *customerArray,int *size,string customerFile);
void printCustomer(Customer *customerArray,const int size);

//PARTS
struct Parts
{
        char partCode;
        string partName;
        int minLimit;
        int maxLimit;
        int complexity;
};
void readFileParts(Parts *partsArray,int *size,const string partsFile);
void printParts(Parts *partsArray,int size);
//
void ListOfPartsCheck(Parts *partsArray,int size,Customer *customerArray,int custSize);
//BUILDER
struct Builders
{
        string name;
        int ability;
        int variability;
};
void readFileBuilders(Builders *buildersArray,int *size,string builderFile);
void printBuilders(Builders *buildersArray,int size);

//Assign builder to customer
int robotComplexity(string listOfParts,Parts *partsArray,int size);
int robotVariability(string listOfParts,int variability);
void builderPerCustomer(Customer *customerArray,Builders *buildersArray, int sizeCustomer, int sizeBuilder,Parts *partsArray,int size,string outputFile);
