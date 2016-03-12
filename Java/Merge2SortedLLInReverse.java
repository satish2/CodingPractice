import java.util.*;
import java.lang.*;

public class Merge2SortedLLInReverse{
	
	static class LinkedList {
		int data;
		LinkedList next;
	}
	
	public static LinkedList GFG61(LinkedList head){
		LinkedList head1 = head, head2 = head.next;
		LinkedList curr1 = head1, curr2 = head2;
		//curr1.next == curr2 <-- at start of every loop
		while(curr1 != null && curr2 != null){
			curr1.next = curr2.next;
			curr1 = curr1.next;
			if(curr1 != null){
				curr2.next = curr1.next;
				curr2 = curr2.next;	
			} else {
				curr2.next = null;
			}
		}
		if(curr2 == null){
			curr1.next = null;
		}
		//head1 , head2 <-- two linkedlists
		head2 = Reverse(head2);
		return Merge2SortedLLS(head1, head2);
	}
	
	public static LinkedList Reverse(LinkedList head){
		LinkedList prev = null, curr = head, next = null;
		while(curr != null){
			next = curr.next;
			curr.next = prev;
			prev = curr;
			curr = next;
		}
		return prev;
	}
	
	public static LinkedList Merge2SortedLLS(LinkedList head1, LinkedList head2){
		if(head1 == null) return head2;
		if(head2 == null) return head1;
		LinkedList head = null;
		if(head1.data < head2.data){
			head = head1;
			head1 = head1.next;
		} else {
			head = head2;
			head2 = head2.next;
		}
		LinkedList curr = head;
		while(head1 != null && head2 != null){
			if(head1.data < head2.data){
				curr.next = head1;
				head1 = head1.next;
				curr = curr.next;
			} else {
				curr.next = head2;
				head2 = head2.next;
				curr = curr.next;
			}
		}
		return head;
	}
	
	
	public static LinkedList merge(LinkedList head1, LinkedList head2){
 		if(head1 == null) return head2;
		if(head2 == null) return head1;
		LinkedList curr = null, prev = null, next1 = head1, next2 = head2;
		while(next1!= null && next2 != null){
			if(next1.data <= next2.data){
				prev = curr;
				curr = next1;
				next1 = next1.next;
				curr.next = prev;
			} else {
				prev = curr;
				curr = next2;
				next2 = next2.next;
				curr.next = prev;
			}
		}
		while(next1!= null){
			prev = curr;
			curr = next1;
			next1 = next1.next;
			curr.next = prev;
		}
		while(next2 != null){
			prev = curr;
			curr = next2;
			next2 = next2.next;
			curr.next = prev;
		}
		return curr;
	}
	
	public static void MakeLL(LinkedList head1){
		Random rand = new Random();
		LinkedList prev = null;
		int i = 0, j = 10;
		while(i < 10 && j > 0){
			if(i%2 ==0){
				head1.data = i;
			} else {
				head1.data = j;
			}
			prev = head1;
			head1.next = new LinkedList();
			head1 = head1.next;
			i++;
			j--;
		}
		prev.next = null;
	}
	
	public static void PrintLL(LinkedList head){
		System.out.println();
		while(head != null){
			System.out.print(head.data + "\t");
			head = head.next;
		}
		return;
	}
	
	public static void main(String[] args){
		/*LinkedList head1 = new LinkedList();
		LinkedList head2 = new LinkedList();
		MakeLL(head1);
		MakeLL(head2);
		PrintLL(head1);
		PrintLL(head2);
		LinkedList head = merge(head1, head2);
		PrintLL(head);*/
		/*GeeksForGeeks 61*/
		LinkedList head = new LinkedList();
		MakeLL(head);
		PrintLL(GFG61(head));
		/*GeeksForGeeks 61*/
	}
	
	
	
}