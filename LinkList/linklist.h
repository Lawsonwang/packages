// Code By WLS
#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <bits/stdc++.h>
template <typename ValueT = int>
class linklist {
	private:
		struct node {
			ValueT val;
			node *nxt, *pre;
		} *head, *p, *tail;
		void init(int n, ValueT vals[]) {
			head = new node;
			head->pre = head->nxt = NULL;
			tail = head;
			for (int i = 1; i <= n; i++) {
				p = new node;
				p->pre = tail;
				p->pre->nxt = p;
				p->nxt = NULL;
				p->val = vals[i];
				tail = p;
			}
		}
		void init(int n) {
			head = new node;
			head->pre = head->nxt = NULL;
			tail = head;
			for (int i = 1; i <= n; i++) {
				p = new node;
				p->pre = tail;
				p->pre->nxt = p;
				p->nxt = NULL;
				p->val = ValueT{};
				tail = p;
			}
		}
		node* del(node *p) {
			p->pre->nxt = p->nxt;
			if (p->nxt != NULL) p->nxt->pre = p->pre;
			node *temp = p;
			p = p->nxt;
			free(temp);
			return p;
		}
		void push_b(ValueT val) {
			p = new node;
			p->val = val;
			p->nxt = NULL;
			p->pre = tail;
			tail->nxt = p;
			tail = p;
		}
		void push_f(ValueT val) {
			p = new node;
			p->val = val;
			p->nxt = head->nxt;
			p->pre = head;
			head->nxt->pre = p;
			head->nxt = p->nxt;
		}
		ValueT pop_b() {
			ValueT vald = tail->val;
			tail = tail->pre;
			node *temp = tail->nxt;
			del(temp);
			return vald;
		}
		ValueT pop_f() {
			ValueT vald = head->nxt->val;
			node *temp = head->nxt;
			del(temp);
			return vald;
		}
		ValueT get_b() {
			ValueT vald = tail->val;
			return vald;
		}
		ValueT get_f() {
			ValueT vald = head->nxt->val;
			return vald;
		}
		void del_pos(int pos) {
			p = head;
			while (pos--) p = p->nxt;
			del(p);
		}
	public:
		linklist() {
			init(0);
		}
		void push_back(ValueT x) { push_b(x); }
		void push_front(ValueT x) { push_f(x); }
		void pop_back() { pop_b(); }
		void pop_front() { pop_f(); }
		ValueT back() { return get_b(); }
		ValueT front() { return get_f(); }
		void erase(int pos) { del_pos(pos); }
		
};

#endif // LINK_LIST_H
