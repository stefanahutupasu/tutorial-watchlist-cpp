#pragma once

template <typename elementType>
class DynamicVector
{
private:
	elementType* elements;
	int size;
	int capacity;

public:
	//default constructor for a DynamicVector
	DynamicVector(int capacity = 10);
	
	//copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& vector);
	
	//destructor
	~DynamicVector();
	
	//assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);
	
	//overloading the subscript operator
	//input: position - a valid position whitin the vector
	//output: a reference to the element on the given position
	elementType& operator[](int position);
	
	//adds an element to the current DynamicVector
	void addElement(const elementType& newElement);
	
	//deletes an element of the current DynamicVector
	void deleteElement(const elementType& elementToDelete);
	
	//searches for an element of the current DynamicVector
	int searchElement(const elementType& elementToSearch);
	
	//getter for the size
	int getSize() const;
	
	//increases the capacity of the current DynamicVector
private:
	void resize(double factor = 2);
};

template <typename elementType>
DynamicVector<elementType>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new elementType[capacity];
}

template <typename elementType>
DynamicVector<elementType>::DynamicVector(const DynamicVector<elementType>& vector)
{
	this->size = vector.size;
	this->capacity = vector.capacity;
	this->elements = new elementType[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];
}

template <typename elementType>
DynamicVector<elementType>::~DynamicVector()
{
	delete[] this->elements;
}

template<typename elementType>
DynamicVector<elementType>& DynamicVector<elementType>::operator=(const DynamicVector<elementType>& vector)
{
	this->size = vector.size;
	this->capacity = vector.capacity;
	this->elements = new elementType[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];
	return *this;
}

template<typename elementType>
elementType& DynamicVector<elementType>::operator[](int position)
{
	return this->elements[position];
}

template<typename elementType>
void DynamicVector<elementType>::addElement(const elementType& newElement)
{
	if (this->size == this->capacity)
		this->resize();

	this->elements[this->size] = newElement;
	this->size++;
}

template <typename elementType>
void DynamicVector<elementType>::deleteElement(const elementType& elementToDelete)
{
	int deleteIndex = 0;
	for (int index = 0; index < this->size; index++)
		if (this->elements[index] == elementToDelete)
		{
			deleteIndex = index;
			break;
		}

	for (int index = deleteIndex; index < this->size - 1; index++)
		this->elements[index] = this->elements[index + 1];

	this->size--;
}

template <typename elementType>
int DynamicVector<elementType>::searchElement(const elementType& elementToSearch)
{
	for (int index = 0; index < this->size; index++)
		if (this->elements[index] == elementToSearch)
			return index;

	return -1;
}

template <typename elementType>
void DynamicVector<elementType>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	elementType* newElements = new elementType[this->capacity];
	for (int index = 0; index < this->size; index++)
		newElements[index] = this->elements[index];

	delete[] this->elements;
	this->elements = newElements;
}

template <typename elementType>
int DynamicVector<elementType>::getSize() const
{
	return this->size;
}
