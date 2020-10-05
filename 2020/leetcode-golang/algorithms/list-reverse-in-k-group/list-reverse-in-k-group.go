package algorithms

import (
	"github.com/leetcode-golang/structures"
)

type ListNode = structures.ListNode

/**
 *	解题思路：
 *	多指针记录，递归反转，通过pre和end记录需要反转k个链表的前后位置。
 */

func reverseKGroup(head *ListNode, k int) *ListNode {
	dummy := &ListNode{Val: -1} //定义头节点
	dummy.Next = head           //链接头节点到主链
	pre, end := dummy, dummy    //pre指group的头节点的上一个节点，end指group的尾节点

	for end.Next != nil {
		//把end移到gorup尾部
		for i := 0; i < k && end != nil; i++ {
			end = end.Next
		}
		//判定有无下一组group
		if end == nil {
			break
		}
		//切断链表
		next := end.Next  //切断前用next记录主链
		end.Next = nil    //切断group链尾与主链的联系
		start := pre.Next //记录group的头节点

		//连接主链
		pre.Next = reverseItem(start) //pre.next 指向 反转链表
		start.Next = next             //反转后start为头节点，链回主链

		//挪动到下一组处理
		pre = start
		end = pre
	}
	return dummy.Next
}

func reverseItem(head *ListNode) *ListNode {
	var pre *ListNode
	cur := head
	for cur != nil {
		cur.Next, pre, cur = pre, cur, cur.Next
	}
	return pre
}
