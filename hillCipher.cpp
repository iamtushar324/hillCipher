#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

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

vector<int> stringToFloatVector(string str){
	vector<int> arr;
	for (int i = 0; i < str.length(); i++)
	{
		int temp = str[i];
		if(temp < 97 || temp > 122){
			throw "Invalid Input String";
		}
		arr.push_back(temp);
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
		int tempAns = 0;
		for (int j = 0; j < mat.size(); j++)
		{
			tempAns += mat[i][j]*arr[i];
		}
		tempAns = tempAns%26;
		ans[i] =tempAns;
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

	return 0;


	}catch(const char* e){
		cout << "ERROR :- " <<  e <<endl;
	}

}