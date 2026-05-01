package main

func main() {
	var a int = 0
	
	for i := 0; i < 5; i++ {
		a += i

		if a % 2 == 0 {
			print(a)
		}
	}

	print(a)
}