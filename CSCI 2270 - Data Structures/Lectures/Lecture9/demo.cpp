Lecture 9 02-04-2019

Next Tuesday Internship Fair 10 AM to 3 PM
 - Come prepare
 - Resume
 - Questions
    - Work
    - What kind of people do you look for
 - Career Service (C4C)
 @ Idea forge


 Singly linked list implementation
  - insert
  - delete

insert
 - Find a node containing a given key (afterMe)
 - insert node containing new value (newValue) directly after.

void SLL :: insert (string afterMe, string newItem)
{
  search(afterMe);
  1. afterMe is empty string
   - make new node be the new head
  2. afterMe not found
   - display error message
  3. afterMe is tail
   - append (can call append fucntion)
  4. afterMe is in the middle
   - create new node
   - write newValue to key of the new node
   - re-link nodes to preserve proper linked list

   if(afterMe == "")
   {
     Node *temp = new Node;
     temp -> key = newValue;
     temp -> next = head;
     head = temp;
     temp = nullptr;
   }
   else
   {
     Node *last = search(afterMe);
     if (last == nullptr)
     {
       cout << "node not found, new node not inserted" << endl;
     }
     else if (last -> next == nullptr)
     {
       appendNode(newValue);
     }
     else // last is either head or somewhere in the middle (not tall)
     {
       Node *temp = new Node;
       temp -> key = newValue;
       temp -> next = last -> next;
       last -> next = temp;
       temp = nullptr;

     }

   }
}

delete Node
void SLL :: deleteNode(string sKey)
{
  3 cases
   - sKey found in head
    - make head.next = head
    - delete node
   - sKey found in tail
    - Keep track of last node while searching
    - use last node to set new tail
    - delete node
   - sKey found in middle
    - keep track of last node
    - use last node relink with temp.next
}
