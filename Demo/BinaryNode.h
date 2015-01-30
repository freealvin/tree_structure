#include <iostream>

 public class BinaryNode<K, V>
 {
	 public K key;

	 public HashSet<V> attach = new HashSet<V>();

	 public BinaryNode<K, V> left;

	 public BinaryNode<K, V> right;

	 public BinaryNode() { }

	 public BinaryNode(K key, V value, BinaryNode<K, V> left, BinaryNode<K, V> right)
	 {
		 this.key = key;
		 this.attach.Add(value);

		 this.left = left;
		 this.right = right;
	 }

	 public void add(K key, V value);
 }

 public void BinaryNode<K,V>::add(K key, V value)
 {
	BinaryNode<K,V> node = Add(key, value, node);
 }