//
//  Node.hpp
//  Chess
//
//  Created by Adam J Leuer on 2017-10-26.
//  Copyright © 2017 Adam James Leuer. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <iostream>
#include <list>


template <typename T>
class Tree {

public:

	struct Node {

	protected:
		T data;

		list <Node> children;

	public:

		explicit Node (T & data) :
			data(data) {}

		void addChild (T & data) {
			Node kid(data);
			children.push_back(kid);
		}

		void setChildren (list <Node> & nodes) {
			this->children = nodes;
		}
	};


	list <Node> siblings;

	Tree () :
		Tree(nullptr)
	{

	}

	explicit Tree (T & data) :
		root(data)
	{
		root.setChildren(siblings);
	}


	void appendSibling (T * data) {
		Node sibling(data);
		siblings.push_back(sibling);
	}

	void addChild (T & data) {
		root.addChild(data);
	}

private:

	Node root;
};


#endif /* Tree_hpp */
