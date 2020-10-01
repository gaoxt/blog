package algorithms

import (
	"github.com/leetcode-golang/structures"
)

type ListNode = structures.ListNode

/**
 *	解题思路：
 *	1.去重，通过map记录不重复的节点，如果重复则往后移动。
 *	2.双指针，以当前节点为点遍历，遍历整个链表如果重复则过滤。
 */

func removeDuplicateNodes(head *ListNode) *ListNode {
	if head == nil {
		return head
	}
	data := map[int]bool{head.Val: true}
	cur := head
	for cur.Next != nil {
		cur := cur.Next
		if !data[cur.Val] {
			data[cur.Val] = true
			cur = cur.Next
		} else {
			cur.Next = cur.Next.Next //如果重复，则跳过next节点。
		}
	}
	cur.Next = nil
	return head
}

func removeDuplicateNodes2(head *ListNode) *ListNode {
	cur := head
	for cur != nil {
		tmp := cur
		for tmp.Next != nil {
			if tmp.Next.Val == cur.Val { //遇到相同的则过滤
				tmp.Next = tmp.Next.Next
			} else {
				tmp = tmp.Next
			}
		}
		cur = cur.Next
	}
	return head
}
