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
	}

	for _, q := range qs {
		_, p := q.ans, q.para
		fmt.Printf("【input】:%v  【output】:%d\n", p, reverseList1(structures.Ints2List(p.one)))
		fmt.Printf("【input】:%v  【output】:%d\n", p, reverseList2(structures.Ints2List(p.one)))
		fmt.Printf("【input】:%v  【output】:%d\n", p, reverseList3(structures.Ints2List(p.one)))
		fmt.Printf("【input】:%v  【output】:%d\n", p, reverseList4(structures.Ints2List(p.one)))
	}
	fmt.Printf("\n\n\n")
}
