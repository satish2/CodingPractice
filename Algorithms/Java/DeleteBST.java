//Delete a node from BST

class DeleteBST {
	
	public boolean DeleteANodeInBST(TreeNode root, int data){
		TreeNode curr = root, parent = null;
		if(root == null) return false;
		while(curr != null){
			if(curr.data == data){
				break;
			} else if (curr.data > data){
				parent = curr;
				curr = curr.left;
			} else if (curr.data < data){
				parent = curr;
				curr = curr.right;
			}
		}
		if(curr == null) return false;
		boolean isLeft = (parent.left == curr);
		/*
		1. Current Node is non-leaf, has two children
		2. Has Only one child
		3. Leaf
		1. -> Get the maximum of left and replace that node with this and delete that node.
		2. -> only left :: make left as this
		3. -> if (isLeft) parent.left - null || parent.right - null
		*/
		if(curr.left != null && curr.right != null){
			TreeNode maxInLeft = getMaxInLeft(curr.left);
			if(isLeft) parent.left = maxInLeft;
			else parent.right = maxInLeft;
		} else if (curr.left == null && curr.right == null) {
			if(isLeft) parent.left = null;
			else parent.right = null;
		}
		else if (curr.left == null){
			if(isLeft) parent.left = curr.right;
			else parent.right = curr.right;
		} else if(curr.right == null) {
			if(isLeft) parent.left = curr.left;
			else parent.right = curr.left;
		}
		return true;
	}
	
	public TreeNode getMaxInLeft(TreeNode root){
		TreeNode parent = null, current = root;
		while(current.right != null){
			parent = current;
			current = current.right;
		}
		parent.right = null;
		return current;
	}
	
	public boolean isBST(TreeNode root){
		if(root == null) return false;
		if(root.left == null && root.right == null) return true;
		boolean isBST = false;
		if(root.left != null && root.data >= getMaxInLeft(root.left)){
			isBST = true;
		} else
			return false;
		if(root.right != null && root.data < getMinInLeft(root.right)){
			isBST = true;
		} else
			return false;
		return isBST;
	}
	//Issue above is it checks for multiple times a node for max and min in subtrees
	
	//Do Inorder traversal and check if curr and greater or equals previous .. if false for one then return false
	//previous initialized to Integer.MIN_VALUE
	public boolean isBST(TreeNode root, int previous){
		if(root == null) return false;
		boolean left = isBST(root.left, previous);
		if(!left) return false;
		
		if(root.data >= previous){
			previous = root.data;
		} else {
			return false;
		}
		
		return isBST(root.right, previous);
	}
	
	//Inorder using Stack L,C,R
	public void InOrderTraversal(TreeNode root){
		Stack<TreeNode> st = new Stack<TreeNode>();
		boolean done = false;
		while(!done){
			while(root != null){
				st.push(root);
				root = root.left;
			}
			if(st.isEmpty()) {
				done = true;
				break;
			} else {
				TreeNode temp = st.pop();
				System.out.println(temp.data);
				temp = temp.right;	
			}
		}
	}

	
	
}