import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class TyrionAndWine {
    
    public static void main(String[] args) {
        Scanner inp = new Scanner(System.in);
        int N = inp.nextInt();
        int K = inp.nextInt();
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
        for(int i=0; i<N; i++){
            pq.add(inp.nextInt());
        }
        if(pq.size() <= 0){
            System.out.println("-1");
            return;                
        }
        int count = 0;
        int i =0;
        while(pq.peek() < K && i<N-1){
            if(pq.size() < 2){
                System.out.println("-1");
                return;                
            }
            count++;
            i++;
            int newgoodness = pq.poll() + 2*(pq.poll());
            pq.offer(newgoodness);
        }
        
        if(i == N-1 && pq.peek() < K) {
            System.out.println("-1");
            return;
        } else 
            System.out.println(count);
    }
}
