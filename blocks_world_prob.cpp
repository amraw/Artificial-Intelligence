/*
 *  File Name : blocks_world_prob.cpp
 *  Created on: 27-Sep-2017
 *  Author: Amit Rawat
 *  UIN: 326005672
 */
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
#include<climits>
#include<utility>
#include<map>
#include<string>

using namespace std;

// Class describing the Node structure
class Node{
	char **stackState; 	// Store the configuration of blocks
	Node * parent;		// Store the reference to the parent
	long int depth;		// Store the depth
	int fvalue;			// Store the function value which is sum of cost and heuristic
	int stackSize;		// Store stack size
	int numbBlk;		// Store number of block
	public:
	// Constructor for assigning node object variables
	Node(char **stackState, Node * parent, long int depth, int stackSize, int numbBlk)
	{
		this->stackState = stackState;
		this->parent = parent;
		this->depth = depth;
		this->stackSize = stackSize;
		this->numbBlk = numbBlk;
	}
	// Getter and Setter function for getting and setting the Node object variables
	long int getDepth(void)
	{
		return depth;
	}

	Node * getParent(void)
	{
		return this->parent;
	}

	char ** getStackState(void)
	{
		return stackState;
	}
	
	void setfvalue(int fvalue)
	{
		this->fvalue = fvalue;
	}
	int getfvalue(void)
	{
		return this->fvalue;
	}

	int getStackSize(void)
	{
		return this->stackSize;
	}
	int getNumbBlk(void)
	{
		return this->numbBlk;
	}
};

