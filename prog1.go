package main

import (
	"fmt"
	"math"
)

type TableRow1 struct {
	n       int
	a, b, d float64
}

type TableRow2 struct {
	n          int
	xn, xn1, d float64
}

func bisection(a, b, eps float64) []TableRow1 {
	var res []TableRow1
	n := 0
	for math.Abs(b-a) >= eps {
		res = append(res, TableRow1{n, a, b, math.Abs(b - a)})
		c := (a + b) / 2.0
		if (math.Sin(a)-2*a-1)*(math.Sin(c)-2*c-1) < 0 {
			b = c
		} else {
			a = c
		}
		n++
	}
	res = append(res, TableRow1{n, a, b, math.Abs(b - a)})
	return res
}

func newton(x0, eps float64) []TableRow2 {
	var res []TableRow2
	n := 0
	diff := eps + 1.0
	for diff >= eps {
		fx := math.Sin(x0) - 2*x0 - 1
		dfx := math.Cos(x0) - 2
		x1 := x0 - fx/dfx
		diff = math.Abs(x1 - x0)
		res = append(res, TableRow2{n, x0, x1, diff})
		x0 = x1
		n++
	}
	return res
}

func simpleIteration(x0, eps float64) []TableRow2 {
	var res []TableRow2
	n := 0
	diff := eps + 1.0
	for diff >= eps {
		x1 := (math.Sin(x0) - 1) / 2.0
		diff = math.Abs(x1 - x0)
		res = append(res, TableRow2{n, x0, x1, diff})
		x0 = x1
		n++
	}
	return res
}

func main() {
	var a, b, eps, x0n, x0s float64
	_, err := fmt.Scan(&a, &b, &eps, &x0n, &x0s)
	if err == nil {
		bres := bisection(a, b, eps)
		for _, r := range bres {
			fmt.Println(r.n, r.a, r.b, r.d)
		}

		nres := newton(x0n, eps)
		for _, r := range nres {
			fmt.Println(r.n, r.xn, r.xn1, r.d)
		}

		sres := simpleIteration(x0s, eps)
		for _, r := range sres {
			fmt.Println(r.n, r.xn, r.xn1, r.d)
		}
	}
}
