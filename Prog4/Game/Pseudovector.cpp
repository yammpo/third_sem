#include "Pseudovector.h"
namespace Game {
	template<class T>
	int Vec<T>::GetPos(const int &s) const {
		for (int i = 0; i < size; ++i)
			if (i == s)
				return i;
		return -1;
	}

	template<class T>
	VecIt<T> Vec<T>::begin() {
		return VecIt<T>(this->data);
	}

	template<class T>
	VecIt<T> Vec<T>::end() {
		return VecIt<T>(this->data + size);
	}

	template<class T>
	VecIt<T> Vec<T>::find(const int &s) const {
		int i = GetPos(s);
		if (i < 0)
			i = size;
		return VecIt<T>(this->data + i);
	}

	template <class  T>
	Vec<T>::Vec(int n) {
		reserve(n);
	}

	template <class  T>
	Vec<T>::~Vec(void) {
		delete[] data;
	}

	template <class  T>
	int Vec<T>::GetSize(void) const {
		return size;
	}

	template <class  T>
	T& Vec<T>::operator[](int i) {
		return data[i];
	}

	template <class T>
	Vec<T> Vec<T>::operator=(const Vec&a) {
		size = a.size;
		for (int i = 0; i != a.size; ++i) {
			this->date[i] = a.data[i];
		}
		return *this;
	}

	template<class T>
	bool VecIt<T>::operator!=(const VecIt &v) const {
		return cur != v.cur;
	}

	template <class T>
	bool VecIt<T>::operator==(const VecIt &v) const {
		return cur == v.cur;
	}

	template<class T>
	T & VecIt<T>::operator*() {
		return *cur;
	}

	template<class T>
	T * VecIt<T>::operator->() {
		return cur;
	}

	template<class T>
	VecIt<T>& VecIt<T>::operator++() {
		++cur;
		return *this;
	}

	template <class T>
	Vec<T>::Vec(Vec&a) {
		this->size = a.size;
		for (int i = 0; i != a.size; ++i) {
			this->date[i] = a.data[i];
		}
	}

	template <class T>
	void Vec<T>::push_back(T val) {
		T* newdata;
		if (size >= cap) {
			cap = cap * 2;
			newdata = new T[cap];
			for (int i = 0; i < size; i++)
				newdata[i] = data[i];
			delete[] data;
			data = newdata;
		}
		data[size] = val;
		size++;
	}

	template <class  T>
	int Vec<T>::GetCapacity() const {
		return cap;
	}

	template <class  T>
	void Vec<T>::remove(const int &i) {
		T* newdata = new T[cap];
		bool f = false;
		for (int j = 0; j < this->size; j++) {
			if (j == i) f = true;
			if (f) newdata[j - 1] = this->data[j];
			else newdata[j] = this->data[j];
		}
		this->size -= 1;
		delete[] this->data;
		this->data = newdata;
	}

	template <class  T>
	void Vec<T>::resize(const int &n) {
		T* newdata = new T[n];
		this->cap = n;
		this->size = n > this->size ? this->size : n;
		for (int i = 0; i < this->size; i++) newdata[i] = this->data[i];
		delete[] this->data;
		this->data = newdata;
	}

	template <class  T>
	void Vec<T>::clear() {
		delete[] this->data;
		this->size = 0;
		this->cap = 1;
		this->data = new T[1];
	}

	template <class  T>
	void Vec<T>::reserve(const int &m) {
		if (this->data)
			delete[] data;
		size = 0;
		cap = m;
		data = new T[m];
	};
};
