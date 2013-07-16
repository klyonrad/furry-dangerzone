/* SparseMatrix class with templates

Licensed under: WTFPL lol
( = do what the fuck you want to and lol at my code)
*/

#pragma once
#include <iostream>

using std::cout; using std::endl;
template <typename a_type> class SparseMatrix;
template <typename a_type> class MatrixElement
{
	friend class SparseMatrix<a_type>;
public:
	MatrixElement(void);
	MatrixElement(long x, long y, a_type);
	~MatrixElement(void);
	void output(void);

protected:
	int row, column;
	a_type value;
};


template <typename a_type>MatrixElement<a_type>::MatrixElement(void)
{
}

template <typename a_type>MatrixElement<a_type>::MatrixElement(long x, long y, a_type newvalue){
	row = x;
	column = y;
	value = newvalue;
}

template <typename a_type>MatrixElement<a_type>::~MatrixElement(void)
{
}

template <typename a_type>void MatrixElement<a_type>::output(void){
	cout.width (8);
	cout << row << "," << column;
	cout << " : " << value << endl;
}