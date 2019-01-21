#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-18;
template<class Type>
inline bool is_zero(Type value){
	return fabs(value) <= EPS;
}

template<class Type>
class Matrix{
private:
	vector<vector<Type> > data;
public:
	int width,height;
	Matrix(int height=0,int width=0,Type value = 0);
	Matrix<Type> (const Matrix<Type> & other);
	Matrix<Type> operator + (const Matrix<Type> & other);
	Matrix<Type> operator - (const Matrix<Type> & other);
	Matrix<Type> operator * (const Matrix<Type> & other);
	Matrix<Type> operator ~();
	vector<Type> operator [](int row)const;
	vector<Type>& operator [] (int row);
	void print();
	static Matrix<Type> eye(int n);
};
typedef Matrix<double> Mat;
template<class Type>
Matrix<Type>::Matrix(const Matrix<Type> & other){
	height = other.height;
	width = other.width;
	data = other.data;
}
template<class Type>
Matrix<Type>::Matrix(int height_,int width_,Type value_){
	height = height_;
	width = width_;
	data.resize(height);
	for (int i=0;i< height;i++){
		data[i].resize(width,value_);
	}
}
template<class Type>
void Matrix<Type>::print(){
	for (int i=0;i<height;i++){
		for (int j=0;j< width;j++){
			cout<<data[i][j]<<" ";
		}
		cout<<endl;
	}
}
template<class Type>
Matrix<Type> Matrix<Type> :: operator + (const Matrix <Type> & other){
	if (other.height != height || other.width != width){
		throw -1;
	}
	Matrix<Type> res(height,width);
	for (int i=0;i< height;i++){
		for (int j=0;j< width;j++){
			res.data[i][j] = data[i][j] + other.data[i][j];
		}
	}
	return res;
}
template<class Type>
Matrix<Type> Matrix<Type> :: operator - (const Matrix<Type> & other){
	if (other.height != height || other.width != width){
		throw -1;
	}
	Matrix<Type> res(height,width);
	for (int i=0;i< height;i++){
		for (int j=0;j< width;j++){
			res.data[i][j] = data[i][j] - other.data[i][j];
		}
	}
	return res;
}
template<class Type>
Matrix<Type> Matrix<Type> :: operator * (const Matrix<Type> & other){
	if ( other.height != width){
		throw -2;
	}
	Matrix<Type> res(height,other.width);
	for (int i=0;i< height;i++){
		for (int j=0;j< other.width;j++){
			for (int k=0;k<width;k++){
				res.data[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}
	return res;
}
template<class Type>
Matrix<Type> Matrix<Type>:: operator ~(){
	int h = height;
	int w = width;
	Matrix<Type> res(w,h);
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			res[i][j] = data[j][i];
		}
	}
	return res;
}
template<class Type>
vector<Type> Matrix<Type> :: operator[](int row)const{
	cout<<row<<" "<<height<<endl;
	if (row > height){
		throw -5;
	}
	return data[row];
}
template<class Type>
vector<Type>& Matrix<Type> :: operator[](int row){
	if (row > height){
		throw -5;
	}
	return data[row];
}
template<class Type>
Matrix<Type> Matrix<Type> :: eye(int n){
	Matrix<Type> res(n,n);
	for (int i=0;i<n;i++){
		res[i][i] = 1;
	}
	return res;
}
int main(){
    Mat test(3,5,2.0);
    test.print();
    return 0;
}