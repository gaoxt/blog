package algorithms

import (
	"fmt"
	"testing"

	"github.com/leetcode-golang/structures"
)

type question struct {
	para
	ans
}

type ans struct {
	one []int
}

type para struct {
	one  []int
	m, n int
}

func Test_Problem(t *testing.T) {

	qs := []question{
		{
			para{[]int{1, 2, 3, 4, 5}, 2, 5},
			ans{[]int{1, 5, 4, 3, 2}},
		},
		{
			para{[]int{1, 2, 3, 4, 5, 6, 7, 8, 9}, 4, 6},
			ans{[]int{1, 2, 3, 6, 5, 4, 7, 8, 9}},
		},
		{
			para{[]int{3}, 3, 5},
			ans{[]int{3}},
		},
	}

	for _, q := range qs {
		_, p := q.ans, q.para
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(reverseList(structures.Ints2List(p.one), p.m, p.n)))
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(reverseBetween(structures.Ints2List(p.one), p.m, p.n)))
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(reverseIteration(structures.Ints2List(p.one), p.m, p.n)))
	}
	fmt.Printf("\n\n\n")
}
