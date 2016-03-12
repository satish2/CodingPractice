import java.lang.*;
import java.util.*;

public class HashTable<Integer,T> {
	
	private class LinkedList {
		T data;
		Integer key;
		LinkedList next;
		
		public LinkedList(){
			this.next = null;
		}
	}


	private ArrayList<LinkedList> array = new ArrayList<LinkedList>(); 
	
	public HashTable(){
		
	}
	
	private int hashfunction(int key){
		return key;
	}
	
	public void put(Integer key, T value){
		Integer index = hashfunction(key);
		LinkedList newnode = new LinkedList();
		newnode.data = value;
		newnode.key = key;
		if(array.get(index) == null){
			array.add(index, newnode);
		} else {
			LinkedList head = array.get(index);
			while(head.next != null){
				head = head.next;
			}
			head.next = newnode;
		}
	}
	
	public T get(Integer key){
		Integer index = hashfunction(key);
		LinkedList head = arr.get(index);
		while(head != null){
			if(head.key == key)
				return head.data;
			head = head.next;
		}
		return null;
	}
}