//ALGO
//check for 3ques
if(p[i]+q[i]+r[i] == 3)
{
	fork1();
	if(!fork2())
	{
			 	if(!forsk3())
			 	{
				 	printf("done 3 ques");
				 	 exit();
				 }	
	exit();
}
//check for 2ques				 	
else if(p[i]+q[i] == 2)
{
	fork1();
	if(!fork2())
	{
			 	printf("done 2 ques");
				exit();
   }	
	exit();
}
//check for 1 ques
else if(p[i] == 1)
{
	fork1();
	exit();
}
else 
{
	printf("none is done");
}

	
	
	
//ending main....	