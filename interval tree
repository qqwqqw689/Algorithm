//interval tree
#include <iostream>
using namespace std;

//structure to represent an interval
struct Interval
{
    int low;  //low endpoint
    int high; //high endpoint
};

//structure to represent a node in interval search tree
struct ITNode
{
    Interval* i;                 //an interval
    int max;                     //the maximum value of any interval endpoint stored in the subtree rooted at x
    ITNode* left,* right;
};

//A utility function to create a new Interval Search Tree Node
ITNode* newNode(Interval i)
{
    ITNode* temp=new ITNode;
    temp->i=new Interval(i);
    temp->max=i.high;
    temp->left=temp->right=nullptr;
    return temp;
}

//A utility function to insert a  new Interval Search Tree Node
//This is similar to BST Insert.Here the low value of interval
//is used to maintain BST property
ITNode* insert(ITNode* root,Interval i)
{
    //Base case :Tree is empty,new node become root
    if (root==nullptr)
        return newNode(i);
    
    //get low value of interval at root
    int l=root->i->low;

    //If root's low value is larger,then new interval goes to
    //left subtree
    if (i.low<l)
        root->left=insert(root->left,i);

    //Else,new node goes to right subtree
    else
        root->right=insert(root->right,i);

    if(root->max<i.high)
        root->max=i.high;

    return root;
} 

//A utility function to check if given two intervals overlap
bool doOVerlap(Interval i1,Interval i2)
{
    if(i1.low<=i2.high&&i2.low<=i1.high)
        return true;
    return false;
}

//The main function that searches a given interval i in a given
//Interval tree
Interval* overlapsearch(ITNode* root,Interval i)
{
    //Base Case,tree is empty
    if(root==nullptr) return nullptr;

    //If given interval overlaps with root
    if(doOVerlap(*(root->i),i))
        return root->i;

    //If left child of root is present and max of left child is
    //greater than or equal to given interval,then i may
    //overlap with an interval in left tree
    if(root->left!=nullptr&&root->left->max>=i.low)
        return overlapsearch(root->left,i);

    //Else interval can only overlap with right subtree
    return overlapsearch(root->right,i);
}

void inorder(ITNode* root)
{
    if(root==nullptr) return;

    inorder(root->left);

    cout<<"["<<root->i->low<<","<<root->i->high<<"]"
        <<" max="<<root->max<<endl;

    inorder(root->right);
}

void devastate(ITNode* root)
{
    ITNode* temp_left=root->left;
    ITNode* temp_right=root->right;

    if(temp_left!=nullptr)
        devastate(temp_left);
    else
        return;

    if(temp_right!=nullptr)
        devastate(temp_right);
    else
        return;    

    delete root;
}
//Driver Program
int main()
{
    //Let us create interval tree
    Interval ints[]={{15,20},{10,30},{17,19},{5,20},{12,15},{30,40}};
    int n=sizeof(ints)/sizeof(ints[0]);
    ITNode* root=nullptr;
    for(int i=0;i<n;i++)
        root=insert(root,ints[i]);

    cout<<"Inorder traversal of constructed Interval Tree is\n";
    inorder(root);

    Interval x={6,7};

    cout<<"\nSearching for interval ["<<x.low<<","<<x.high<<"]";
    Interval* res=overlapsearch(root,x);
    if(res==nullptr)
        cout<<"\nNo Overlapping Interval";
    else
        cout<<"\nOverlapping with ["<<res->low<<","<<res->high<<"]";

    devastate(root);

    return 0;
}
