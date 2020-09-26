package algorithms

import "github.com/leetcode-golang/structures"

type ListNode = structures.ListNode

/**
 *	将链表的前 n 个节点反转（n <= 链表长度）
 *	解题思路：
 *	1.递归
 */

var successor *ListNode = nil //记录要链的下一个节点

func reverseList(head *ListNode, n int) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	if n == 1 {
		successor = head.Next //如果反转到最后一个，则记录下一个要链的节点，方便最后链过去。
		return head
	}
	//以head.Next为起点，反转到n-1个节点。这段理解为返回一个反转好的列表。 (1<-2) 3->4->5->6->null
	last := reverseList(head.Next, n-1)
	head.Next.Next = head //2个Next指的是，也就是1->2->null变成3->1
	head.Next = successor //接上原链表，...->1->3->...
	return last
}
