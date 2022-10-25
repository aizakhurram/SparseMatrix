#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include <string>
using namespace std;

class SparseMatrix {
    struct node {
        int value;
        int colIndex;
        node* nextinrow;
        node() {
            nextinrow = NULL;

        }
        node(int v) : value(v) {}
    };
    node* head;
    int M;
    int N;
    vector<node*> rowlist;

public:

    void insert(int val, int col, int row) {
        node* nn = new node(val);
        nn->colIndex = col;
        if (head == NULL) {
            head = nn;
            rowlist[row]->nextinrow = nn;
            return;
        }
        else {

            node* temp = rowlist[row];
            while (temp->nextinrow != NULL) {
                temp = temp->nextinrow;
            }
            temp->nextinrow = nn;
            temp->nextinrow->nextinrow = NULL;
           
        }

    }
   int colcount(string num){
   	int count2=0;
    	int count=num.size();
    //	cout<<count<<endl;
    	for(int i=0; num[i]!='\0' ; i++){
    		if(num[i]==' ' || num[i]=='-'){
			
    		count2++;
    		
         	}
		}
		count=count-count2;
		return count;
	}
	void readfortranspose(const char* filename) {

        ifstream fin;
        fin.open(filename, ios::in);
        string num;
        int num2;
        int count = 0;
        if (!fin)
        {
            cout << "Text file could not be loaded. Please verify its name and location.\n";
            system("pause");
            return;
        }
        while (!fin.eof()) {
            getline(fin, num);
            count++;
        }
        
        cout << endl;
        N = count-1;
        fin.close();
        fin.open(filename, ios::in);
        getline(fin, num);
        M=colcount(num);
        
        fin.close();
        for (int i = 0; i < M; i++)
        {
            node* new_node = new node;
            new_node->value = i;
            rowlist.push_back(new_node);
            rowlist[i]->nextinrow = NULL;
           
        }
         
        fin.open(filename, ios::in);
        int k=0, col=1;
        if (!fin.eof()) {
        	while(k<M){
			
            for (int i = 0; i <=N; i++)
            {
            	
                for (int j = 1; j <=M; j++) {
                    fin >> num2;
                    if (num2 != 0) 
					{
                        this->insert(num2, col, i);
                    }
                      break;
                }
                 
            }
            col++;
            k++;
        }
        }
        fin.close();
    
    }
    void read(const char* filename) {

        ifstream fin;
        fin.open(filename, ios::in);
        string num;
        int num2;
        int count = 0;
        if (!fin)
        {
            cout << "Text file could not be loaded. Please verify its name and location.\n";
            system("pause");
            return;
        }
        while (!fin.eof()) {
            getline(fin, num);
            count++;
        }
        
        cout << endl;
        M = count-1;
        fin.close();
        fin.open(filename, ios::in);
        getline(fin, num);
        N=colcount(num);
        
        fin.close();
        for (int i = 0; i < M; i++)
        {
            node* new_node = new node;
            new_node->value = i;
            rowlist.push_back(new_node);
            rowlist[i]->nextinrow = NULL;
           
        }
         
        fin.open(filename, ios::in);
        if (!fin.eof()) {
            for (int i = 0; i < M; i++)
            {
                for (int j = 1; j <= N; j++) {
                    fin >> num2;
                  
                    if (num2 != 0) {
                    //	cout<<"val: "<<num2<<" row: "<<i<<" col: "<<j<<endl;
                        this->insert(num2, j, i);

                    }
                }
            }
        }
        fin.close();
    
    }
    void print() const {
    	int k=1;
        for (int i = 0; i < M, k<=M; i++)
        {
              cout <<"row["<<k<<"] =>";
            node* temp = rowlist[i]->nextinrow;
            if(rowlist[i]->nextinrow==NULL){
            	cout<<" NULL";
			}
            while (temp != NULL) {
               cout<<" ["<< temp->colIndex << " , " << temp->value << " ]==> ";
                temp = temp->nextinrow;
               
            }
             k++;
            cout << endl;
        }
    }
    void Transpose(char* filename){
    	this->readfortranspose(filename);
    	this->print();
    	
	}

