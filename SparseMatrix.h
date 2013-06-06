/* SparseMatrix class with templates

Licensed under: WTFPL lol
( = do what the fuck you want to and lol at my code)
*/
#include "stdafx.h"
#pragma once
#include "MatrixElement.h"
#include <vector>

using std::vector;

template <typename a_type> class SparseMatrix {
public:
	SparseMatrix(void);
	SparseMatrix(const SparseMatrix<a_type> &); // copy constructor
	~SparseMatrix(void);
	void setValue(long row, long column, a_type value);
	void addValue(long row, long column, a_type value);
	void operator+=(const SparseMatrix<a_type> &);
	// SparseMatrix<a_type> & operator=(const SparseMatrix &righthandside);
	void outputElementsHigherThan(a_type);

private:
	vector<MatrixElement<a_type> * > values;
private:
	MatrixElement<a_type> * hasValue(long, long); // returns 0 ("false") if there is no value
	vector<MatrixElement<a_type> *> valueIsHigherThan(a_type);
};

template<typename a_type> SparseMatrix<a_type>::SparseMatrix(void)
{
}

template<typename a_type> SparseMatrix<a_type>::SparseMatrix(const SparseMatrix<a_type> &){

}

template<typename a_type>SparseMatrix<a_type>::~SparseMatrix(void)
{
	for (unsigned int i=0; i<values.size(); i++)
		delete values[i];
}

template<typename a_type> MatrixElement<a_type> * SparseMatrix<a_type>::hasValue(long x, long y) {
	for (unsigned int i = 0; i<values.size(); i++){ // search through the values
		if (values[i]->row == x)
			if (values[i]->column == y)
				return values[i];		
	}
	return NULL; // aka false when that column and row don't exist
}

template<typename a_type> void SparseMatrix<a_type>::setValue(long row, long column, a_type value)
{	
	MatrixElement<a_type> * temp = hasValue(row, column);
	if (temp)
		temp->value = value;
	else	{
		MatrixElement<a_type> * temp2 = new MatrixElement<a_type>(row, column, value);
		values.push_back(temp2);
	}
}

template<typename a_type>void SparseMatrix<a_type>::addValue(long row, long column, a_type value)
{	
	MatrixElement<a_type> *temp = hasValue(row, column);
	if (temp)
		temp->value += value;
	else	{
		MatrixElement<a_type> *temp2 = new MatrixElement<a_type>(row, column, value);
		values.push_back(temp2);
	}
}

// das hier lief nicht so performant:
/* template<typename a_type>void SparseMatrix<a_type>::operator+=(const SparseMatrix<a_type> &righthandside){
for (int unsigned i = 0; i < righthandside.values.size(); i++)
{
bool matched = false;
for (unsigned int j = 0; j<values.size(); j++) // search through this->values
{ 
if (values[j]->row == righthandside.values[i]->row)
if (values[j]->column == righthandside.values[i]->column){
values[j]->value += righthandside.values[i]->value;
matched = true;
break;
}
}
if (matched == false){
MatrixElement<a_type> * temp = new MatrixElement<a_type> (righthandside.values[i]->row, righthandside.values[i]->column, righthandside.values[i]->value);
values.push_back(temp);
}
}		
} */

//das hier lief (im Debug) performanter:

template<typename a_type>void SparseMatrix<a_type>::operator+=(const SparseMatrix &righthandside){
	for (unsigned int i = 0; i < righthandside.values.size(); i++) 
		this->addValue(righthandside.values[i]->row, righthandside.values[i]->column, righthandside.values[i]->value);		
}

/* unfinished! template<typename a_type>SparseMatrix<a_type>& SparseMatrix<a_type>::operator=(const SparseMatrix& righthandside){
if (this == &righthandside) // same object?
return *this; // yes, so skip assignment, and just return *this.
SparseMatrix<a_type> *temp = new SparseMatrix<a_type>;
for (unsigned int i = 0; i < righthandside.values.size(); i++)
{ 
temp->addValue(righthandside.values[i]->row, righthandside.values[i]->column, righthandside.values[i]->value);
}
return temp;
} */

template<typename a_type> vector<MatrixElement<a_type> *> SparseMatrix<a_type>::valueIsHigherThan(a_type number){
	vector<MatrixElement<a_type> *> toReturn;	
	for (unsigned int i = 0; i<values.size(); i++){ // search through the values
		if (values[i]->value > number)
			toReturn.push_back(values[i]);	// caution when using that vector. references to elements in the "main" Matrix			
	}
	return toReturn; // what happens when this is empty?
}

template<typename a_type> void SparseMatrix<a_type>::outputElementsHigherThan(a_type number){
	vector<MatrixElement<a_type> *> toOutput(valueIsHigherThan(number)); // using copy constructor. pointers reference the same elements as in "main" matrix

	for (unsigned int i = 0; i < toOutput.size(); i++)
	{
		toOutput[i]->output();
	}
}