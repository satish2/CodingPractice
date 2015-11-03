/*Demonstrates Java's Pass-by-value*/
import java.util.*;
import java.lang.*;
import java.io.*;

class test1 {
		public int val = 0;
}

class PassByValue
{
	public static test1 change(test1 t1){
		t1 = new test1();
		t1.val = 2;
		return t1;
	}
	
	public static void main (String[] args) throws java.lang.Exception
	{
		test1 t1 = new test1();
		test1 t2 = change(t1);
		System.out.println(t1.val);
		System.out.println(t2.val);
	}
}
