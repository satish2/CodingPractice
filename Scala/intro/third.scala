object third {
def main(args:Array[String]):Unit = {

	for{i <- 1 to 10}{
	for{j <- 1 to 10}
		println(i*j)
	}
}
}
