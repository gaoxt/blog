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
			para{[]int{1, 2, 3, 3, 2, 1}},
			ans{[]int{1, 2, 3}},
		},
		{
			para{[]int{1, 1, 1, 1, 2}},
			ans{[]int{1, 2}},
		},
	}

	for _, q := range qs {
		_, p := q.ans, q.para
		// fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(removeDuplicateNodes(structures.Ints2List(p.one))))
		fmt.Printf("【input】:%v  【output】:%v\n", p, structures.List2Ints(removeDuplicateNodes2(structures.Ints2List(p.one))))
	}
	fmt.Printf("\n\n\n")
}
