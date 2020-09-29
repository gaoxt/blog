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
}

func Test_Problem(t *testing.T) {

	qs := []question{
		{
			para{[]int{1, 2, 3}},
			ans{[]int{3, 2, 1}},
		},
		{
			para{[]int{1, 2, 3, 4, 5, 6}},
			ans{[]int{6, 5, 4, 3, 2, 1}},
		},
		{
			para{[]int{3}},
			ans{[]int{3}},
		},
		{
			para{[]int{}},
			ans{[]int{}},
		},
	}

	for _, q := range qs {
		_, p := q.ans, q.para
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(reverseList(structures.Ints2List(p.one))))
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(reverseListRecursion(structures.Ints2List(p.one))))
	}
	fmt.Printf("\n\n\n")
}
