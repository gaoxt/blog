package algorithms

import (
	"github.com/leetcode-golang/structures"
)

type ListNode = structures.ListNode

/**
 *	反转整个链表
 *	解题思路：
 *	1.双指针，通过一个临时指针保存next的位置，把当前指针不断写给新链表。
 *	2.递归，递归到最后一个，开始不断往前截断给新链表。
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
	last := reverseListRecursion(head.Next) //不要用压栈思想，这里表示递归后完成后的反转链表。5->...->2->null，1->2->null
	head.Next.Next = head                   //理解为下一个结点的指向，希望2的下一个节点指向自己，即在当前head1的next为2，指向自己，2->1。
	head.Next = nil                         //补上链尾，2->1->null。压栈思想里是切断链表循环。
	return last
}
