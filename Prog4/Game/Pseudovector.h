#pragma once
namespace Game {
	template <class T>
	class VecIt;

	template <class T>
	class Vec {
		friend class VecIt<T>;
	private:
		T *data;
		int size;
		int cap;
		int GetPos(const int&) const;
	public:
		typedef VecIt<T> Iterator;
		Iterator begin();
		Iterator end();
		Iterator find(const int&) const;
		Vec(int = 1);
		Vec(Vec&);
		Vec operator=(const Vec&);
		int GetCapacity() const;
		int GetSize() const;
		T& operator [](int);
		void push_back(T);
		void reserve(const int &m);
		void clear();
		void remove(const int &i);
		void resize(const int &n);
		int get_size() { return size; }
		~Vec<T>(void);
	};

	template <class T>
	class VecIt {
	private:
		T *cur;
	public:
		VecIt() : cur(0) {}
		VecIt(T *n) : cur(n) {}
		bool operator!=(const VecIt&) const;
		bool operator==(const VecIt&) const;
		T& operator *();
		T* operator ->();
		VecIt<T>& operator ++();
	};
};