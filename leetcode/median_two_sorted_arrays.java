/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

import java.util.*;

public class Median {
    private int[] array1;
    private int[] array2;
    
    public static void main (String[] args) {
            
        int array1[10] = { -10, -9, -2, -1, 0, 2, 6, 8, 18, 22 };
        int array2[10] = { -33, -22, -7, 2, 3 ,6, 18, 22, 33, 47};
        findMedianSortedArrays(array1, array2);
    }

    public double findMedianSortedArrays(int[] ar1, int[] ar2) {
       
        /*
         * There are two possibilities.
         * Take a number line and imagine both arrays on that number line. 
         * Array 1 and Array 2 can have nothing in common. Discrete sets. 
         *    - In this case, <array1> ...... <array2>. In this case, median would be 
         *    - Total len =   len(array1) + len(array2). 
         *    - If odd, floor(total_len/2); Since arrays start with 0.
         *    - If even, half of (total_array[total_len/2-1] + total_array[total_len/2])
         *
         * Arrays have common set of integers.
         *    - Merge them and return median. 
         */
        int[] total_array = merge_array(ar1, ar2);
        int totalLength = total_array.length;
        double median = 0.0;
        if (totalLength %2 == 0) {
            int medianIndex = (totalLength/2) -1;
            median = total_array[medianIndex] + total_array[medianIndex + 1];
            median = median/2;
        } else {
            int medianIndex = (int)Math.floor(totalLength/2);
            median = total_array[medianIndex];
        }
        return median;
    }

    private int[] merge_array(int[] a1, int[] a2) {
        int i = 0;
        int j = 0; 
        int k = 0;
        int total_length = a1.length + a2.length;
        int[] total_array = new int[total_length];
        for (k = 0; k < total_length; k++) {
            total_array[k] = 0;
        }
        k = 0;
        while (i < a1.length && j < a2.length) {
            if (a1[i] < a2[j]) {
                total_array[k] = a1[i];
                i++;
                k++;
            } else {
                total_array[k] = a2[j];
                j++;
                k++;
            }
        }

        while (i < a1.length) {
            total_array[k] = a1[i];
            i++;
            k++;
        }

        while (j < a2.length) {
            total_array[k] = a2[j];
            j++;
            k++;
        }

        return total_array;
    }

}
