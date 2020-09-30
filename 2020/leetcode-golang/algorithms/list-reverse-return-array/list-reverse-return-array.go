package algorithms

import (
	"github.com/leetcode-golang/structures"
)

type ListNode = structures.ListNode

/**
 *	解题思路：
 *	1.头插，先反转，再按序插入数组。
 *	2.倒插，先移动指针，再倒序插入数组。
 *	3.递归，到底部依次退函数栈时开始放入数组
 *	4.头插倒序，先移动指针插入数组，再倒序数组。
 */

func reverseList1(head *ListNode) []int {
	var newHead *ListNode
	arr := []int{}
	for head != nil {
		head.Next, newHead, head = newHead, head, head.Next
	}

	for newHead != nil {
		arr = append(arr, newHead.Val)
		newHead = newHead.Next
	}
	return arr
}

func reverseList2(head *ListNode) []int {
	var cur = head
	count := 0
	for cur != nil {
		cur = cur.Next
		count++
	}
	arr := make([]int, count)
	for i := count - 1; i >= 0; i-- {
		arr[i] = head.Val
		head = head.Next
	}
	return arr
}

func reverseList3(head *ListNode) []int {
	if head == nil {
		return nil
	}
	return appendData(head)
}

func appendData(head *ListNode) []int {
	if head.Next != nil {
		list := appendData(head.Next)
		list = append(list, head.Val)
		return list
	}

	return []int{head.Val}
}

func reverseList4(head *ListNode) []int {
	arr := []int{}
	for head != nil {
		arr = append(arr, head.Val)
		head = head.Next
	}
	for i, j := 0, len(arr)-1; i < j; {
		arr[i], arr[j] = arr[j], arr[i]
		i++
		j--
	}
	return arr
}
