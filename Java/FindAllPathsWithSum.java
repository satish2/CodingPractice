//Find all paths in tree with given sum
import java.util.*;
import java.lang.*;

public class FindAllPathsWithSum {
	
	static class TreeNode {
		int data;
		TreeNode left;
		TreeNode right;
	}
	
	static class Queue<T> {
		
		class QueueNode {
			T data;
			QueueNode next;
			
			public QueueNode() {
				this.next = null;
			}
		}
		
		QueueNode head;
		QueueNode tail;
		
		public Queue(){
			this.head = null;
			this.tail = null;
		}
		
		public void enqueue(T data){
			QueueNode newnode = new QueueNode();
			newnode.data = data;
			if(this.head == null){
				this.head = newnode;
				this.tail = newnode;
				return;
			}
			this.tail.next = newnode;
			this.tail = newnode;
		}
		
		public T dequeue(){
			if(this.head == null){
				return null;
			}
			
			T temp = this.head.data;
			this.head = this.head.next;
			return temp;
		}
		
		public boolean isEmpty(){
			return (this.head == null);
		}
		
	}
	
	public static void MakeTree(TreeNode root){
		Queue<TreeNode> q = new Queue<TreeNode>();
		q.enqueue(root);
		int i = 1, limit = 10;
		while(!q.isEmpty()){
				TreeNode temp = q.dequeue();
				temp.data = i;
				if(isLeftExists(i, limit)){
					temp.left = new TreeNode();
					q.enqueue(temp.left);
				} 
				if(isRightExists(i, limit)){
					temp.right = new TreeNode();
					q.enqueue(temp.right);
				}
				i++;
		}
	}
	
	public static boolean isLeftExists(int i, int limit){
		return (2*i <= limit);
	}
	
	public static boolean isRightExists(int i, int limit){
		return (2*i+1 <= limit);
	}
	
	public static void PrintInOrderTraversal(TreeNode root){
		if(root == null) return;
		PrintInOrderTraversal(root.left);
		System.out.print(root.data + "\t");
		PrintInOrderTraversal(root.right);
	}
	
	public static Integer[] path;
	
	public static void findAllPathsWithSum(TreeNode root, int sum, int level){
		if(root == null) return;
		path[level] = root.data;
		int temp = 0;
		for(int i = level; i >= 0;i--){
			temp += path[i];
			if(temp == sum){
				PrintPath(i, level);
			}
		}
		findAllPathsWithSum(root.left,sum, level+1);
		findAllPathsWithSum(root.right,sum, level+1);
	}
	
	public static void PrintPath(int st, int end){
		while(st <= end){
			System.out.print(path[st] + "\t");
			st++;
		}
		System.out.println();
	}
	
	public static int diameter(TreeNode root){
		if(root == null) return 0;
		int lHeight = getHeight(root.left);
		int rHeight = getHeight(root.right);
		int lDiameter = diameter(root.left);
		int rDiameter = diameter(root.right);
		return max(lHeight+rHeight+1, max(lDiameter, rDiameter));
	}
	
	public static int max (int a, int b){
		return a > b ? a : b;
	}
	
	public static int getHeight(TreeNode root){
		return getDepth(root);
	}
	
	public static int getDepth(TreeNode root){
		if(root == null) return 0;
		else return 1 + max(getDepth(root.left),getDepth(root.right));
	}
	
	public static void main(String[] args){
		if(args.length < 1) {
			System.out.println("Please pass integer which is sum");
			return;
		}
		System.out.println(args[0]);
		int sum = Integer.parseInt(args[0]);
		TreeNode root = new TreeNode();
		MakeTree(root);
		path = new Integer[getDepth(root)];
		PrintInOrderTraversal(root);
		System.out.println("\nPaths with sum = " + sum + " are :");
		findAllPathsWithSum(root, sum, 0);
		System.out.println("Diamter of this tree = " + diameter(root));
	}
	
}