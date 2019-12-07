#define C class
#define S struct
#define T template
#define U using
#define TN typename
S z{C x{};}; //zero

T<C X>
S s{ //successor
	U x=X;
};

T<C X=z, C R=z>
S Y{ // list
	U x=X;
	U r=R;
};

T<C X>
S Y<X,z>{
	U x=X;
	U r=Y<z,z>;
};

T<C L=Y<>, C X=z, C R=Y<>>
S tape{
	//U l=L;
	U x=X;
	//U r=R;
	
	//shifting the pointer
	U rshift=tape<Y<x,L>, TN R::x, TN R::r>;
	U lshift=tape<TN L::r, TN L::x, Y<x,R>>;

	// inheritance too hard
	U plus=tape<L,s<X>,R>;
	U minus=tape<L,TN X::x,R>;
};

T<char X>
S h{S x{}; static constexpr char c=X;}; //holder
 
T<C CODE, C MEM=tape<>, C OUT_SO_FAR=z>
S Machine{
	U out=TN Machine<TN CODE::rshift, MEM, OUT_SO_FAR>::out;
};

T<C...x>
U machine=TN Machine<x...>::out;

T<C LC, C RC, C MEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<'.'>, RC>,
	MEM, OUT_SO_FAR>
	{
	U out=machine< TN tape< LC, h<'.'>, RC>::rshift, MEM, Y<TN MEM::x, OUT_SO_FAR> >;
};


T<C LC, C RC, C MEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<'+'>, RC>,
	MEM, OUT_SO_FAR>
	{
	U out=machine<
		TN tape< LC, h<'+'>, RC>::rshift,
		TN MEM::plus,
		OUT_SO_FAR
		>;
};


T<C LC, C RC, C MEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<'-'>, RC>,
	MEM, OUT_SO_FAR>
	{
	U out=machine<
		TN tape< LC, h<'-'>, RC>::rshift,
		TN MEM::minus,
		OUT_SO_FAR
		>;
};

T<C LC, C RC, C MEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<'<'>, RC>,
	MEM, OUT_SO_FAR>
	{
	U out=machine<
		TN tape< LC, h<'<'>, RC>::rshift,
		TN MEM::lshift,
		OUT_SO_FAR
		>;
};

T<C LC, C RC, C MEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<'>'>, RC>,
	MEM, OUT_SO_FAR>
	{
	U out=machine<
		TN tape< LC, h<'>'>, RC>::rshift,
		TN MEM::rshift,
		OUT_SO_FAR
		>;
};

T<C L>
S RJump{
	U x=TN RJump<TN L::rshift>::x;
};
T<C L>
U rjump=TN RJump<L>::x;
T<C L, C R>
S RJump<tape<L, h<'['>, R>>{
	U x= rjump<rjump<TN tape<L, h<'['>, R>::rshift>>;
};
T<C L, C R>
S RJump<tape<L, h<']'>, R>>{
	U x= TN tape<L, h<']'>, R>::rshift;
};


T<C L>
S LJump{
	U x=TN LJump<TN L::lshift>::x;
};
T<C L>
U ljump=TN LJump<L>::x;
T<C L, C R>
S LJump<tape<L, h<']'>, R>>{
	U x= ljump<TN ljump<TN tape<L, h<']'>, R>::lshift>::lshift::lshift>;
};

T<C L, C R>
S LJump<tape<L, h<'['>, R>>{
	U x= TN tape<L, h<'['>, R>::rshift;
};


T<C L, C MEM, C OUT_SO_FAR>
S Machine<tape<L,z,Y<>>, MEM, OUT_SO_FAR>{
	U out=OUT_SO_FAR;
};


T<C LC, C RC, C LMEM, C RMEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<'['>, RC>,
	tape< LMEM, z, RMEM>,
	OUT_SO_FAR>
	{
	U out=machine<
		rjump<TN tape< LC, h<'['>, RC>::rshift>,
		tape< LMEM, z, RMEM>,
		OUT_SO_FAR
		>;
};

T<C LC, C RC, C LMEM, C RMEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<']'>, RC>,
	tape<LMEM, z, RMEM>,
	OUT_SO_FAR>
	{
	U out=machine<
		TN tape< LC, h<']'>, RC>::rshift,
		tape<LMEM, z, RMEM>,
		OUT_SO_FAR
		>;
};

T<C LC, C RC, C MEM, C OUT_SO_FAR>
S Machine<
	tape< LC, h<']'>, RC>,
	MEM,
	OUT_SO_FAR>
	{
	U out=machine<
		ljump<TN tape< LC, h<']'>, RC>::lshift>,
		MEM,
		OUT_SO_FAR
		>;
};

T<char...X>
S Dots2List;
T<char...X>
U dots2Y=TN Dots2List<X...>::x;

T<char H, char...A>
S Dots2List<H,A...>{
	U x=Y<h<H>, dots2Y<A...>>;
};

T<>
S Dots2List<>{
	U x=Y<>;
};

T<C x>
constexpr char tint2ch= tint2ch<TN x::x>+1;
T<>
constexpr char tint2ch<z> = 0;

T<C a>
S Y2chars{
	U x=Y<TN Y2chars<TN a::r>::x, h<tint2ch<TN a::x>> >;
};
T<>
S Y2chars<Y<>>{
	U x=Y<>;
};
T<C a>
U y2chars=TN Y2chars<a>::x;

T<C x>
U id=x; // makes the compiler display the result only

int a=
	id<y2chars<machine<
		// "Hello World!" code from wikipedia
		tape<Y<>, h<'p'>, dots2Y<'+','+','+','+','+','+','+','+','[','>','+','+','+','+','[','>','+','+','>','+','+','+','>','+','+','+','>','+','<','<','<','<','-',']','>','+','>','+','>','-','>','>','+','[','<',']','<','-',']','>','>','.','>','-','-','-','.','+','+','+','+','+','+','+','.','.','+','+','+','.','>','>','.','<','-','.','<','.','+','+','+','.','-','-','-','-','-','-','.','-','-','-','-','-','-','-','-','.','>','>','+','.','>','+','+','.'> >,
		tape<>,
		Y<>
		>>>();

int main(){
	return 0;
}