// Class for Generating random states
class generateRandomState{
	char **stack;
	int stackSize;
	int numbBlk;
	public:
	// Constructor for assigning variables of random state generator object
	generateRandomState(int stackSize, int numbBlk)
	{
		this->stackSize = stackSize;
		this->numbBlk = numbBlk;
		stack = new char * [stackSize];
		for(int itr=0; itr<stackSize; itr++)
		{
			stack[itr] = new char[numbBlk];
			memset(stack[itr],'0',numbBlk);
		}
	}
	/*
	 * Function Name: generateRandomStateFunc
	 * Input: void
	 * Return: reference to the random state generated
	 */
	char ** generateRandomStateFunc(void)
	{
		srand(time(0));
		int numbRandOper = 40;
		char block = 'A';
		int firstBlk = 0;
		int operation = -1;
		// Goal state is generated here
		for(int itr=0; itr<numbBlk; itr++)
		{
				stack[0][itr] = block;
				block++;
		}
		// Performing randomly 1 of 18 random operation in 100 iteration on goal state to generate a random state
		for(int itr=0; itr<100; itr++)
		{
			operation = rand()%18; // randomly select the value of operation to be performed
			switch(operation)
			{
				case 0:
					pickAndMoveBlock();
					break;
				case 1:
					swapBlock(firstBlk);
					break;
				case 2:
					swapBlock2(firstBlk);
					break;
				case 3:
					move2Blocks();
					break;
				case 4:
					move2Blocks2();
					break;
				case 5:
					moveAllBlock();
					break;
				case 6:
					moveAllBlock2();
					break;
				case 7:
					moveAllBlock3();
					break;
				case 8:
					pickAndMoveBlock();
					swapBlock(firstBlk);
					break;
				case 9:
					swapBlock(firstBlk);
					moveAllBlock2();
					break;
				case 10:
					swapBlock(firstBlk);
					moveAllBlock3();
					break;
				case 11:
					swapBlock(firstBlk);
					moveAllBlock();
					break;
				case 12:
					swapBlock(firstBlk);
					move2Blocks();
					break;
				case 13:
					swapBlock(firstBlk);
					move2Blocks2();
					break;
				case 14:
					swapBlock2(firstBlk);
					swapBlock(firstBlk);
					break;
				case 15:
					move2Blocks();
					move2Blocks2();
					break;
				case 16:
					move2Blocks();
					move2Blocks2();
					swapBlock(firstBlk);
					break;
				case 17:
					move2Blocks();
					move2Blocks2();
					swapBlock2(firstBlk);
					break;
				case 18:
					move2Blocks();
					moveAllBlock3();
					swapBlock2(firstBlk);
					break;
				case 19:
					move2Blocks();
					move2Blocks2();
					moveAllBlock3();
					break;
				case 20:
					moveAllBlock3();
					move2Blocks2();
					swapBlock2(firstBlk);
					break;
				default:
						break;
			}

		}
		return stack;
	}
	// It randomly move one block from one stack to another
	void pickAndMoveBlock(void)
	{
		srand(time(0));
		int stackSelect;
		char blockSelect;
		while (1)
		{
			int randNumb = rand();
			stackSelect = randNumb % (stackSize);
			int itr = 0;
			while(stack[stackSelect][itr] != '0' && itr<numbBlk)
			{
				itr++;
			}
			itr--;
			if(itr>=0 && stack[stackSelect][itr]!='0')
			{
				blockSelect = stack[stackSelect][itr];
				stack[stackSelect][itr] = '0';
				break;
			}

		}
		int stackMove;
		while ( 1 )
		{
			stackMove = rand() % (stackSize);
			if(stackMove == stackSelect)
				continue;
			if(stack[stackMove][0] == '0')
			{
				stack[stackMove][0] = blockSelect;
				break;
			}
			else
			{
				int itr;
				for(itr = 0; itr<numbBlk && stack[stackMove][itr] !='0'; itr++);
				if(itr<numbBlk)
				{
					stack[stackMove][itr] = blockSelect;
					break;
				}
			}
		}
	}
	// It swap two blocks
	void swapBlock(int &firstBlk)
	{
		while(stack[firstBlk][0] == 0)
		{
			firstBlk = (firstBlk+1)%stackSize;

		}

		int secondBlk = (firstBlk+1)%stackSize;
		int itr1;
		for(itr1=0; itr1<numbBlk && stack[firstBlk][itr1]!='0'; itr1++);
		int itr2;
		for(itr2=0; itr2<numbBlk && stack[secondBlk][itr2]!='0'; itr2++);
		if(itr1>0)
			itr1--;
		if(itr2>0)
			itr2--;
		char temp = stack[firstBlk][itr1];
		stack[firstBlk][itr1] = stack[secondBlk][itr2];
		stack[secondBlk][itr2] = temp;
		firstBlk = (firstBlk+1)%stackSize;
	}
	//It swap block differently
	void swapBlock2(int &firstBlk)
	{
		while(stack[firstBlk][0] == 0)
		{
			firstBlk = (firstBlk+1)%stackSize;

		}

		int secondBlk = (firstBlk+2)%stackSize;
		int itr1;
		for(itr1=0; itr1<numbBlk && stack[firstBlk][itr1]!='0'; itr1++);
		int itr2;
		for(itr2=0; itr2<numbBlk && stack[secondBlk][itr2]!='0'; itr2++);
		if(itr1>0)
			itr1--;
		if(itr2>0)
			itr2--;
		char temp = stack[firstBlk][itr1];
		stack[firstBlk][itr1] = stack[secondBlk][itr2];
		stack[secondBlk][itr2] = temp;
		firstBlk = (firstBlk+1)%stackSize;
	}
	// It move two blocks randomly
	void move2Blocks(void)
	{
		srand(time(0));
		int stackSelect;
		char blockSelect1;
		char blockSelect2;
		while (1)
		{
			int randNumb = rand();
			stackSelect = randNumb % (stackSize);
			int itr = 0;
			while(stack[stackSelect][itr] != '0' && itr<numbBlk)
			{
				itr++;
			}
			itr--;
			if(itr>=1 && stack[stackSelect][itr]!='0')
			{
				blockSelect1 = stack[stackSelect][itr];
				stack[stackSelect][itr] = '0';
				itr--;
				blockSelect2 = stack[stackSelect][itr];
				stack[stackSelect][itr] = '0';
				break;
			}

		}
		int stackMove;
		while ( 1 )
		{
			stackMove = rand() % (stackSize);
			if(stackMove == stackSelect)
				continue;
			if(stack[stackMove][0] == '0')
			{
				stack[stackMove][0] = blockSelect1;
				stack[stackMove][1] = blockSelect2;
				break;
			}
			else
			{
				int itr;
				for(itr = 0; itr<numbBlk && stack[stackMove][itr] !='0'; itr++);
				if(itr<numbBlk-1)
				{
					stack[stackMove][itr] = blockSelect1;
					itr++;
					stack[stackMove][itr] = blockSelect2;
					break;
				}
			}
		}
	}
	// It distribute two block from one stack to two other different stack
	void move2Blocks2(void)
	{
		srand(time(0));
		int stackSelect;
		char blockSelect1;
		char blockSelect2;
		while (1)
		{
			int randNumb = rand();
			stackSelect = randNumb % (stackSize);
			int itr = 0;
			while(stack[stackSelect][itr] != '0' && itr<numbBlk)
			{
				itr++;
			}
			itr--;
			if(itr>=1 && stack[stackSelect][itr]!='0')
			{
				blockSelect1 = stack[stackSelect][itr];
				stack[stackSelect][itr] = '0';
				itr--;
				blockSelect2 = stack[stackSelect][itr];
				stack[stackSelect][itr] = '0';
				break;
			}

		}
		int stackMove;
		while ( 1 )
		{
			stackMove = rand() % (stackSize);
			if(stackMove == stackSelect)
				continue;
			if(stack[stackMove][0] == '0')
			{
				stack[stackMove][0] = blockSelect1;
				break;
			}
			else
			{
				int itr;
				for(itr = 0; itr<numbBlk && stack[stackMove][itr] !='0'; itr++);
				if(itr<numbBlk)
				{
					stack[stackMove][itr] = blockSelect1;
					break;
				}
			}
		}
		int stackMove2 = (stackMove+1)%stackSize;
		while(stackMove2 == stackSelect || stackMove2==stackMove)
		{
			stackMove2 = (stackMove2+1)%stackSize;
		}

		if(stack[stackMove2][0] == '0')
			{
				stack[stackMove2][0] = blockSelect2;
			}
			else
			{
				int itr;
				for(itr = 0; itr<numbBlk && stack[stackMove2][itr] !='0'; itr++);
				if(itr<numbBlk)
				{
					stack[stackMove2][itr] = blockSelect2;
				}
			}
	}
	// It move all block from one stack to the other stack in reverse order
	void moveAllBlock(void)
	{
		srand(time(0));
		int stackSelect;
		int itr1 = 0;
		while (1)
		{
			int randNumb = rand();
			stackSelect = randNumb % (stackSize);
			while(stack[stackSelect][itr1] != '0' && itr1<numbBlk)
			{
				itr1++;
			}
			itr1--;
			if(itr1>=1 && stack[stackSelect][itr1]!='0')
			{
				break;
			}

		}
		int stackMove;
		int itr2 = 0;
		while ( 1 )
		{
			stackMove = rand() % (stackSize);
			if(stackMove == stackSelect)
				continue;
			if(stack[stackMove][itr2] == '0')
			{
				while(itr1>=0)
				{
					stack[stackMove][itr2] = stack[stackSelect][itr1];
					stack[stackSelect][itr1] = '0';
					itr1--;
					itr2++;
				}
				break;
			}
			else
			{
				for(itr2 = 0; itr2<numbBlk && stack[stackMove][itr2] !='0'; itr2++);
				if(itr2<numbBlk)
				{
					while(itr1>=0)
					{
						stack[stackMove][itr2] = stack[stackSelect][itr1];
						stack[stackSelect][itr1] = '0';
						itr1--;
						itr2++;
					}
					break;
				}
			}
		}
	}
	// It move all block from a random row to the other random row in reverse order
	void moveAllBlock2(void)
	{
		srand(time(0));
		int stackSelect;
		int itr1 = 0;
		while (1)
		{
			int randNumb = rand();
			stackSelect = randNumb % (stackSize);
			while(stack[stackSelect][itr1] != '0' && itr1<numbBlk)
			{
				itr1++;
			}
			itr1--;
			if(itr1>=0 && stack[stackSelect][itr1]!='0')
			{
				break;
			}

		}
		int stackMove;
		int itr2 = 0;
		while ( 1 )
		{
			stackMove = rand() % (stackSize);
			if(stackMove == stackSelect)
				continue;
			if(stack[stackMove][itr2] == '0')
			{
				while(itr1>=0)
				{
					stack[stackMove][itr2] = stack[stackSelect][itr1];
					stack[stackSelect][itr1] = '0';
					itr1--;
					itr2++;
				}
				break;
			}
			else
			{
				for(itr2 = 0; itr2<numbBlk && stack[stackMove][itr2] !='0'; itr2++);
				if(itr2<numbBlk)
				{
					while(itr1>=0)
					{
						stack[stackMove][itr2] = stack[stackSelect][itr1];
						stack[stackSelect][itr1] = '0';
						itr1--;
						itr2++;
					}
					break;
				}
			}
		}
	}
	// It move all block from one row to two different row in alternate order
	void moveAllBlock3(void)
	{
		srand(time(0));
		int stackSelect;
		int itr1 = 0;
		while (1)
		{
			int randNumb = rand();
			stackSelect = randNumb % (stackSize);
			while(stack[stackSelect][itr1] != '0' && itr1<numbBlk)
			{
				itr1++;
			}
			itr1--;
			if(itr1>=1 && stack[stackSelect][itr1]!='0')
			{
				break;
			}

		}
		int itr2 = 0;
		int stackMove1 = (stackSelect+1)%stackSize;
		while(stackMove1==stackSelect)
		{
			stackMove1 = (stackMove1+1)%stackSize;
		}
		int itr3 = 0;
		int stackMove2 = (stackSelect+1)%stackSize;
		while(stackMove1==stackSelect || stackMove2==stackMove1)
		{
			stackMove2 = (stackMove2+1)%stackSize;
		}
		for(itr2 = 0; itr2<numbBlk && stack[stackMove1][itr2] !='0'; itr2++);
		for(itr3 = 0; itr2<numbBlk && stack[stackMove2][itr3] !='0'; itr3++);
		bool flip = true;
		while(itr1>=0)
		{
			if(flip) // Boolean for distributing blocks in alternat order
			{
				stack[stackMove2][itr3] = stack[stackSelect][itr1];
				itr3++;
			}
			else
			{
				stack[stackMove1][itr2] = stack[stackSelect][itr1];
				itr2++;
			}
			stack[stackSelect][itr1] = '0';
			itr1--;
			flip = !flip;
		}
	}
	// Function for printing the stack state
	void printState(char **stack)
	{
		for(int itr = 0; itr < stackSize; itr++)
		{
			cout<<itr+1<<" |";
			for(int itr2=0; itr2<numbBlk && stack[itr][itr2] !='0'; itr2++)
				cout<<" "<<stack[itr][itr2];
			cout<<endl;
		}
	}

};

