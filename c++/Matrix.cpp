// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;
class multiplicationExepction : public exception{
    public:
        const char* what() throw() {
            return "multiplication error";
        }
};
class matrix{
    int row;
    int col;
    // int *ptr[];//ptr is a array of a pointers
    int** ptr;//ptr is a pointer pointing to the pointer

    public:
    //if you declare the default constructor and never define it 
    //this cause linker error if defalut constructor is used
        matrix(){//default counstructor;
            this->row = this->col = 0;
            this->ptr = nullptr;
        }
        matrix(int row,int col){
            this->row = row;
            this->col = col;

            ptr = new int* [row];//allocate a array of pointers (which act as row);
            
            for(int i = 0; i < row; i++){
                ptr[i] = new int[col];

                for(int j = 0; j < col; j++){
                    ptr[i][j] = 0;
                }

            }
        }
        //copy constructor using const keyword 
        //when temp object was copied then const is used
        matrix(const matrix& arr){
            this->row = arr.row;
            this->col = arr.col;
            //use deep copy here

            (this->ptr) = new int*[this->row];
            for(int i = 0; i < this->row; i++){
                (this->ptr)[i] = new int[this->col];
                for(int j = 0; j < this->col; j++){
                    (this->ptr)[i][j] = (arr.ptr)[i][j];
                }
            }

        }
        //virtual destructor because polymorphism
        virtual ~matrix(){
            if(ptr != nullptr){
                //delete the col array first 
                for(int i = 0; i <row; i++){
                    delete[]ptr[i];
                }
                delete[] ptr;

                ptr = nullptr;
            }
        }
        //it return int* because after that arr[i][j] = ptr[i][j], which can be calculated via pointers arithmatic
        int* operator[](int n){
            return ptr[n];
        }
        //it is not recommended to use matrix& as return type, but I want to check how it works
        matrix& operator+(const matrix& arr){
            matrix *temp = new  matrix();//use default constructor so no memory loss
            temp->row = this->row;
            temp->col = this->col;

            temp->ptr = new int*[temp->row];

            for(int i = 0; i < temp->row; i++){
                (temp->ptr)[i] = new int[temp->col];
                for(int j = 0; j < temp->col; j++){
                    (temp->ptr)[i][j] = (this->ptr)[i][j] + (arr.ptr)[i][j];
                }
            }

            return *(temp);//similar to giving name to dynamic created object via a ref.
        }
        matrix& operator*(const matrix& arr){
            if(this->col != arr.row){
                multiplicationExepction error;
                throw error;
            }
            matrix *temp = new  matrix();
            temp->row = this->row;
            temp->col = arr.col;

            temp->ptr = new int*[temp->row];

            for(int i = 0; i < temp->row; i++){
                (temp->ptr)[i] = new int[temp->col];
                for(int j = 0; j < temp->col; j++){
                    int sum = 0;
                    for(int k = 0; k < this->col; k++){
                        sum+= (this->ptr)[i][k] * (arr.ptr)[k][j];
                    }
                    (temp->ptr)[i][j] = sum;
                }
            }

            return *(temp);
        }
        //rule of three
        //1. destructor,
        //2. copy const,         -use deepcopy
        //3. oprator overload =  -use deepcopy
        matrix& operator =(const matrix & arr){
            this->row = arr.row;
            this->col = arr.col;

            //use deep copy
            (this->ptr) = new int*[this->row];
            for(int i = 0; i < this->row; i++){
                (this->ptr)[i] = new int[this->col];
                for(int j = 0; j < this->col; j++){
                    (this->ptr)[i][j] = (arr.ptr)[i][j];
                }
            }
            return *this;
        }
        friend ostream& operator <<(ostream& print,const matrix& arr);
};
ostream& operator <<(ostream & print,const matrix& arr){
    print<<"your matrix is"<<endl;
    for(int i = 0; i < arr.row; i++){
        for(int j = 0; j < arr.col; j++){
            print<<(arr.ptr)[i][j]<<" ";
        }
        print<<endl;
    }
    return print;
}
int main(){

    int row,col;
    cin>>row>>col;

    matrix arr1(row,col);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cin>>arr1[i][j];
        }
    }
    cout<<"Your array1 is"<<endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout<<arr1[i][j]<<" ";
        }
        cout<<endl;
    }

    matrix arr2(row,col);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cin>>arr2[i][j];
        }
    }
    cout<<"Your array2 is"<<endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout<<arr2[i][j]<<" ";
        }
        cout<<endl;
    }

    matrix arr3 = arr1 + arr2;
    cout<<"after addition : "<<endl<<arr3<<endl;

    try{
        matrix arr4 = arr1 * arr2;
        cout<<"after multipication : "<<endl<<arr4<<endl;
    }
    catch(multiplicationExepction& error){
        cout<<error.what()<<endl;
    }
    return 0;
}