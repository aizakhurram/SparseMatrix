#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include <string>
using namespace std;

class SparseMatrix {
    struct node {
        double value;
        int colIndex;
        node* nextinrow;
        node() {
            nextinrow = NULL;

        }
        node(double v) : value(v) {}
    };
    node* head;
    int M;
    int N;
    vector<node*> rowlist;

public:

    void insert(double val, int col, int row) {
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
        double num2;
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
        float num2;
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
               cout<<"["<< temp->colIndex << " , " << temp->value<<"]";
               if(temp->nextinrow!=NULL){
               	 cout<< " ==> ";
			   }
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
	void Skew_symmetric(SparseMatrix& t){
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
     cout<<"\n-A of matrix: \n";
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
			return;
		}
		else if(check==0){
			cout<<"not Skew-symmetric."<<endl;
			return;
		}
	}
	else{
		cout<<"not Skew-symmetric."<<endl;
		return;
}
}
	int calculateDeterminant(){
		int val=1, val2=1;
		   for(int i=0; i<M; i++){
		   	for(int j=1, k=0; j<=N, k<N; j++, k++){
		   		if(i==k){
		   		 val=(this->returnvalue(j,i))* val;	 
		   	}
		   	else{
		   		val2=(this->returnvalue(j,i))* val2;
			   }
			   }
		   }
	
          val2=val-val2;
          return val2;
		
	}
	void InverseofMatrix(){
		
		int determinant=this->calculateDeterminant();
		if(determinant!=0){
		
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
        for(int i=M; i>=0; i--){
        	for(int j=1, k=0; j<=N; j++, k++){
        		if(i==1 && k==1){
        			if(this->returnvalue(j,i)!=0){
					
					temp.insert(this->returnvalue(j,i),j-1,i-1);
				    }
				}
        		if(i==0 && k==0){
        				if(this->returnvalue(j,i)!=0){
        		    temp.insert(this->returnvalue(j,i),j+1,i+1);
				}
			}
				
				if(i==0 && k==1){
						if(this->returnvalue(j,i)!=0){
					temp.insert(-this->returnvalue(j,i),j,i);
				}
			}
				if(i==1 && k==0){
						if(this->returnvalue(j,i)!=0){
					temp.insert(-this->returnvalue(j,i),j,i);
				}
			}
				
			}
		}
		cout<<"\nAdjoint of Matrix: \n";
		temp.print();
		
	
		SparseMatrix temp2;
		temp2.M=temp.M;
		temp2.N=temp.N;
			for (int i = 0; i < M; i++)
        {
            node* new_node = new node;
            new_node->value = i;
            temp2.rowlist.push_back(new_node);
            temp2.rowlist[i]->nextinrow = NULL;
           
        }
		for(int i=0; i<M; i++){
			double d=0.00;
			for(int j=1; j<=N; j++){

				d=(temp.returnvalue(j,i)) * 1.0 /(determinant);
				if(d!=0){
					temp2.insert(d,j,i);
				}
			}
		}
		cout<<"\nInverse of Matrix: "<<endl;
		temp2.print();
	}
	else{
		cout<<"Determinant=0 so cannot find inverse!!"<<endl;
		exit(0);
	}
	}
      bool SubMatrix(SparseMatrix& obj)
    {
        bool check = false;
        int Value1;
        int Value2;
        if (obj.M <= M && obj.N <= N)
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 1; j <= N; j++)
                {
                    for (int k = 0; k < obj.M; k++)
                    {
                        for (int l = 1; l <= obj.N; l++)
                        {
                            if (i + k < M && j + l <= N)
                            {
                                Value1 = returnvalue(j + l, i + k);
                            }
                            else
                            {
                                l = obj.N + 1;
                                k = obj.M;
                                continue;
                            }
                            Value2=obj.returnvalue(l,k);
                            if (Value2 == Value1 && l == obj.N && k == obj.M - 1)
                            {
                                check = true;
                                break;
                            }
                            else if (Value1!=Value2)
                            {
                                l = obj.N + 1;
                                k = obj.M;
                                continue;
                            }
                        }
                    }
                }
            }
        }
        if (check == true) {
        	return check;
        }
        else {
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
    

    cout<<"Sparse Matrix: "<<endl;
    SparseMatrix s1("data.txt"); 
    s1.print();
     
    SparseMatrix s2(s1);
    cout<<"\nTranspose: ";
    s2.Transpose("data.txt");

     if(s1.isSymmetric(s2)){
     	cout<<"Is Symmetric"<<endl;
	 }
	 else{
	 	cout<<"Not symmetric"<<endl;
	 }
	 s1.Skew_symmetric(s2);
     
     
     
    //Multiplication Check: 
//       cout<<"Sparse Matrix: "<<endl;
//    SparseMatrix s1("data.txt"); 
//    s1.print();
//     
//    cout<<"\nSecond matrix: "<<endl;
//    SparseMatrix obj("second.txt");
//    obj.print();
//    cout<<"\nMultiplication: "<<endl;
//    SparseMatrix C=s1*obj;
//    C.print();
//    cout<<endl;

     //Addition Check:
//     cout<<"1st Sparse Matrix: "<<endl;
//    SparseMatrix s1("data.txt"); 
//    s1.print();
//    
//    cout<<"\n2nd Sparse Matrix copied throught copy constructor: "<<endl;
//    SparseMatrix s2(s1);
//    s2.print();
//    cout<<"\nAfter Addition of 1st and 2nd matrices: "<<endl;
//    
//    SparseMatrix s3=s1+s2;
//    s3.print();
     
     
//     //INVERSE
//    SparseMatrix s1("inv.txt");
//	int determinant=0;
//	cout<<"Matrix: "<<endl;
//	s1.print();
//	cout<<endl;
//	determinant=s1.calculateDeterminant();
//	cout<<"Determinant of Matrix: "<<determinant<<endl;
//	s1.InverseofMatrix();
//   
      //SUB MATRIX:
//     cout<<"Sparse Matrix: "<<endl;
//    SparseMatrix s1("Matrix.txt"); 
//    s1.print();
//     
//     cout<<"Second matrix: "<<endl;
//     SparseMatrix sub("check.txt");
//     sub.print();
//    if(s1.SubMatrix(sub)){
//    	cout<<"Is a Sub-Matrix!"<<endl;
//	}
//	else{
//		cout<<"Not a Sub-Matrix!"<<endl;
//	}
    return 0;
}