struct CompareNodesFvalue : public std::binary_function<Node*, Node*, bool>
	{
		// Function for comparing the function value of the two nodes used in priority queue
		 /*
 		  * Function Name: binary_function
 		  * Input: two node pointers
 		  * Return: boolean value
 		  */
  		bool operator()(Node* lhs, Node* rhs) const
  		{
     		return lhs->getfvalue() > rhs->getfvalue(); // return true if left hand side function value is greater than the right value
  		}
	};
	

struct CompareNodes : public std::binary_function<string&, string&, bool>
	{
		// Function for checking if keys of two nodes are equal or not
		/*
 		 * Function Name: binary_function
 		 * Input: two string references
 		 * Return: boolean value
 		 */	
  		bool operator()( const string& lhs,  const string& rhs) const
  		{
     		return lhs.compare(rhs) != 0; // check if keys of two nodes are equal or not
  		}
	};

// Class for implementing the A* search
class AstarSearch{
	long goalTestCount;		// Variable for storing the total goal test count
	long maxQueueSize;		// Variable for storing the maximum queue size
	int depth;			    // Variable for storing depth
	int numbBlk;			// Store the number of block
	int stackSize;			// Store stack size
	char * blockOrdered;	// Store the blocks in correct order e.g A B C D e.tc . Used for comparision in various function. 
	int halfDifference;		// Store mid value of the difference of the integer value of the first and last block
	public:
	// Constructor for assigning the values to the variable of AstarSearch object
	AstarSearch(int stackSize , int numbBlk)
	{
		this->numbBlk = numbBlk;
		this->stackSize = stackSize;
		this->goalTestCount = 0;
		this->maxQueueSize = 0;
		blockOrdered = new char[numbBlk];
		blockOrdered[0] = 'A';
		for(int itr1 = 1; itr1<numbBlk; itr1++)
		{
			blockOrdered[itr1] = blockOrdered[itr1-1]+1;
		}
		halfDifference = (blockOrdered[numbBlk-1]-blockOrdered[0])/2;
	}
	
