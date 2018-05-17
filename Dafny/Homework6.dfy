datatype Tree<T> = Leaf(T) | Node(Tree<T>, Tree<T>, T)
datatype List<T> = Nil | Cons(T, List<T>)

//this one should call append
//flattens the tree into a list
function flatten<T>(tree:Tree<T>):List<T>
{
  match(tree)
      case Node(Tree1, Tree2, node) => Cons(node, append(flatten(Tree1), flatten(Tree2)))
      case Leaf(T) => Cons(T, Nil)
}

//Pain
function append<T>(xs:List<T>, ys:List<T>):List<T>
{
	match(xs)
		case Nil => ys
		case Cons(xsFirst, xsRest) =>  Cons(xsFirst, append(xsRest, ys))
}

function treeContains<T>(tree:Tree<T>, element:T):bool
{
	listContains(flatten(tree), element)
}

function listContains<T>(x:List<T>, element:T):bool
{
	match(x)
      case Nil => false
      case Cons(T, xRest) => if T == element 
                             then true 
                             else listContains(xRest, element) 
}


lemma sameElements<T>(tree:Tree<T>, element:T)
ensures treeContains(tree, element) <==> listContains(flatten(tree), element)
{
	
}