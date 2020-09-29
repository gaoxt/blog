package algorithms

import (
	"github.com/leetcode-golang/structures"
)

type ListNode = structures.ListNode

/**
 *	解题思路：
 *	1.reverseList 拼链迭代法
 *	2.reverseBetween 递归法
 *	3.reverseIteration 顺序拼链迭代法，结构清晰。
 */

func reverseList(head *ListNode, m, n int) *ListNode {
	if m == n || head.Next == nil {
		return head
	}
	count := 0
	var newhead = head                           //链表开头
	var pre *ListNode = nil                      //反转的链表
	var headpoint1, headpoint2 = head, head.Next //记录反转开始时的两个节点
	for head != nil {
		count++
		//需要反转的部分
		if count >= m && count <= n {
			//如果到达最后一个反转的位置，则开始拼接头尾
			if count == n {
				if m == 1 {
					newhead.Next = head.Next
					newhead = head
				} else {
					headpoint1.Next = head      //把反转链表的头 指给 原链表头。
					headpoint2.Next = head.Next //把原链表尾巴 指给 反转链表的尾巴
				}
			}
			head.Next, pre, head = pre, head, head.Next //反转链表
		} else {
			headpoint1 = head
			headpoint2 = head.Next
			head = head.Next //指针下移
		}
	}
	return newhead
}

//反转前 n 个元素，参考list-reverse-part
var successor *ListNode = nil //记录要链的下一个节点
func reverseN(head *ListNode, n int) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	if n == 1 {
		successor = head.Next
		return head
	}
	last := reverseN(head.Next, n-1)
	head.Next.Next = head
	head.Next = successor
	return last
}

func reverseBetween(head *ListNode, m, n int) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	if m == 1 {
		// m等于1相当于反转前 n 个元素
		return reverseN(head, n)
	}
	// 前进到反转的起点触发。
	head.Next = reverseBetween(head.Next, m-1, n-1)
	return head

}

func reverseIteration(head *ListNode, m, n int) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	var prev *ListNode = nil
	var cur = head
	//前进直到需要反转的位置
	for m > 1 {
		prev = cur
		cur = cur.Next
		m--
		n--
	}
	//tail记录反转链尾，con记录反转前置节点
	var tail, con, tmp *ListNode = cur, prev, nil
	//开始反转
	for n > 0 {
		tmp = cur.Next
		cur.Next = prev
		prev = cur
		cur = tmp
		n--
	}
	//拼接反转链表prev 到 前置链表con
	if con != nil {
		con.Next = prev
	} else {
		head = prev
	}
	//拼接反转链尾 到 原链表之后
	tail.Next = cur
	return head

}