	// Function in which A* search is implemented
		/*
 		 * Function Name: AstarSearchImp
 		 * Input: Reference to start state
 		 * Return: void
 		 */	
	void AstarSearchImp(Node * startNode)
	{
		Node * currentNode;
		priority_queue<Node *, vector<Node*>, CompareNodesFvalue> frontier; // priority queue for storing states in ascending order of there function value
		map<string, Node *, CompareNodes> visitedNodes; // Map for storing the visited nodes
		udpateFunctValueofNode(startNode);	// Calculate the cost and huersitic value of start node and set the functional value
		long itrerator=0; // keep track of iterations
		if(startNode!=NULL)
		{
			frontier.push(startNode); // push start node to queue
			while(!frontier.empty())
			{
				itrerator++;
				if(itrerator> 17000) // break if iteration exceeds the limit i.e 17000
				{
					// Print message and stack state
					cout<<"Failure! "<<", iteration="<<itrerator<<", depth="<<currentNode->getDepth()<<", total_goal_test="<<goalTestCount<<", max_queue_size="<<maxQueueSize<<endl;
					cout<<"Start State"<<endl;
					printState(startNode->getStackState());
					break;
				}
				if(maxQueueSize < frontier.size())
				{
					maxQueueSize = frontier.size(); // keep track of the maximum queue size
				}
				currentNode = frontier.top(); // Get top node from priority queue
				if(!isVisited(currentNode,visitedNodes)) // Check whether it is visited or not
				{
 					visitedNodes.insert(pair<string, Node *>(generateKey(currentNode), currentNode)); // insert current node in visited node
					if(goalTest(currentNode->getStackState())) // check whether current state is goal state
					{
						cout<<"success! "<<", iteration="<<itrerator<<", depth="<<currentNode->getDepth()<<", total_goal_test="<<goalTestCount<<", max_queue_size="<<maxQueueSize<<endl;
						cout<<"Solution path:"<<endl;
						printTraceBack(currentNode); // when solution found it print the path to the solution
						freeAllNodes(frontier, visitedNodes); // free the memory allocated
						break;
					}
					else
					{
						frontier.pop(); // pop the top element form the queue
						vector<Node *> successorNodes; // variable for storing successor nodes
						successorNodes = successor(currentNode); // generate all the successor nodes
						udpateFunctValue(successorNodes); // update there functional value
						vector<Node *>::iterator itr; 
						for(itr = successorNodes.begin(); itr!=successorNodes.end(); itr++)
						{
							if(ischildVisited((*itr),visitedNodes)) // check whether node is visited
							{
								freeNode((*itr)); // free it if visited
							}
							else
							{
								frontier.push((*itr));// if not visited then add it to the priority queue
							}
						}

					}
				}
				else
				{
					frontier.pop();// if already visited then pop it out and no need to find it's children nodes
				}
				
			}
		}
		else
		{
			cout<<"NULL Start State is provided"<<endl;
		}
	}
	// Checks whether a node is already visited or not
	bool isVisited(Node * search, map<string, Node *, CompareNodes> visitedNodes)
	{
		map<string, Node *, CompareNodes>:: iterator itr;
		itr = visitedNodes.find(generateKey(search));
		if(itr != visitedNodes.end())
		{
			if(search->getfvalue() < (itr->second)->getfvalue())
			{
				visitedNodes.erase(itr);
				// relplace the existing node in visited node list with a similar node having lower function value
				visitedNodes.insert(pair<string, Node *>(generateKey(search), search)); 
				return false;
			}
			return true;
		}
		return false;
	}
	// Checks whether a successor node is already visited or not
	bool ischildVisited(Node * search, map<string, Node *, CompareNodes> visitedNodes)
	{
		map<string, Node *, CompareNodes>:: iterator itr;
		itr = visitedNodes.find(generateKey(search));
		if(itr != visitedNodes.end())
		{
			if(search->getfvalue() < (itr->second)->getfvalue())
			{
				return false; // return false if generated
			}
			return true;
		}
		return false;
	}

