#ifndef BG_LARRAY_H_
#define BG_LARRAY_H_
#include <sparsehash/dense_hash_map>
#include <tr1/unordered_map>

#include "limits.h"
using google::dense_hash_map;
using namespace std::tr1;
#define DENSE_HASHMAP

typedef int vertex;
template <class T>
class HashMap
{
private:
	T initialValue_;
	T* array;
	vertex nVtx;

#ifdef DENSE_HASHMAP
	dense_hash_map<size_t, T> data_;
#else
	std::tr1::unordered_map<size_t,T> data_;
#endif

public:
#ifdef DENSE_HASHMAP
	typedef typename dense_hash_map<size_t,T>::iterator iterator;
	T & operator [] (size_t index) {
		return data_[index];
	}
	void setEmptyKey() {
		data_.set_empty_key(-1);
	}
	void setDeletedKey() {
		data_.set_deleted_key(-2);
	}
	bool hasDefaultValue(size_t index) {
		iterator it = data_.find(index);
		if (it==data_.end())
			return true;
		return (it->second == initialValue_);
	}
#else
	typedef typename std::tr1::unordered_map<size_t,T>::iterator iterator;
	T & operator [] (size_t index)
	{
		typename std::tr1::unordered_map<size_t,T>::iterator it = data_.find(index);
		if (it==data_.end())
			return data_.insert(std::make_pair(index, initialValue_)).first->second;
		return it->second;
	}
	bool hasDefaultValue(size_t index) {
		typename std::tr1::unordered_map<size_t, T>::iterator iter = data_.find(index);
		if (iter==data_.end())
			return true;
		return (iter->second ==initialValue_);
	}
#endif

	HashMap(T initialValue, vertex _nVtx) :
		initialValue_(initialValue), nVtx(_nVtx) {
#ifdef DENSE_HASHMAP
		setEmptyKey();
		setDeletedKey();
#endif
	}
	void reset(T initialValue) {
		data_.clear();
		initialValue_ = initialValue;
	}
	void erase(size_t index) {
		data_.erase(index);
	}
	int size() {
		return data_.size();
	}
	iterator begin() {
		return data_.begin();
	}
	iterator end() {
		return data_.end();
	}
};

#endif

