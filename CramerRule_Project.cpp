#include <iostream>
#include <cmath>
#include <vector>

 using namespace std;

 /*
CRAMER'S RULE
1st calculate determinant of A
reduce matrix recursively until it's inthe form ad-bc
2nd Calculate each determinant of replacing columns with results
-stores determinants in vector array
3rd Displays results
- dx/dA dy/dA dz/dA
Notes
can take any number of order
returns 0 if determinant of A is 0
 */
 
 void getsize(vector< vector<double> >&temp, int order) //sizes vector to match copy (construct)

 {

     temp.resize(order);
        for(int i=0;i<order;i++)
     {
         temp[i].resize(order);
     }
 }

//////////////////////////////////////////////////////////////////////////////////

void get_order(int &order)  // gets matrix order from user

 {
        cout <<"Please input matrix n x n separately from the result\n\n";

        cout << "Enter matrix order without result's column: ";
        cin >> order;
 }

//////////////////////////////////////////////////////////////////////////////////

 void get_matrix(vector< vector<double> >&matrix, int order)  //gets matrix elements from user

 {
 cout << "\n\n Enter matrix n x n:\n";

 for(int i=0;i<order;i++) {

 //Create a vector

 vector<double> row;
 for(int j=0;j<order;++j){
 double value;
 cin >> value;
 row.push_back(value);
 }

 //Push the row in matrix
 matrix.push_back(row);
 }
 }

//////////////////////////////////////////////////////////////////////////////////

 void enter_result(vector<double>&result, int order)  //gets results from user

  {
 cout << "Enter the results of each row: ";
 for(int i=0;i<order;i++) {
 double value;
 cin >> value;
 result.push_back(value);
 }
 }

//////////////////////////////////////////////////////////////////////////////////

 void make_temp (vector< vector<double> >&temp, vector< vector<double> >&matrix, int order, int element)
  {

 /*Places correct numbers in the right place of temp vector*/
 //order is the order of the temp so originally -1 of matrix
 
 for (int i = 1; i < order+1; i++){ //loop set to iterate through matrix, i=1because first row is not used
 int k = 0; //k is used to loop through temp
 for (int j = 0; j < order+1; j++){

 if ( j==element ) {
     continue; //when col element is reached it will skip
 }else{
 temp[i-1][k] = matrix[i][j];  //adds element corresponding to newtemp vector;
 k++; //adds one to k counter for col position
 }}}}

//////////////////////////////////////////////////////////////////////////////////

 void print(vector< vector<double> >&matrix, int order, vector< double > result)
 {  
     //prints any matrix given in any order


    cout<< "\n\nThe matrix you input is:\n";

    for(int i=0;i<order;++i)
    {
        for(int j=0;j<order;++j)
    {
        cout << matrix[i][j] << " ";
    }
        cout <<"\n";
    }
        cout <<endl;
        
        cout<< "With results: ";


        for (int i=0; i<order; i++)
        cout << result[i] << " ";
        cout<<"\n\n";
 }
//////////////////////////////////////////////////////////////////////////////////

 double det_calc(vector< vector<double> >&matrix, int order)
  {
  /*Recursively loops down to get determinant in form ad-bc like a tree
162 and adds to the determinant*/

 vector< vector<double> > temp;
 getsize(temp, order-1);
 int sign = 1;
 double det = 0;



 if (order == 2) { //STOPRECURSIVE loop (BaseCase)
 return ((matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0])); 
 }

 for (int i = 0; i < order; i++)
 {

 make_temp (temp, matrix, order-1, i); //calls makeTemp to initialize tempvector
 det += sign * matrix[0][i] * det_calc(temp, order-1); //recursively callsdetCalc 
 sign *= -1; //flips sign to be added or substracted
 }

 return det; //return determinant result
 }
 
//////////////////////////////////////////////////////////////////////////////////
 
double find_dets(vector< vector<double> >&matrix, vector<double>&result, int column,int order)
 {
      //Gets determinant of x, y, z....by replacing results with each row and calculatingdeterminant

 vector< vector<double> > temp;

 temp = matrix;

 for (int i = 0; i < order; i++){
 temp[i][column]= result[i];
 }

 return (det_calc (temp, order));
 }
 
//////////////////////////////////////////////////////////////////////////////////

 int main()
 {

 int order;
 double det;
 int count = 1;

 vector< vector<double> > matrix;
 vector< double > result;
 vector< double > dets;

 get_order(order);
 get_matrix(matrix, order);

 enter_result(result, order);

 print(matrix, order, result);

 det = det_calc (matrix, order);

 if (det == 0)
 {
 cout<< "The matrix is singular";
 return 0;
 }
 

 for (int i=0; i<order; i++){
 dets.push_back(find_dets(matrix, result, i, order));
 }

 cout << "The solutions: "<<endl<<endl;

 for (int i=0; i<order; i++){
 cout << "x"<<count << " = " << dets[i]/det<<endl<<endl;
 count++;
 }


 return 0;
 }