	// Generates the unique key for storing a visited node in the map
	string generateKey(Node * node)
	{
		string key;

		char ** stackState = node->getStackState();
		for(int itr = 0; itr < stackSize; itr++)
		{
			for(int itr2 = 0; itr2 < numbBlk; itr2++)
			{
				if(stackState[itr][itr2] != '0')
				{
					key.push_back((char)(itr+1));
					key.push_back((char)(itr2+1));
					key.push_back(stackState[itr][itr2]);
				}
				else
				{
					key.push_back('_');
				}
			}
		}
		return key;
	}
	
		// Function for calculating the heuristic value
		/*
 		 * Function Name: calculateHeuristicValue
 		 * Input: Reference to stack state
 		 * Return: heuristic value calculated
 		 */	
	long calculateHeuristicValue(char ** stackState)
	{
		long hNvalue = 0; // variable storing heuristic value
		// Various subroutines called for calculating the heuristic value
		hNvalue = heuristic1(stackState, hNvalue);
		hNvalue = heuristic2(stackState, hNvalue);
		hNvalue = heuristic3(stackState, hNvalue);
		hNvalue = heuristic4(stackState, hNvalue);
		hNvalue = heuristic5(stackState, hNvalue);
		return hNvalue;
	}

	// Function which count the number of blocks to be shifted in order to get each block which is out of position
	long heuristic1(char ** stackState, long hNvalue)
	{
		int itr = 0;
		for(itr=0; itr<numbBlk && stackState[0][itr]==blockOrdered[itr]; itr++); // find the starting block which is not in correct order
		for(int  itr1 = itr; itr1<numbBlk;itr1++) // iterate over all the blocks out of order
		{
			for(int itr2=1; itr2<stackSize; itr2++) // search blocks starting from second stack till stack size
			{
				int itr3;
				for(itr3=0; itr3<numbBlk && stackState[itr2][itr3]!=blockOrdered[itr1]; itr3++); // search the block in all the row starting from row 1 till stackSize
				if(itr3<numbBlk && stackState[itr2][itr3]==blockOrdered[itr1])
				{
					itr3++;
					while(itr3<numbBlk && stackState[itr2][itr3]!='0')
					{
						if(stackState[itr2][itr3]>blockOrdered[itr1])
						{
							hNvalue++;	// Increment the heuristic value for each block above the target block which is at higher position in goal state
						}
						itr3++;
					}
					break;
				}
			}
		}
		return hNvalue;
	}
	
