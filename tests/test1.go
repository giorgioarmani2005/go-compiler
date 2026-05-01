package main

func main() {
	var a int = 0
	
	for i := 0; a < 5; i++ {
		print(i)

		if i % 2 == 0 {
			continue
		}
	}

	print(a)
}