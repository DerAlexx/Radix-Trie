//============================================================================
// Name        : Trie.h
// Author      : Alexander M. Westphal / Paul Schroeder / Klaus Riedl
// Version     : Version 1.0
// Copyright   :
// Description : Trie.h Template
// Compiler and C++ Version: GNU GCC / C++14 Standard
//============================================================================

#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
#include <typeinfo>
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <cstring>
#include <stdlib.h>

template<class T, class E = char> class Trie {

public:	
	class _node;
	class InternalNode;
	class Leaf;
	class TrieIterator;
	typedef std::basic_string<E> key_type;
	typedef std::pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef TrieIterator iterator;
	typedef std::map<E, _node*> mappy;

	InternalNode* root;
	TrieIterator it;
    TrieIterator ab;
	Trie(){
		root = new InternalNode("");
	};


	class _node {
	public:
		T mPath;
		mappy mappyTheLittleMap;
		virtual bool insert(key_type, T) = 0;
		virtual bool clear() = 0;
		virtual bool erase(const key_type& value) = 0;
		virtual void clearKlausi() = 0;
	};

	class Leaf: public _node {
	public:
		mappy mappyTheLittleMap;
		key_type mMeaning;
		T mPath;
		Leaf(key_type value, T path) {
			mMeaning = value;
			mPath = path;
		}

		bool insert(key_type, T) {
			return false;
		}

		bool clear(){
			return false;
		}

		bool erase(const key_type& value) {
			return false;
		}

		void clearKlausi() {}
	};

	class InternalNode: public _node {
	public:
		mappy mappyTheLittleMap;
		T mPath;

		InternalNode(T path) {
			mPath = path;
		}
		InternalNode() = default;
		bool insert(key_type key, T value) {
			try {
				using namespace std;
				E currentChar = key[0];
				InternalNode* next;
				if (!currentChar =='#') {
					if (mappyTheLittleMap.empty() || mappyTheLittleMap.find(currentChar) == mappyTheLittleMap.end()) {
						next = new InternalNode(mPath += currentChar);
						mappyTheLittleMap.insert(pair<E,_node*>(currentChar, static_cast<_node*>(next)));
					} else {
						next = static_cast<InternalNode*>(mappyTheLittleMap.find(currentChar)->second);
					}
				} else if (!mappyTheLittleMap.count(currentChar)) {
					Leaf *last = new Leaf(value, mPath += currentChar);
					mappyTheLittleMap.insert(pair<E,_node*>(currentChar, static_cast<_node*>(last)));
					return true;
				}
				next->insert(key.erase(0, 1), value);
				return true;
			} catch (...) {
				using namespace std;
				cout << "An error occurred" << endl;
				return false;
			}
		}

		void clearKlausi() {
			if (!mappyTheLittleMap.empty()) {
				for (typename mappy::iterator it=mappyTheLittleMap.begin(); it!=mappyTheLittleMap.end(); it++) {
					it -> second -> clearKlausi();
					delete it -> second;
				}
				mappyTheLittleMap.clear();
			}
		}

		bool clear() {
			_node* next = mappyTheLittleMap.begin()->second;
			mappyTheLittleMap.clear();
			delete this;
			if (std::strcmp(typeid(next).name(), "InternalNode") == 0) {
				next->clear();
			} else if (std::strcmp(typeid(next).name(), "Leaf") == 0) {
				delete next;
				return true;
			}
			return false;
		}

		void clearTrie() {
			auto iterator = mappyTheLittleMap.begin();
			while (iterator != mappyTheLittleMap.end()) {
				iterator->second->clear();
				delete iterator->second;
				iterator++;
			}
			mappyTheLittleMap.clear();
		}

		bool erase(const key_type& value) {
			using namespace std;
			string str_key = string(value) + "#";
			cout << str_key << endl;
			bool newDelete = true;
			InternalNode* current = this;
			InternalNode* deleteNode = current;
			if (!(current->mappyTheLittleMap.empty())) {
				for (char& currentChar : str_key) {
					if (current->mappyTheLittleMap.find(currentChar) != current->mappyTheLittleMap.end()) {
						if (current->mappyTheLittleMap.size() == 1 && newDelete) {
							deleteNode = current;
							newDelete = false;
						} else if (current->mappyTheLittleMap.size() > 1) {
							newDelete = true;
						}
					} else {
						return false;
					}
					current = static_cast<InternalNode*>(current->mappyTheLittleMap.find(currentChar)->second);
				}
				deleteNode->clear();
			} else {
				return false;
			}
			return false;
		}
		bool empty() {
			return mappyTheLittleMap.empty();
		}
	};

	class TrieIterator {
	private:
		std::stack<typename mappy::iterator> stackyTheLittleStack;
	public:
		TrieIterator()=default;

		T& operator*() {
            Leaf* last = static_cast<Leaf*>(&stackyTheLittleStack.top().first->second);
            return last->operator *();
		};

		bool operator !=(const TrieIterator& rhs) {
			return !operator ==(rhs);
		};

		bool operator ==(const TrieIterator& rhs) {
            return this->stackyTheLittleStack == rhs.stackyTheLittleStack;
		};

		TrieIterator& operator ++() {
            while(stackyTheLittleStack.top()++ == stackyTheLittleStack.top().end()){
                stackyTheLittleStack.pop();
            }
            stackyTheLittleStack.top()++->second->slideLeft();
    };

        void slideLeft(InternalNode* node){
            InternalNode* current = node;
            while(current->mappyTheLittleMap.begin()->first != '#'){
                auto ki = current->mappyTheLittleMap.begin();
                current = current->mappyTheLittleMap.begin()->second;
                stackyTheLittleStack.push(ki);
            }
            auto ki = current->mappyTheLittleMap.begin();
            stackyTheLittleStack.push(ki);
        }
	};


	/**
	 * Method to return whether the Map isEmpty or not
	 */
	bool empty() {
		return root->empty();
	}

	/**
	 *   Insert a single InternalNode or Leaf.
	 */
	iterator insert(const value_type& value) {
		key_type a = value.first + "#";
		T b = value.second;
		root->insert(a,b);
		return it;
	}

	/**
	 *   Delete a single InternalNode or a Leaf.
	 */
	void erase(const key_type& value) {
		root->erase(value);
	}



	/**
	 * Method to clear the Tree.
	 * Except for the root.
	 */
	void clear() {
		try {
			root->clearKlausi();
		} catch(...) {
			std::cout << "Root has no children yet! \n";
		}
	}

	/**
	 *  fehlt noch
	 *
	 */
	void showTrie() {
		iterator it = begin();
		std::string word = "";
		while(it != end())  {
			InternalNode* kNode=static_cast<InternalNode*>(it.mNode);
			E character = kNode -> mPath.back();
			if(character == '#') {
				++it;
				T path = *it;
				std::cout << word << "------->" << path << std::endl;
				word = "";
			} else {
				word += character;
				++it;
			}
		}
	}

	iterator lower_bound(const key_type& testElement) {
		return iterator(); //dont need
	}

	iterator upper_bound(const key_type& testElement) {
		return iterator(); //dont need
	}

	iterator find(key_type& testElement) {
		iterator it = begin();
		while(it != end()){
		    if (it.operator*() == testElement){
		        return it;
		    }
		    it++;
		}
	}

	iterator begin() {
		return it.slideLeft(root);
	}

	iterator end() {
        return ab;
	}
};

#endif // TRIE_H_INCLUDED