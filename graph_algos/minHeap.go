package main
import "fmt"

// PriorityQueue implements a min-heap using a slice.
//
// The smallest element is always at index 0.
// For an element at index i (zero-based indexing):
//   - Parent:      (i - 1) / 2
//   - Left child:  2*i + 1
//   - Right child: 2*i + 2
//
// The min-heap property requires every parent to be less than
// or equal to its children.

type PriorityQueue struct {
	heap []int
}

// Push inserts x into the priority queue and restores the min-heap property.
//
// Time complexity: O(log n) worst case.
func (pq *PriorityQueue) Push(x int) {
	pq.heap = append(pq.heap, x)

	i := len(pq.heap) - 1

	// Sift the new element upward until the heap property is restored.
	for i > 0 {
		parent := (i - 1) / 2

		if pq.heap[parent] <= pq.heap[i] {
			break
		}

		pq.heap[parent], pq.heap[i] = pq.heap[i], pq.heap[parent]
		i = parent
	}
}

// pushDown restores the min-heap property starting at index i,
// assuming the subtrees rooted at its children are already valid min-heaps.
//
// Time complexity: O(log n) worst case.
func (pq *PriorityQueue) pushDown(i int) {
	for 2*i+1 < len(pq.heap) {
		// Start with the left child.
		smallest := 2*i + 1

		// Select the right child if it exists and is smaller.
		right := 2*i + 2
		if right < len(pq.heap) && pq.heap[right] < pq.heap[smallest] {
			smallest = right
		}

		// The heap property is already satisfied.
		if pq.heap[i] <= pq.heap[smallest] {
			break
		}

		// Move the smaller child upward and continue downward.
		pq.heap[i], pq.heap[smallest] = pq.heap[smallest], pq.heap[i]
		i = smallest
	}
}

// Pop removes and returns the smallest element.
//
// It returns (0, false) if the priority queue is empty.
//
// Time complexity: O(log n) worst case.
func (pq *PriorityQueue) Pop() (int, bool) {
	if len(pq.heap) == 0 {
		return 0, false
	}

	minValue := pq.heap[0]
	last := len(pq.heap) - 1

	// Move the last element to the root and remove the last element.
	pq.heap[0] = pq.heap[last]
	pq.heap = pq.heap[:last]

	// Restore the min-heap property.
	pq.pushDown(0)

	return minValue, true
}

// Peek returns the smallest element without removing it.
//
// It returns (0, false) if the priority queue is empty.
//
// Time complexity: O(1).
func (pq *PriorityQueue) Peek() (int, bool) {
	if len(pq.heap) == 0 {
		return 0, false
	}

	return pq.heap[0], true
}

// Len returns the number of elements in the priority queue.
//
// Time complexity: O(1).
func (pq *PriorityQueue) Len() int {
	return len(pq.heap)
}

// Heapify replaces the current priority queue contents with a copy of arr
// and rearranges the elements to satisfy the min-heap property.
//
// The input slice is not modified.
// An empty input produces an empty priority queue.
//
// Time complexity: O(n).
func (pq *PriorityQueue) Heapify(arr []int) {
	pq.heap = append([]int(nil), arr...)

	// Leaf nodes already satisfy the heap property.
	// Start at the last non-leaf node and process nodes in reverse order.
	for i := len(pq.heap)/2 - 1; i >= 0; i-- {
		pq.pushDown(i)
	}
}

func main() {
	pq := &PriorityQueue{}

	pq.Push(7)
	pq.Push(3)
	pq.Push(9)
	pq.Push(1)

	fmt.Println(pq.Peek()) // 1 true
	fmt.Println(pq.Len())  // 4

	for pq.Len() > 0 {
		x, ok := pq.Pop()
		if !ok {
			break
		}
		fmt.Println(x)
	}

	fmt.Println(pq.Pop()) // 0 false
}