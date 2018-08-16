#ifndef DT_H
#indef DT_H

namespace Metagross {
	struct Node {
		int depth;
		double thresh;
		Node* left;
		Node* right;
	};
	
	class DecisionTree {
		private:
			int maxDepth;
			Node head;
		public:
			//Constructors
			DecisionTree();
			DecisionTree(int maxDepth);
			DecisionTree(Node head);
			DecisionTree(Node head, int maxDepth);
	};
}