datatype Tree<T> = Leaf | Node(Tree<T>, Tree<T>, T)
datatype List<T> = Nil | Cons(T, List<T>)

//this one should call append
//flattens the tree into a list
function flatten<T>(tree:Tree<T>):List<T>
{
  match(tree)
      case Node(Tree1, Tree2, node) => Cons(node, append(flatten(Tree1), flatten(Tree2)))
      case Leaf => Nil
}

//Pain
//this function is straight out of the in class examples
function append<T>(xs:List<T>, ys:List<T>):List<T>
//ensures (xs == Nil) ==> (append(xs, ys) == ys)
//ensures (ys == Nil) ==> (append(xs, ys) == xs)
{
	match(xs)
		case Nil => ys
		case Cons(z, zs) => Cons(z, append(zs, ys))
}

//traverse the tree and look for things
function treeContains<T>(tree:Tree<T>, element:T):bool
{
	//listContains(flatten(tree), element)
  match(tree)
      case Node(Tree1, Tree2, node) => (node == element || treeContains(Tree1, element) || treeContains(Tree2, element))
      case Leaf => false
}

function listContains<T>(x:List<T>, element:T):bool
{
	match(x)
      case Nil => false
      case Cons(value, xRest) => value == element || listContains(xRest, element) 
}


method sameElements<T>(tree:Tree<T>, element:T)
ensures treeContains(tree, element) <==> listContains(flatten(tree), element)
{
   match(tree)
   case Leaf => {
     calc{ treeContains(tree, element) 
       == listContains(flatten(tree), element);
      }
   }
   case Node(Tree1, Tree2, node) => {
     
   }
}