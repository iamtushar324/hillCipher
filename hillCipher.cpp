#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

int N ;

vector<vector<float> > constructArrayFromKeyString(string key);


void printMat(vector<vector<float> > mat){
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat.size(); j++)
		{
		cout<< mat[i][j]<<' ';
		}
		cout << endl;
		
	}
}
void printMat(vector<vector<int> > mat){
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat.size(); j++)
		{
		cout<< mat[i][j]<<' ';
		}
		cout << endl;
		
	}
}

vector<int> stringToFloatVector(string str){
	vector<int> arr;
	for (int i = 0; i < str.length(); i++)
	{
		int temp = str[i];
		if(temp < 97 || temp > 122){
			throw "Invalid Input String";
		}
		if(temp > 96){
		arr.push_back(temp - 97);
		}else{
		arr.push_back(temp - 65);
		}
	}
	return arr;
	
}
vector<vector<float> > constructArrayFromKeyString(string key){
	vector<float> arr;

	for(int i = 0 ; i < key.length(); i++){
		float num = 0;
		int length =0;
		int place =1;

		while(key[i + length] != ' ' && i + length < key.length()){
			length++;
			place = place * 10;

		}
		place = place / 10;
		int maxLeng = i+length;

		while(i <= maxLeng){
			int temp = key[i];
			temp -= 48;
			num = num+(place*temp);
			place= place / 10;
			i++;
		}

		i--;
		arr.push_back(num);
	}

	int matLen = sqrt(arr.size());
	vector<vector<float> > mat;
	for(int i = 0 ; i < matLen ; i++ )
	{
		vector<float> temp;
		for (int j = i*matLen; j < (i+1)*matLen; j++)
		{
			temp.push_back(arr[j]);
		}
		mat.push_back(temp);
		
	}
	return mat;
}

vector<int> matMultiplication(vector<vector<float> > mat , vector<int> arr){
	vector<int> ans(mat.size());
	for (int i = 0; i < mat.size(); i++)
	{
		float tempAns = 0;
		for (int j = 0; j < mat.size(); j++)
		{
			tempAns += mat[i][j]*arr[j];
		}
		int aa = round(tempAns);
		ans[i] = aa%26 ;
	}
	return ans;
	
}

void printFloatVectorToString(vector<int> arr){
	for(int i = 0 ; i < arr.size() ; i++){
		char temp = arr[i] + 97;
		cout << temp;
	}
	cout << endl;
}

vector<int> encrypt(vector<vector<float> > mat , vector<int> plainText){
	vector<int> cypherVector = matMultiplication(mat , plainText);
	cout << "Cypher Text :- ";
	printFloatVectorToString(cypherVector);
	return cypherVector;

}
vector<int> decrypt(vector<vector<float> > mat , vector<int> plainText){
	vector<int> cypherVector = matMultiplication(mat , plainText);
	cout << "Decrypted Text :- ";
	printFloatVectorToString(cypherVector);
	return cypherVector;

}
	

vector<vector<float> > invOfMatrix(vector<vector<float> > mat){
	int n = mat.size(), i , j , k;
	float d ,a[10][10] = {0};

	for (i = 1; i <= n; i++)
	{
        for (j = 1; j <= n; j++)
        {
            a[i][j] = mat[i-1][j-1];
        }
    	} 

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= 2 * n; j++)
        {
            if (j == (i + n))
            {
                a[i][j] = 1;
            }
        }
    }
    for (i = n; i > 1; i--)
    {
        if (a[i-1][1] < a[i][1])
        {
            for(j = 1; j <= n * 2; j++)
            {
                d = a[i][j];
                a[i][j] = a[i-1][j];
                a[i-1][j] = d;
            }
        }
    }
     for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n * 2; j++)
        {
            if (j != i)
            {
                d = a[j][i] / a[i][i];
                for (k = 1; k <= n * 2; k++)
                {
                    a[j][k] = a[j][k] - (a[i][k] * d);
                }
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        d=a[i][i];
        for (j = 1; j <= n * 2; j++)
        {
            a[i][j] = a[i][j] / d;
        }
    }
    vector<vector<float> > inv(n);

    for (i = 1; i <= n; i++)
    {
	vector<float> rowTemp;
        for (j = n + 1; j <= n * 2; j++)
        {
	    rowTemp.push_back(a[i][j]);
        }
	inv[i-1] = rowTemp;
    }

    return inv;

}

int main(){
	try{

	freopen("inp.txt","r",stdin);
	freopen("output.txt","w",stdout);

	string key;
	getline(cin,key);

	string plainText;
	getline(cin,plainText);

	vector<vector<float> > matKey = constructArrayFromKeyString(key);

	printMat(matKey);
	cout << plainText<<endl;
	vector<int> plainTextVector = stringToFloatVector(plainText);
	vector<int> cypherVector = encrypt(matKey , plainTextVector );

	vector<vector<float> > invMat = invOfMatrix(matKey);
	printMat(invMat);
	vector<int> deVector = decrypt(invMat, cypherVector);

	return 0;


	}catch(const char* e){
		cout << "ERROR :- " <<  e <<endl;
	}

}