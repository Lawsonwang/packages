// Code By WLS
#ifndef SEG_TREE_H
#define SEG_TREE_H

#include <vector>
#include <iostream>
using namespace std;

template <typename ValueT = int, typename IndexT = int>
class segtree {
	public:
		static const int MAX_SIZE = 1e4 + 5;
	private:
		IndexT n;
		struct node {
			IndexT l, r;
			ValueT sum, lazy;
			IndexT len() {
				return r - l + 1;
			}
			node(IndexT l = 0, IndexT r = 0, ValueT s = ValueT{}, ValueT lz = ValueT{}):l{l}, r{r}, sum{s}, lazy{lz} {}
		};
		vector<ValueT> a;
		vector<node> t;
		void push_up(const IndexT &x) {
			t[x].sum = t[x * 2].sum + t[x * 2 + 1].sum;
		}
		void push_down(const IndexT &x) {
			if (t[x].lazy) {
				t[x * 2].sum += t[x].lazy * t[x * 2].len();
				t[x * 2 + 1].sum += t[x].lazy * t[x * 2 + 1].len();
				t[x * 2].lazy += t[x].lazy;
				t[x * 2 + 1].lazy += t[x].lazy;
				t[x].lazy = 0;
			}
		}
		void build(const IndexT &p, const IndexT &l, const IndexT &r) {
			t[p] = (node){l, r, ValueT{}, ValueT{}};
			if (l == r) {
				t[p].sum = a[l];
				return;
			}
			IndexT mid = (l + r) >> 1;
			build(p * 2, l, mid);
			build(p * 2 + 1, mid + 1, r);
			push_up(p);
		}

		ValueT qry(const IndexT &p, const IndexT &x, const IndexT &y) {
			IndexT l = t[p].l, r = t[p].r;
			if (x <= l && r <= y) {
				return t[p].sum;
			}
			push_down(p);
			IndexT mid = (l + r) >> 1;
			ValueT ans = 0;
			if (x <= mid) ans += qry(p * 2, x, y);
			if (mid + 1 <= y) ans += qry(p * 2 + 1, x, y);
			return ans;
		}
		void upd(const IndexT &p, const IndexT &x, const IndexT &y, const ValueT &num) {
			IndexT l = t[p].l, r = t[p].r;
			if (x <= l && r <= y) {
				t[p].sum += num * t[p].len();
				t[p].lazy += num;
				return;
			}
			push_down(p);
			IndexT mid = (l + r) >> 1;
			if (x <= mid) upd(p * 2, x, y, num);
			if (mid + 1 <= y) upd(p * 2 + 1, x, y, num);
			push_up(p);
		}
	public: 
		segtree() {
			n = MAX_SIZE;
			a.resize(n + 1);
			t.resize(4 * n + 4);
			build(1, 1, n);
		}
		segtree(const IndexT &size) {
			n = size;
			a.resize(n + 1);
			t.resize(4 * n + 4);
			build(1, 1, n);
		}
		segtree(const IndexT &size, ValueT numbers[]) {
			n = size;
			a.resize(n + 1);
			t.resize(4 * n + 4);
			for (IndexT i = 1; i <= n; i++) a[i] = numbers[i];
			build(1, 1, n);
		}
		segtree(const IndexT &size, vector<ValueT> numbers) {
			n = size;
			a.resize(n + 1);
			t.resize(4 * n + 4);
			a = numbers;
			build(1, 1, n);
		}
		segtree(vector<ValueT> numbers, const bool &useVecSize = false) {
			if (useVecSize) n = numbers.size();
			else n = MAX_SIZE;
			a.resize(n + 1);
			t.resize(4 * n + 4);
			a = numbers;
			build(1, 1, n);
		}
		IndexT size() const { return n; }
		ValueT at(const IndexT &p) { return qry(1, p, p); }
		ValueT operator [] (const IndexT &p) { return qry(1, p, p); }
		ValueT query() { return qry(1, 1, n); }
		ValueT query(const IndexT &left, const IndexT &right) { return qry(1, left, right); }
		void update(const ValueT &addn) { upd(1, 1, n, addn); }
		void update(const IndexT &p, const ValueT &addn) { upd(1, p, p, addn); }
		void update(const IndexT &left, const IndexT &right, const ValueT &addn) { upd(1, left, right, addn); }
};


#endif // SEG_TREE_H
