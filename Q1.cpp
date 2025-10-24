#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
int main()
{
	string sentense="",temp;
	unsigned int cnt= 0;
	vector<string> arr;
	vector<unsigned int> len;
	while(cin>>temp)
	{
		sentense += temp;
		sentense+=" ";
	}
	temp="";
	char ch;
	for(unsigned int i = 0;i<sentense.size();i++)
	{
		ch=sentense[i];
		if(ch==' '||(ch=='.'&&i<sentense.size()-2)||ch==','){
			arr.push_back(temp);
			temp="";
			cnt++;
		}
		else{
			if(ch!='.')temp+=sentense[i];
		}
	}
	for(unsigned int i = 0;i<arr.size();i++)
	{
		len.push_back(arr[i].size());
	}
	int temp1;
	string temp2;
	for(unsigned int i = 0;i < len.size()-1;i++)
	{
		for(unsigned int j = 0;j < len.size()-1;j++)
		{
			if(len[j]<len[j+1])
			{
				temp1=len[j];
				len[j]=len[j+1];
				len[j+1]=temp1;
				temp2=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp2;
			}
		}
	}
	cout<<"The number of the words:"<<cnt<<endl;
	cout<<"The longest word:"<<arr[0]<<endl<<"Length:"<<arr[0].size()<<endl;
	cout<<"Output in the order of length:";
	for(unsigned int i = 0;i<arr.size();i++)
	{
		cout<<arr[i]<<'/';
	}
	system("Pause");
	return 0;
}
//Rose is red.Violet is blue.Heart is sweet,and so are you.