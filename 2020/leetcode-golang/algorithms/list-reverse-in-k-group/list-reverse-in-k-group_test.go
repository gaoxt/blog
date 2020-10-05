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
	one []int
	m   int
}

func Test_Problem(t *testing.T) {

	qs := []question{
		{
			para{[]int{1, 2, 3, 4, 5}, 2},
			ans{[]int{2, 1, 4, 3, 5}},
		},
		{
			para{[]int{1, 2, 3, 4, 5}, 3},
			ans{[]int{3, 2, 1, 4, 5}},
		},
	}

	for _, q := range qs {
		_, p := q.ans, q.para
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(reverseKGroup(structures.Ints2List(p.one), p.m)))
	}
	fmt.Printf("\n\n\n")
}
