#ifndef _MPNODE_H_
#define _MPNODE_H_

template <class T>
class MPNode
{

public:
	MPNode();
	~MPNode();

	MPNode(const MPNode<T>& a){
		this->value = a.getValue();
		this->key = a.getKey();
	};

	//成员变量的set、get方法
	T getValue() const { return value; }
	void setValue(T val) { value = val; }
	int getKey() const { return key; }
	void setKey(int val) { key = val; }
private:
	T value;//值
	int key;//键
};

template <class T>
MPNode<T>::MPNode()
{
}

template <class T>
MPNode<T>::~MPNode()
{
}

#endif