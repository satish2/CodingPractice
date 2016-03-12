//Given a Sentence, Reverse words in it
import java.util.*;
import java.lang.*;

public class ReverseWordsInSentence {
	
	
	public static String ReverseString(String str){
		StringBuilder sb = new StringBuilder(str);
		return sb.reverse().toString();
	}
	
	public static String ReverseWordsInSentence(String sentence){
		sentence = ReverseString(sentence);
		String output = "";
		int st = 0, end = 0;
		while(true){
			while( st < sentence.length() && sentence.charAt(st) == ' '){
				st ++;
				output += ' ';
			}
			if(st >= sentence.length()) break;
			end = st;
			while(end < sentence.length() && sentence.charAt(end) != ' '){
				end++;
			}
			if(st == end && end > sentence.length()) break;
			output += ReverseString(sentence.substring(st, end));
			st = end;
		}
		return output;
	}
	
	public static void main(String[] args){
		Scanner inp = new Scanner(System.in);
		String sentence = inp.nextLine();
		System.out.println(ReverseWordsInSentence(sentence));
	}
	
}