	/*It counts the number of blocks which are out of position in the first row to be 
	shifted to another row*/
	long heuristic2(char ** stackState, long hNvalue)
	{
		int itr;
		for(itr = 0; itr<numbBlk && stackState[0][itr] == blockOrdered[itr]; itr++);
		for(int itr2 = itr; itr2<numbBlk && stackState[0][itr2] !='0'; itr2++)
		{
			hNvalue++;
		}
		return hNvalue;
	}
    //This heuristic supports the movement of the block over a block which is placed above it in goal state
	long heuristic3(char ** stackState, long hNvalue)
	{
		int maxDifference = INT_MIN;
		int itr2;
		int itr3;


		for(int itr1=0; itr1<stackSize; itr1++)
		{
			maxDifference = INT_MIN;
			if(itr1==0)
			{
				for(itr2=0; itr2<numbBlk && stackState[0][itr2]!=blockOrdered[itr2]; itr2++);
				for(itr3=itr2; itr3<numbBlk && stackState[0][itr3]!='0'; itr3++);
				itr3--;
				int itr4 = itr3-1;
				/* if the difference b/w the integer values of top block and lower block i.e (top block-lower block) in a row is greater than the
				 mid integer value of all the blocks than it increase heuristic value by 2 otherwise it increase it by 1*/
				while(itr4>=itr2)
				{
					// caculate difference in integer value b/w the top block and all the lower blocks one by one
					int difference = stackState[itr1][itr3] - stackState[itr1][itr4]; 
					itr4--;
					if(difference >0 && difference > maxDifference)
					{
						maxDifference = difference; // keep track of max difference
					}
				}
				/* if block B is placed over A then difference is positive otherwise if A is placed over B then difference is negative
				therefore it increase heuristic value for cases where block in higher position is placed over a block in lower position which is not at 
				its correct position compare to goal state*/
				if(maxDifference > halfDifference) 
				{
					hNvalue += 2;
				}
				else
				{
					hNvalue ++;
				}
			}
			else
			{
				for(itr2=0; itr2<numbBlk && stackState[itr1][itr2]!='0'; itr2++);
				itr2--;
				itr3 = itr2-1;
				while(itr3>=0)
				{
					int difference = stackState[itr1][itr2] - stackState[itr1][itr3];
					itr3--;
					if(difference >0 && difference > maxDifference)
					{
						maxDifference = difference;
					}
				}
				if(maxDifference > halfDifference)
				{
					hNvalue += 2;
				}
				else
				{
					hNvalue ++;
				}
			}
		}
		return hNvalue;
	}
	//It reduces the value of heuristic by the number of the blocks which are aligned in the correct order in the first row
	long heuristic4(char ** stackState, long hNvalue)
	{
		for(int itr=0; itr<numbBlk; itr++)
		{
			if(stackState[0][itr]==blockOrdered[itr])
			{
				hNvalue--;// For each correct order of block heursitic value is decreased by one
			}
			else
			{
				break;
			}
				
		}
		return hNvalue;
	}
	//This subroutine calculates how far the current state is from the goal state
	long heuristic5(char ** stackState, long hNvalue)
	{
		char block = 'A';
		int itr;
		for(itr=0; itr<numbBlk; itr++)
		{
			if(stackState[0][itr] != block) // break if it find any block is not in correct order or is not present in correct position
			{
				break;
			}
			block++;
		}
		while(itr < numbBlk)
		{
			hNvalue++; // Increase the heursitic value times the number block which are not in correct position.
			itr++;
		}
		return hNvalue;
	}
	// Calcuate and set the total cost for each successor node
	void udpateFunctValue(vector<Node *> successorNode)
	{
		vector<Node *>::iterator itr;
		long gN = 0;
		long hN = 0;
		for(itr=successorNode.begin(); itr!=successorNode.end(); itr++)
		{
			gN = (*itr)->getDepth(); // Equivalent to the number of blocks moved
			hN = calculateHeuristicValue((*itr)->getStackState()); // Calucalte heuristic value for the given node state
			(*itr)->setfvalue(gN+hN); // update the function value
		}
	}
	// Calcuate and set the total cost which is sum of number of blocks moved and heuristic value
	void udpateFunctValueofNode(Node * node)
	{
		long gN = node->getDepth();
		long hN = calculateHeuristicValue(node->getStackState());
		node->setfvalue(gN+hN);
	}
	// Generate the successor nodes of a parent node passed to the function
	vector<Node *> successor(Node * parent)
	{
		vector <Node *> succssorNodes;
		char ** parentStackState = parent->getStackState();
		for(int itr1=0; itr1 < stackSize; itr1++)
		{
			char topBlockSelect;
			int blk;
			if(parentStackState[itr1][0] == '0')
			{
				continue;
			}
			else
			{
				for(blk=0; blk < numbBlk && parentStackState[itr1][blk] !='0'; blk++); 
				blk--;
				topBlockSelect = parentStackState[itr1][blk]; // select the top block from each row
				for(int itr2=0; itr2 < stackSize; itr2++) 
				{
					if(itr1==itr2)
					{
						continue;
					}
					else
					{
						char ** newStack = makeCopy(parentStackState,itr1,blk);
						int newStackBlk;
						if(newStack[itr2][0] == '0')
						{
							newStack[itr2][0] = topBlockSelect;
						}
						else
						{
							for(newStackBlk=0; newStackBlk<numbBlk && newStack[itr2][newStackBlk]!='0'; newStackBlk++);
							if(newStackBlk<numbBlk && newStack[itr2][newStackBlk]=='0')
							{
								newStack[itr2][newStackBlk] = topBlockSelect;// move it to the top of all remaining row one by one
							}
						}
						Node * newNode = new Node(newStack, parent, parent->getDepth()+1,stackSize, numbBlk);// generate a new child node
						succssorNodes.push_back(newNode);// push it in the succssorNodes vector
					}
				}
			}
		}
		return succssorNodes;
	}
	// Just for creating the copy of parent which is used to generate children states
	char ** makeCopy(char ** parentStateStack, int currentStack, int blkLoc)
	{
		char ** newStack;
		newStack = new char * [stackSize];
		for(int itr1=0; itr1<stackSize; itr1++)
		{
			newStack[itr1] = new char[numbBlk];
			memset(newStack[itr1],'0',numbBlk);
			for(int itr2=0; itr2<numbBlk; itr2++)
			{
				if(itr1== currentStack && itr2==blkLoc)
				{
					newStack[itr1][itr2] = '0';
				}
				else
				{
					newStack[itr1][itr2] = parentStateStack[itr1][itr2];
				}
			}
		}
		return newStack;
	}
	// Check whether current node is goal state or not
	bool goalTest(char ** stackState)
	{
		bool result = true;
		char block = 'A';
		for(int itr2 = 0; itr2 < numbBlk; itr2++)
		{
			if(stackState[0][itr2] != block)
			{
				result = false;
				break;
			}
			block++;
		}
		goalTestCount++; // keep track of how many times goal test function is called
		return result;
	}
	// Return the number of time the goal test call
	long int getGoalTestCount(void)
	{
		return goalTestCount;
	}
	// Function for printing the path to the goal state from starting state
	void printTraceBack(Node * stackState)
	{
		if(stackState->getParent()!=NULL)
		{
			printTraceBack(stackState->getParent());
		}

		printState(stackState->getStackState());
		cout<<endl;
	}
	// Function for printing the state of a node
	void printState(char **stack)
	{
		for(int itr = 0; itr < stackSize; itr++)
		{
			cout<<itr+1<<" |";
			for(int itr2=0; itr2<numbBlk && stack[itr][itr2] !='0'; itr2++)
				cout<<" "<<stack[itr][itr2];
			cout<<endl;
		}
	}
	// free the memory of variables in node
	void freeNode(Node * node)
	{
		int stackSize = node->getStackSize();
		char ** StackState = node->getStackState();
		if(StackState!=NULL)
		{
			for(int itr=0; itr<stackSize; itr++)
			{
				delete []StackState[itr];
			}
			delete[]StackState;
		}

	}

	// Free the memory allocated in nodes
	void freeAllNodes(priority_queue<Node *, vector<Node*>, CompareNodesFvalue> frontier, map<string, Node *, CompareNodes> visitedNodes)
	{
		Node * currentNode;
		while(!frontier.empty())
		{
			currentNode = frontier.top();
			frontier.pop();
			freeNode(currentNode);
			free(currentNode);
		}
	}

};

int main(int argc, char **argv)
{
	int stackSize = atoi(argv[1]);
	int numbBlk = atoi(argv[2]);
	generateRandomState startState(stackSize,numbBlk);
	char **stackState = startState.generateRandomStateFunc();
	startState.printState(stackState);
	Node startNode(stackState, NULL,0,stackSize,numbBlk);
	AstarSearch search(stackSize,numbBlk);
	search.AstarSearchImp(&startNode);
	return 0;
}