    SparseMatrix(char* filename) {
        this->read(filename);
      
    }
    SparseMatrix(const SparseMatrix& obj){
        M=obj.M;
        N=obj.N;
       
         for (int i = 0; i < M; i++)
        {
            node* new_node = new node;
            new_node->value = i;
            rowlist.push_back(new_node);
            rowlist[i]->nextinrow = NULL;
           
        }
        for(int i=0; i<M; i++){
         node* node1=this->rowlist[i];
         node* node2=obj.rowlist[i];
         while(node2->nextinrow!=NULL){
            node1->nextinrow=node2->nextinrow;
            node1=node1->nextinrow;
            node2=node2->nextinrow;
            node1->colIndex=node2->colIndex;
            node1->value=node2->value;
         }
        
         
        }


    }
    int returnvalue(int column, int row)
    {
    
        node* temp = rowlist[row];
        if(rowlist[row]==NULL){
        	return 0;
		}
        while (temp != NULL) 
        {
            if (temp->colIndex==column)
            {
                return temp->value;
            }
            temp = temp->nextinrow;
        } 
        return 0;
    }
    SparseMatrix(){
    	M=0;
    	N=0;
    //	rowlist=NULL;
	}
    const SparseMatrix  operator = (const SparseMatrix & obj){
         SparseMatrix temp(obj);
         return temp;
    }
    SparseMatrix operator+(SparseMatrix& obj)
    {
        SparseMatrix a;
        a.M=obj.M,
        a.N=obj.N;
        if (M == obj.M && N == obj.N)
        {
            for (int i = 0; i < M; i++)
            {
                node* new_node = new node;
                new_node->value = i;
                a.rowlist.push_back(new_node);
                a.rowlist[i]->nextinrow = NULL;
            }
            for (int i = 0; i < M; i++)
            {
                for (int j = 1; j <= N; j++)
                {
			
                    if (obj.returnvalue(j, i) + returnvalue(j, i)!=0)
                    {
                        a.insert(obj.returnvalue(j, i) + returnvalue(j, i), j, i);
                    }	
                
                }
            
            }
        }
        else
        {
            cout << "The matrices are not of same dimensions";
        }
       
        return a;
    }
    SparseMatrix operator*(SparseMatrix& obj)
    {
        SparseMatrix a;
        a.M=this->M;  
        a.N=obj.N;
        
        int sum = 0;
        if (N == obj.M)
        {
            for (int i = 0; i < M; i++)
            {
                node* new_node = new node;
                new_node->value = i;
                a.rowlist.push_back(new_node);
                a.rowlist[i]->nextinrow = NULL;
            }
            for (int i = 0; i < M; i++)
            {
                for (int j = 1; j <= N; j++)
                {
                    int sum = 0;
                    for (int k = 0; k < obj.M; k++)
                    {
                        sum = (obj.returnvalue(j, k)*returnvalue(k+1,i)) + sum;
                    }
                    if (sum !=0)
                    {
                        a.insert(sum, j, i);
                    }
                }
            }
        }
        else
        {
            cout << "The matrices are not of same dimensions";
        }
        return a;
    }
    bool isSymmetric(SparseMatrix& obj){
    	bool check=0;
    	if(M!=N){
    		return false;
		}
        else{
	        	for(int i=0; i<M; i++){
    		for(int j=1; j<=N; j++){
    			 if(this->returnvalue(j, i)==obj.returnvalue(j,i)){
    			 	check=1;
				 }
				 else{
				 	check=0;
				 }
			}
		}
		if(check==1){
			return true;
		}
		else{
			return false;
		}
	}
        
        
	}
	bool Skew_symmetric(SparseMatrix& t){
		SparseMatrix temp;
		 temp.M=M;
        temp.N=N;
       
         for (int i = 0; i < M; i++)
        {
            node* new_node = new node;
            new_node->value = i;
            temp.rowlist.push_back(new_node);
            temp.rowlist[i]->nextinrow = NULL;
           
        }
        for(int i=0; i<M; i++){
         node* node1=temp.rowlist[i];
         node* node2=rowlist[i];
         while(node2->nextinrow!=NULL){
            node1->nextinrow=node2->nextinrow;
            node1=node1->nextinrow;
            node2=node2->nextinrow;
            node1->colIndex=node2->colIndex;
            node1->value=-(node2->value);
         }
        
     }
      temp.print();
     bool check=0;
    if(temp.M==t.M && temp.N==t.N){
    
    	for(int i=0; i<M; i++){
    		for(int j=1; j<=N; j++){
    			 if(temp.returnvalue(j, i)==t.returnvalue(j,i)){
    			 	check=1;
				 }
				 else{
				 	check=0;
				 }
			}
		}
		if(check==1){
			cout<<"Is Skew-Symmetric"<<endl;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		cout<<"not Skew-symmetric."<<endl;
		return false;
	}
	

       
         
	}
     ~SparseMatrix(){
        
          for(int i=0; i<M; i++){
               delete[]rowlist[i];
          }
          node*temp=head;
          delete head;
          temp=NULL;
        
          M=0;
          N=0;
     }
   
};
int main() {
    
    cout<<"1st Sparse Matrix: "<<endl;
    SparseMatrix s1("data.txt"); 
    s1.print();
    
    cout<<"\n2nd Sparse Matrix copied throught copy constructor: "<<endl;
    SparseMatrix s2(s1);
    s2.print();
    cout<<"\nAfter Addition of 1st and 2nd matrices: "<<endl;
    
    SparseMatrix s3=s1+s2;
    s3.print();
    


    return 0;
}
