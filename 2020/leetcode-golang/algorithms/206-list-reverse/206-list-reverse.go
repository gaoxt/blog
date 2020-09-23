package algorithms

import (
	"github.com/leetcode-golang/structures"
)

type ListNode = structures.ListNode

/**
 *	解题思路：
 *	1.双指针，通过一个临时指针保存next的位置，把当前指针不断写给新链表。
 *	2.递归，递归到最后一个，开始不断往前回溯截断给新链表。
 */

func reverseList(head *ListNode) *ListNode {
	var pre *ListNode = nil
	curr := head
	for curr != nil {
		tmp := curr.Next //保存下一个截断点
		curr.Next = pre  //开始截断
		pre = curr       //截断的值给新链表
		curr = tmp       //还原旧链表
		// curr.Next, pre, curr = pre, curr, curr.Next	//Go语法糖写法
	}
	return pre
}

func reverseListRecursion(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	p := reverseListRecursion(head.Next)
	head.Next.Next = head
	head.Next = nil //截断只取一个，终止链表循环
	return p
}
