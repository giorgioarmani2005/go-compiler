package main



func main() {
  var a, b, c = 1+1, 2+2, 3+3

  var k = 32

  i := 5

  for i := 0; i < 10; i++ {
    if i % 2 == 0 {
      print(a)
      a++
    } else if i % 3 == 0 {
      print(a)
    } else if i % 5 == 0 {
      print(b)
    } else {
      print(c)
    }

    for j := i; i < 25; j++ {
    //   print(j)
    //   print(j)

      if j % 2 == 0 {
        print(j)
      }
    }

    print(i)
  }

  if k < 32 {
    print(k)
  }

  print(k)
}
